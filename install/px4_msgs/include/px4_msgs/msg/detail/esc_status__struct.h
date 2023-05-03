// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/EscStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESC_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ESC_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'CONNECTED_ESC_MAX'.
enum
{
  px4_msgs__msg__EscStatus__CONNECTED_ESC_MAX = 8
};

/// Constant 'ESC_CONNECTION_TYPE_PPM'.
enum
{
  px4_msgs__msg__EscStatus__ESC_CONNECTION_TYPE_PPM = 0
};

/// Constant 'ESC_CONNECTION_TYPE_SERIAL'.
enum
{
  px4_msgs__msg__EscStatus__ESC_CONNECTION_TYPE_SERIAL = 1
};

/// Constant 'ESC_CONNECTION_TYPE_ONESHOT'.
enum
{
  px4_msgs__msg__EscStatus__ESC_CONNECTION_TYPE_ONESHOT = 2
};

/// Constant 'ESC_CONNECTION_TYPE_I2C'.
enum
{
  px4_msgs__msg__EscStatus__ESC_CONNECTION_TYPE_I2C = 3
};

/// Constant 'ESC_CONNECTION_TYPE_CAN'.
enum
{
  px4_msgs__msg__EscStatus__ESC_CONNECTION_TYPE_CAN = 4
};

/// Constant 'ESC_CONNECTION_TYPE_DSHOT'.
enum
{
  px4_msgs__msg__EscStatus__ESC_CONNECTION_TYPE_DSHOT = 5
};

// Include directives for member types
// Member 'esc'
#include "px4_msgs/msg/detail/esc_report__struct.h"

// Struct defined in msg/EscStatus in the package px4_msgs.
typedef struct px4_msgs__msg__EscStatus
{
  uint64_t timestamp;
  uint16_t counter;
  uint8_t esc_count;
  uint8_t esc_connectiontype;
  uint8_t esc_online_flags;
  uint8_t esc_armed_flags;
  px4_msgs__msg__EscReport esc[8];
} px4_msgs__msg__EscStatus;

// Struct for a sequence of px4_msgs__msg__EscStatus.
typedef struct px4_msgs__msg__EscStatus__Sequence
{
  px4_msgs__msg__EscStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__EscStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ESC_STATUS__STRUCT_H_
