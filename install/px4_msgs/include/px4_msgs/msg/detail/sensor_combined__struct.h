// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorCombined.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_COMBINED__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_COMBINED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'RELATIVE_TIMESTAMP_INVALID'.
enum
{
  px4_msgs__msg__SensorCombined__RELATIVE_TIMESTAMP_INVALID = 2147483647l
};

/// Constant 'CLIPPING_X'.
enum
{
  px4_msgs__msg__SensorCombined__CLIPPING_X = 1
};

/// Constant 'CLIPPING_Y'.
enum
{
  px4_msgs__msg__SensorCombined__CLIPPING_Y = 2
};

/// Constant 'CLIPPING_Z'.
enum
{
  px4_msgs__msg__SensorCombined__CLIPPING_Z = 4
};

// Struct defined in msg/SensorCombined in the package px4_msgs.
typedef struct px4_msgs__msg__SensorCombined
{
  uint64_t timestamp;
  float gyro_rad[3];
  uint32_t gyro_integral_dt;
  int32_t accelerometer_timestamp_relative;
  float accelerometer_m_s2[3];
  uint32_t accelerometer_integral_dt;
  uint8_t accelerometer_clipping;
  uint8_t gyro_clipping;
  uint8_t accel_calibration_count;
  uint8_t gyro_calibration_count;
} px4_msgs__msg__SensorCombined;

// Struct for a sequence of px4_msgs__msg__SensorCombined.
typedef struct px4_msgs__msg__SensorCombined__Sequence
{
  px4_msgs__msg__SensorCombined * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorCombined__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_COMBINED__STRUCT_H_
