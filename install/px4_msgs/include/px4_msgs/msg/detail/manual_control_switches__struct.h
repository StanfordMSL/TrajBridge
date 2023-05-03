// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ManualControlSwitches.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MANUAL_CONTROL_SWITCHES__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__MANUAL_CONTROL_SWITCHES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'SWITCH_POS_NONE'.
enum
{
  px4_msgs__msg__ManualControlSwitches__SWITCH_POS_NONE = 0
};

/// Constant 'SWITCH_POS_ON'.
enum
{
  px4_msgs__msg__ManualControlSwitches__SWITCH_POS_ON = 1
};

/// Constant 'SWITCH_POS_MIDDLE'.
enum
{
  px4_msgs__msg__ManualControlSwitches__SWITCH_POS_MIDDLE = 2
};

/// Constant 'SWITCH_POS_OFF'.
enum
{
  px4_msgs__msg__ManualControlSwitches__SWITCH_POS_OFF = 3
};

/// Constant 'MODE_SLOT_NONE'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_NONE = 0
};

/// Constant 'MODE_SLOT_1'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_1 = 1
};

/// Constant 'MODE_SLOT_2'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_2 = 2
};

/// Constant 'MODE_SLOT_3'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_3 = 3
};

/// Constant 'MODE_SLOT_4'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_4 = 4
};

/// Constant 'MODE_SLOT_5'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_5 = 5
};

/// Constant 'MODE_SLOT_6'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_6 = 6
};

/// Constant 'MODE_SLOT_NUM'.
enum
{
  px4_msgs__msg__ManualControlSwitches__MODE_SLOT_NUM = 6
};

// Struct defined in msg/ManualControlSwitches in the package px4_msgs.
typedef struct px4_msgs__msg__ManualControlSwitches
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  uint8_t mode_slot;
  uint8_t arm_switch;
  uint8_t return_switch;
  uint8_t loiter_switch;
  uint8_t offboard_switch;
  uint8_t kill_switch;
  uint8_t gear_switch;
  uint8_t transition_switch;
  uint8_t photo_switch;
  uint8_t video_switch;
  uint8_t engage_main_motor_switch;
  uint32_t switch_changes;
} px4_msgs__msg__ManualControlSwitches;

// Struct for a sequence of px4_msgs__msg__ManualControlSwitches.
typedef struct px4_msgs__msg__ManualControlSwitches__Sequence
{
  px4_msgs__msg__ManualControlSwitches * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ManualControlSwitches__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__MANUAL_CONTROL_SWITCHES__STRUCT_H_
