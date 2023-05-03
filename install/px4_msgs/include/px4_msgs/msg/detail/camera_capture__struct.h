// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/CameraCapture.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CAMERA_CAPTURE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__CAMERA_CAPTURE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/CameraCapture in the package px4_msgs.
typedef struct px4_msgs__msg__CameraCapture
{
  uint64_t timestamp;
  uint64_t timestamp_utc;
  uint32_t seq;
  double lat;
  double lon;
  float alt;
  float ground_distance;
  float q[4];
  int8_t result;
} px4_msgs__msg__CameraCapture;

// Struct for a sequence of px4_msgs__msg__CameraCapture.
typedef struct px4_msgs__msg__CameraCapture__Sequence
{
  px4_msgs__msg__CameraCapture * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__CameraCapture__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__CAMERA_CAPTURE__STRUCT_H_
