// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/InternalCombustionEngineStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__INTERNAL_COMBUSTION_ENGINE_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__INTERNAL_COMBUSTION_ENGINE_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATE_STOPPED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__STATE_STOPPED = 0
};

/// Constant 'STATE_STARTING'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__STATE_STARTING = 1
};

/// Constant 'STATE_RUNNING'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__STATE_RUNNING = 2
};

/// Constant 'STATE_FAULT'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__STATE_FAULT = 3
};

/// Constant 'FLAG_GENERAL_ERROR'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_GENERAL_ERROR = 1ul
};

/// Constant 'FLAG_CRANKSHAFT_SENSOR_ERROR_SUPPORTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_CRANKSHAFT_SENSOR_ERROR_SUPPORTED = 2ul
};

/// Constant 'FLAG_CRANKSHAFT_SENSOR_ERROR'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_CRANKSHAFT_SENSOR_ERROR = 4ul
};

/// Constant 'FLAG_TEMPERATURE_SUPPORTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_TEMPERATURE_SUPPORTED = 8ul
};

/// Constant 'FLAG_TEMPERATURE_BELOW_NOMINAL'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_TEMPERATURE_BELOW_NOMINAL = 16ul
};

/// Constant 'FLAG_TEMPERATURE_ABOVE_NOMINAL'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_TEMPERATURE_ABOVE_NOMINAL = 32ul
};

/// Constant 'FLAG_TEMPERATURE_OVERHEATING'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_TEMPERATURE_OVERHEATING = 64ul
};

/// Constant 'FLAG_TEMPERATURE_EGT_ABOVE_NOMINAL'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_TEMPERATURE_EGT_ABOVE_NOMINAL = 128ul
};

/// Constant 'FLAG_FUEL_PRESSURE_SUPPORTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_FUEL_PRESSURE_SUPPORTED = 256ul
};

/// Constant 'FLAG_FUEL_PRESSURE_BELOW_NOMINAL'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_FUEL_PRESSURE_BELOW_NOMINAL = 512ul
};

/// Constant 'FLAG_FUEL_PRESSURE_ABOVE_NOMINAL'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_FUEL_PRESSURE_ABOVE_NOMINAL = 1024ul
};

/// Constant 'FLAG_DETONATION_SUPPORTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_DETONATION_SUPPORTED = 2048ul
};

/// Constant 'FLAG_DETONATION_OBSERVED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_DETONATION_OBSERVED = 4096ul
};

/// Constant 'FLAG_MISFIRE_SUPPORTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_MISFIRE_SUPPORTED = 8192ul
};

/// Constant 'FLAG_MISFIRE_OBSERVED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_MISFIRE_OBSERVED = 16384ul
};

/// Constant 'FLAG_OIL_PRESSURE_SUPPORTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_OIL_PRESSURE_SUPPORTED = 32768ul
};

/// Constant 'FLAG_OIL_PRESSURE_BELOW_NOMINAL'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_OIL_PRESSURE_BELOW_NOMINAL = 65536ul
};

/// Constant 'FLAG_OIL_PRESSURE_ABOVE_NOMINAL'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_OIL_PRESSURE_ABOVE_NOMINAL = 131072ul
};

/// Constant 'FLAG_DEBRIS_SUPPORTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_DEBRIS_SUPPORTED = 262144ul
};

/// Constant 'FLAG_DEBRIS_DETECTED'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__FLAG_DEBRIS_DETECTED = 524288ul
};

/// Constant 'SPARK_PLUG_SINGLE'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__SPARK_PLUG_SINGLE = 0
};

/// Constant 'SPARK_PLUG_FIRST_ACTIVE'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__SPARK_PLUG_FIRST_ACTIVE = 1
};

/// Constant 'SPARK_PLUG_SECOND_ACTIVE'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__SPARK_PLUG_SECOND_ACTIVE = 2
};

/// Constant 'SPARK_PLUG_BOTH_ACTIVE'.
enum
{
  px4_msgs__msg__InternalCombustionEngineStatus__SPARK_PLUG_BOTH_ACTIVE = 3
};

// Struct defined in msg/InternalCombustionEngineStatus in the package px4_msgs.
typedef struct px4_msgs__msg__InternalCombustionEngineStatus
{
  uint64_t timestamp;
  uint8_t state;
  uint32_t flags;
  uint8_t engine_load_percent;
  uint32_t engine_speed_rpm;
  float spark_dwell_time_ms;
  float atmospheric_pressure_kpa;
  float intake_manifold_pressure_kpa;
  float intake_manifold_temperature;
  float coolant_temperature;
  float oil_pressure;
  float oil_temperature;
  float fuel_pressure;
  float fuel_consumption_rate_cm3pm;
  float estimated_consumed_fuel_volume_cm3;
  uint8_t throttle_position_percent;
  uint8_t ecu_index;
  uint8_t spark_plug_usage;
  float ignition_timing_deg;
  float injection_time_ms;
  float cylinder_head_temperature;
  float exhaust_gas_temperature;
  float lambda_coefficient;
} px4_msgs__msg__InternalCombustionEngineStatus;

// Struct for a sequence of px4_msgs__msg__InternalCombustionEngineStatus.
typedef struct px4_msgs__msg__InternalCombustionEngineStatus__Sequence
{
  px4_msgs__msg__InternalCombustionEngineStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__InternalCombustionEngineStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__INTERNAL_COMBUSTION_ENGINE_STATUS__STRUCT_H_
