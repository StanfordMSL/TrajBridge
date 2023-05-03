// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleImuStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_IMU_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_IMU_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/VehicleImuStatus in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleImuStatus
{
  uint64_t timestamp;
  uint32_t accel_device_id;
  uint32_t gyro_device_id;
  uint32_t accel_clipping[3];
  uint32_t gyro_clipping[3];
  uint32_t accel_error_count;
  uint32_t gyro_error_count;
  float accel_rate_hz;
  float gyro_rate_hz;
  float accel_raw_rate_hz;
  float gyro_raw_rate_hz;
  float accel_vibration_metric;
  float gyro_vibration_metric;
  float delta_angle_coning_metric;
  float mean_accel[3];
  float mean_gyro[3];
  float var_accel[3];
  float var_gyro[3];
  float temperature_accel;
  float temperature_gyro;
} px4_msgs__msg__VehicleImuStatus;

// Struct for a sequence of px4_msgs__msg__VehicleImuStatus.
typedef struct px4_msgs__msg__VehicleImuStatus__Sequence
{
  px4_msgs__msg__VehicleImuStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleImuStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_IMU_STATUS__STRUCT_H_
