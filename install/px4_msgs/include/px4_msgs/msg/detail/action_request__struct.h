// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ActionRequest.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ACTION_REQUEST__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ACTION_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ACTION_DISARM'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_DISARM = 0
};

/// Constant 'ACTION_ARM'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_ARM = 1
};

/// Constant 'ACTION_TOGGLE_ARMING'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_TOGGLE_ARMING = 2
};

/// Constant 'ACTION_UNKILL'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_UNKILL = 3
};

/// Constant 'ACTION_KILL'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_KILL = 4
};

/// Constant 'ACTION_SWITCH_MODE'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_SWITCH_MODE = 5
};

/// Constant 'ACTION_VTOL_TRANSITION_TO_MULTICOPTER'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_VTOL_TRANSITION_TO_MULTICOPTER = 6
};

/// Constant 'ACTION_VTOL_TRANSITION_TO_FIXEDWING'.
enum
{
  px4_msgs__msg__ActionRequest__ACTION_VTOL_TRANSITION_TO_FIXEDWING = 7
};

/// Constant 'SOURCE_RC_STICK_GESTURE'.
enum
{
  px4_msgs__msg__ActionRequest__SOURCE_RC_STICK_GESTURE = 0
};

/// Constant 'SOURCE_RC_SWITCH'.
enum
{
  px4_msgs__msg__ActionRequest__SOURCE_RC_SWITCH = 1
};

/// Constant 'SOURCE_RC_BUTTON'.
enum
{
  px4_msgs__msg__ActionRequest__SOURCE_RC_BUTTON = 2
};

/// Constant 'SOURCE_RC_MODE_SLOT'.
enum
{
  px4_msgs__msg__ActionRequest__SOURCE_RC_MODE_SLOT = 3
};

// Struct defined in msg/ActionRequest in the package px4_msgs.
typedef struct px4_msgs__msg__ActionRequest
{
  uint64_t timestamp;
  uint8_t action;
  uint8_t source;
  uint8_t mode;
} px4_msgs__msg__ActionRequest;

// Struct for a sequence of px4_msgs__msg__ActionRequest.
typedef struct px4_msgs__msg__ActionRequest__Sequence
{
  px4_msgs__msg__ActionRequest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ActionRequest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ACTION_REQUEST__STRUCT_H_
