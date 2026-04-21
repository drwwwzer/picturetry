// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#ifndef DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__FUNCTIONS_H_
#define DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "doorlock_sniper/msg/rosidl_generator_c__visibility_control.h"

#include "doorlock_sniper/msg/detail/video_packet__struct.h"

/// Initialize msg/VideoPacket message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * doorlock_sniper__msg__VideoPacket
 * )) before or use
 * doorlock_sniper__msg__VideoPacket__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
bool
doorlock_sniper__msg__VideoPacket__init(doorlock_sniper__msg__VideoPacket * msg);

/// Finalize msg/VideoPacket message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
void
doorlock_sniper__msg__VideoPacket__fini(doorlock_sniper__msg__VideoPacket * msg);

/// Create msg/VideoPacket message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * doorlock_sniper__msg__VideoPacket__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
doorlock_sniper__msg__VideoPacket *
doorlock_sniper__msg__VideoPacket__create();

/// Destroy msg/VideoPacket message.
/**
 * It calls
 * doorlock_sniper__msg__VideoPacket__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
void
doorlock_sniper__msg__VideoPacket__destroy(doorlock_sniper__msg__VideoPacket * msg);

/// Check for msg/VideoPacket message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
bool
doorlock_sniper__msg__VideoPacket__are_equal(const doorlock_sniper__msg__VideoPacket * lhs, const doorlock_sniper__msg__VideoPacket * rhs);

/// Copy a msg/VideoPacket message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
bool
doorlock_sniper__msg__VideoPacket__copy(
  const doorlock_sniper__msg__VideoPacket * input,
  doorlock_sniper__msg__VideoPacket * output);

/// Initialize array of msg/VideoPacket messages.
/**
 * It allocates the memory for the number of elements and calls
 * doorlock_sniper__msg__VideoPacket__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
bool
doorlock_sniper__msg__VideoPacket__Sequence__init(doorlock_sniper__msg__VideoPacket__Sequence * array, size_t size);

/// Finalize array of msg/VideoPacket messages.
/**
 * It calls
 * doorlock_sniper__msg__VideoPacket__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
void
doorlock_sniper__msg__VideoPacket__Sequence__fini(doorlock_sniper__msg__VideoPacket__Sequence * array);

/// Create array of msg/VideoPacket messages.
/**
 * It allocates the memory for the array and calls
 * doorlock_sniper__msg__VideoPacket__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
doorlock_sniper__msg__VideoPacket__Sequence *
doorlock_sniper__msg__VideoPacket__Sequence__create(size_t size);

/// Destroy array of msg/VideoPacket messages.
/**
 * It calls
 * doorlock_sniper__msg__VideoPacket__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
void
doorlock_sniper__msg__VideoPacket__Sequence__destroy(doorlock_sniper__msg__VideoPacket__Sequence * array);

/// Check for msg/VideoPacket message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
bool
doorlock_sniper__msg__VideoPacket__Sequence__are_equal(const doorlock_sniper__msg__VideoPacket__Sequence * lhs, const doorlock_sniper__msg__VideoPacket__Sequence * rhs);

/// Copy an array of msg/VideoPacket messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_doorlock_sniper
bool
doorlock_sniper__msg__VideoPacket__Sequence__copy(
  const doorlock_sniper__msg__VideoPacket__Sequence * input,
  doorlock_sniper__msg__VideoPacket__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__FUNCTIONS_H_
