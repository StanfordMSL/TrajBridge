// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ControlAllocatorStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CONTROL_ALLOCATOR_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__CONTROL_ALLOCATOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ACTUATOR_SATURATION_OK'.
enum
{
  px4_msgs__msg__ControlAllocatorStatus__ACTUATOR_SATURATION_OK = 0
};

/// Constant 'ACTUATOR_SATURATION_UPPER_DYN'.
enum
{
  px4_msgs__msg__ControlAllocatorStatus__ACTUATOR_SATURATION_UPPER_DYN = 1
};

/// Constant 'ACTUATOR_SATURATION_UPPER'.
enum
{
  px4_msgs__msg__ControlAllocatorStatus__ACTUATOR_SATURATION_UPPER = 2
};

/// Constant 'ACTUATOR_SATURATION_LOWER_DYN'.
enum
{
  px4_msgs__msg__ControlAllocatorStatus__ACTUATOR_SATURATION_LOWER_DYN = -1
};

/// Constant 'ACTUATOR_SATURATION_LOWER'.
enum
{
  px4_msgs__msg__ControlAllocatorStatus__ACTUATOR_SATURATION_LOWER = -2
};

// Struct defined in msg/ControlAllocatorStatus in the package px4_msgs.
typedef struct px4_msgs__msg__ControlAllocatorStatus
{
  uint64_t timestamp;
  bool torque_setpoint_achieved;
  float unallocated_torque[3];
  bool thrust_setpoint_achieved;
  float unallocated_thrust[3];
  int8_t actuator_saturation[16];
  uint16_t handled_motor_failure_mask;
} px4_msgs__msg__ControlAllocatorStatus;

// Struct for a sequence of px4_msgs__msg__ControlAllocatorStatus.
typedef struct px4_msgs__msg__ControlAllocatorStatus__Sequence
{
  px4_msgs__msg__ControlAllocatorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ControlAllocatorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__CONTROL_ALLOCATOR_STATUS__STRUCT_H_
