// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from px4_msgs:msg/VehicleOpticalFlowVel.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "px4_msgs/msg/detail/vehicle_optical_flow_vel__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace px4_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void VehicleOpticalFlowVel_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) px4_msgs::msg::VehicleOpticalFlowVel(_init);
}

void VehicleOpticalFlowVel_fini_function(void * message_memory)
{
  auto typed_message = static_cast<px4_msgs::msg::VehicleOpticalFlowVel *>(message_memory);
  typed_message->~VehicleOpticalFlowVel();
}

size_t size_function__VehicleOpticalFlowVel__vel_body(const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * get_const_function__VehicleOpticalFlowVel__vel_body(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 2> *>(untyped_member);
  return &member[index];
}

void * get_function__VehicleOpticalFlowVel__vel_body(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 2> *>(untyped_member);
  return &member[index];
}

size_t size_function__VehicleOpticalFlowVel__vel_ne(const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * get_const_function__VehicleOpticalFlowVel__vel_ne(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 2> *>(untyped_member);
  return &member[index];
}

void * get_function__VehicleOpticalFlowVel__vel_ne(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 2> *>(untyped_member);
  return &member[index];
}

size_t size_function__VehicleOpticalFlowVel__flow_uncompensated_integral(const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * get_const_function__VehicleOpticalFlowVel__flow_uncompensated_integral(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 2> *>(untyped_member);
  return &member[index];
}

void * get_function__VehicleOpticalFlowVel__flow_uncompensated_integral(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 2> *>(untyped_member);
  return &member[index];
}

size_t size_function__VehicleOpticalFlowVel__flow_compensated_integral(const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * get_const_function__VehicleOpticalFlowVel__flow_compensated_integral(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 2> *>(untyped_member);
  return &member[index];
}

void * get_function__VehicleOpticalFlowVel__flow_compensated_integral(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 2> *>(untyped_member);
  return &member[index];
}

size_t size_function__VehicleOpticalFlowVel__gyro_rate(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__VehicleOpticalFlowVel__gyro_rate(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__VehicleOpticalFlowVel__gyro_rate(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__VehicleOpticalFlowVel__gyro_rate_integral(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__VehicleOpticalFlowVel__gyro_rate_integral(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__VehicleOpticalFlowVel__gyro_rate_integral(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember VehicleOpticalFlowVel_message_member_array[8] = {
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "timestamp_sample",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, timestamp_sample),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "vel_body",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, vel_body),  // bytes offset in struct
    nullptr,  // default value
    size_function__VehicleOpticalFlowVel__vel_body,  // size() function pointer
    get_const_function__VehicleOpticalFlowVel__vel_body,  // get_const(index) function pointer
    get_function__VehicleOpticalFlowVel__vel_body,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "vel_ne",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, vel_ne),  // bytes offset in struct
    nullptr,  // default value
    size_function__VehicleOpticalFlowVel__vel_ne,  // size() function pointer
    get_const_function__VehicleOpticalFlowVel__vel_ne,  // get_const(index) function pointer
    get_function__VehicleOpticalFlowVel__vel_ne,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "flow_uncompensated_integral",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, flow_uncompensated_integral),  // bytes offset in struct
    nullptr,  // default value
    size_function__VehicleOpticalFlowVel__flow_uncompensated_integral,  // size() function pointer
    get_const_function__VehicleOpticalFlowVel__flow_uncompensated_integral,  // get_const(index) function pointer
    get_function__VehicleOpticalFlowVel__flow_uncompensated_integral,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "flow_compensated_integral",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, flow_compensated_integral),  // bytes offset in struct
    nullptr,  // default value
    size_function__VehicleOpticalFlowVel__flow_compensated_integral,  // size() function pointer
    get_const_function__VehicleOpticalFlowVel__flow_compensated_integral,  // get_const(index) function pointer
    get_function__VehicleOpticalFlowVel__flow_compensated_integral,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "gyro_rate",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, gyro_rate),  // bytes offset in struct
    nullptr,  // default value
    size_function__VehicleOpticalFlowVel__gyro_rate,  // size() function pointer
    get_const_function__VehicleOpticalFlowVel__gyro_rate,  // get_const(index) function pointer
    get_function__VehicleOpticalFlowVel__gyro_rate,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "gyro_rate_integral",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::VehicleOpticalFlowVel, gyro_rate_integral),  // bytes offset in struct
    nullptr,  // default value
    size_function__VehicleOpticalFlowVel__gyro_rate_integral,  // size() function pointer
    get_const_function__VehicleOpticalFlowVel__gyro_rate_integral,  // get_const(index) function pointer
    get_function__VehicleOpticalFlowVel__gyro_rate_integral,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers VehicleOpticalFlowVel_message_members = {
  "px4_msgs::msg",  // message namespace
  "VehicleOpticalFlowVel",  // message name
  8,  // number of fields
  sizeof(px4_msgs::msg::VehicleOpticalFlowVel),
  VehicleOpticalFlowVel_message_member_array,  // message members
  VehicleOpticalFlowVel_init_function,  // function to initialize message memory (memory has to be allocated)
  VehicleOpticalFlowVel_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t VehicleOpticalFlowVel_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &VehicleOpticalFlowVel_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace px4_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<px4_msgs::msg::VehicleOpticalFlowVel>()
{
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::VehicleOpticalFlowVel_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, px4_msgs, msg, VehicleOpticalFlowVel)() {
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::VehicleOpticalFlowVel_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
