// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/Ping.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__PING__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__PING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Ping in the package px4_msgs.
typedef struct px4_msgs__msg__Ping
{
  uint64_t timestamp;
  uint64_t ping_time;
  uint32_t ping_sequence;
  uint32_t dropped_packets;
  float rtt_ms;
  uint8_t system_id;
  uint8_t component_id;
} px4_msgs__msg__Ping;

// Struct for a sequence of px4_msgs__msg__Ping.
typedef struct px4_msgs__msg__Ping__Sequence
{
  px4_msgs__msg__Ping * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__Ping__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__PING__STRUCT_H_
