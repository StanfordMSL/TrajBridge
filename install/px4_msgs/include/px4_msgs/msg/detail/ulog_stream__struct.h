// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/UlogStream.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ULOG_STREAM__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ULOG_STREAM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'FLAGS_NEED_ACK'.
enum
{
  px4_msgs__msg__UlogStream__FLAGS_NEED_ACK = 1
};

/// Constant 'ORB_QUEUE_LENGTH'.
enum
{
  px4_msgs__msg__UlogStream__ORB_QUEUE_LENGTH = 16
};

// Struct defined in msg/UlogStream in the package px4_msgs.
typedef struct px4_msgs__msg__UlogStream
{
  uint64_t timestamp;
  uint8_t length;
  uint8_t first_message_offset;
  uint16_t msg_sequence;
  uint8_t flags;
  uint8_t data[249];
} px4_msgs__msg__UlogStream;

// Struct for a sequence of px4_msgs__msg__UlogStream.
typedef struct px4_msgs__msg__UlogStream__Sequence
{
  px4_msgs__msg__UlogStream * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__UlogStream__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ULOG_STREAM__STRUCT_H_
