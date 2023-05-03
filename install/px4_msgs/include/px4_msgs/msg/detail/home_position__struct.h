// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/HomePosition.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__HOME_POSITION__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__HOME_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/HomePosition in the package px4_msgs.
typedef struct px4_msgs__msg__HomePosition
{
  uint64_t timestamp;
  double lat;
  double lon;
  float alt;
  float x;
  float y;
  float z;
  float yaw;
  bool valid_alt;
  bool valid_hpos;
  bool valid_lpos;
  bool manual_home;
} px4_msgs__msg__HomePosition;

// Struct for a sequence of px4_msgs__msg__HomePosition.
typedef struct px4_msgs__msg__HomePosition__Sequence
{
  px4_msgs__msg__HomePosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__HomePosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__HOME_POSITION__STRUCT_H_
