// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/GeofenceResult.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__GEOFENCE_RESULT__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__GEOFENCE_RESULT__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__GeofenceResult __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__GeofenceResult __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GeofenceResult_
{
  using Type = GeofenceResult_<ContainerAllocator>;

  explicit GeofenceResult_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->geofence_violation_reason = 0;
      this->primary_geofence_breached = false;
      this->primary_geofence_action = 0;
      this->home_required = false;
    }
  }

  explicit GeofenceResult_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->geofence_violation_reason = 0;
      this->primary_geofence_breached = false;
      this->primary_geofence_action = 0;
      this->home_required = false;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _geofence_violation_reason_type =
    uint8_t;
  _geofence_violation_reason_type geofence_violation_reason;
  using _primary_geofence_breached_type =
    bool;
  _primary_geofence_breached_type primary_geofence_breached;
  using _primary_geofence_action_type =
    uint8_t;
  _primary_geofence_action_type primary_geofence_action;
  using _home_required_type =
    bool;
  _home_required_type home_required;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__geofence_violation_reason(
    const uint8_t & _arg)
  {
    this->geofence_violation_reason = _arg;
    return *this;
  }
  Type & set__primary_geofence_breached(
    const bool & _arg)
  {
    this->primary_geofence_breached = _arg;
    return *this;
  }
  Type & set__primary_geofence_action(
    const uint8_t & _arg)
  {
    this->primary_geofence_action = _arg;
    return *this;
  }
  Type & set__home_required(
    const bool & _arg)
  {
    this->home_required = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t GF_ACTION_NONE =
    0u;
  static constexpr uint8_t GF_ACTION_WARN =
    1u;
  static constexpr uint8_t GF_ACTION_LOITER =
    2u;
  static constexpr uint8_t GF_ACTION_RTL =
    3u;
  static constexpr uint8_t GF_ACTION_TERMINATE =
    4u;
  static constexpr uint8_t GF_ACTION_LAND =
    5u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::GeofenceResult_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::GeofenceResult_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::GeofenceResult_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::GeofenceResult_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__GeofenceResult
    std::shared_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__GeofenceResult
    std::shared_ptr<px4_msgs::msg::GeofenceResult_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GeofenceResult_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->geofence_violation_reason != other.geofence_violation_reason) {
      return false;
    }
    if (this->primary_geofence_breached != other.primary_geofence_breached) {
      return false;
    }
    if (this->primary_geofence_action != other.primary_geofence_action) {
      return false;
    }
    if (this->home_required != other.home_required) {
      return false;
    }
    return true;
  }
  bool operator!=(const GeofenceResult_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GeofenceResult_

// alias to use template instance with default allocator
using GeofenceResult =
  px4_msgs::msg::GeofenceResult_<std::allocator<void>>;

// constant definitions
template<typename ContainerAllocator>
constexpr uint8_t GeofenceResult_<ContainerAllocator>::GF_ACTION_NONE;
template<typename ContainerAllocator>
constexpr uint8_t GeofenceResult_<ContainerAllocator>::GF_ACTION_WARN;
template<typename ContainerAllocator>
constexpr uint8_t GeofenceResult_<ContainerAllocator>::GF_ACTION_LOITER;
template<typename ContainerAllocator>
constexpr uint8_t GeofenceResult_<ContainerAllocator>::GF_ACTION_RTL;
template<typename ContainerAllocator>
constexpr uint8_t GeofenceResult_<ContainerAllocator>::GF_ACTION_TERMINATE;
template<typename ContainerAllocator>
constexpr uint8_t GeofenceResult_<ContainerAllocator>::GF_ACTION_LAND;

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__GEOFENCE_RESULT__STRUCT_HPP_
