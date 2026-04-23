#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <QThread>
#include <QImage>
#include <QMutex>
#include <list>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
}

class VideoDecoder : public QThread {
    Q_OBJECT
public:
    explicit VideoDecoder(AVCodecID codecId = AV_CODEC_ID_H264, QObject *parent = nullptr);//AV_CODEC_ID_HEVC
    ~VideoDecoder();

    // 接收子线程安全的调用
    void pushData(const QByteArray &data);
    void stop();
    void resetDecoder();   // 🆕 添加这一行
signals:
    void frameReady(const QImage &image);

protected:
    void run() override;

private:
    void processBuffer();
    // void processData(const uint8_t *data, int size);
    void receiveFrames(); 
    // void applyExtradata();

    // FFmpeg structures
    const AVCodec *m_codec = nullptr;
    AVCodecContext *m_codecCtx = nullptr;
    //  AVCodecParserContext *m_parser = nullptr;
    AVFrame *m_frame = nullptr;
    // AVFrame *m_rgbFrame = nullptr;
    AVPacket *m_packet = nullptr;
    SwsContext *m_swsCtx = nullptr;

    int m_width = 0;
    int m_height = 0;
    int m_pixFmt = -1; // 保存 AVPixelFormat
    int m_receivedPackets = 0;
    int m_decodeErrors = 0;    // ← 必须存在
    int m_decodedFrames = 0;
    bool m_needFlush = false;

    bool m_running = true;
    QMutex m_mutex;
    QByteArray m_streamBuffer; 
    // QByteArray m_extradata;  // 存储 SPS + PPS
    // bool m_extradataReady = false;
    
    // bool m_extradataApplied = false;  // 🆕 记录是否已应用 extradata
    std::list<QByteArray> m_queue;
};

#endif // VIDEODECODER_H
