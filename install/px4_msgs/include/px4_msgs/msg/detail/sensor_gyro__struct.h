// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorGyro.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GYRO__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GYRO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ORB_QUEUE_LENGTH'.
enum
{
  px4_msgs__msg__SensorGyro__ORB_QUEUE_LENGTH = 8
};

// Struct defined in msg/SensorGyro in the package px4_msgs.
typedef struct px4_msgs__msg__SensorGyro
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  uint32_t device_id;
  float x;
  float y;
  float z;
  float temperature;
  uint32_t error_count;
  uint8_t clip_counter[3];
  uint8_t samples;
} px4_msgs__msg__SensorGyro;

// Struct for a sequence of px4_msgs__msg__SensorGyro.
typedef struct px4_msgs__msg__SensorGyro__Sequence
{
  px4_msgs__msg__SensorGyro * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorGyro__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GYRO__STRUCT_H_
