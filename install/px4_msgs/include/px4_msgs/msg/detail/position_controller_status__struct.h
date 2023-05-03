// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/PositionControllerStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__POSITION_CONTROLLER_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__POSITION_CONTROLLER_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/PositionControllerStatus in the package px4_msgs.
typedef struct px4_msgs__msg__PositionControllerStatus
{
  uint64_t timestamp;
  float nav_roll;
  float nav_pitch;
  float nav_bearing;
  float target_bearing;
  float xtrack_error;
  float wp_dist;
  float acceptance_radius;
  float yaw_acceptance;
  float altitude_acceptance;
  uint8_t type;
} px4_msgs__msg__PositionControllerStatus;

// Struct for a sequence of px4_msgs__msg__PositionControllerStatus.
typedef struct px4_msgs__msg__PositionControllerStatus__Sequence
{
  px4_msgs__msg__PositionControllerStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__PositionControllerStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__POSITION_CONTROLLER_STATUS__STRUCT_H_
