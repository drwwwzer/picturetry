// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice
#include "doorlock_sniper/msg/detail/video_packet__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
doorlock_sniper__msg__VideoPacket__init(doorlock_sniper__msg__VideoPacket * msg)
{
  if (!msg) {
    return false;
  }
  // sequence_id
  // timestamp_ns
  // data
  return true;
}

void
doorlock_sniper__msg__VideoPacket__fini(doorlock_sniper__msg__VideoPacket * msg)
{
  if (!msg) {
    return;
  }
  // sequence_id
  // timestamp_ns
  // data
}

bool
doorlock_sniper__msg__VideoPacket__are_equal(const doorlock_sniper__msg__VideoPacket * lhs, const doorlock_sniper__msg__VideoPacket * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sequence_id
  if (lhs->sequence_id != rhs->sequence_id) {
    return false;
  }
  // timestamp_ns
  if (lhs->timestamp_ns != rhs->timestamp_ns) {
    return false;
  }
  // data
  for (size_t i = 0; i < 150; ++i) {
    if (lhs->data[i] != rhs->data[i]) {
      return false;
    }
  }
  return true;
}

bool
doorlock_sniper__msg__VideoPacket__copy(
  const doorlock_sniper__msg__VideoPacket * input,
  doorlock_sniper__msg__VideoPacket * output)
{
  if (!input || !output) {
    return false;
  }
  // sequence_id
  output->sequence_id = input->sequence_id;
  // timestamp_ns
  output->timestamp_ns = input->timestamp_ns;
  // data
  for (size_t i = 0; i < 150; ++i) {
    output->data[i] = input->data[i];
  }
  return true;
}

doorlock_sniper__msg__VideoPacket *
doorlock_sniper__msg__VideoPacket__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  doorlock_sniper__msg__VideoPacket * msg = (doorlock_sniper__msg__VideoPacket *)allocator.allocate(sizeof(doorlock_sniper__msg__VideoPacket), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(doorlock_sniper__msg__VideoPacket));
  bool success = doorlock_sniper__msg__VideoPacket__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
doorlock_sniper__msg__VideoPacket__destroy(doorlock_sniper__msg__VideoPacket * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    doorlock_sniper__msg__VideoPacket__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
doorlock_sniper__msg__VideoPacket__Sequence__init(doorlock_sniper__msg__VideoPacket__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  doorlock_sniper__msg__VideoPacket * data = NULL;

  if (size) {
    data = (doorlock_sniper__msg__VideoPacket *)allocator.zero_allocate(size, sizeof(doorlock_sniper__msg__VideoPacket), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = doorlock_sniper__msg__VideoPacket__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        doorlock_sniper__msg__VideoPacket__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
doorlock_sniper__msg__VideoPacket__Sequence__fini(doorlock_sniper__msg__VideoPacket__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      doorlock_sniper__msg__VideoPacket__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

doorlock_sniper__msg__VideoPacket__Sequence *
doorlock_sniper__msg__VideoPacket__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  doorlock_sniper__msg__VideoPacket__Sequence * array = (doorlock_sniper__msg__VideoPacket__Sequence *)allocator.allocate(sizeof(doorlock_sniper__msg__VideoPacket__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = doorlock_sniper__msg__VideoPacket__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
doorlock_sniper__msg__VideoPacket__Sequence__destroy(doorlock_sniper__msg__VideoPacket__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    doorlock_sniper__msg__VideoPacket__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
doorlock_sniper__msg__VideoPacket__Sequence__are_equal(const doorlock_sniper__msg__VideoPacket__Sequence * lhs, const doorlock_sniper__msg__VideoPacket__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!doorlock_sniper__msg__VideoPacket__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
doorlock_sniper__msg__VideoPacket__Sequence__copy(
  const doorlock_sniper__msg__VideoPacket__Sequence * input,
  doorlock_sniper__msg__VideoPacket__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(doorlock_sniper__msg__VideoPacket);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    doorlock_sniper__msg__VideoPacket * data =
      (doorlock_sniper__msg__VideoPacket *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!doorlock_sniper__msg__VideoPacket__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          doorlock_sniper__msg__VideoPacket__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!doorlock_sniper__msg__VideoPacket__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
