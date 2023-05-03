// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/RtlTimeEstimate.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__RTL_TIME_ESTIMATE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__RTL_TIME_ESTIMATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/RtlTimeEstimate in the package px4_msgs.
typedef struct px4_msgs__msg__RtlTimeEstimate
{
  uint64_t timestamp;
  bool valid;
  float time_estimate;
  float safe_time_estimate;
} px4_msgs__msg__RtlTimeEstimate;

// Struct for a sequence of px4_msgs__msg__RtlTimeEstimate.
typedef struct px4_msgs__msg__RtlTimeEstimate__Sequence
{
  px4_msgs__msg__RtlTimeEstimate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__RtlTimeEstimate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__RTL_TIME_ESTIMATE__STRUCT_H_
