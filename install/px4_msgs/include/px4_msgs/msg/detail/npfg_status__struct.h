// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/NpfgStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__NPFG_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__NPFG_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/NpfgStatus in the package px4_msgs.
typedef struct px4_msgs__msg__NpfgStatus
{
  uint64_t timestamp;
  uint8_t wind_est_valid;
  float lat_accel;
  float lat_accel_ff;
  float bearing_feas;
  float bearing_feas_on_track;
  float signed_track_error;
  float track_error_bound;
  float airspeed_ref;
  float bearing;
  float heading_ref;
  float min_ground_speed_ref;
  float adapted_period;
  float p_gain;
  float time_const;
} px4_msgs__msg__NpfgStatus;

// Struct for a sequence of px4_msgs__msg__NpfgStatus.
typedef struct px4_msgs__msg__NpfgStatus__Sequence
{
  px4_msgs__msg__NpfgStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__NpfgStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__NPFG_STATUS__STRUCT_H_
