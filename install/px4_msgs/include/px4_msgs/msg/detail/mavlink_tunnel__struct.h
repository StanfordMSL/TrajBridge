// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/MavlinkTunnel.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MAVLINK_TUNNEL__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__MAVLINK_TUNNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_UNKNOWN'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_UNKNOWN = 0
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED0'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED0 = 200
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED1'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED1 = 201
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED2'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED2 = 202
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED3'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED3 = 203
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED4'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED4 = 204
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED5'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED5 = 205
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED6'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED6 = 206
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED7'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED7 = 207
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED8'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED8 = 208
};

/// Constant 'MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED9'.
enum
{
  px4_msgs__msg__MavlinkTunnel__MAV_TUNNEL_PAYLOAD_TYPE_STORM32_RESERVED9 = 209
};

// Struct defined in msg/MavlinkTunnel in the package px4_msgs.
typedef struct px4_msgs__msg__MavlinkTunnel
{
  uint64_t timestamp;
  uint16_t payload_type;
  uint8_t target_system;
  uint8_t target_component;
  uint8_t payload_length;
  uint8_t payload[128];
} px4_msgs__msg__MavlinkTunnel;

// Struct for a sequence of px4_msgs__msg__MavlinkTunnel.
typedef struct px4_msgs__msg__MavlinkTunnel__Sequence
{
  px4_msgs__msg__MavlinkTunnel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__MavlinkTunnel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__MAVLINK_TUNNEL__STRUCT_H_
