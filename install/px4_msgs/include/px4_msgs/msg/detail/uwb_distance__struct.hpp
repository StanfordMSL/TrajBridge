// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/UwbDistance.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__UWB_DISTANCE__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__UWB_DISTANCE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__UwbDistance __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__UwbDistance __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UwbDistance_
{
  using Type = UwbDistance_<ContainerAllocator>;

  explicit UwbDistance_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->time_uwb_ms = 0ul;
      this->counter = 0ul;
      this->sessionid = 0ul;
      this->time_offset = 0ul;
      this->status = 0;
      std::fill<typename std::array<uint16_t, 12>::iterator, uint16_t>(this->anchor_distance.begin(), this->anchor_distance.end(), 0);
      std::fill<typename std::array<bool, 12>::iterator, bool>(this->nlos.begin(), this->nlos.end(), false);
      std::fill<typename std::array<float, 12>::iterator, float>(this->aoafirst.begin(), this->aoafirst.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->position.begin(), this->position.end(), 0.0f);
    }
  }

  explicit UwbDistance_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : anchor_distance(_alloc),
    nlos(_alloc),
    aoafirst(_alloc),
    position(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->time_uwb_ms = 0ul;
      this->counter = 0ul;
      this->sessionid = 0ul;
      this->time_offset = 0ul;
      this->status = 0;
      std::fill<typename std::array<uint16_t, 12>::iterator, uint16_t>(this->anchor_distance.begin(), this->anchor_distance.end(), 0);
      std::fill<typename std::array<bool, 12>::iterator, bool>(this->nlos.begin(), this->nlos.end(), false);
      std::fill<typename std::array<float, 12>::iterator, float>(this->aoafirst.begin(), this->aoafirst.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->position.begin(), this->position.end(), 0.0f);
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _time_uwb_ms_type =
    uint32_t;
  _time_uwb_ms_type time_uwb_ms;
  using _counter_type =
    uint32_t;
  _counter_type counter;
  using _sessionid_type =
    uint32_t;
  _sessionid_type sessionid;
  using _time_offset_type =
    uint32_t;
  _time_offset_type time_offset;
  using _status_type =
    uint16_t;
  _status_type status;
  using _anchor_distance_type =
    std::array<uint16_t, 12>;
  _anchor_distance_type anchor_distance;
  using _nlos_type =
    std::array<bool, 12>;
  _nlos_type nlos;
  using _aoafirst_type =
    std::array<float, 12>;
  _aoafirst_type aoafirst;
  using _position_type =
    std::array<float, 3>;
  _position_type position;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__time_uwb_ms(
    const uint32_t & _arg)
  {
    this->time_uwb_ms = _arg;
    return *this;
  }
  Type & set__counter(
    const uint32_t & _arg)
  {
    this->counter = _arg;
    return *this;
  }
  Type & set__sessionid(
    const uint32_t & _arg)
  {
    this->sessionid = _arg;
    return *this;
  }
  Type & set__time_offset(
    const uint32_t & _arg)
  {
    this->time_offset = _arg;
    return *this;
  }
  Type & set__status(
    const uint16_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__anchor_distance(
    const std::array<uint16_t, 12> & _arg)
  {
    this->anchor_distance = _arg;
    return *this;
  }
  Type & set__nlos(
    const std::array<bool, 12> & _arg)
  {
    this->nlos = _arg;
    return *this;
  }
  Type & set__aoafirst(
    const std::array<float, 12> & _arg)
  {
    this->aoafirst = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<float, 3> & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::UwbDistance_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::UwbDistance_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::UwbDistance_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::UwbDistance_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__UwbDistance
    std::shared_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__UwbDistance
    std::shared_ptr<px4_msgs::msg::UwbDistance_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UwbDistance_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->time_uwb_ms != other.time_uwb_ms) {
      return false;
    }
    if (this->counter != other.counter) {
      return false;
    }
    if (this->sessionid != other.sessionid) {
      return false;
    }
    if (this->time_offset != other.time_offset) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    if (this->anchor_distance != other.anchor_distance) {
      return false;
    }
    if (this->nlos != other.nlos) {
      return false;
    }
    if (this->aoafirst != other.aoafirst) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const UwbDistance_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UwbDistance_

// alias to use template instance with default allocator
using UwbDistance =
  px4_msgs::msg::UwbDistance_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__UWB_DISTANCE__STRUCT_HPP_
