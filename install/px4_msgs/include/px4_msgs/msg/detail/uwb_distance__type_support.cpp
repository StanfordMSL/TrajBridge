// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from px4_msgs:msg/UwbDistance.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "px4_msgs/msg/detail/uwb_distance__struct.hpp"
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

void UwbDistance_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) px4_msgs::msg::UwbDistance(_init);
}

void UwbDistance_fini_function(void * message_memory)
{
  auto typed_message = static_cast<px4_msgs::msg::UwbDistance *>(message_memory);
  typed_message->~UwbDistance();
}

size_t size_function__UwbDistance__anchor_distance(const void * untyped_member)
{
  (void)untyped_member;
  return 12;
}

const void * get_const_function__UwbDistance__anchor_distance(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint16_t, 12> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbDistance__anchor_distance(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint16_t, 12> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbDistance__nlos(const void * untyped_member)
{
  (void)untyped_member;
  return 12;
}

const void * get_const_function__UwbDistance__nlos(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<bool, 12> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbDistance__nlos(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<bool, 12> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbDistance__aoafirst(const void * untyped_member)
{
  (void)untyped_member;
  return 12;
}

const void * get_const_function__UwbDistance__aoafirst(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 12> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbDistance__aoafirst(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 12> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbDistance__position(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbDistance__position(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbDistance__position(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 3> *>(untyped_member);
  return &member[index];
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember UwbDistance_message_member_array[10] = {
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "time_uwb_ms",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, time_uwb_ms),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "counter",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, counter),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "sessionid",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, sessionid),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "time_offset",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, time_offset),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "status",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, status),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_distance",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    12,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, anchor_distance),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbDistance__anchor_distance,  // size() function pointer
    get_const_function__UwbDistance__anchor_distance,  // get_const(index) function pointer
    get_function__UwbDistance__anchor_distance,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "nlos",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    12,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, nlos),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbDistance__nlos,  // size() function pointer
    get_const_function__UwbDistance__nlos,  // get_const(index) function pointer
    get_function__UwbDistance__nlos,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "aoafirst",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    12,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, aoafirst),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbDistance__aoafirst,  // size() function pointer
    get_const_function__UwbDistance__aoafirst,  // get_const(index) function pointer
    get_function__UwbDistance__aoafirst,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbDistance, position),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbDistance__position,  // size() function pointer
    get_const_function__UwbDistance__position,  // get_const(index) function pointer
    get_function__UwbDistance__position,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers UwbDistance_message_members = {
  "px4_msgs::msg",  // message namespace
  "UwbDistance",  // message name
  10,  // number of fields
  sizeof(px4_msgs::msg::UwbDistance),
  UwbDistance_message_member_array,  // message members
  UwbDistance_init_function,  // function to initialize message memory (memory has to be allocated)
  UwbDistance_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t UwbDistance_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &UwbDistance_message_members,
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
get_message_type_support_handle<px4_msgs::msg::UwbDistance>()
{
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::UwbDistance_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, px4_msgs, msg, UwbDistance)() {
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::UwbDistance_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
