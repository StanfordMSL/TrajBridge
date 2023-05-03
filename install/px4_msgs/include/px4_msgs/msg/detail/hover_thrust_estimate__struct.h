// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/HoverThrustEstimate.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__HOVER_THRUST_ESTIMATE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__HOVER_THRUST_ESTIMATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/HoverThrustEstimate in the package px4_msgs.
typedef struct px4_msgs__msg__HoverThrustEstimate
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  float hover_thrust;
  float hover_thrust_var;
  float accel_innov;
  float accel_innov_var;
  float accel_innov_test_ratio;
  float accel_noise_var;
  bool valid;
} px4_msgs__msg__HoverThrustEstimate;

// Struct for a sequence of px4_msgs__msg__HoverThrustEstimate.
typedef struct px4_msgs__msg__HoverThrustEstimate__Sequence
{
  px4_msgs__msg__HoverThrustEstimate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__HoverThrustEstimate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__HOVER_THRUST_ESTIMATE__STRUCT_H_
