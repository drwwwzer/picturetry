// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "doorlock_sniper/msg/detail/video_packet__rosidl_typesupport_introspection_c.h"
#include "doorlock_sniper/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "doorlock_sniper/msg/detail/video_packet__functions.h"
#include "doorlock_sniper/msg/detail/video_packet__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  doorlock_sniper__msg__VideoPacket__init(message_memory);
}

void doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_fini_function(void * message_memory)
{
  doorlock_sniper__msg__VideoPacket__fini(message_memory);
}

size_t doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__size_function__VideoPacket__data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 150;
}

const void * doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__get_const_function__VideoPacket__data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__get_function__VideoPacket__data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__fetch_function__VideoPacket__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__get_const_function__VideoPacket__data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__assign_function__VideoPacket__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__get_function__VideoPacket__data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_member_array[3] = {
  {
    "sequence_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(doorlock_sniper__msg__VideoPacket, sequence_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timestamp_ns",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(doorlock_sniper__msg__VideoPacket, timestamp_ns),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    150,  // array size
    false,  // is upper bound
    offsetof(doorlock_sniper__msg__VideoPacket, data),  // bytes offset in struct
    NULL,  // default value
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__size_function__VideoPacket__data,  // size() function pointer
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__get_const_function__VideoPacket__data,  // get_const(index) function pointer
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__get_function__VideoPacket__data,  // get(index) function pointer
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__fetch_function__VideoPacket__data,  // fetch(index, &value) function pointer
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__assign_function__VideoPacket__data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_members = {
  "doorlock_sniper__msg",  // message namespace
  "VideoPacket",  // message name
  3,  // number of fields
  sizeof(doorlock_sniper__msg__VideoPacket),
  doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_member_array,  // message members
  doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_init_function,  // function to initialize message memory (memory has to be allocated)
  doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_type_support_handle = {
  0,
  &doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_doorlock_sniper
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, doorlock_sniper, msg, VideoPacket)() {
  if (!doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_type_support_handle.typesupport_identifier) {
    doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &doorlock_sniper__msg__VideoPacket__rosidl_typesupport_introspection_c__VideoPacket_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
