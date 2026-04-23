#!/usr/bin/env python3
import paho.mqtt.client as mqtt
import time
from pathlib import Path

# MQTT 配置
BROKER_IP = "127.0.0.1"
BROKER_PORT = 3333
TOPIC = "CustomByteBlock"

# 视频文件
H264_FILE = "test_stream_clean.h264"
PACKET_SIZE = 150

def encode_custom_byte_block(data: bytes) -> bytes:
    """
    手动编码 CustomByteBlock Protobuf 消息
    message CustomByteBlock {
        bytes data = 1;
    }
    编码格式：字段标签 (1 << 3 | 2) = 0x0a，后跟 VarInt 长度，再跟数据
    """
    # 计算 VarInt 长度
    length = len(data)
    varint = b""
    while length > 0x7f:
        varint += bytes([(length & 0x7f) | 0x80])
        length >>= 7
    varint += bytes([length & 0x7f])
    
    return b'\x0a' + varint + data

def publish_custom_stream():
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.connect(BROKER_IP, BROKER_PORT, 60)
    client.loop_start()
    
    data = Path(H264_FILE).read_bytes()
    print(f"Loaded {len(data)} bytes from {H264_FILE}")
    
    seq = 0
    offset = 0
    while offset < len(data):
        chunk = data[offset:offset+PACKET_SIZE]
        if not chunk:
            break
        if len(chunk) < PACKET_SIZE:
            chunk = chunk.ljust(PACKET_SIZE, b'\x00')
        
        # 手动编码 Protobuf
        payload = encode_custom_byte_block(chunk)
        client.publish(TOPIC, payload)
        print(f"Sent MQTT packet {seq}, chunk size {len(chunk)}, payload size {len(payload)}")
        
        seq += 1
        offset += PACKET_SIZE
        time.sleep(0.001)
    
    print("MQTT sending completed.")
    client.loop_stop()
    client.disconnect()

if __name__ == "__main__":
    while True:
        publish_custom_stream()
        time.sleep(1)