// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleCommandAck.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_COMMAND_ACK__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_COMMAND_ACK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'VEHICLE_CMD_RESULT_ACCEPTED'.
enum
{
  px4_msgs__msg__VehicleCommandAck__VEHICLE_CMD_RESULT_ACCEPTED = 0
};

/// Constant 'VEHICLE_CMD_RESULT_TEMPORARILY_REJECTED'.
enum
{
  px4_msgs__msg__VehicleCommandAck__VEHICLE_CMD_RESULT_TEMPORARILY_REJECTED = 1
};

/// Constant 'VEHICLE_CMD_RESULT_DENIED'.
enum
{
  px4_msgs__msg__VehicleCommandAck__VEHICLE_CMD_RESULT_DENIED = 2
};

/// Constant 'VEHICLE_CMD_RESULT_UNSUPPORTED'.
enum
{
  px4_msgs__msg__VehicleCommandAck__VEHICLE_CMD_RESULT_UNSUPPORTED = 3
};

/// Constant 'VEHICLE_CMD_RESULT_FAILED'.
enum
{
  px4_msgs__msg__VehicleCommandAck__VEHICLE_CMD_RESULT_FAILED = 4
};

/// Constant 'VEHICLE_CMD_RESULT_IN_PROGRESS'.
enum
{
  px4_msgs__msg__VehicleCommandAck__VEHICLE_CMD_RESULT_IN_PROGRESS = 5
};

/// Constant 'VEHICLE_CMD_RESULT_CANCELLED'.
enum
{
  px4_msgs__msg__VehicleCommandAck__VEHICLE_CMD_RESULT_CANCELLED = 6
};

/// Constant 'ARM_AUTH_DENIED_REASON_GENERIC'.
enum
{
  px4_msgs__msg__VehicleCommandAck__ARM_AUTH_DENIED_REASON_GENERIC = 0
};

/// Constant 'ARM_AUTH_DENIED_REASON_NONE'.
enum
{
  px4_msgs__msg__VehicleCommandAck__ARM_AUTH_DENIED_REASON_NONE = 1
};

/// Constant 'ARM_AUTH_DENIED_REASON_INVALID_WAYPOINT'.
enum
{
  px4_msgs__msg__VehicleCommandAck__ARM_AUTH_DENIED_REASON_INVALID_WAYPOINT = 2
};

/// Constant 'ARM_AUTH_DENIED_REASON_TIMEOUT'.
enum
{
  px4_msgs__msg__VehicleCommandAck__ARM_AUTH_DENIED_REASON_TIMEOUT = 3
};

/// Constant 'ARM_AUTH_DENIED_REASON_AIRSPACE_IN_USE'.
enum
{
  px4_msgs__msg__VehicleCommandAck__ARM_AUTH_DENIED_REASON_AIRSPACE_IN_USE = 4
};

/// Constant 'ARM_AUTH_DENIED_REASON_BAD_WEATHER'.
enum
{
  px4_msgs__msg__VehicleCommandAck__ARM_AUTH_DENIED_REASON_BAD_WEATHER = 5
};

/// Constant 'ORB_QUEUE_LENGTH'.
enum
{
  px4_msgs__msg__VehicleCommandAck__ORB_QUEUE_LENGTH = 4
};

// Struct defined in msg/VehicleCommandAck in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleCommandAck
{
  uint64_t timestamp;
  uint32_t command;
  uint8_t result;
  uint8_t result_param1;
  int32_t result_param2;
  uint8_t target_system;
  uint8_t target_component;
  bool from_external;
} px4_msgs__msg__VehicleCommandAck;

// Struct for a sequence of px4_msgs__msg__VehicleCommandAck.
typedef struct px4_msgs__msg__VehicleCommandAck__Sequence
{
  px4_msgs__msg__VehicleCommandAck * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleCommandAck__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_COMMAND_ACK__STRUCT_H_
