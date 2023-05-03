// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/EstimatorSensorBias.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESTIMATOR_SENSOR_BIAS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ESTIMATOR_SENSOR_BIAS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/EstimatorSensorBias in the package px4_msgs.
typedef struct px4_msgs__msg__EstimatorSensorBias
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  uint32_t gyro_device_id;
  float gyro_bias[3];
  float gyro_bias_limit;
  float gyro_bias_variance[3];
  bool gyro_bias_valid;
  bool gyro_bias_stable;
  uint32_t accel_device_id;
  float accel_bias[3];
  float accel_bias_limit;
  float accel_bias_variance[3];
  bool accel_bias_valid;
  bool accel_bias_stable;
  uint32_t mag_device_id;
  float mag_bias[3];
  float mag_bias_limit;
  float mag_bias_variance[3];
  bool mag_bias_valid;
  bool mag_bias_stable;
} px4_msgs__msg__EstimatorSensorBias;

// Struct for a sequence of px4_msgs__msg__EstimatorSensorBias.
typedef struct px4_msgs__msg__EstimatorSensorBias__Sequence
{
  px4_msgs__msg__EstimatorSensorBias * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__EstimatorSensorBias__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ESTIMATOR_SENSOR_BIAS__STRUCT_H_
