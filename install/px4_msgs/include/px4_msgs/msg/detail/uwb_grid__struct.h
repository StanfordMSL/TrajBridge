// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/UwbGrid.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__UWB_GRID__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__UWB_GRID__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/UwbGrid in the package px4_msgs.
typedef struct px4_msgs__msg__UwbGrid
{
  uint64_t timestamp;
  uint16_t initator_time;
  uint8_t num_anchors;
  double target_gps[4];
  int16_t target_pos[3];
  int16_t anchor_pos_0[3];
  int16_t anchor_pos_1[3];
  int16_t anchor_pos_2[3];
  int16_t anchor_pos_3[3];
  int16_t anchor_pos_4[3];
  int16_t anchor_pos_5[3];
  int16_t anchor_pos_6[3];
  int16_t anchor_pos_7[3];
  int16_t anchor_pos_8[3];
  int16_t anchor_pos_9[3];
  int16_t anchor_pos_10[3];
  int16_t anchor_pos_11[3];
} px4_msgs__msg__UwbGrid;

// Struct for a sequence of px4_msgs__msg__UwbGrid.
typedef struct px4_msgs__msg__UwbGrid__Sequence
{
  px4_msgs__msg__UwbGrid * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__UwbGrid__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__UWB_GRID__STRUCT_H_
