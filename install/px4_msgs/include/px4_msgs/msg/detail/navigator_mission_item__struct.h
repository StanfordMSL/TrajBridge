// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/NavigatorMissionItem.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__NAVIGATOR_MISSION_ITEM__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__NAVIGATOR_MISSION_ITEM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/NavigatorMissionItem in the package px4_msgs.
typedef struct px4_msgs__msg__NavigatorMissionItem
{
  uint64_t timestamp;
  uint32_t instance_count;
  uint16_t sequence_current;
  uint16_t nav_cmd;
  float latitude;
  float longitude;
  float time_inside;
  float acceptance_radius;
  float loiter_radius;
  float yaw;
  float altitude;
  uint8_t frame;
  uint8_t origin;
  bool loiter_exit_xtrack;
  bool force_heading;
  bool altitude_is_relative;
  bool autocontinue;
  bool vtol_back_transition;
} px4_msgs__msg__NavigatorMissionItem;

// Struct for a sequence of px4_msgs__msg__NavigatorMissionItem.
typedef struct px4_msgs__msg__NavigatorMissionItem__Sequence
{
  px4_msgs__msg__NavigatorMissionItem * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__NavigatorMissionItem__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__NAVIGATOR_MISSION_ITEM__STRUCT_H_
