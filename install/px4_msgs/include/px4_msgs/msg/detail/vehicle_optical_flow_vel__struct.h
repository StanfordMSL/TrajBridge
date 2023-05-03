// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleOpticalFlowVel.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_OPTICAL_FLOW_VEL__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_OPTICAL_FLOW_VEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/VehicleOpticalFlowVel in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleOpticalFlowVel
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  float vel_body[2];
  float vel_ne[2];
  float flow_uncompensated_integral[2];
  float flow_compensated_integral[2];
  float gyro_rate[3];
  float gyro_rate_integral[3];
} px4_msgs__msg__VehicleOpticalFlowVel;

// Struct for a sequence of px4_msgs__msg__VehicleOpticalFlowVel.
typedef struct px4_msgs__msg__VehicleOpticalFlowVel__Sequence
{
  px4_msgs__msg__VehicleOpticalFlowVel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleOpticalFlowVel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_OPTICAL_FLOW_VEL__STRUCT_H_
