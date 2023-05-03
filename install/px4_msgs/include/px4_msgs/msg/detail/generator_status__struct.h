// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/GeneratorStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__GENERATOR_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__GENERATOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATUS_FLAG_OFF'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_OFF = 1ull
};

/// Constant 'STATUS_FLAG_READY'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_READY = 2ull
};

/// Constant 'STATUS_FLAG_GENERATING'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_GENERATING = 4ull
};

/// Constant 'STATUS_FLAG_CHARGING'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_CHARGING = 8ull
};

/// Constant 'STATUS_FLAG_REDUCED_POWER'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_REDUCED_POWER = 16ull
};

/// Constant 'STATUS_FLAG_MAXPOWER'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_MAXPOWER = 32ull
};

/// Constant 'STATUS_FLAG_OVERTEMP_WARNING'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_OVERTEMP_WARNING = 64ull
};

/// Constant 'STATUS_FLAG_OVERTEMP_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_OVERTEMP_FAULT = 128ull
};

/// Constant 'STATUS_FLAG_ELECTRONICS_OVERTEMP_WARNING'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_ELECTRONICS_OVERTEMP_WARNING = 256ull
};

/// Constant 'STATUS_FLAG_ELECTRONICS_OVERTEMP_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_ELECTRONICS_OVERTEMP_FAULT = 512ull
};

/// Constant 'STATUS_FLAG_ELECTRONICS_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_ELECTRONICS_FAULT = 1024ull
};

/// Constant 'STATUS_FLAG_POWERSOURCE_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_POWERSOURCE_FAULT = 2048ull
};

/// Constant 'STATUS_FLAG_COMMUNICATION_WARNING'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_COMMUNICATION_WARNING = 4096ull
};

/// Constant 'STATUS_FLAG_COOLING_WARNING'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_COOLING_WARNING = 8192ull
};

/// Constant 'STATUS_FLAG_POWER_RAIL_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_POWER_RAIL_FAULT = 16384ull
};

/// Constant 'STATUS_FLAG_OVERCURRENT_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_OVERCURRENT_FAULT = 32768ull
};

/// Constant 'STATUS_FLAG_BATTERY_OVERCHARGE_CURRENT_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_BATTERY_OVERCHARGE_CURRENT_FAULT = 65536ull
};

/// Constant 'STATUS_FLAG_OVERVOLTAGE_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_OVERVOLTAGE_FAULT = 131072ull
};

/// Constant 'STATUS_FLAG_BATTERY_UNDERVOLT_FAULT'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_BATTERY_UNDERVOLT_FAULT = 262144ull
};

/// Constant 'STATUS_FLAG_START_INHIBITED'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_START_INHIBITED = 524288ull
};

/// Constant 'STATUS_FLAG_MAINTENANCE_REQUIRED'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_MAINTENANCE_REQUIRED = 1048576ull
};

/// Constant 'STATUS_FLAG_WARMING_UP'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_WARMING_UP = 2097152ull
};

/// Constant 'STATUS_FLAG_IDLE'.
enum
{
  px4_msgs__msg__GeneratorStatus__STATUS_FLAG_IDLE = 4194304ull
};

// Struct defined in msg/GeneratorStatus in the package px4_msgs.
typedef struct px4_msgs__msg__GeneratorStatus
{
  uint64_t timestamp;
  uint64_t status;
  float battery_current;
  float load_current;
  float power_generated;
  float bus_voltage;
  float bat_current_setpoint;
  uint32_t runtime;
  int32_t time_until_maintenance;
  uint16_t generator_speed;
  int16_t rectifier_temperature;
  int16_t generator_temperature;
} px4_msgs__msg__GeneratorStatus;

// Struct for a sequence of px4_msgs__msg__GeneratorStatus.
typedef struct px4_msgs__msg__GeneratorStatus__Sequence
{
  px4_msgs__msg__GeneratorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__GeneratorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__GENERATOR_STATUS__STRUCT_H_
