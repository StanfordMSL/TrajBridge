// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from px4_msgs:msg/GimbalDeviceAttitudeStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "px4_msgs/msg/detail/gimbal_device_attitude_status__rosidl_typesupport_introspection_c.h"
#include "px4_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "px4_msgs/msg/detail/gimbal_device_attitude_status__functions.h"
#include "px4_msgs/msg/detail/gimbal_device_attitude_status__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  px4_msgs__msg__GimbalDeviceAttitudeStatus__init(message_memory);
}

void GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_fini_function(void * message_memory)
{
  px4_msgs__msg__GimbalDeviceAttitudeStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_member_array[10] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_system",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, target_system),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_component",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, target_component),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "device_flags",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, device_flags),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "q",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, q),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angular_velocity_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, angular_velocity_x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angular_velocity_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, angular_velocity_y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angular_velocity_z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, angular_velocity_z),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "failure_flags",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, failure_flags),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "received_from_mavlink",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__GimbalDeviceAttitudeStatus, received_from_mavlink),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_members = {
  "px4_msgs__msg",  // message namespace
  "GimbalDeviceAttitudeStatus",  // message name
  10,  // number of fields
  sizeof(px4_msgs__msg__GimbalDeviceAttitudeStatus),
  GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_member_array,  // message members
  GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_type_support_handle = {
  0,
  &GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_px4_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, px4_msgs, msg, GimbalDeviceAttitudeStatus)() {
  if (!GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_type_support_handle.typesupport_identifier) {
    GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GimbalDeviceAttitudeStatus__rosidl_typesupport_introspection_c__GimbalDeviceAttitudeStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
