#include "VideoDecoder.h"
#include <QDebug>
#include <libavutil/imgutils.h>
VideoDecoder::VideoDecoder(AVCodecID codecId, QObject *parent) : QThread(parent) {
    av_log_set_level(AV_LOG_INFO);
    m_codec = avcodec_find_decoder(codecId);
    if (!m_codec) { qCritical() << "Codec not found!"; return; }
    m_codecCtx = avcodec_alloc_context3(m_codec);
    m_codecCtx->flags |= AV_CODEC_FLAG_LOW_DELAY;
m_codecCtx->flags2 |= AV_CODEC_FLAG2_SHOW_ALL;   // 即使有错误也输出帧
m_codecCtx->error_concealment = FF_EC_GUESS_MVS | FF_EC_DEBLOCK; // 错误掩盖
m_codecCtx->thread_count = 1;
    if (avcodec_open2(m_codecCtx, m_codec, nullptr) < 0) { qCritical() << "Could not open codec!"; return; }
    m_packet = av_packet_alloc();
    m_frame = av_frame_alloc();
    // m_rgbFrame = av_frame_alloc();
    // m_extradataApplied = false;
}

VideoDecoder::~VideoDecoder() {
    stop(); wait();
    if (m_swsCtx) sws_freeContext(m_swsCtx);
    if (m_frame) av_frame_free(&m_frame);
    if (m_packet) av_packet_free(&m_packet);
    if (m_codecCtx) { avcodec_close(m_codecCtx); avcodec_free_context(&m_codecCtx); }
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
    if (m_queue.size() > 500) {
        // 放宽队列到 100 帧（大约 3 秒以上缓冲），如果还是超出则只能丢弃最老的帧
        // 这在极端弱网/主板卡顿下才触发丢弃
        m_queue.pop_front();
    }
    m_queue.push_back(data);
}

void VideoDecoder::stop() {
    m_running = false;
}

void VideoDecoder::resetDecoder() {
    QMutexLocker locker(&m_mutex);
    m_queue.clear();
    m_streamBuffer.clear();
    if (m_codecCtx) avcodec_flush_buffers(m_codecCtx);
    qDebug() << "🔄 Decoder flushed";
}
void VideoDecoder::run()
{
    qDebug() << "🚀 VideoDecoder thread started";
    while (m_running) {
        QByteArray data;
        {
            QMutexLocker locker(&m_mutex);
            if (!m_queue.empty()) {
                data = m_queue.front();
                m_queue.pop_front();
            }
        }
        if (!data.isEmpty()) {
            {
                QMutexLocker locker(&m_mutex);
                m_streamBuffer.append(data);
            }
            
                            // 只有当缓冲区至少达到一个起始码的最小长度时才尝试解析
                if (m_streamBuffer.size() >= 4) {
                    processBuffer();
                }
        } else {
            QThread::msleep(2);
        }
    }
}

void VideoDecoder::receiveFrames()
{
    static int receiveCallCount = 0;
if (++receiveCallCount % 100 == 0) {
    qDebug() << "receiveFrames called";
}
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
            // QImage image(w, h, QImage::Format_RGB32);
            // uint8_t *dest[4] = { image.bits(), nullptr, nullptr, nullptr };
            // int dest_linesize[4] = { static_cast<int>(image.bytesPerLine()), 0, 0, 0 };
            // 使用 FFmpeg 分配临时缓冲区，保证步长和大小完全符合要求
                        // 创建 QImage 直接作为目标缓冲区
            QImage image(w, h, QImage::Format_RGB32);
            uint8_t *dest[4] = { image.bits(), nullptr, nullptr, nullptr };
            int dest_linesize[4] = { w * 4, 0, 0, 0 };

            // 确保 SwsContext 使用安全标志，避免 SIMD 越界
            if (m_width != w || m_height != h || m_pixFmt != m_frame->format || !m_swsCtx) {
                m_width = w;
                m_height = h;
                m_pixFmt = m_frame->format;
                if (m_swsCtx) sws_freeContext(m_swsCtx);
                m_swsCtx = sws_getContext(w, h, (AVPixelFormat)m_frame->format,
                                          w, h, AV_PIX_FMT_RGB32,
                                          SWS_BILINEAR | SWS_ACCURATE_RND,
                                          nullptr, nullptr, nullptr);
            }

            if (!m_swsCtx) {
                av_frame_unref(m_frame);
                continue;
            }

            // 执行像素格式转换
            int ret_scale = sws_scale(m_swsCtx,
                                      m_frame->data, m_frame->linesize,
                                      0, h,
                                      dest, dest_linesize);

            av_frame_unref(m_frame);

            if (ret_scale > 0) {
                m_decodedFrames++;
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
// void VideoDecoder::applyExtradata() {
//     if (m_extradataReady && m_codecCtx && !m_extradata.isEmpty()) {
//         m_codecCtx->extradata = reinterpret_cast<uint8_t*>(m_extradata.data());
//         m_codecCtx->extradata_size = m_extradata.size();
//         // 重新打开解码器以应用 extradata（或使用 avcodec_parameters_from_context）
//         avcodec_close(m_codecCtx);
//         avcodec_open2(m_codecCtx, m_codec, nullptr);
//         m_extradataReady = false; // 仅需设置一次
//         qDebug() << "📌 Extradata applied, size:" << m_extradata.size();
//     }
// }
void VideoDecoder::processBuffer()
{
    if (!m_codecCtx) return;
    QMutexLocker locker(&m_mutex);

    const uint8_t *data_ptr = reinterpret_cast<const uint8_t*>(m_streamBuffer.constData());
    int data_size = m_streamBuffer.size();

    while (data_size >= 4) {
        // 1. 查找 Annex‑B 起始码 (00 00 00 01 或 00 00 01)
        int start_pos = -1;
        int start_code_len = 0;
        for (int i = 0; i < data_size - 3; ++i) {
            if (data_ptr[i] == 0 && data_ptr[i+1] == 0) {
                if (data_ptr[i+2] == 1) {
                    start_pos = i;
                    start_code_len = 3;
                    break;
                } else if (i+3 < data_size && data_ptr[i+2] == 0 && data_ptr[i+3] == 1) {
                    start_pos = i;
                    start_code_len = 4;
                    break;
                }
            }
        }
                if (start_pos == -1) {
            // 没有找到起始码，保留数据等待更多分片到达
            break;
        }

        // 2. 查找下一个起始码，确定当前 NALU 结束位置
        int end_pos = -1;
        for (int i = start_pos + start_code_len; i < data_size - 3; ++i) {
            if (data_ptr[i] == 0 && data_ptr[i+1] == 0) {
                if (data_ptr[i+2] == 1) {
                    end_pos = i;
                    break;
                } else if (i+3 < data_size && data_ptr[i+2] == 0 && data_ptr[i+3] == 1) {
                    end_pos = i;
                    break;
                }
            }
        }
        int nal_size = (end_pos == -1) ? (data_size - start_pos) : (end_pos - start_pos);
        const uint8_t *nal_data = data_ptr + start_pos;

        // 3. 获取 H.264 NAL 类型（低5位），并只发送 VCL NALU (1-5)
        if (nal_size > start_code_len) {
            uint8_t nal_type = nal_data[start_code_len] & 0x1F;
            static int dbgCount = 0;
            if (++dbgCount <= 20) {
                qDebug() << "🔍 H.264 NAL type:" << nal_type << " size:" << nal_size;
            }

                        // 发送 VCL NALU (1-5) 以及 SPS (7) 和 PPS (8)
            if ((nal_type >= 1 && nal_type <= 5) || nal_type == 7 || nal_type == 8) {
                AVPacket *pkt = av_packet_alloc();
                if (pkt) {
                    pkt->data = const_cast<uint8_t*>(nal_data);
                    pkt->size = nal_size;
                    int ret = avcodec_send_packet(m_codecCtx, pkt);
                    if (ret == 0) {
                        receiveFrames();
                    } else if (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
                        qWarning() << "❌ Send packet error:" << ret << "NAL type:" << nal_type;
                        m_decodeErrors++;
                    }
                    av_packet_free(&pkt);
                }
            }
        }

        // 4. 从缓冲区移除已处理的 NALU 及其之前的数据
        int remove_len = start_pos + nal_size;
        if (remove_len > 0 && remove_len <= m_streamBuffer.size()) {
            m_streamBuffer.remove(0, remove_len);
            data_ptr = reinterpret_cast<const uint8_t*>(m_streamBuffer.constData());
            data_size = m_streamBuffer.size();
        } else {
            break;
        }
    }
}