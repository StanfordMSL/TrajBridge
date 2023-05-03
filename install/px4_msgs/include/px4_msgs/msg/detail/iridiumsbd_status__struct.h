// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/IridiumsbdStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__IRIDIUMSBD_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__IRIDIUMSBD_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/IridiumsbdStatus in the package px4_msgs.
typedef struct px4_msgs__msg__IridiumsbdStatus
{
  uint64_t timestamp;
  uint64_t last_heartbeat;
  uint16_t tx_buf_write_index;
  uint16_t rx_buf_read_index;
  uint16_t rx_buf_end_index;
  uint16_t failed_sbd_sessions;
  uint16_t successful_sbd_sessions;
  uint16_t num_tx_buf_reset;
  uint8_t signal_quality;
  uint8_t state;
  bool ring_pending;
  bool tx_buf_write_pending;
  bool tx_session_pending;
  bool rx_read_pending;
  bool rx_session_pending;
} px4_msgs__msg__IridiumsbdStatus;

// Struct for a sequence of px4_msgs__msg__IridiumsbdStatus.
typedef struct px4_msgs__msg__IridiumsbdStatus__Sequence
{
  px4_msgs__msg__IridiumsbdStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__IridiumsbdStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__IRIDIUMSBD_STATUS__STRUCT_H_
