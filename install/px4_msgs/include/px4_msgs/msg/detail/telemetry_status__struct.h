// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/TelemetryStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__TELEMETRY_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__TELEMETRY_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'LINK_TYPE_GENERIC'.
enum
{
  px4_msgs__msg__TelemetryStatus__LINK_TYPE_GENERIC = 0
};

/// Constant 'LINK_TYPE_UBIQUITY_BULLET'.
enum
{
  px4_msgs__msg__TelemetryStatus__LINK_TYPE_UBIQUITY_BULLET = 1
};

/// Constant 'LINK_TYPE_WIRE'.
enum
{
  px4_msgs__msg__TelemetryStatus__LINK_TYPE_WIRE = 2
};

/// Constant 'LINK_TYPE_USB'.
enum
{
  px4_msgs__msg__TelemetryStatus__LINK_TYPE_USB = 3
};

/// Constant 'LINK_TYPE_IRIDIUM'.
enum
{
  px4_msgs__msg__TelemetryStatus__LINK_TYPE_IRIDIUM = 4
};

/// Constant 'HEARTBEAT_TIMEOUT_US'.
enum
{
  px4_msgs__msg__TelemetryStatus__HEARTBEAT_TIMEOUT_US = 2500000ull
};

// Struct defined in msg/TelemetryStatus in the package px4_msgs.
typedef struct px4_msgs__msg__TelemetryStatus
{
  uint64_t timestamp;
  uint8_t type;
  uint8_t mode;
  bool flow_control;
  bool forwarding;
  bool mavlink_v2;
  bool ftp;
  uint8_t streams;
  float data_rate;
  float rate_multiplier;
  float tx_rate_avg;
  float tx_error_rate_avg;
  uint32_t tx_message_count;
  uint32_t tx_buffer_overruns;
  float rx_rate_avg;
  uint32_t rx_message_count;
  uint32_t rx_message_lost_count;
  uint32_t rx_buffer_overruns;
  uint32_t rx_parse_errors;
  uint32_t rx_packet_drop_count;
  float rx_message_lost_rate;
  bool heartbeat_type_antenna_tracker;
  bool heartbeat_type_gcs;
  bool heartbeat_type_onboard_controller;
  bool heartbeat_type_gimbal;
  bool heartbeat_type_adsb;
  bool heartbeat_type_camera;
  bool heartbeat_type_parachute;
  bool heartbeat_type_open_drone_id;
  bool heartbeat_component_telemetry_radio;
  bool heartbeat_component_log;
  bool heartbeat_component_osd;
  bool heartbeat_component_obstacle_avoidance;
  bool heartbeat_component_vio;
  bool heartbeat_component_pairing_manager;
  bool heartbeat_component_udp_bridge;
  bool heartbeat_component_uart_bridge;
  bool avoidance_system_healthy;
  bool open_drone_id_system_healthy;
  bool parachute_system_healthy;
} px4_msgs__msg__TelemetryStatus;

// Struct for a sequence of px4_msgs__msg__TelemetryStatus.
typedef struct px4_msgs__msg__TelemetryStatus__Sequence
{
  px4_msgs__msg__TelemetryStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__TelemetryStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__TELEMETRY_STATUS__STRUCT_H_
