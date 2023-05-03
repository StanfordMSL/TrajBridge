// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleLocalPositionSetpoint.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_LOCAL_POSITION_SETPOINT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_LOCAL_POSITION_SETPOINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/VehicleLocalPositionSetpoint in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleLocalPositionSetpoint
{
  uint64_t timestamp;
  float x;
  float y;
  float z;
  float vx;
  float vy;
  float vz;
  float acceleration[3];
  float thrust[3];
  float yaw;
  float yawspeed;
} px4_msgs__msg__VehicleLocalPositionSetpoint;

// Struct for a sequence of px4_msgs__msg__VehicleLocalPositionSetpoint.
typedef struct px4_msgs__msg__VehicleLocalPositionSetpoint__Sequence
{
  px4_msgs__msg__VehicleLocalPositionSetpoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleLocalPositionSetpoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_LOCAL_POSITION_SETPOINT__STRUCT_H_
