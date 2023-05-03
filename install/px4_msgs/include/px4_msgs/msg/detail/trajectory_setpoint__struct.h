// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/TrajectorySetpoint.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__TRAJECTORY_SETPOINT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__TRAJECTORY_SETPOINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/TrajectorySetpoint in the package px4_msgs.
typedef struct px4_msgs__msg__TrajectorySetpoint
{
  uint64_t timestamp;
  float position[3];
  float velocity[3];
  float acceleration[3];
  float jerk[3];
  float yaw;
  float yawspeed;
} px4_msgs__msg__TrajectorySetpoint;

// Struct for a sequence of px4_msgs__msg__TrajectorySetpoint.
typedef struct px4_msgs__msg__TrajectorySetpoint__Sequence
{
  px4_msgs__msg__TrajectorySetpoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__TrajectorySetpoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__TRAJECTORY_SETPOINT__STRUCT_H_
