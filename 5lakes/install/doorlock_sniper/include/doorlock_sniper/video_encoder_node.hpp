#ifndef DOORLOCK_SNIPER_VIDEO_ENCODER_NODE_HPP_
#define DOORLOCK_SNIPER_VIDEO_ENCODER_NODE_HPP_

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <gst/app/gstappsrc.h>
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <deque>

#include "doorlock_sniper/msg/video_packet.hpp"

namespace doorlock_sniper
{

class VideoEncoderNode : public rclcpp::Node
{
public:
  explicit VideoEncoderNode(const rclcpp::NodeOptions & options);
  ~VideoEncoderNode() override;

private:
  void initialize_gstreamer();
  void shutdown_gstreamer();
  
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
  cv::Mat preprocess_image(const cv::Mat & input);
  
  void push_frame_to_gstreamer(const cv::Mat & frame);
  void pull_stream_and_packetize();
  
  void display_loop();

  GstElement * pipeline_;
  GstElement * appsrc_;
  GstElement * appsink_;
  GstBus * bus_;
  bool gst_ready_ = false;
  bool gst_warned_not_ready_ = false;
  std::string active_encoder_name_ = "none";
  
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
  rclcpp::Publisher<doorlock_sniper::msg::VideoPacket>::SharedPtr packet_pub_;
  
  // 统计与状态（调整顺序，与初始化列表一致）
  uint64_t packet_sequence_id_ = 0;   // 移到这里，先声明
  uint32_t frame_count_ = 0;
  
  // 显示线程
  std::thread display_thread_;
  std::atomic<bool> display_running_;  // 后声明
  
  std::mutex frame_mutex_;
  cv::Mat display_frame_;
  
  // 流式分包缓冲区
  std::vector<uint8_t> stream_buffer_;
  std::deque<std::pair<int64_t, size_t>> sent_window_;
  size_t sent_window_bytes_ = 0;
  uint64_t dropped_bytes_ = 0;
  uint32_t dropped_events_ = 0;
  int64_t last_telemetry_ns_ = 0;
  std::mutex buffer_mutex_;

  // 帧率控制
  int64_t last_encode_stamp_ns_ = 0;
  uint64_t display_frame_counter_ = 0;
  
  // 参数
  int param_crop_size_ = 800;
  int param_output_size_ = 400;
  int param_output_fps_ = 60;
  int param_target_bitrate_ = 40;
  int param_packet_size_ = 150;
  bool param_force_monochrome_ = false;
  double param_bandwidth_limit_kbytes_ = 7.0;
  double param_bandwidth_window_s_ = 2.0;
  double param_max_tx_delay_s_ = 1.0;
  bool param_enable_display_ = true;
  bool param_debug_dump_enable_ = false;
  int param_debug_dump_every_n_frames_ = 20;
  bool param_debug_dump_save_final_ = true;
  std::string param_input_topic_;
  std::string param_x264_preset_ = "auto";
  std::string param_debug_dump_dir_ = "sniper_debug_imgs";
};

} // namespace doorlock_sniper

#endif
