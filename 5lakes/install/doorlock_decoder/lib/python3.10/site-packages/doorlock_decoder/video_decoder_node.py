import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
from doorlock_sniper.msg import VideoPacket
import av
import cv2
import threading
import queue
from pathlib import Path


class VideoDecoderNode(Node):
    def __init__(self):
        super().__init__('video_decoder_node')
        
        # 参数
        self.declare_parameter('topic', '/video_stream')
        self.declare_parameter('display', True)
        self.declare_parameter('width', 400)
        self.declare_parameter('height', 400)
        self.declare_parameter('display_scale', 2)
        self.declare_parameter('debug_dump_enable', False)
        self.declare_parameter('debug_dump_every_n_frames', 20)
        self.declare_parameter('debug_dump_save_decoder', True)
        self.declare_parameter('debug_dump_dir', 'sniper_debug_imgs')
        
        topic = self.get_parameter('topic').value
        self.display = self.get_parameter('display').value
        self.width = int(self.get_parameter('width').value)
        self.height = int(self.get_parameter('height').value)
        self.display_scale = max(1, int(self.get_parameter('display_scale').value))
        self.display_width = self.width * self.display_scale
        self.display_height = self.height * self.display_scale
        self.debug_dump_enable = bool(self.get_parameter('debug_dump_enable').value)
        self.debug_dump_every_n_frames = max(1, int(self.get_parameter('debug_dump_every_n_frames').value))
        self.debug_dump_save_decoder = bool(self.get_parameter('debug_dump_save_decoder').value)
        self.debug_dump_dir = Path(str(self.get_parameter('debug_dump_dir').value)) / 'decoder'
        self.display_frame_counter = 0
        if self.debug_dump_enable and self.debug_dump_save_decoder:
            self.debug_dump_dir.mkdir(parents=True, exist_ok=True)
            self.get_logger().info(
                f'Debug dump enabled: every {self.debug_dump_every_n_frames} frames -> {self.debug_dump_dir}'
            )
        elif self.debug_dump_enable:
            self.get_logger().warn('debug_dump_enable=true but debug_dump_save_decoder=false')

        # 流式解码器状态
        self.codec = None
        self._reset_decoder(log=False, reason='startup')
        self.frame_count = 0
        self.packet_count = 0
        self.parsed_packet_count = 0
        self.gap_count = 0
        self.last_seq = None
        
        # 显示队列
        if self.display:
            self.frame_queue = queue.Queue(maxsize=1)
            self.display_thread = threading.Thread(target=self._display_loop, daemon=True)
            self.display_thread.start()
        
        # QoS
        qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            history=HistoryPolicy.KEEP_LAST,
            depth=50
        )
        
        self.subscription = self.create_subscription(
            VideoPacket,
            topic,
            self._packet_callback,
            qos
        )
        
        self.get_logger().info(f'Decoder started: subscribing to {topic}')

    def _reset_decoder(self, *, log: bool = True, reason: str = ''):
        self.codec = av.CodecContext.create('h264', 'r')
        self.codec.thread_type = 'SLICE'
        self.codec.thread_count = 1
        self.codec.flags |= av.codec.context.Flags.LOW_DELAY
        if log:
            self.get_logger().warn(f'Reset decoder ({reason})')

    def _handle_decoded_frame(self, frame):
        if frame is None or frame.width == 0 or frame.height == 0:
            return

        img = frame.to_ndarray(format='bgr24')
        if img is None or img.size == 0:
            return

        self.frame_count += 1
        if self.display:
            try:
                self.frame_queue.put_nowait(img)
            except queue.Full:
                try:
                    _ = self.frame_queue.get_nowait()  # 丢弃旧帧，优先显示最新帧
                except queue.Empty:
                    pass
                try:
                    self.frame_queue.put_nowait(img)
                except queue.Full:
                    pass
        elif self.frame_count % 60 == 0:
            self.get_logger().info(f'Decoded {self.frame_count} frames')
        
    def _packet_callback(self, msg):
        """接收 150byte 分片，先 parse，再 decode。"""
        self.packet_count += 1

        # 丢包检测
        if self.last_seq is not None and msg.sequence_id != self.last_seq + 1:
            self.gap_count += 1
            self.get_logger().warn(
                f'Gap detected: {self.last_seq} -> {msg.sequence_id}, reset decoder')
            # 任意 150B 分片丢失都会破坏码流同步，直接重置等待下一组 SPS/PPS + IDR
            self._reset_decoder(reason='sequence gap')
        self.last_seq = msg.sequence_id

        chunk = bytes(msg.data)

        try:
            parsed_packets = self.codec.parse(chunk)
            self.parsed_packet_count += len(parsed_packets)
            for packet in parsed_packets:
                for frame in self.codec.decode(packet):
                    self._handle_decoded_frame(frame)
        except av.AVError as e:
            self.get_logger().debug(f'Decode error: {e!s}')

        if self.packet_count % 600 == 0:
            self.get_logger().info(
                f'Rx packets={self.packet_count} parsed_h264={self.parsed_packet_count} '
                f'decoded_frames={self.frame_count} gaps={self.gap_count}')
    def apply_custom_effects(self, img):
        import numpy as np
        """对图像应用局部灰度 + 准心"""
        h, w = img.shape[:2]
        center_x, center_y = w // 2, h // 2
        radius = min(w, h) // 3   # 中心彩色区域半径

        # 1. 局部灰度：中心圆形区域保留原色，外部变为灰度
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        gray_bgr = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
        mask = np.zeros((h, w), dtype=np.uint8)
        cv2.circle(mask, (center_x, center_y), radius, 255, -1)
        mask_inv = cv2.bitwise_not(mask)
        # 保留彩色区域
        img_color = cv2.bitwise_and(img, img, mask=mask)
        # 外部区域灰度
        img_gray = cv2.bitwise_and(gray_bgr, gray_bgr, mask=mask_inv)
        result = cv2.add(img_color, img_gray)

        # 2. 绘制准心（十字线 + 中心点）
        cv2.line(result, (center_x - 20, center_y), (center_x + 20, center_y), (0, 255, 0), 2)
        cv2.line(result, (center_x, center_y - 20), (center_x, center_y + 20), (0, 255, 0), 2)
        cv2.circle(result, (center_x, center_y), 5, (0, 0, 255), -1)
        return result
    def _display_loop(self):
        """独立线程显示"""
        window_name = 'Doorlock Sniper'
        cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)
        cv2.resizeWindow(window_name, self.display_width, self.display_height)
        
        while rclpy.ok():
            try:
                img = self.frame_queue.get(timeout=0.005)

                if img is None:  # 退出信号
                    break
                if img.size > 0:  # 再次检查
                    img_disp = cv2.resize(
                        img,
                        (self.display_width, self.display_height),
                        interpolation=cv2.INTER_NEAREST
                    )
                    img_processed = self.apply_custom_effects(img_disp)
                    cv2.imshow(window_name, img_processed)
                    if self.debug_dump_enable and self.debug_dump_save_decoder:
                        self.display_frame_counter += 1
                        if self.display_frame_counter % self.debug_dump_every_n_frames == 0:
                            frame_id = f'{self.display_frame_counter:08d}'
                            out_path = self.debug_dump_dir / f'decoder_{frame_id}.png'
                            cv2.imwrite(str(out_path), img_disp)
                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        self.get_logger().info('User quit')
                        rclpy.shutdown()
                        break
            except queue.Empty:
                continue
            except Exception as e:
                self.get_logger().error(f'Display error: {e}')
                break
        
        cv2.destroyAllWindows()

    def destroy_node(self):
        if self.display:
            try:
                self.frame_queue.put_nowait(None)  # 退出信号
            except queue.Full:
                pass
            self.display_thread.join(timeout=1.0)
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = VideoDecoderNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
