// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/TiltrotorExtraControls.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__TILTROTOR_EXTRA_CONTROLS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__TILTROTOR_EXTRA_CONTROLS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/TiltrotorExtraControls in the package px4_msgs.
typedef struct px4_msgs__msg__TiltrotorExtraControls
{
  uint64_t timestamp;
  float collective_tilt_normalized_setpoint;
  float collective_thrust_normalized_setpoint;
} px4_msgs__msg__TiltrotorExtraControls;

// Struct for a sequence of px4_msgs__msg__TiltrotorExtraControls.
typedef struct px4_msgs__msg__TiltrotorExtraControls__Sequence
{
  px4_msgs__msg__TiltrotorExtraControls * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__TiltrotorExtraControls__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__TILTROTOR_EXTRA_CONTROLS__STRUCT_H_
