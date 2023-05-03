// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/LandingGear.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__LANDING_GEAR__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__LANDING_GEAR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'GEAR_UP'.
enum
{
  px4_msgs__msg__LandingGear__GEAR_UP = 1
};

/// Constant 'GEAR_DOWN'.
enum
{
  px4_msgs__msg__LandingGear__GEAR_DOWN = -1
};

/// Constant 'GEAR_KEEP'.
enum
{
  px4_msgs__msg__LandingGear__GEAR_KEEP = 0
};

// Struct defined in msg/LandingGear in the package px4_msgs.
typedef struct px4_msgs__msg__LandingGear
{
  uint64_t timestamp;
  int8_t landing_gear;
} px4_msgs__msg__LandingGear;

// Struct for a sequence of px4_msgs__msg__LandingGear.
typedef struct px4_msgs__msg__LandingGear__Sequence
{
  px4_msgs__msg__LandingGear * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__LandingGear__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__LANDING_GEAR__STRUCT_H_
