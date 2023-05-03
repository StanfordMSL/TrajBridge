// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/BatteryStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__BATTERY_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__BATTERY_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'BATTERY_SOURCE_POWER_MODULE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_SOURCE_POWER_MODULE = 0
};

/// Constant 'BATTERY_SOURCE_EXTERNAL'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_SOURCE_EXTERNAL = 1
};

/// Constant 'BATTERY_SOURCE_ESCS'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_SOURCE_ESCS = 2
};

/// Constant 'BATTERY_WARNING_NONE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_WARNING_NONE = 0
};

/// Constant 'BATTERY_WARNING_LOW'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_WARNING_LOW = 1
};

/// Constant 'BATTERY_WARNING_CRITICAL'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_WARNING_CRITICAL = 2
};

/// Constant 'BATTERY_WARNING_EMERGENCY'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_WARNING_EMERGENCY = 3
};

/// Constant 'BATTERY_WARNING_FAILED'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_WARNING_FAILED = 4
};

/// Constant 'BATTERY_STATE_UNHEALTHY'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_STATE_UNHEALTHY = 6
};

/// Constant 'BATTERY_STATE_CHARGING'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_STATE_CHARGING = 7
};

/// Constant 'BATTERY_FAULT_DEEP_DISCHARGE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_DEEP_DISCHARGE = 0
};

/// Constant 'BATTERY_FAULT_SPIKES'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_SPIKES = 1
};

/// Constant 'BATTERY_FAULT_CELL_FAIL'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_CELL_FAIL = 2
};

/// Constant 'BATTERY_FAULT_OVER_CURRENT'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_OVER_CURRENT = 3
};

/// Constant 'BATTERY_FAULT_OVER_TEMPERATURE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_OVER_TEMPERATURE = 4
};

/// Constant 'BATTERY_FAULT_UNDER_TEMPERATURE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_UNDER_TEMPERATURE = 5
};

/// Constant 'BATTERY_FAULT_INCOMPATIBLE_VOLTAGE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_INCOMPATIBLE_VOLTAGE = 6
};

/// Constant 'BATTERY_FAULT_INCOMPATIBLE_FIRMWARE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_INCOMPATIBLE_FIRMWARE = 7
};

/// Constant 'BATTERY_FAULT_INCOMPATIBLE_MODEL'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_INCOMPATIBLE_MODEL = 8
};

/// Constant 'BATTERY_FAULT_HARDWARE_FAILURE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_HARDWARE_FAILURE = 9
};

/// Constant 'BATTERY_WARNING_OVER_TEMPERATURE'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_WARNING_OVER_TEMPERATURE = 10
};

/// Constant 'BATTERY_FAULT_COUNT'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_FAULT_COUNT = 11
};

/// Constant 'BATTERY_MODE_UNKNOWN'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_MODE_UNKNOWN = 0
};

/// Constant 'BATTERY_MODE_AUTO_DISCHARGING'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_MODE_AUTO_DISCHARGING = 1
};

/// Constant 'BATTERY_MODE_HOT_SWAP'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_MODE_HOT_SWAP = 2
};

/// Constant 'BATTERY_MODE_COUNT'.
enum
{
  px4_msgs__msg__BatteryStatus__BATTERY_MODE_COUNT = 3
};

/// Constant 'MAX_INSTANCES'.
enum
{
  px4_msgs__msg__BatteryStatus__MAX_INSTANCES = 4
};

// Struct defined in msg/BatteryStatus in the package px4_msgs.
typedef struct px4_msgs__msg__BatteryStatus
{
  uint64_t timestamp;
  bool connected;
  float voltage_v;
  float voltage_filtered_v;
  float current_a;
  float current_filtered_a;
  float current_average_a;
  float discharged_mah;
  float remaining;
  float scale;
  float time_remaining_s;
  float temperature;
  uint8_t cell_count;
  uint8_t source;
  uint8_t priority;
  uint16_t capacity;
  uint16_t cycle_count;
  uint16_t average_time_to_empty;
  uint16_t serial_number;
  uint16_t manufacture_date;
  uint16_t state_of_health;
  uint16_t max_error;
  uint8_t id;
  uint16_t interface_error;
  float voltage_cell_v[14];
  float max_cell_voltage_delta;
  bool is_powering_off;
  bool is_required;
  uint16_t faults;
  uint32_t custom_faults;
  uint8_t warning;
  uint8_t mode;
  float average_power;
  float available_energy;
  float full_charge_capacity_wh;
  float remaining_capacity_wh;
  float design_capacity;
  uint16_t average_time_to_full;
  uint16_t over_discharge_count;
  float nominal_voltage;
} px4_msgs__msg__BatteryStatus;

// Struct for a sequence of px4_msgs__msg__BatteryStatus.
typedef struct px4_msgs__msg__BatteryStatus__Sequence
{
  px4_msgs__msg__BatteryStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__BatteryStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__BATTERY_STATUS__STRUCT_H_
