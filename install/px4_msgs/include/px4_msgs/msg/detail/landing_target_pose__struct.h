// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/LandingTargetPose.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__LANDING_TARGET_POSE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__LANDING_TARGET_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/LandingTargetPose in the package px4_msgs.
typedef struct px4_msgs__msg__LandingTargetPose
{
  uint64_t timestamp;
  bool is_static;
  bool rel_pos_valid;
  bool rel_vel_valid;
  float x_rel;
  float y_rel;
  float z_rel;
  float vx_rel;
  float vy_rel;
  float cov_x_rel;
  float cov_y_rel;
  float cov_vx_rel;
  float cov_vy_rel;
  bool abs_pos_valid;
  float x_abs;
  float y_abs;
  float z_abs;
} px4_msgs__msg__LandingTargetPose;

// Struct for a sequence of px4_msgs__msg__LandingTargetPose.
typedef struct px4_msgs__msg__LandingTargetPose__Sequence
{
  px4_msgs__msg__LandingTargetPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__LandingTargetPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__LANDING_TARGET_POSE__STRUCT_H_
