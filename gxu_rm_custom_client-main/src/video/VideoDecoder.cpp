#include "VideoDecoder.h"
#include <QDebug>

VideoDecoder::VideoDecoder(AVCodecID codecId, QObject *parent) : QThread(parent) {//AV_CODEC_ID_H264
    // 屏蔽FFmpeg过于多余的内部报错（如刚启动时必须等待I帧导致的 PPS 丢失错误）
    // 把日志级别调至 FATAL（或者 QUIET），彻底告别刷屏
    av_log_set_level(AV_LOG_FATAL);

    // 强制声明 H.265 (HEVC) 解码器
    m_codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!m_codec) {
        qCritical() << "H.265/HEVC codec not found!";
        return;
    }

    m_codecCtx = avcodec_alloc_context3(m_codec);
    
    // 关键修正：开启 H.265 最强容错隐蔽和极低延迟解码功能
    m_codecCtx->flags |= AV_CODEC_FLAG_LOW_DELAY;
    m_codecCtx->flags2 |= AV_CODEC_FLAG2_FAST;
    // m_codecCtx->error_concealment = 3; // FF_EC_GUESS_MVS | FF_EC_DEBLOCK，丢包就自动猜图遮掩，不报花屏错
    m_codecCtx->thread_count = 2;      // 小开一下多线程加速解码吞吐

    if (avcodec_open2(m_codecCtx, m_codec, nullptr) < 0) {
        qCritical() << "Could not open H.265/HEVC codec!";
        return;
    }

    m_parser = av_parser_init(m_codec->id);
    if (!m_parser) {
        qCritical() << "Could not initialize HEVC parser!";
    }

    m_packet = av_packet_alloc();
    m_frame = av_frame_alloc();
    m_rgbFrame = av_frame_alloc();
}

VideoDecoder::~VideoDecoder() {
    stop();
    wait();

    if (m_swsCtx) sws_freeContext(m_swsCtx);
    if (m_parser) {
        av_parser_close(m_parser);
    }
    if (m_frame) av_frame_free(&m_frame);
    if (m_rgbFrame) av_frame_free(&m_rgbFrame);
    if (m_packet) av_packet_free(&m_packet);
    if (m_codecCtx) {
        avcodec_close(m_codecCtx);
        avcodec_free_context(&m_codecCtx);
    }
}

void VideoDecoder::pushData(const QByteArray &data) {
    
    if (data.isEmpty()) return;
        if (data.isEmpty()) return;
    
    static int count = 0;
    if (++count % 50 == 0) {
        qDebug() << "📦 VideoDecoder::pushData, size:" << data.size() << "queue size:" << m_queue.size();
    }
    QMutexLocker locker(&m_mutex);
    // 限定队列长度防止内存泄漏
    if (m_queue.size() > 100) {
        // 放宽队列到 100 帧（大约 3 秒以上缓冲），如果还是超出则只能丢弃最老的帧
        // 这在极端弱网/主板卡顿下才触发丢弃
        m_queue.pop_front();
    }
    m_queue.push_back(data);
}

void VideoDecoder::stop() {
    m_running = false;
}

void VideoDecoder::run()
{
    qDebug() << "🚀 VideoDecoder thread started";
    while (m_running) {
        // ... 处理刷新请求 ...

        QByteArray data;
        {
            QMutexLocker locker(&m_mutex);
            if (!m_queue.empty()) {
                data = m_queue.front();
                m_queue.pop_front();
            }
        }

        if (!data.isEmpty()) {
            QMutexLocker locker(&m_mutex); // 保护 m_streamBuffer
            m_streamBuffer.append(data);
        }

        // 只要缓冲区有足够数据，就尝试解析
        if (m_streamBuffer.size() > 0) {
            processBuffer();
        } else {
            QThread::msleep(2);
        }
    }
}

void VideoDecoder::receiveFrames()
{
    // 循环从解码器接收所有可用的帧
    while (true) {
        int ret = avcodec_receive_frame(m_codecCtx, m_frame);
        if (ret == 0) {
            // ✅ 解码成功，处理帧
            static int frameCount = 0;
            if (++frameCount % 30 == 0) {
                qDebug() << "✅ Decoded frame" << frameCount
                         << "size:" << m_frame->width << "x" << m_frame->height;
            }

            int w = m_frame->width;
            int h = m_frame->height;

            // 有效性检查
            if (w <= 0 || h <= 0 || !m_frame->data[0]) {
                av_frame_unref(m_frame);
                continue;
            }

            // 检查是否需要重新初始化图像转换器（分辨率或像素格式变化）
            if (m_width != w || m_height != h || m_pixFmt != m_frame->format || !m_swsCtx) {
                m_width = w;
                m_height = h;
                m_pixFmt = m_frame->format;
                if (m_swsCtx) sws_freeContext(m_swsCtx);
                m_swsCtx = sws_getContext(w, h, (AVPixelFormat)m_frame->format,
                                          w, h, AV_PIX_FMT_RGB32,
                                          SWS_BILINEAR, nullptr, nullptr, nullptr);
            }

            if (!m_swsCtx) {
                av_frame_unref(m_frame);
                continue;
            }

            // 创建 QImage 用于存放 RGB 数据
            QImage image(w, h, QImage::Format_RGB32);
            uint8_t *dest[4] = { image.bits(), nullptr, nullptr, nullptr };
            int dest_linesize[4] = { static_cast<int>(image.bytesPerLine()), 0, 0, 0 };

            // 执行像素格式转换（YUV → RGB32）
            int ret_scale = sws_scale(m_swsCtx,
                                      m_frame->data, m_frame->linesize,
                                      0, h,
                                      dest, dest_linesize);

            // 释放 FFmpeg 帧引用，以便复用
            av_frame_unref(m_frame);

            if (ret_scale > 0) {
                m_decodedFrames++;
                // 深拷贝后发送到主线程（UI 线程）
                emit frameReady(image.copy());
            }
        } else {
            // 解码失败或需要更多数据
            // EAGAIN 表示需要更多输入数据，EOF 表示流结束，正常退出循环
            if (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
                qWarning() << "❌ avcodec_receive_frame error:" << ret;
                m_decodeErrors++;   // 记录解码错误
            }
            break;  // 无论哪种非成功情况，都退出循环等待下一次数据
        }
    }
}
// void VideoDecoder::processData(const uint8_t *data, int size)
// {
//     if (size <= 0 || !m_codecCtx) return;

//         // 🆕 打印原始数据前 8 字节（十六进制）
//     static int hexCount = 0;
//     if (++hexCount <= 5) {  // 仅打印前 5 次，避免刷屏
//         QString hex;
//         for (int i = 0; i < std::min(size, 8); ++i) {
//             hex += QString("%1 ").arg(data[i], 2, 16, QChar('0'));
//         }
//         qDebug() << "🔬 processData first 8 bytes:" << hex;
//     }

//     // 直接送入 parser（parser 会自动处理跨包边界的情况）
//     uint8_t *data_ptr = const_cast<uint8_t*>(data);
//     int data_size = size;

//     while (data_size > 0) {
//         int parsed_len = av_parser_parse2(m_parser, m_codecCtx,
//                                           &m_packet->data, &m_packet->size,
//                                           data_ptr, data_size,
//                                           AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
//                                                   // 🆕 打印解析结果
//         static int parseCount = 0;
//         if (++parseCount % 100 == 0) {
//             qDebug() << "📊 av_parser_parse2 returned:" << parsed_len
//                      << "packet size:" << m_packet->size
//                      << "consumed:" << data_size << "->" << (data_size - parsed_len);
//         }

//         if (parsed_len < 0) {
//             m_decodeErrors++;
//             qWarning() << "❌ av_parser_parse2 error:" << parsed_len;
//             break;
//         }
//         data_ptr += parsed_len;
//         data_size -= parsed_len;

//         if (m_packet->size > 0) {
//             static int pktCount = 0;
//         if (++pktCount % 50 == 0) {
//             qDebug() << "📦 Parser produced packet, size:" << m_packet->size;
//         }


//             int ret = avcodec_send_packet(m_codecCtx, m_packet);
//             if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
//                 m_decodeErrors++;
//             }
//             // 接收解码帧（与原有逻辑相同）
//              receiveFrames();
//         }
//     }
// }
void VideoDecoder::processBuffer()
{
    if (!m_parser || !m_codecCtx) return;

    QMutexLocker locker(&m_mutex);  // 🆕 加锁保护 m_streamBuffer
    const uint8_t *data_ptr = reinterpret_cast<const uint8_t*>(m_streamBuffer.constData());
    int data_size = m_streamBuffer.size();

    while (data_size > 0) {
        int parsed_len = av_parser_parse2(m_parser, m_codecCtx,
                                          &m_packet->data, &m_packet->size,
                                          data_ptr, data_size,
                                          AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);

        if (parsed_len < 0) {
            m_decodeErrors++;
            qWarning() << "❌ av_parser_parse2 error:" << parsed_len;
            break;
        }

        // 移除已解析的数据
        if (parsed_len > 0) {
            m_streamBuffer.remove(0, parsed_len);
            data_ptr = reinterpret_cast<const uint8_t*>(m_streamBuffer.constData());
            data_size = m_streamBuffer.size();
        } else {
            // 解析器需要更多数据，保留缓冲区内容，退出循环
            break;
        }

        if (m_packet->size > 0) {
            // 🆕 添加 packet 产出日志
            static int pktCount = 0;
            if (++pktCount % 50 == 0) {
                qDebug() << "📦 Parser produced packet, size:" << m_packet->size;
            }

            int ret = avcodec_send_packet(m_codecCtx, m_packet);
            if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
                m_decodeErrors++;
            }
            av_packet_unref(m_packet);
            // 注意：receiveFrames 可能发射信号，临时解锁避免死锁
            locker.unlock();
            receiveFrames();
            locker.relock();
        }
    }
}