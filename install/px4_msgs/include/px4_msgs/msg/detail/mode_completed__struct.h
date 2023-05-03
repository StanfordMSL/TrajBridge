// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ModeCompleted.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MODE_COMPLETED__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__MODE_COMPLETED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'RESULT_SUCCESS'.
enum
{
  px4_msgs__msg__ModeCompleted__RESULT_SUCCESS = 0
};

/// Constant 'RESULT_FAILURE_OTHER'.
enum
{
  px4_msgs__msg__ModeCompleted__RESULT_FAILURE_OTHER = 100
};

// Struct defined in msg/ModeCompleted in the package px4_msgs.
typedef struct px4_msgs__msg__ModeCompleted
{
  uint64_t timestamp;
  uint8_t result;
  uint8_t nav_state;
} px4_msgs__msg__ModeCompleted;

// Struct for a sequence of px4_msgs__msg__ModeCompleted.
typedef struct px4_msgs__msg__ModeCompleted__Sequence
{
  px4_msgs__msg__ModeCompleted * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ModeCompleted__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__MODE_COMPLETED__STRUCT_H_
