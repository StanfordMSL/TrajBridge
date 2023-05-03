// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/EscReport.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESC_REPORT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ESC_REPORT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'FAILURE_OVER_CURRENT'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_OVER_CURRENT = 0
};

/// Constant 'FAILURE_OVER_VOLTAGE'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_OVER_VOLTAGE = 1
};

/// Constant 'FAILURE_MOTOR_OVER_TEMPERATURE'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_MOTOR_OVER_TEMPERATURE = 2
};

/// Constant 'FAILURE_OVER_RPM'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_OVER_RPM = 3
};

/// Constant 'FAILURE_INCONSISTENT_CMD'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_INCONSISTENT_CMD = 4
};

/// Constant 'FAILURE_MOTOR_STUCK'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_MOTOR_STUCK = 5
};

/// Constant 'FAILURE_GENERIC'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_GENERIC = 6
};

/// Constant 'FAILURE_MOTOR_WARN_TEMPERATURE'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_MOTOR_WARN_TEMPERATURE = 7
};

/// Constant 'FAILURE_WARN_ESC_TEMPERATURE'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_WARN_ESC_TEMPERATURE = 8
};

/// Constant 'FAILURE_OVER_ESC_TEMPERATURE'.
enum
{
  px4_msgs__msg__EscReport__FAILURE_OVER_ESC_TEMPERATURE = 9
};

/// Constant 'ESC_FAILURE_COUNT'.
enum
{
  px4_msgs__msg__EscReport__ESC_FAILURE_COUNT = 10
};

// Struct defined in msg/EscReport in the package px4_msgs.
typedef struct px4_msgs__msg__EscReport
{
  uint64_t timestamp;
  uint32_t esc_errorcount;
  int32_t esc_rpm;
  float esc_voltage;
  float esc_current;
  float esc_temperature;
  uint8_t esc_address;
  uint8_t esc_cmdcount;
  uint8_t esc_state;
  uint8_t actuator_function;
  uint16_t failures;
  int8_t esc_power;
} px4_msgs__msg__EscReport;

// Struct for a sequence of px4_msgs__msg__EscReport.
typedef struct px4_msgs__msg__EscReport__Sequence
{
  px4_msgs__msg__EscReport * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__EscReport__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ESC_REPORT__STRUCT_H_
