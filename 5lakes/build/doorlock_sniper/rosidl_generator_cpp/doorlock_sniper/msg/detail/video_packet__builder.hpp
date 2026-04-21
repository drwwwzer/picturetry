// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#ifndef DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__BUILDER_HPP_
#define DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "doorlock_sniper/msg/detail/video_packet__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace doorlock_sniper
{

namespace msg
{

namespace builder
{

class Init_VideoPacket_data
{
public:
  explicit Init_VideoPacket_data(::doorlock_sniper::msg::VideoPacket & msg)
  : msg_(msg)
  {}
  ::doorlock_sniper::msg::VideoPacket data(::doorlock_sniper::msg::VideoPacket::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::doorlock_sniper::msg::VideoPacket msg_;
};

class Init_VideoPacket_timestamp_ns
{
public:
  explicit Init_VideoPacket_timestamp_ns(::doorlock_sniper::msg::VideoPacket & msg)
  : msg_(msg)
  {}
  Init_VideoPacket_data timestamp_ns(::doorlock_sniper::msg::VideoPacket::_timestamp_ns_type arg)
  {
    msg_.timestamp_ns = std::move(arg);
    return Init_VideoPacket_data(msg_);
  }

private:
  ::doorlock_sniper::msg::VideoPacket msg_;
};

class Init_VideoPacket_sequence_id
{
public:
  Init_VideoPacket_sequence_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VideoPacket_timestamp_ns sequence_id(::doorlock_sniper::msg::VideoPacket::_sequence_id_type arg)
  {
    msg_.sequence_id = std::move(arg);
    return Init_VideoPacket_timestamp_ns(msg_);
  }

private:
  ::doorlock_sniper::msg::VideoPacket msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::doorlock_sniper::msg::VideoPacket>()
{
  return doorlock_sniper::msg::builder::Init_VideoPacket_sequence_id();
}

}  // namespace doorlock_sniper

#endif  // DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__BUILDER_HPP_
