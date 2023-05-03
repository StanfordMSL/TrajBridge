// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/FollowTargetStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__FOLLOW_TARGET_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__FOLLOW_TARGET_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/FollowTargetStatus in the package px4_msgs.
typedef struct px4_msgs__msg__FollowTargetStatus
{
  uint64_t timestamp;
  float tracked_target_course;
  float follow_angle;
  float orbit_angle_setpoint;
  float angular_rate_setpoint;
  float desired_position_raw[3];
  bool in_emergency_ascent;
  float gimbal_pitch;
} px4_msgs__msg__FollowTargetStatus;

// Struct for a sequence of px4_msgs__msg__FollowTargetStatus.
typedef struct px4_msgs__msg__FollowTargetStatus__Sequence
{
  px4_msgs__msg__FollowTargetStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__FollowTargetStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__FOLLOW_TARGET_STATUS__STRUCT_H_
