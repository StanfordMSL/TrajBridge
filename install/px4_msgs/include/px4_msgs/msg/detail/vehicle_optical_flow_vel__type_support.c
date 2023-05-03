// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from px4_msgs:msg/VehicleOpticalFlowVel.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "px4_msgs/msg/detail/vehicle_optical_flow_vel__rosidl_typesupport_introspection_c.h"
#include "px4_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "px4_msgs/msg/detail/vehicle_optical_flow_vel__functions.h"
#include "px4_msgs/msg/detail/vehicle_optical_flow_vel__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  px4_msgs__msg__VehicleOpticalFlowVel__init(message_memory);
}

void VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_fini_function(void * message_memory)
{
  px4_msgs__msg__VehicleOpticalFlowVel__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_member_array[8] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timestamp_sample",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, timestamp_sample),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vel_body",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, vel_body),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vel_ne",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, vel_ne),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "flow_uncompensated_integral",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, flow_uncompensated_integral),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "flow_compensated_integral",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, flow_compensated_integral),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gyro_rate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, gyro_rate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gyro_rate_integral",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__VehicleOpticalFlowVel, gyro_rate_integral),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_members = {
  "px4_msgs__msg",  // message namespace
  "VehicleOpticalFlowVel",  // message name
  8,  // number of fields
  sizeof(px4_msgs__msg__VehicleOpticalFlowVel),
  VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_member_array,  // message members
  VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_init_function,  // function to initialize message memory (memory has to be allocated)
  VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_type_support_handle = {
  0,
  &VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_px4_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, px4_msgs, msg, VehicleOpticalFlowVel)() {
  if (!VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_type_support_handle.typesupport_identifier) {
    VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &VehicleOpticalFlowVel__rosidl_typesupport_introspection_c__VehicleOpticalFlowVel_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
