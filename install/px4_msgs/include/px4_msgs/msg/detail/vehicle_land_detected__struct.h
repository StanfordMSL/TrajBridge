// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleLandDetected.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_LAND_DETECTED__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_LAND_DETECTED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/VehicleLandDetected in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleLandDetected
{
  uint64_t timestamp;
  bool freefall;
  bool ground_contact;
  bool maybe_landed;
  bool landed;
  bool in_ground_effect;
  bool in_descend;
  bool has_low_throttle;
  bool vertical_movement;
  bool horizontal_movement;
  bool rotational_movement;
  bool close_to_ground_or_skipped_check;
  bool at_rest;
} px4_msgs__msg__VehicleLandDetected;

// Struct for a sequence of px4_msgs__msg__VehicleLandDetected.
typedef struct px4_msgs__msg__VehicleLandDetected__Sequence
{
  px4_msgs__msg__VehicleLandDetected * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleLandDetected__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_LAND_DETECTED__STRUCT_H_
