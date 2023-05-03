// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/DebugVect.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__DEBUG_VECT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__DEBUG_VECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/DebugVect in the package px4_msgs.
typedef struct px4_msgs__msg__DebugVect
{
  uint64_t timestamp;
  uint8_t name[10];
  float x;
  float y;
  float z;
} px4_msgs__msg__DebugVect;

// Struct for a sequence of px4_msgs__msg__DebugVect.
typedef struct px4_msgs__msg__DebugVect__Sequence
{
  px4_msgs__msg__DebugVect * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__DebugVect__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__DEBUG_VECT__STRUCT_H_
