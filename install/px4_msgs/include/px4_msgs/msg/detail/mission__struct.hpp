// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/Mission.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MISSION__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__MISSION__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__Mission __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__Mission __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Mission_
{
  using Type = Mission_<ContainerAllocator>;

  explicit Mission_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->dataman_id = 0;
      this->count = 0;
      this->current_seq = 0l;
    }
  }

  explicit Mission_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->dataman_id = 0;
      this->count = 0;
      this->current_seq = 0l;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _dataman_id_type =
    uint8_t;
  _dataman_id_type dataman_id;
  using _count_type =
    uint16_t;
  _count_type count;
  using _current_seq_type =
    int32_t;
  _current_seq_type current_seq;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__dataman_id(
    const uint8_t & _arg)
  {
    this->dataman_id = _arg;
    return *this;
  }
  Type & set__count(
    const uint16_t & _arg)
  {
    this->count = _arg;
    return *this;
  }
  Type & set__current_seq(
    const int32_t & _arg)
  {
    this->current_seq = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::Mission_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::Mission_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::Mission_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::Mission_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::Mission_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::Mission_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::Mission_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::Mission_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::Mission_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::Mission_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__Mission
    std::shared_ptr<px4_msgs::msg::Mission_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__Mission
    std::shared_ptr<px4_msgs::msg::Mission_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Mission_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->dataman_id != other.dataman_id) {
      return false;
    }
    if (this->count != other.count) {
      return false;
    }
    if (this->current_seq != other.current_seq) {
      return false;
    }
    return true;
  }
  bool operator!=(const Mission_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Mission_

// alias to use template instance with default allocator
using Mission =
  px4_msgs::msg::Mission_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__MISSION__STRUCT_HPP_
