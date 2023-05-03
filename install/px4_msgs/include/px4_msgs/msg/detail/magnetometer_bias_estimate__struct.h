// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/MagnetometerBiasEstimate.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MAGNETOMETER_BIAS_ESTIMATE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__MAGNETOMETER_BIAS_ESTIMATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/MagnetometerBiasEstimate in the package px4_msgs.
typedef struct px4_msgs__msg__MagnetometerBiasEstimate
{
  uint64_t timestamp;
  float bias_x[4];
  float bias_y[4];
  float bias_z[4];
  bool valid[4];
  bool stable[4];
} px4_msgs__msg__MagnetometerBiasEstimate;

// Struct for a sequence of px4_msgs__msg__MagnetometerBiasEstimate.
typedef struct px4_msgs__msg__MagnetometerBiasEstimate__Sequence
{
  px4_msgs__msg__MagnetometerBiasEstimate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__MagnetometerBiasEstimate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__MAGNETOMETER_BIAS_ESTIMATE__STRUCT_H_
