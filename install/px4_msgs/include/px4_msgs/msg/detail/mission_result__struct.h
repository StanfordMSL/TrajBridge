// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/MissionResult.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MISSION_RESULT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__MISSION_RESULT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MISSION_EXECUTION_MODE_NORMAL'.
enum
{
  px4_msgs__msg__MissionResult__MISSION_EXECUTION_MODE_NORMAL = 0
};

/// Constant 'MISSION_EXECUTION_MODE_REVERSE'.
enum
{
  px4_msgs__msg__MissionResult__MISSION_EXECUTION_MODE_REVERSE = 1
};

/// Constant 'MISSION_EXECUTION_MODE_FAST_FORWARD'.
enum
{
  px4_msgs__msg__MissionResult__MISSION_EXECUTION_MODE_FAST_FORWARD = 2
};

// Struct defined in msg/MissionResult in the package px4_msgs.
typedef struct px4_msgs__msg__MissionResult
{
  uint64_t timestamp;
  uint32_t instance_count;
  int32_t seq_reached;
  uint16_t seq_current;
  uint16_t seq_total;
  bool valid;
  bool warning;
  bool finished;
  bool failure;
  bool item_do_jump_changed;
  uint16_t item_changed_index;
  uint16_t item_do_jump_remaining;
  uint8_t execution_mode;
} px4_msgs__msg__MissionResult;

// Struct for a sequence of px4_msgs__msg__MissionResult.
typedef struct px4_msgs__msg__MissionResult__Sequence
{
  px4_msgs__msg__MissionResult * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__MissionResult__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__MISSION_RESULT__STRUCT_H_
