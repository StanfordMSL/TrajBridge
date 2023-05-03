// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/IrlockReport.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__IRLOCK_REPORT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__IRLOCK_REPORT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/IrlockReport in the package px4_msgs.
typedef struct px4_msgs__msg__IrlockReport
{
  uint64_t timestamp;
  uint16_t signature;
  float pos_x;
  float pos_y;
  float size_x;
  float size_y;
} px4_msgs__msg__IrlockReport;

// Struct for a sequence of px4_msgs__msg__IrlockReport.
typedef struct px4_msgs__msg__IrlockReport__Sequence
{
  px4_msgs__msg__IrlockReport * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__IrlockReport__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__IRLOCK_REPORT__STRUCT_H_
