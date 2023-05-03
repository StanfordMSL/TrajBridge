// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/EscStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESC_STATUS__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__ESC_STATUS__TRAITS_HPP_

#include "px4_msgs/msg/detail/esc_status__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'esc'
#include "px4_msgs/msg/detail/esc_report__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<px4_msgs::msg::EscStatus>()
{
  return "px4_msgs::msg::EscStatus";
}

template<>
inline const char * name<px4_msgs::msg::EscStatus>()
{
  return "px4_msgs/msg/EscStatus";
}

template<>
struct has_fixed_size<px4_msgs::msg::EscStatus>
  : std::integral_constant<bool, has_fixed_size<px4_msgs::msg::EscReport>::value> {};

template<>
struct has_bounded_size<px4_msgs::msg::EscStatus>
  : std::integral_constant<bool, has_bounded_size<px4_msgs::msg::EscReport>::value> {};

template<>
struct is_message<px4_msgs::msg::EscStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__ESC_STATUS__TRAITS_HPP_
