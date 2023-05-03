// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/TecsStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__TECS_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__TECS_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'TECS_MODE_NORMAL'.
enum
{
  px4_msgs__msg__TecsStatus__TECS_MODE_NORMAL = 0
};

/// Constant 'TECS_MODE_UNDERSPEED'.
enum
{
  px4_msgs__msg__TecsStatus__TECS_MODE_UNDERSPEED = 1
};

// Struct defined in msg/TecsStatus in the package px4_msgs.
typedef struct px4_msgs__msg__TecsStatus
{
  uint64_t timestamp;
  float altitude_sp;
  float altitude_reference;
  float height_rate_reference;
  float height_rate_direct;
  float height_rate_setpoint;
  float height_rate;
  float equivalent_airspeed_sp;
  float true_airspeed_sp;
  float true_airspeed_filtered;
  float true_airspeed_derivative_sp;
  float true_airspeed_derivative;
  float true_airspeed_derivative_raw;
  float total_energy_rate_sp;
  float total_energy_rate;
  float total_energy_balance_rate_sp;
  float total_energy_balance_rate;
  float throttle_integ;
  float pitch_integ;
  float throttle_sp;
  float pitch_sp_rad;
  float throttle_trim;
  uint8_t mode;
} px4_msgs__msg__TecsStatus;

// Struct for a sequence of px4_msgs__msg__TecsStatus.
typedef struct px4_msgs__msg__TecsStatus__Sequence
{
  px4_msgs__msg__TecsStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__TecsStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__TECS_STATUS__STRUCT_H_
