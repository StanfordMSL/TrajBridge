// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ARMING_STATE_INIT'.
enum
{
  px4_msgs__msg__VehicleStatus__ARMING_STATE_INIT = 0
};

/// Constant 'ARMING_STATE_STANDBY'.
enum
{
  px4_msgs__msg__VehicleStatus__ARMING_STATE_STANDBY = 1
};

/// Constant 'ARMING_STATE_ARMED'.
enum
{
  px4_msgs__msg__VehicleStatus__ARMING_STATE_ARMED = 2
};

/// Constant 'ARMING_STATE_STANDBY_ERROR'.
enum
{
  px4_msgs__msg__VehicleStatus__ARMING_STATE_STANDBY_ERROR = 3
};

/// Constant 'ARMING_STATE_SHUTDOWN'.
enum
{
  px4_msgs__msg__VehicleStatus__ARMING_STATE_SHUTDOWN = 4
};

/// Constant 'ARMING_STATE_IN_AIR_RESTORE'.
enum
{
  px4_msgs__msg__VehicleStatus__ARMING_STATE_IN_AIR_RESTORE = 5
};

/// Constant 'ARMING_STATE_MAX'.
enum
{
  px4_msgs__msg__VehicleStatus__ARMING_STATE_MAX = 6
};

/// Constant 'ARM_DISARM_REASON_TRANSITION_TO_STANDBY'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_TRANSITION_TO_STANDBY = 0
};

/// Constant 'ARM_DISARM_REASON_RC_STICK'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_RC_STICK = 1
};

/// Constant 'ARM_DISARM_REASON_RC_SWITCH'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_RC_SWITCH = 2
};

/// Constant 'ARM_DISARM_REASON_COMMAND_INTERNAL'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_COMMAND_INTERNAL = 3
};

/// Constant 'ARM_DISARM_REASON_COMMAND_EXTERNAL'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_COMMAND_EXTERNAL = 4
};

/// Constant 'ARM_DISARM_REASON_MISSION_START'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_MISSION_START = 5
};

/// Constant 'ARM_DISARM_REASON_SAFETY_BUTTON'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_SAFETY_BUTTON = 6
};

/// Constant 'ARM_DISARM_REASON_AUTO_DISARM_LAND'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_AUTO_DISARM_LAND = 7
};

/// Constant 'ARM_DISARM_REASON_AUTO_DISARM_PREFLIGHT'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_AUTO_DISARM_PREFLIGHT = 8
};

/// Constant 'ARM_DISARM_REASON_KILL_SWITCH'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_KILL_SWITCH = 9
};

/// Constant 'ARM_DISARM_REASON_LOCKDOWN'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_LOCKDOWN = 10
};

/// Constant 'ARM_DISARM_REASON_FAILURE_DETECTOR'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_FAILURE_DETECTOR = 11
};

/// Constant 'ARM_DISARM_REASON_SHUTDOWN'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_SHUTDOWN = 12
};

/// Constant 'ARM_DISARM_REASON_UNIT_TEST'.
enum
{
  px4_msgs__msg__VehicleStatus__ARM_DISARM_REASON_UNIT_TEST = 13
};

/// Constant 'NAVIGATION_STATE_MANUAL'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_MANUAL = 0
};

/// Constant 'NAVIGATION_STATE_ALTCTL'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_ALTCTL = 1
};

/// Constant 'NAVIGATION_STATE_POSCTL'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_POSCTL = 2
};

/// Constant 'NAVIGATION_STATE_AUTO_MISSION'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_MISSION = 3
};

/// Constant 'NAVIGATION_STATE_AUTO_LOITER'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_LOITER = 4
};

/// Constant 'NAVIGATION_STATE_AUTO_RTL'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_RTL = 5
};

/// Constant 'NAVIGATION_STATE_UNUSED3'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_UNUSED3 = 8
};

/// Constant 'NAVIGATION_STATE_UNUSED'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_UNUSED = 9
};

/// Constant 'NAVIGATION_STATE_ACRO'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_ACRO = 10
};

/// Constant 'NAVIGATION_STATE_UNUSED1'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_UNUSED1 = 11
};

/// Constant 'NAVIGATION_STATE_DESCEND'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_DESCEND = 12
};

/// Constant 'NAVIGATION_STATE_TERMINATION'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_TERMINATION = 13
};

/// Constant 'NAVIGATION_STATE_OFFBOARD'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_OFFBOARD = 14
};

/// Constant 'NAVIGATION_STATE_STAB'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_STAB = 15
};

/// Constant 'NAVIGATION_STATE_UNUSED2'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_UNUSED2 = 16
};

/// Constant 'NAVIGATION_STATE_AUTO_TAKEOFF'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_TAKEOFF = 17
};

/// Constant 'NAVIGATION_STATE_AUTO_LAND'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_LAND = 18
};

/// Constant 'NAVIGATION_STATE_AUTO_FOLLOW_TARGET'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_FOLLOW_TARGET = 19
};

/// Constant 'NAVIGATION_STATE_AUTO_PRECLAND'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_PRECLAND = 20
};

/// Constant 'NAVIGATION_STATE_ORBIT'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_ORBIT = 21
};

/// Constant 'NAVIGATION_STATE_AUTO_VTOL_TAKEOFF'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_AUTO_VTOL_TAKEOFF = 22
};

/// Constant 'NAVIGATION_STATE_MAX'.
enum
{
  px4_msgs__msg__VehicleStatus__NAVIGATION_STATE_MAX = 23
};

/// Constant 'FAILURE_NONE'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_NONE = 0
};

/// Constant 'FAILURE_ROLL'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_ROLL = 1
};

/// Constant 'FAILURE_PITCH'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_PITCH = 2
};

/// Constant 'FAILURE_ALT'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_ALT = 4
};

/// Constant 'FAILURE_EXT'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_EXT = 8
};

/// Constant 'FAILURE_ARM_ESC'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_ARM_ESC = 16
};

/// Constant 'FAILURE_BATTERY'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_BATTERY = 32
};

/// Constant 'FAILURE_IMBALANCED_PROP'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_IMBALANCED_PROP = 64
};

/// Constant 'FAILURE_MOTOR'.
enum
{
  px4_msgs__msg__VehicleStatus__FAILURE_MOTOR = 128
};

/// Constant 'HIL_STATE_OFF'.
enum
{
  px4_msgs__msg__VehicleStatus__HIL_STATE_OFF = 0
};

/// Constant 'HIL_STATE_ON'.
enum
{
  px4_msgs__msg__VehicleStatus__HIL_STATE_ON = 1
};

/// Constant 'VEHICLE_TYPE_UNKNOWN'.
enum
{
  px4_msgs__msg__VehicleStatus__VEHICLE_TYPE_UNKNOWN = 0
};

/// Constant 'VEHICLE_TYPE_ROTARY_WING'.
enum
{
  px4_msgs__msg__VehicleStatus__VEHICLE_TYPE_ROTARY_WING = 1
};

/// Constant 'VEHICLE_TYPE_FIXED_WING'.
enum
{
  px4_msgs__msg__VehicleStatus__VEHICLE_TYPE_FIXED_WING = 2
};

/// Constant 'VEHICLE_TYPE_ROVER'.
enum
{
  px4_msgs__msg__VehicleStatus__VEHICLE_TYPE_ROVER = 3
};

/// Constant 'VEHICLE_TYPE_AIRSHIP'.
enum
{
  px4_msgs__msg__VehicleStatus__VEHICLE_TYPE_AIRSHIP = 4
};

// Struct defined in msg/VehicleStatus in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleStatus
{
  uint64_t timestamp;
  uint64_t armed_time;
  uint64_t takeoff_time;
  uint8_t arming_state;
  uint8_t latest_arming_reason;
  uint8_t latest_disarming_reason;
  uint64_t nav_state_timestamp;
  uint8_t nav_state_user_intention;
  uint8_t nav_state;
  uint16_t failure_detector_status;
  uint8_t hil_state;
  uint8_t vehicle_type;
  bool failsafe;
  bool failsafe_and_user_took_over;
  bool gcs_connection_lost;
  uint8_t gcs_connection_lost_counter;
  bool high_latency_data_link_lost;
  bool is_vtol;
  bool is_vtol_tailsitter;
  bool in_transition_mode;
  bool in_transition_to_fw;
  uint8_t system_type;
  uint8_t system_id;
  uint8_t component_id;
  bool safety_button_available;
  bool safety_off;
  bool power_input_valid;
  bool usb_connected;
  bool open_drone_id_system_present;
  bool open_drone_id_system_healthy;
  bool parachute_system_present;
  bool parachute_system_healthy;
  bool avoidance_system_required;
  bool avoidance_system_valid;
  bool rc_calibration_in_progress;
  bool calibration_enabled;
  bool pre_flight_checks_pass;
} px4_msgs__msg__VehicleStatus;

// Struct for a sequence of px4_msgs__msg__VehicleStatus.
typedef struct px4_msgs__msg__VehicleStatus__Sequence
{
  px4_msgs__msg__VehicleStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_
