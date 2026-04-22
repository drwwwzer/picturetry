#!/usr/bin/env python3
import socket
import struct
import time

UDP_IP = "127.0.0.1"
UDP_PORT = 3334
PACKET_SIZE = 150
HEADER_SIZE = 12
SEQ_START = 0

def send_h264_file(filename):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    with open(filename, "rb") as f:
        data = f.read()
    
    seq = SEQ_START
    timestamp_ns = int(time.time() * 1e9)  # 模拟纳秒时间戳
    
    print(f"Loaded {len(data)} bytes from {filename}")
    offset = 0
    while offset < len(data):
        chunk = data[offset:offset+PACKET_SIZE]
        if not chunk:
            break
        
        # 如果最后一块不足150字节，用零填充（解码器会忽略填充）
        if len(chunk) < PACKET_SIZE:
            chunk = chunk.ljust(PACKET_SIZE, b'\x00')
        
        # 构造包头：sequence_id (uint32) + timestamp_ns (uint64) ，小端序
        header = struct.pack('<IQ', seq, timestamp_ns)
        packet = header + chunk
        
        sock.sendto(packet, (UDP_IP, UDP_PORT))
        print(f"Sent seq={seq}, offset={offset}, len={len(chunk)}")
        
        seq += 1
        offset += PACKET_SIZE
        time.sleep(0.001)  # 避免发送过快淹没接收缓冲区
    
    print("File sending completed.")
    sock.close()

if __name__ == "__main__":
    send_h264_file("test_stream.h264")