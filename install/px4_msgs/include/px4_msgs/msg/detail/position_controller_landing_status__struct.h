// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/PositionControllerLandingStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__POSITION_CONTROLLER_LANDING_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__POSITION_CONTROLLER_LANDING_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'NOT_ABORTED'.
enum
{
  px4_msgs__msg__PositionControllerLandingStatus__NOT_ABORTED = 0
};

/// Constant 'ABORTED_BY_OPERATOR'.
enum
{
  px4_msgs__msg__PositionControllerLandingStatus__ABORTED_BY_OPERATOR = 1
};

/// Constant 'TERRAIN_NOT_FOUND'.
enum
{
  px4_msgs__msg__PositionControllerLandingStatus__TERRAIN_NOT_FOUND = 2
};

/// Constant 'TERRAIN_TIMEOUT'.
enum
{
  px4_msgs__msg__PositionControllerLandingStatus__TERRAIN_TIMEOUT = 3
};

/// Constant 'UNKNOWN_ABORT_CRITERION'.
enum
{
  px4_msgs__msg__PositionControllerLandingStatus__UNKNOWN_ABORT_CRITERION = 4
};

// Struct defined in msg/PositionControllerLandingStatus in the package px4_msgs.
typedef struct px4_msgs__msg__PositionControllerLandingStatus
{
  uint64_t timestamp;
  float lateral_touchdown_offset;
  bool flaring;
  uint8_t abort_status;
} px4_msgs__msg__PositionControllerLandingStatus;

// Struct for a sequence of px4_msgs__msg__PositionControllerLandingStatus.
typedef struct px4_msgs__msg__PositionControllerLandingStatus__Sequence
{
  px4_msgs__msg__PositionControllerLandingStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__PositionControllerLandingStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__POSITION_CONTROLLER_LANDING_STATUS__STRUCT_H_
