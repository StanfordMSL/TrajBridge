// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/SensorGnssRelative.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RELATIVE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RELATIVE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/SensorGnssRelative in the package px4_msgs.
typedef struct px4_msgs__msg__SensorGnssRelative
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  uint32_t device_id;
  uint64_t time_utc_usec;
  uint16_t reference_station_id;
  float position[3];
  float position_accuracy[3];
  float heading;
  float heading_accuracy;
  float position_length;
  float accuracy_length;
  bool gnss_fix_ok;
  bool differential_solution;
  bool relative_position_valid;
  bool carrier_solution_floating;
  bool carrier_solution_fixed;
  bool moving_base_mode;
  bool reference_position_miss;
  bool reference_observations_miss;
  bool heading_valid;
  bool relative_position_normalized;
} px4_msgs__msg__SensorGnssRelative;

// Struct for a sequence of px4_msgs__msg__SensorGnssRelative.
typedef struct px4_msgs__msg__SensorGnssRelative__Sequence
{
  px4_msgs__msg__SensorGnssRelative * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__SensorGnssRelative__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SENSOR_GNSS_RELATIVE__STRUCT_H_
