// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ManualControlSetpoint.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MANUAL_CONTROL_SETPOINT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__MANUAL_CONTROL_SETPOINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'SOURCE_UNKNOWN'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_UNKNOWN = 0
};

/// Constant 'SOURCE_RC'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_RC = 1
};

/// Constant 'SOURCE_MAVLINK_0'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_MAVLINK_0 = 2
};

/// Constant 'SOURCE_MAVLINK_1'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_MAVLINK_1 = 3
};

/// Constant 'SOURCE_MAVLINK_2'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_MAVLINK_2 = 4
};

/// Constant 'SOURCE_MAVLINK_3'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_MAVLINK_3 = 5
};

/// Constant 'SOURCE_MAVLINK_4'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_MAVLINK_4 = 6
};

/// Constant 'SOURCE_MAVLINK_5'.
enum
{
  px4_msgs__msg__ManualControlSetpoint__SOURCE_MAVLINK_5 = 7
};

// Struct defined in msg/ManualControlSetpoint in the package px4_msgs.
typedef struct px4_msgs__msg__ManualControlSetpoint
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  bool valid;
  uint8_t data_source;
  float roll;
  float pitch;
  float yaw;
  float throttle;
  float flaps;
  float aux1;
  float aux2;
  float aux3;
  float aux4;
  float aux5;
  float aux6;
  bool sticks_moving;
} px4_msgs__msg__ManualControlSetpoint;

// Struct for a sequence of px4_msgs__msg__ManualControlSetpoint.
typedef struct px4_msgs__msg__ManualControlSetpoint__Sequence
{
  px4_msgs__msg__ManualControlSetpoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ManualControlSetpoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__MANUAL_CONTROL_SETPOINT__STRUCT_H_
