// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from px4_msgs:msg/UwbGrid.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "px4_msgs/msg/detail/uwb_grid__struct.hpp"
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

void UwbGrid_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) px4_msgs::msg::UwbGrid(_init);
}

void UwbGrid_fini_function(void * message_memory)
{
  auto typed_message = static_cast<px4_msgs::msg::UwbGrid *>(message_memory);
  typed_message->~UwbGrid();
}

size_t size_function__UwbGrid__target_gps(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__UwbGrid__target_gps(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__target_gps(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 4> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__target_pos(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__target_pos(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__target_pos(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_0(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_0(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_0(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_1(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_1(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_1(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_2(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_2(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_2(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_3(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_3(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_3(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_4(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_4(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_4(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_5(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_5(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_5(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_6(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_6(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_6(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_7(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_7(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_7(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_8(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_8(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_8(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_9(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_9(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_9(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_10(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_10(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_10(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

size_t size_function__UwbGrid__anchor_pos_11(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__UwbGrid__anchor_pos_11(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__UwbGrid__anchor_pos_11(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 3> *>(untyped_member);
  return &member[index];
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember UwbGrid_message_member_array[17] = {
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "initator_time",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, initator_time),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "num_anchors",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, num_anchors),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "target_gps",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, target_gps),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__target_gps,  // size() function pointer
    get_const_function__UwbGrid__target_gps,  // get_const(index) function pointer
    get_function__UwbGrid__target_gps,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "target_pos",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, target_pos),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__target_pos,  // size() function pointer
    get_const_function__UwbGrid__target_pos,  // get_const(index) function pointer
    get_function__UwbGrid__target_pos,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_0",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_0),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_0,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_0,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_0,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_1",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_1),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_1,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_1,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_1,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_2",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_2),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_2,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_2,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_2,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_3",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_3),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_3,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_3,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_3,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_4",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_4),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_4,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_4,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_4,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_5",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_5),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_5,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_5,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_5,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_6",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_6),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_6,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_6,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_6,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_7",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_7),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_7,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_7,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_7,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_8",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_8),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_8,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_8,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_8,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_9",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_9),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_9,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_9,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_9,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_10",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_10),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_10,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_10,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_10,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "anchor_pos_11",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs::msg::UwbGrid, anchor_pos_11),  // bytes offset in struct
    nullptr,  // default value
    size_function__UwbGrid__anchor_pos_11,  // size() function pointer
    get_const_function__UwbGrid__anchor_pos_11,  // get_const(index) function pointer
    get_function__UwbGrid__anchor_pos_11,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers UwbGrid_message_members = {
  "px4_msgs::msg",  // message namespace
  "UwbGrid",  // message name
  17,  // number of fields
  sizeof(px4_msgs::msg::UwbGrid),
  UwbGrid_message_member_array,  // message members
  UwbGrid_init_function,  // function to initialize message memory (memory has to be allocated)
  UwbGrid_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t UwbGrid_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &UwbGrid_message_members,
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
get_message_type_support_handle<px4_msgs::msg::UwbGrid>()
{
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::UwbGrid_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, px4_msgs, msg, UwbGrid)() {
  return &::px4_msgs::msg::rosidl_typesupport_introspection_cpp::UwbGrid_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
