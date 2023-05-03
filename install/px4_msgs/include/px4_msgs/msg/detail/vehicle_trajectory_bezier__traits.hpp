// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/VehicleTrajectoryBezier.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_TRAJECTORY_BEZIER__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_TRAJECTORY_BEZIER__TRAITS_HPP_

#include "px4_msgs/msg/detail/vehicle_trajectory_bezier__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'control_points'
#include "px4_msgs/msg/detail/trajectory_bezier__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<px4_msgs::msg::VehicleTrajectoryBezier>()
{
  return "px4_msgs::msg::VehicleTrajectoryBezier";
}

template<>
inline const char * name<px4_msgs::msg::VehicleTrajectoryBezier>()
{
  return "px4_msgs/msg/VehicleTrajectoryBezier";
}

template<>
struct has_fixed_size<px4_msgs::msg::VehicleTrajectoryBezier>
  : std::integral_constant<bool, has_fixed_size<px4_msgs::msg::TrajectoryBezier>::value> {};

template<>
struct has_bounded_size<px4_msgs::msg::VehicleTrajectoryBezier>
  : std::integral_constant<bool, has_bounded_size<px4_msgs::msg::TrajectoryBezier>::value> {};

template<>
struct is_message<px4_msgs::msg::VehicleTrajectoryBezier>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_TRAJECTORY_BEZIER__TRAITS_HPP_
