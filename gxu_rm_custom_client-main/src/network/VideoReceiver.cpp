#include "VideoReceiver.h"
#include <QDebug>
#include <QNetworkDatagram>
#include <QtEndian>
#include <QDateTime>
#include <QTimer>

VideoReceiver::VideoReceiver(quint16 port, QObject *parent)
    : QObject(parent), m_udpSocket(new QUdpSocket(this))
{
    // 强制增加 Socket 的接收缓冲区（8MB），极其关键：防止大码率视频下底层 UDP 疯狂丢包酿成花屏。
    m_udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 8 * 1024 * 1024);

    if (m_udpSocket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        m_udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 8 * 1024 * 1024); // 再次设保靠谱
        qDebug() << "VideoReceiver UDP socket bound to port" << port << "Buffer size up to 8MB";
        connect(m_udpSocket, &QUdpSocket::readyRead, this, &VideoReceiver::readPendingDatagrams);
        
        // // 高频清理过期不完整的帧防止拥堵
        // QTimer *timer = new QTimer(this);
        // connect(timer, &QTimer::timeout, this, &VideoReceiver::cleanOldFrames);
        // timer->start(10); // 改为10ms高频检查，不给破损帧长达一秒的拥塞机会
    } else {
        qWarning() << "Failed to bind UDP port" << port;
    }
    
    
}

VideoReceiver::~VideoReceiver() {
    m_udpSocket->close();
}

// void VideoReceiver::cleanOldFrames() {
//     qint64 now = QDateTime::currentMSecsSinceEpoch();
//     auto it = m_frames.begin();
//     while (it != m_frames.end()) {
//         if (now - it.value().timestamp > 150) { 
//             // 彻底去除发射“错误拼团、缺损头尾”等残次帧的魔改逻辑，
//             // 所有丢包产生的问题交由后方强大的 ffmpeg av_parser 分析补救或自然跨过。
//             it = m_frames.erase(it);
//         } else {
//             ++it;
//         }
//     }
// }

// VideoReceiver.cpp 修改后的关键部分
void VideoReceiver::readPendingDatagrams()
{
    // 1. 定义新协议常量 (与 Pacific_doorlock_sniper 编码端一致)
    const int HEADER_SIZE = 12;          // 4字节 seq + 8字节 ts
    const int PAYLOAD_SIZE = 150;        // 或 300，取决于编码端配置
    const int TOTAL_PACKET_SIZE = HEADER_SIZE + PAYLOAD_SIZE;

    static uint32_t lastSeq = 0;
    static bool firstPacket = true;

    while (m_udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
        QByteArray data = datagram.data();
                // 🆕 添加日志，打印实际收到的包大小
        static int logCount = 0;
        if (++logCount <= 5) {
            qDebug() << "📏 Received datagram size:" << data.size() << "(expected:" << TOTAL_PACKET_SIZE << ")";
        }

        // 2. 严格校验包大小
        if (data.size() != TOTAL_PACKET_SIZE) {
            continue;
        }

        // 3. 解析 VideoPacket 头 (小端序)
        const uint8_t *ptr = reinterpret_cast<const uint8_t*>(data.constData());
        uint32_t seq = *reinterpret_cast<const uint32_t*>(ptr);
        // uint64_t timestamp = *reinterpret_cast<const uint64_t*>(ptr + 4); // 暂不使用

        // 4. 丢包检测，并触发解码器重置
        if (!firstPacket && seq != lastSeq + 1) {
            qDebug() << "Packet loss detected:" << lastSeq << "->" << seq;
            emit packetLossDetected();
        }
        lastSeq = seq;
        firstPacket = false;

        // 5. 提取 H.264 载荷，直接发送 (每个包已是完整片段)
        QByteArray payload = data.mid(HEADER_SIZE, PAYLOAD_SIZE);
        emit dataReceived(payload);
    }
}