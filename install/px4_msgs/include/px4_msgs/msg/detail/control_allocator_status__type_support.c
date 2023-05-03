// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from px4_msgs:msg/ControlAllocatorStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "px4_msgs/msg/detail/control_allocator_status__rosidl_typesupport_introspection_c.h"
#include "px4_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "px4_msgs/msg/detail/control_allocator_status__functions.h"
#include "px4_msgs/msg/detail/control_allocator_status__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  px4_msgs__msg__ControlAllocatorStatus__init(message_memory);
}

void ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_fini_function(void * message_memory)
{
  px4_msgs__msg__ControlAllocatorStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_member_array[7] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__ControlAllocatorStatus, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "torque_setpoint_achieved",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__ControlAllocatorStatus, torque_setpoint_achieved),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "unallocated_torque",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__ControlAllocatorStatus, unallocated_torque),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "thrust_setpoint_achieved",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__ControlAllocatorStatus, thrust_setpoint_achieved),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "unallocated_thrust",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__ControlAllocatorStatus, unallocated_thrust),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "actuator_saturation",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__ControlAllocatorStatus, actuator_saturation),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "handled_motor_failure_mask",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(px4_msgs__msg__ControlAllocatorStatus, handled_motor_failure_mask),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_members = {
  "px4_msgs__msg",  // message namespace
  "ControlAllocatorStatus",  // message name
  7,  // number of fields
  sizeof(px4_msgs__msg__ControlAllocatorStatus),
  ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_member_array,  // message members
  ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_type_support_handle = {
  0,
  &ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_px4_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, px4_msgs, msg, ControlAllocatorStatus)() {
  if (!ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_type_support_handle.typesupport_identifier) {
    ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ControlAllocatorStatus__rosidl_typesupport_introspection_c__ControlAllocatorStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
