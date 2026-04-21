// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "doorlock_sniper/msg/detail/video_packet__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace doorlock_sniper
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void VideoPacket_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) doorlock_sniper::msg::VideoPacket(_init);
}

void VideoPacket_fini_function(void * message_memory)
{
  auto typed_message = static_cast<doorlock_sniper::msg::VideoPacket *>(message_memory);
  typed_message->~VideoPacket();
}

size_t size_function__VideoPacket__data(const void * untyped_member)
{
  (void)untyped_member;
  return 150;
}

const void * get_const_function__VideoPacket__data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 150> *>(untyped_member);
  return &member[index];
}

void * get_function__VideoPacket__data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 150> *>(untyped_member);
  return &member[index];
}

void fetch_function__VideoPacket__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__VideoPacket__data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__VideoPacket__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__VideoPacket__data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember VideoPacket_message_member_array[3] = {
  {
    "sequence_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(doorlock_sniper::msg::VideoPacket, sequence_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "timestamp_ns",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(doorlock_sniper::msg::VideoPacket, timestamp_ns),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    150,  // array size
    false,  // is upper bound
    offsetof(doorlock_sniper::msg::VideoPacket, data),  // bytes offset in struct
    nullptr,  // default value
    size_function__VideoPacket__data,  // size() function pointer
    get_const_function__VideoPacket__data,  // get_const(index) function pointer
    get_function__VideoPacket__data,  // get(index) function pointer
    fetch_function__VideoPacket__data,  // fetch(index, &value) function pointer
    assign_function__VideoPacket__data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers VideoPacket_message_members = {
  "doorlock_sniper::msg",  // message namespace
  "VideoPacket",  // message name
  3,  // number of fields
  sizeof(doorlock_sniper::msg::VideoPacket),
  VideoPacket_message_member_array,  // message members
  VideoPacket_init_function,  // function to initialize message memory (memory has to be allocated)
  VideoPacket_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t VideoPacket_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &VideoPacket_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace doorlock_sniper


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<doorlock_sniper::msg::VideoPacket>()
{
  return &::doorlock_sniper::msg::rosidl_typesupport_introspection_cpp::VideoPacket_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, doorlock_sniper, msg, VideoPacket)() {
  return &::doorlock_sniper::msg::rosidl_typesupport_introspection_cpp::VideoPacket_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
