// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from doorlock_sniper:msg/VideoPacket.idl
// generated code does not contain a copyright notice

#ifndef DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__STRUCT_HPP_
#define DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__doorlock_sniper__msg__VideoPacket __attribute__((deprecated))
#else
# define DEPRECATED__doorlock_sniper__msg__VideoPacket __declspec(deprecated)
#endif

namespace doorlock_sniper
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VideoPacket_
{
  using Type = VideoPacket_<ContainerAllocator>;

  explicit VideoPacket_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence_id = 0ull;
      this->timestamp_ns = 0ull;
      std::fill<typename std::array<uint8_t, 150>::iterator, uint8_t>(this->data.begin(), this->data.end(), 0);
    }
  }

  explicit VideoPacket_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : data(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence_id = 0ull;
      this->timestamp_ns = 0ull;
      std::fill<typename std::array<uint8_t, 150>::iterator, uint8_t>(this->data.begin(), this->data.end(), 0);
    }
  }

  // field types and members
  using _sequence_id_type =
    uint64_t;
  _sequence_id_type sequence_id;
  using _timestamp_ns_type =
    uint64_t;
  _timestamp_ns_type timestamp_ns;
  using _data_type =
    std::array<uint8_t, 150>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__sequence_id(
    const uint64_t & _arg)
  {
    this->sequence_id = _arg;
    return *this;
  }
  Type & set__timestamp_ns(
    const uint64_t & _arg)
  {
    this->timestamp_ns = _arg;
    return *this;
  }
  Type & set__data(
    const std::array<uint8_t, 150> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    doorlock_sniper::msg::VideoPacket_<ContainerAllocator> *;
  using ConstRawPtr =
    const doorlock_sniper::msg::VideoPacket_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      doorlock_sniper::msg::VideoPacket_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      doorlock_sniper::msg::VideoPacket_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__doorlock_sniper__msg__VideoPacket
    std::shared_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__doorlock_sniper__msg__VideoPacket
    std::shared_ptr<doorlock_sniper::msg::VideoPacket_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VideoPacket_ & other) const
  {
    if (this->sequence_id != other.sequence_id) {
      return false;
    }
    if (this->timestamp_ns != other.timestamp_ns) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const VideoPacket_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VideoPacket_

// alias to use template instance with default allocator
using VideoPacket =
  doorlock_sniper::msg::VideoPacket_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace doorlock_sniper

#endif  // DOORLOCK_SNIPER__MSG__DETAIL__VIDEO_PACKET__STRUCT_HPP_
