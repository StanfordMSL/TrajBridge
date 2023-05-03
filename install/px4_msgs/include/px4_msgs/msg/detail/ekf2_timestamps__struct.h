// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/Ekf2Timestamps.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__EKF2_TIMESTAMPS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__EKF2_TIMESTAMPS__STRUCT_H_

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
  px4_msgs__msg__Ekf2Timestamps__RELATIVE_TIMESTAMP_INVALID = 32767
};

// Struct defined in msg/Ekf2Timestamps in the package px4_msgs.
typedef struct px4_msgs__msg__Ekf2Timestamps
{
  uint64_t timestamp;
  int16_t airspeed_timestamp_rel;
  int16_t distance_sensor_timestamp_rel;
  int16_t optical_flow_timestamp_rel;
  int16_t vehicle_air_data_timestamp_rel;
  int16_t vehicle_magnetometer_timestamp_rel;
  int16_t visual_odometry_timestamp_rel;
} px4_msgs__msg__Ekf2Timestamps;

// Struct for a sequence of px4_msgs__msg__Ekf2Timestamps.
typedef struct px4_msgs__msg__Ekf2Timestamps__Sequence
{
  px4_msgs__msg__Ekf2Timestamps * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__Ekf2Timestamps__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__EKF2_TIMESTAMPS__STRUCT_H_
