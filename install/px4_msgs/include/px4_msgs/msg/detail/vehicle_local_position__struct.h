// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleLocalPosition.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_LOCAL_POSITION__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_LOCAL_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'DIST_BOTTOM_SENSOR_NONE'.
enum
{
  px4_msgs__msg__VehicleLocalPosition__DIST_BOTTOM_SENSOR_NONE = 0
};

/// Constant 'DIST_BOTTOM_SENSOR_RANGE'.
enum
{
  px4_msgs__msg__VehicleLocalPosition__DIST_BOTTOM_SENSOR_RANGE = 1
};

/// Constant 'DIST_BOTTOM_SENSOR_FLOW'.
enum
{
  px4_msgs__msg__VehicleLocalPosition__DIST_BOTTOM_SENSOR_FLOW = 2
};

// Struct defined in msg/VehicleLocalPosition in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleLocalPosition
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  bool xy_valid;
  bool z_valid;
  bool v_xy_valid;
  bool v_z_valid;
  float x;
  float y;
  float z;
  float delta_xy[2];
  uint8_t xy_reset_counter;
  float delta_z;
  uint8_t z_reset_counter;
  float vx;
  float vy;
  float vz;
  float z_deriv;
  float delta_vxy[2];
  uint8_t vxy_reset_counter;
  float delta_vz;
  uint8_t vz_reset_counter;
  float ax;
  float ay;
  float az;
  float heading;
  float delta_heading;
  uint8_t heading_reset_counter;
  bool heading_good_for_control;
  bool xy_global;
  bool z_global;
  uint64_t ref_timestamp;
  double ref_lat;
  double ref_lon;
  float ref_alt;
  float dist_bottom;
  bool dist_bottom_valid;
  uint8_t dist_bottom_sensor_bitfield;
  float eph;
  float epv;
  float evh;
  float evv;
  bool dead_reckoning;
  float vxy_max;
  float vz_max;
  float hagl_min;
  float hagl_max;
} px4_msgs__msg__VehicleLocalPosition;

// Struct for a sequence of px4_msgs__msg__VehicleLocalPosition.
typedef struct px4_msgs__msg__VehicleLocalPosition__Sequence
{
  px4_msgs__msg__VehicleLocalPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleLocalPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_LOCAL_POSITION__STRUCT_H_
