// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#ifndef DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__TRAITS_HPP_
#define DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "doorlock_sniper/msg/detail/video_packet__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace doorlock_sniper
{

namespace msg
{

inline void to_flow_style_yaml(
  const VideoPacket & msg,
  std::ostream & out)
{
  out << "{";
  // member: sequence_id
  {
    out << "sequence_id: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence_id, out);
    out << ", ";
  }

  // member: timestamp_ns
  {
    out << "timestamp_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_ns, out);
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VideoPacket & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: sequence_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sequence_id: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence_id, out);
    out << "\n";
  }

  // member: timestamp_ns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_ns, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VideoPacket & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace doorlock_sniper

namespace rosidl_generator_traits
{

[[deprecated("use doorlock_sniper::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const doorlock_sniper::msg::VideoPacket & msg,
  std::ostream & out, size_t indentation = 0)
{
  doorlock_sniper::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use doorlock_sniper::msg::to_yaml() instead")]]
inline std::string to_yaml(const doorlock_sniper::msg::VideoPacket & msg)
{
  return doorlock_sniper::msg::to_yaml(msg);
}

template<>
inline const char * data_type<doorlock_sniper::msg::VideoPacket>()
{
  return "doorlock_sniper::msg::VideoPacket";
}

template<>
inline const char * name<doorlock_sniper::msg::VideoPacket>()
{
  return "doorlock_sniper/msg/VideoPacket";
}

template<>
struct has_fixed_size<doorlock_sniper::msg::VideoPacket>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<doorlock_sniper::msg::VideoPacket>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<doorlock_sniper::msg::VideoPacket>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__TRAITS_HPP_
