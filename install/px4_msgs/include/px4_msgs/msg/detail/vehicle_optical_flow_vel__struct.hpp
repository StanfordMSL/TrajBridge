// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/VehicleOpticalFlowVel.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_OPTICAL_FLOW_VEL__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_OPTICAL_FLOW_VEL__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__VehicleOpticalFlowVel __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__VehicleOpticalFlowVel __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleOpticalFlowVel_
{
  using Type = VehicleOpticalFlowVel_<ContainerAllocator>;

  explicit VehicleOpticalFlowVel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      std::fill<typename std::array<float, 2>::iterator, float>(this->vel_body.begin(), this->vel_body.end(), 0.0f);
      std::fill<typename std::array<float, 2>::iterator, float>(this->vel_ne.begin(), this->vel_ne.end(), 0.0f);
      std::fill<typename std::array<float, 2>::iterator, float>(this->flow_uncompensated_integral.begin(), this->flow_uncompensated_integral.end(), 0.0f);
      std::fill<typename std::array<float, 2>::iterator, float>(this->flow_compensated_integral.begin(), this->flow_compensated_integral.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->gyro_rate.begin(), this->gyro_rate.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->gyro_rate_integral.begin(), this->gyro_rate_integral.end(), 0.0f);
    }
  }

  explicit VehicleOpticalFlowVel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : vel_body(_alloc),
    vel_ne(_alloc),
    flow_uncompensated_integral(_alloc),
    flow_compensated_integral(_alloc),
    gyro_rate(_alloc),
    gyro_rate_integral(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->timestamp_sample = 0ull;
      std::fill<typename std::array<float, 2>::iterator, float>(this->vel_body.begin(), this->vel_body.end(), 0.0f);
      std::fill<typename std::array<float, 2>::iterator, float>(this->vel_ne.begin(), this->vel_ne.end(), 0.0f);
      std::fill<typename std::array<float, 2>::iterator, float>(this->flow_uncompensated_integral.begin(), this->flow_uncompensated_integral.end(), 0.0f);
      std::fill<typename std::array<float, 2>::iterator, float>(this->flow_compensated_integral.begin(), this->flow_compensated_integral.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->gyro_rate.begin(), this->gyro_rate.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->gyro_rate_integral.begin(), this->gyro_rate_integral.end(), 0.0f);
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _timestamp_sample_type =
    uint64_t;
  _timestamp_sample_type timestamp_sample;
  using _vel_body_type =
    std::array<float, 2>;
  _vel_body_type vel_body;
  using _vel_ne_type =
    std::array<float, 2>;
  _vel_ne_type vel_ne;
  using _flow_uncompensated_integral_type =
    std::array<float, 2>;
  _flow_uncompensated_integral_type flow_uncompensated_integral;
  using _flow_compensated_integral_type =
    std::array<float, 2>;
  _flow_compensated_integral_type flow_compensated_integral;
  using _gyro_rate_type =
    std::array<float, 3>;
  _gyro_rate_type gyro_rate;
  using _gyro_rate_integral_type =
    std::array<float, 3>;
  _gyro_rate_integral_type gyro_rate_integral;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__timestamp_sample(
    const uint64_t & _arg)
  {
    this->timestamp_sample = _arg;
    return *this;
  }
  Type & set__vel_body(
    const std::array<float, 2> & _arg)
  {
    this->vel_body = _arg;
    return *this;
  }
  Type & set__vel_ne(
    const std::array<float, 2> & _arg)
  {
    this->vel_ne = _arg;
    return *this;
  }
  Type & set__flow_uncompensated_integral(
    const std::array<float, 2> & _arg)
  {
    this->flow_uncompensated_integral = _arg;
    return *this;
  }
  Type & set__flow_compensated_integral(
    const std::array<float, 2> & _arg)
  {
    this->flow_compensated_integral = _arg;
    return *this;
  }
  Type & set__gyro_rate(
    const std::array<float, 3> & _arg)
  {
    this->gyro_rate = _arg;
    return *this;
  }
  Type & set__gyro_rate_integral(
    const std::array<float, 3> & _arg)
  {
    this->gyro_rate_integral = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__VehicleOpticalFlowVel
    std::shared_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__VehicleOpticalFlowVel
    std::shared_ptr<px4_msgs::msg::VehicleOpticalFlowVel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleOpticalFlowVel_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->timestamp_sample != other.timestamp_sample) {
      return false;
    }
    if (this->vel_body != other.vel_body) {
      return false;
    }
    if (this->vel_ne != other.vel_ne) {
      return false;
    }
    if (this->flow_uncompensated_integral != other.flow_uncompensated_integral) {
      return false;
    }
    if (this->flow_compensated_integral != other.flow_compensated_integral) {
      return false;
    }
    if (this->gyro_rate != other.gyro_rate) {
      return false;
    }
    if (this->gyro_rate_integral != other.gyro_rate_integral) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleOpticalFlowVel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleOpticalFlowVel_

// alias to use template instance with default allocator
using VehicleOpticalFlowVel =
  px4_msgs::msg::VehicleOpticalFlowVel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_OPTICAL_FLOW_VEL__STRUCT_HPP_
