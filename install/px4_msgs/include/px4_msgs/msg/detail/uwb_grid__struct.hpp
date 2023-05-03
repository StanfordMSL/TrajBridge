// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/UwbGrid.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__UWB_GRID__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__UWB_GRID__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__UwbGrid __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__UwbGrid __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UwbGrid_
{
  using Type = UwbGrid_<ContainerAllocator>;

  explicit UwbGrid_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->initator_time = 0;
      this->num_anchors = 0;
      std::fill<typename std::array<double, 4>::iterator, double>(this->target_gps.begin(), this->target_gps.end(), 0.0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->target_pos.begin(), this->target_pos.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_0.begin(), this->anchor_pos_0.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_1.begin(), this->anchor_pos_1.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_2.begin(), this->anchor_pos_2.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_3.begin(), this->anchor_pos_3.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_4.begin(), this->anchor_pos_4.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_5.begin(), this->anchor_pos_5.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_6.begin(), this->anchor_pos_6.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_7.begin(), this->anchor_pos_7.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_8.begin(), this->anchor_pos_8.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_9.begin(), this->anchor_pos_9.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_10.begin(), this->anchor_pos_10.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_11.begin(), this->anchor_pos_11.end(), 0);
    }
  }

  explicit UwbGrid_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target_gps(_alloc),
    target_pos(_alloc),
    anchor_pos_0(_alloc),
    anchor_pos_1(_alloc),
    anchor_pos_2(_alloc),
    anchor_pos_3(_alloc),
    anchor_pos_4(_alloc),
    anchor_pos_5(_alloc),
    anchor_pos_6(_alloc),
    anchor_pos_7(_alloc),
    anchor_pos_8(_alloc),
    anchor_pos_9(_alloc),
    anchor_pos_10(_alloc),
    anchor_pos_11(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->initator_time = 0;
      this->num_anchors = 0;
      std::fill<typename std::array<double, 4>::iterator, double>(this->target_gps.begin(), this->target_gps.end(), 0.0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->target_pos.begin(), this->target_pos.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_0.begin(), this->anchor_pos_0.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_1.begin(), this->anchor_pos_1.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_2.begin(), this->anchor_pos_2.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_3.begin(), this->anchor_pos_3.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_4.begin(), this->anchor_pos_4.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_5.begin(), this->anchor_pos_5.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_6.begin(), this->anchor_pos_6.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_7.begin(), this->anchor_pos_7.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_8.begin(), this->anchor_pos_8.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_9.begin(), this->anchor_pos_9.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_10.begin(), this->anchor_pos_10.end(), 0);
      std::fill<typename std::array<int16_t, 3>::iterator, int16_t>(this->anchor_pos_11.begin(), this->anchor_pos_11.end(), 0);
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _initator_time_type =
    uint16_t;
  _initator_time_type initator_time;
  using _num_anchors_type =
    uint8_t;
  _num_anchors_type num_anchors;
  using _target_gps_type =
    std::array<double, 4>;
  _target_gps_type target_gps;
  using _target_pos_type =
    std::array<int16_t, 3>;
  _target_pos_type target_pos;
  using _anchor_pos_0_type =
    std::array<int16_t, 3>;
  _anchor_pos_0_type anchor_pos_0;
  using _anchor_pos_1_type =
    std::array<int16_t, 3>;
  _anchor_pos_1_type anchor_pos_1;
  using _anchor_pos_2_type =
    std::array<int16_t, 3>;
  _anchor_pos_2_type anchor_pos_2;
  using _anchor_pos_3_type =
    std::array<int16_t, 3>;
  _anchor_pos_3_type anchor_pos_3;
  using _anchor_pos_4_type =
    std::array<int16_t, 3>;
  _anchor_pos_4_type anchor_pos_4;
  using _anchor_pos_5_type =
    std::array<int16_t, 3>;
  _anchor_pos_5_type anchor_pos_5;
  using _anchor_pos_6_type =
    std::array<int16_t, 3>;
  _anchor_pos_6_type anchor_pos_6;
  using _anchor_pos_7_type =
    std::array<int16_t, 3>;
  _anchor_pos_7_type anchor_pos_7;
  using _anchor_pos_8_type =
    std::array<int16_t, 3>;
  _anchor_pos_8_type anchor_pos_8;
  using _anchor_pos_9_type =
    std::array<int16_t, 3>;
  _anchor_pos_9_type anchor_pos_9;
  using _anchor_pos_10_type =
    std::array<int16_t, 3>;
  _anchor_pos_10_type anchor_pos_10;
  using _anchor_pos_11_type =
    std::array<int16_t, 3>;
  _anchor_pos_11_type anchor_pos_11;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__initator_time(
    const uint16_t & _arg)
  {
    this->initator_time = _arg;
    return *this;
  }
  Type & set__num_anchors(
    const uint8_t & _arg)
  {
    this->num_anchors = _arg;
    return *this;
  }
  Type & set__target_gps(
    const std::array<double, 4> & _arg)
  {
    this->target_gps = _arg;
    return *this;
  }
  Type & set__target_pos(
    const std::array<int16_t, 3> & _arg)
  {
    this->target_pos = _arg;
    return *this;
  }
  Type & set__anchor_pos_0(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_0 = _arg;
    return *this;
  }
  Type & set__anchor_pos_1(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_1 = _arg;
    return *this;
  }
  Type & set__anchor_pos_2(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_2 = _arg;
    return *this;
  }
  Type & set__anchor_pos_3(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_3 = _arg;
    return *this;
  }
  Type & set__anchor_pos_4(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_4 = _arg;
    return *this;
  }
  Type & set__anchor_pos_5(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_5 = _arg;
    return *this;
  }
  Type & set__anchor_pos_6(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_6 = _arg;
    return *this;
  }
  Type & set__anchor_pos_7(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_7 = _arg;
    return *this;
  }
  Type & set__anchor_pos_8(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_8 = _arg;
    return *this;
  }
  Type & set__anchor_pos_9(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_9 = _arg;
    return *this;
  }
  Type & set__anchor_pos_10(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_10 = _arg;
    return *this;
  }
  Type & set__anchor_pos_11(
    const std::array<int16_t, 3> & _arg)
  {
    this->anchor_pos_11 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::UwbGrid_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::UwbGrid_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::UwbGrid_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::UwbGrid_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__UwbGrid
    std::shared_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__UwbGrid
    std::shared_ptr<px4_msgs::msg::UwbGrid_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UwbGrid_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->initator_time != other.initator_time) {
      return false;
    }
    if (this->num_anchors != other.num_anchors) {
      return false;
    }
    if (this->target_gps != other.target_gps) {
      return false;
    }
    if (this->target_pos != other.target_pos) {
      return false;
    }
    if (this->anchor_pos_0 != other.anchor_pos_0) {
      return false;
    }
    if (this->anchor_pos_1 != other.anchor_pos_1) {
      return false;
    }
    if (this->anchor_pos_2 != other.anchor_pos_2) {
      return false;
    }
    if (this->anchor_pos_3 != other.anchor_pos_3) {
      return false;
    }
    if (this->anchor_pos_4 != other.anchor_pos_4) {
      return false;
    }
    if (this->anchor_pos_5 != other.anchor_pos_5) {
      return false;
    }
    if (this->anchor_pos_6 != other.anchor_pos_6) {
      return false;
    }
    if (this->anchor_pos_7 != other.anchor_pos_7) {
      return false;
    }
    if (this->anchor_pos_8 != other.anchor_pos_8) {
      return false;
    }
    if (this->anchor_pos_9 != other.anchor_pos_9) {
      return false;
    }
    if (this->anchor_pos_10 != other.anchor_pos_10) {
      return false;
    }
    if (this->anchor_pos_11 != other.anchor_pos_11) {
      return false;
    }
    return true;
  }
  bool operator!=(const UwbGrid_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UwbGrid_

// alias to use template instance with default allocator
using UwbGrid =
  px4_msgs::msg::UwbGrid_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__UWB_GRID__STRUCT_HPP_
