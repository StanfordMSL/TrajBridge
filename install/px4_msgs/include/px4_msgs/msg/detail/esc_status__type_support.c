// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from px4_msgs:msg/EscStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "px4_msgs/msg/detail/esc_status__rosidl_typesupport_introspection_c.h"
#include "px4_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "px4_msgs/msg/detail/esc_status__functions.h"
#include "px4_msgs/msg/detail/esc_status__struct.h"


// Include directives for member types
// Member `esc`
#include "px4_msgs/msg/esc_report.h"
// Member `esc`
#include "px4_msgs/msg/detail/esc_report__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void EscStatus__rosidl_typesupport_introspection_c__EscStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  px4_msgs__msg__EscStatus__init(message_memory);
}

void EscStatus__rosidl_typesupport_introspection_c__EscStatus_fini_function(void * message_memory)
{
  px4_msgs__msg__EscStatus__fini(message_memory);
}

size_t EscStatus__rosidl_typesupport_introspection_c__size_function__EscReport__esc(
  const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * EscStatus__rosidl_typesupport_introspection_c__get_const_function__EscReport__esc(
  const void * untyped_member, size_t index)
{
  const px4_msgs__msg__EscReport ** member =
    (const px4_msgs__msg__EscReport **)(untyped_member);
  return &(*member)[index];
}

void * EscStatus__rosidl_typesupport_introspection_c__get_function__EscReport__esc(
  void * untyped_member, size_t index)
{
  px4_msgs__msg__EscReport ** member =
    (px4_msgs__msg__EscReport **)(untyped_member);
  return &(*member)[index];
}

static rosidl_typesupport_introspection_c__MessageMember EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_member_array[7] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__EscStatus, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "counter",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__EscStatus, counter),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "esc_count",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__EscStatus, esc_count),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "esc_connectiontype",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__EscStatus, esc_connectiontype),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "esc_online_flags",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__EscStatus, esc_online_flags),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "esc_armed_flags",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__EscStatus, esc_armed_flags),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "esc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__EscStatus, esc),  // bytes offset in struct
    NULL,  // default value
    EscStatus__rosidl_typesupport_introspection_c__size_function__EscReport__esc,  // size() function pointer
    EscStatus__rosidl_typesupport_introspection_c__get_const_function__EscReport__esc,  // get_const(index) function pointer
    EscStatus__rosidl_typesupport_introspection_c__get_function__EscReport__esc,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_members = {
  "px4_msgs__msg",  // message namespace
  "EscStatus",  // message name
  7,  // number of fields
  sizeof(px4_msgs__msg__EscStatus),
  EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_member_array,  // message members
  EscStatus__rosidl_typesupport_introspection_c__EscStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  EscStatus__rosidl_typesupport_introspection_c__EscStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_type_support_handle = {
  0,
  &EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_px4_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, px4_msgs, msg, EscStatus)() {
  EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, px4_msgs, msg, EscReport)();
  if (!EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_type_support_handle.typesupport_identifier) {
    EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &EscStatus__rosidl_typesupport_introspection_c__EscStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
