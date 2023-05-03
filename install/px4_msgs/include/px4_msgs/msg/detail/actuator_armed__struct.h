// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ActuatorArmed.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ACTUATOR_ARMED__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ACTUATOR_ARMED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/ActuatorArmed in the package px4_msgs.
typedef struct px4_msgs__msg__ActuatorArmed
{
  uint64_t timestamp;
  bool armed;
  bool prearmed;
  bool ready_to_arm;
  bool lockdown;
  bool manual_lockdown;
  bool force_failsafe;
  bool in_esc_calibration_mode;
} px4_msgs__msg__ActuatorArmed;

// Struct for a sequence of px4_msgs__msg__ActuatorArmed.
typedef struct px4_msgs__msg__ActuatorArmed__Sequence
{
  px4_msgs__msg__ActuatorArmed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ActuatorArmed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ACTUATOR_ARMED__STRUCT_H_
