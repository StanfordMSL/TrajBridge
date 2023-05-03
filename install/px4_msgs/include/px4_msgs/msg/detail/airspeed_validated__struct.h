// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/AirspeedValidated.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__AIRSPEED_VALIDATED__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__AIRSPEED_VALIDATED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/AirspeedValidated in the package px4_msgs.
typedef struct px4_msgs__msg__AirspeedValidated
{
  uint64_t timestamp;
  float indicated_airspeed_m_s;
  float calibrated_airspeed_m_s;
  float true_airspeed_m_s;
  float calibrated_ground_minus_wind_m_s;
  float true_ground_minus_wind_m_s;
  bool airspeed_sensor_measurement_valid;
  int8_t selected_airspeed_index;
} px4_msgs__msg__AirspeedValidated;

// Struct for a sequence of px4_msgs__msg__AirspeedValidated.
typedef struct px4_msgs__msg__AirspeedValidated__Sequence
{
  px4_msgs__msg__AirspeedValidated * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__AirspeedValidated__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__AIRSPEED_VALIDATED__STRUCT_H_
