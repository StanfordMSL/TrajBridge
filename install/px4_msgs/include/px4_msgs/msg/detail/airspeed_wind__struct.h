// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/AirspeedWind.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__AIRSPEED_WIND__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__AIRSPEED_WIND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'SOURCE_AS_BETA_ONLY'.
enum
{
  px4_msgs__msg__AirspeedWind__SOURCE_AS_BETA_ONLY = 0
};

/// Constant 'SOURCE_AS_SENSOR_1'.
enum
{
  px4_msgs__msg__AirspeedWind__SOURCE_AS_SENSOR_1 = 1
};

/// Constant 'SOURCE_AS_SENSOR_2'.
enum
{
  px4_msgs__msg__AirspeedWind__SOURCE_AS_SENSOR_2 = 2
};

/// Constant 'SOURCE_AS_SENSOR_3'.
enum
{
  px4_msgs__msg__AirspeedWind__SOURCE_AS_SENSOR_3 = 3
};

// Struct defined in msg/AirspeedWind in the package px4_msgs.
typedef struct px4_msgs__msg__AirspeedWind
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  float windspeed_north;
  float windspeed_east;
  float variance_north;
  float variance_east;
  float tas_innov;
  float tas_innov_var;
  float tas_scale_raw;
  float tas_scale_raw_var;
  float tas_scale_validated;
  float beta_innov;
  float beta_innov_var;
  uint8_t source;
} px4_msgs__msg__AirspeedWind;

// Struct for a sequence of px4_msgs__msg__AirspeedWind.
typedef struct px4_msgs__msg__AirspeedWind__Sequence
{
  px4_msgs__msg__AirspeedWind * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__AirspeedWind__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__AIRSPEED_WIND__STRUCT_H_
