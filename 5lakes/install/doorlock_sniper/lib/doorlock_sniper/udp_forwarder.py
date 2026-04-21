#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from doorlock_sniper.msg import VideoPacket
import socket
import struct

class UDPForwarder(Node):
    def __init__(self):
        super().__init__('udp_forwarder')
        self.sub = self.create_subscription(
            VideoPacket,
            '/video_stream',
            self.callback,
            50
        )
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.target_addr = ('127.0.0.1', 3334)  # 与 gxu_rm_custom_client 监听端口一致
        self.get_logger().info('UDP Forwarder sending to 127.0.0.1:3334')

    def callback(self, msg):
        # 打包格式：sequence_id (uint32) + timestamp_ns (uint64) + data (uint8[300])
        header = struct.pack('<IQ', msg.sequence_id, msg.timestamp_ns)
        payload = bytes(msg.data)
        self.sock.sendto(header + payload, self.target_addr)
        

def main(args=None):
    rclpy.init(args=args)
    node = UDPForwarder()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()