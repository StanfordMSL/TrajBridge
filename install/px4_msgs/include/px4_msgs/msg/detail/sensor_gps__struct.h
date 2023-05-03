// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorGps.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GPS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GPS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'JAMMING_STATE_UNKNOWN'.
enum
{
  px4_msgs__msg__SensorGps__JAMMING_STATE_UNKNOWN = 0
};

/// Constant 'JAMMING_STATE_OK'.
enum
{
  px4_msgs__msg__SensorGps__JAMMING_STATE_OK = 1
};

/// Constant 'JAMMING_STATE_WARNING'.
enum
{
  px4_msgs__msg__SensorGps__JAMMING_STATE_WARNING = 2
};

/// Constant 'JAMMING_STATE_CRITICAL'.
enum
{
  px4_msgs__msg__SensorGps__JAMMING_STATE_CRITICAL = 3
};

/// Constant 'SPOOFING_STATE_UNKNOWN'.
enum
{
  px4_msgs__msg__SensorGps__SPOOFING_STATE_UNKNOWN = 0
};

/// Constant 'SPOOFING_STATE_NONE'.
enum
{
  px4_msgs__msg__SensorGps__SPOOFING_STATE_NONE = 1
};

/// Constant 'SPOOFING_STATE_INDICATED'.
enum
{
  px4_msgs__msg__SensorGps__SPOOFING_STATE_INDICATED = 2
};

/// Constant 'SPOOFING_STATE_MULTIPLE'.
enum
{
  px4_msgs__msg__SensorGps__SPOOFING_STATE_MULTIPLE = 3
};

// Struct defined in msg/SensorGps in the package px4_msgs.
typedef struct px4_msgs__msg__SensorGps
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  uint32_t device_id;
  int32_t lat;
  int32_t lon;
  int32_t alt;
  int32_t alt_ellipsoid;
  float s_variance_m_s;
  float c_variance_rad;
  uint8_t fix_type;
  float eph;
  float epv;
  float hdop;
  float vdop;
  int32_t noise_per_ms;
  uint16_t automatic_gain_control;
  uint8_t jamming_state;
  int32_t jamming_indicator;
  uint8_t spoofing_state;
  float vel_m_s;
  float vel_n_m_s;
  float vel_e_m_s;
  float vel_d_m_s;
  float cog_rad;
  bool vel_ned_valid;
  int32_t timestamp_time_relative;
  uint64_t time_utc_usec;
  uint8_t satellites_used;
  float heading;
  float heading_offset;
  float heading_accuracy;
  float rtcm_injection_rate;
  uint8_t selected_rtcm_instance;
} px4_msgs__msg__SensorGps;

// Struct for a sequence of px4_msgs__msg__SensorGps.
typedef struct px4_msgs__msg__SensorGps__Sequence
{
  px4_msgs__msg__SensorGps * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorGps__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GPS__STRUCT_H_
