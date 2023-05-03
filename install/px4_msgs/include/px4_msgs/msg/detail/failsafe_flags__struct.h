// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/FailsafeFlags.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__FAILSAFE_FLAGS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__FAILSAFE_FLAGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/FailsafeFlags in the package px4_msgs.
typedef struct px4_msgs__msg__FailsafeFlags
{
  uint64_t timestamp;
  uint32_t mode_req_angular_velocity;
  uint32_t mode_req_attitude;
  uint32_t mode_req_local_alt;
  uint32_t mode_req_local_position;
  uint32_t mode_req_local_position_relaxed;
  uint32_t mode_req_global_position;
  uint32_t mode_req_mission;
  uint32_t mode_req_offboard_signal;
  uint32_t mode_req_home_position;
  uint32_t mode_req_wind_and_flight_time_compliance;
  uint32_t mode_req_prevent_arming;
  uint32_t mode_req_manual_control;
  uint32_t mode_req_other;
  bool angular_velocity_invalid;
  bool attitude_invalid;
  bool local_altitude_invalid;
  bool local_position_invalid;
  bool local_position_invalid_relaxed;
  bool local_velocity_invalid;
  bool global_position_invalid;
  bool auto_mission_missing;
  bool offboard_control_signal_lost;
  bool home_position_invalid;
  bool manual_control_signal_lost;
  bool gcs_connection_lost;
  uint8_t battery_warning;
  bool battery_low_remaining_time;
  bool battery_unhealthy;
  bool primary_geofence_breached;
  bool mission_failure;
  bool vtol_fixed_wing_system_failure;
  bool wind_limit_exceeded;
  bool flight_time_limit_exceeded;
  bool local_position_accuracy_low;
  bool fd_critical_failure;
  bool fd_esc_arming_failure;
  bool fd_imbalanced_prop;
  bool fd_motor_failure;
} px4_msgs__msg__FailsafeFlags;

// Struct for a sequence of px4_msgs__msg__FailsafeFlags.
typedef struct px4_msgs__msg__FailsafeFlags__Sequence
{
  px4_msgs__msg__FailsafeFlags * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__FailsafeFlags__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__FAILSAFE_FLAGS__STRUCT_H_
