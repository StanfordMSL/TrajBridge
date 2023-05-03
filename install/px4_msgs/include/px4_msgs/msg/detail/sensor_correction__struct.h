// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorCorrection.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_CORRECTION__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_CORRECTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/SensorCorrection in the package px4_msgs.
typedef struct px4_msgs__msg__SensorCorrection
{
  uint64_t timestamp;
  uint32_t gyro_device_ids[4];
  float gyro_temperature[4];
  float gyro_offset_0[3];
  float gyro_offset_1[3];
  float gyro_offset_2[3];
  float gyro_offset_3[3];
  uint32_t accel_device_ids[4];
  float accel_temperature[4];
  float accel_offset_0[3];
  float accel_offset_1[3];
  float accel_offset_2[3];
  float accel_offset_3[3];
  uint32_t baro_device_ids[4];
  float baro_temperature[4];
  float baro_offset_0;
  float baro_offset_1;
  float baro_offset_2;
  float baro_offset_3;
} px4_msgs__msg__SensorCorrection;

// Struct for a sequence of px4_msgs__msg__SensorCorrection.
typedef struct px4_msgs__msg__SensorCorrection__Sequence
{
  px4_msgs__msg__SensorCorrection * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorCorrection__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_CORRECTION__STRUCT_H_
