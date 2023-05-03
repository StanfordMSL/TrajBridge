// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorBaro.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_BARO__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_BARO__STRUCT_H_

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
  px4_msgs__msg__SensorBaro__ORB_QUEUE_LENGTH = 4
};

// Struct defined in msg/SensorBaro in the package px4_msgs.
typedef struct px4_msgs__msg__SensorBaro
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  uint32_t device_id;
  float pressure;
  float temperature;
  uint32_t error_count;
} px4_msgs__msg__SensorBaro;

// Struct for a sequence of px4_msgs__msg__SensorBaro.
typedef struct px4_msgs__msg__SensorBaro__Sequence
{
  px4_msgs__msg__SensorBaro * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorBaro__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_BARO__STRUCT_H_
