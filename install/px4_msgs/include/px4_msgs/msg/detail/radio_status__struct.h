// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/RadioStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__RADIO_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__RADIO_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/RadioStatus in the package px4_msgs.
typedef struct px4_msgs__msg__RadioStatus
{
  uint64_t timestamp;
  uint8_t rssi;
  uint8_t remote_rssi;
  uint8_t txbuf;
  uint8_t noise;
  uint8_t remote_noise;
  uint16_t rxerrors;
  uint16_t fix;
} px4_msgs__msg__RadioStatus;

// Struct for a sequence of px4_msgs__msg__RadioStatus.
typedef struct px4_msgs__msg__RadioStatus__Sequence
{
  px4_msgs__msg__RadioStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__RadioStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__RADIO_STATUS__STRUCT_H_
