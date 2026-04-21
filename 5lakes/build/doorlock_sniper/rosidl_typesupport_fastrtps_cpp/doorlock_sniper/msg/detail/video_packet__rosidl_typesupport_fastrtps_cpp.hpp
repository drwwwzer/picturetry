// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#ifndef DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "doorlock_sniper/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "doorlock_sniper/msg/detail/video_packet__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace doorlock_sniper
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_doorlock_sniper
cdr_serialize(
  const doorlock_sniper::msg::VideoPacket & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_doorlock_sniper
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  doorlock_sniper::msg::VideoPacket & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_doorlock_sniper
get_serialized_size(
  const doorlock_sniper::msg::VideoPacket & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_doorlock_sniper
max_serialized_size_VideoPacket(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace doorlock_sniper

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_doorlock_sniper
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, doorlock_sniper, msg, VideoPacket)();

#ifdef __cplusplus
}
#endif

#endif  // DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
