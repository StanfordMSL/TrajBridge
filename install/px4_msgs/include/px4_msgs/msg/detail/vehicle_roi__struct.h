// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleRoi.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_ROI__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_ROI__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ROI_NONE'.
enum
{
  px4_msgs__msg__VehicleRoi__ROI_NONE = 0
};

/// Constant 'ROI_WPNEXT'.
enum
{
  px4_msgs__msg__VehicleRoi__ROI_WPNEXT = 1
};

/// Constant 'ROI_WPINDEX'.
enum
{
  px4_msgs__msg__VehicleRoi__ROI_WPINDEX = 2
};

/// Constant 'ROI_LOCATION'.
enum
{
  px4_msgs__msg__VehicleRoi__ROI_LOCATION = 3
};

/// Constant 'ROI_TARGET'.
enum
{
  px4_msgs__msg__VehicleRoi__ROI_TARGET = 4
};

/// Constant 'ROI_ENUM_END'.
enum
{
  px4_msgs__msg__VehicleRoi__ROI_ENUM_END = 5
};

// Struct defined in msg/VehicleRoi in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleRoi
{
  uint64_t timestamp;
  uint8_t mode;
  double lat;
  double lon;
  float alt;
  float roll_offset;
  float pitch_offset;
  float yaw_offset;
} px4_msgs__msg__VehicleRoi;

// Struct for a sequence of px4_msgs__msg__VehicleRoi.
typedef struct px4_msgs__msg__VehicleRoi__Sequence
{
  px4_msgs__msg__VehicleRoi * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleRoi__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_ROI__STRUCT_H_
