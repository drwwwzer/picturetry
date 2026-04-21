// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#ifndef DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__STRUCT_H_
#define DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VideoPacket in the package doorlock_sniper.
/**
  * 流式视频数据包 - 固定150字节
 */
typedef struct doorlock_sniper__msg__VideoPacket
{
  /// 全局包序号
  uint64_t sequence_id;
  /// ROS2 时间戳
  uint64_t timestamp_ns;
  /// 固定150字节负载（最后一包不足则补零）
  uint8_t data[150];
} doorlock_sniper__msg__VideoPacket;

// Struct for a sequence of doorlock_sniper__msg__VideoPacket.
typedef struct doorlock_sniper__msg__VideoPacket__Sequence
{
  doorlock_sniper__msg__VideoPacket * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} doorlock_sniper__msg__VideoPacket__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__STRUCT_H_
