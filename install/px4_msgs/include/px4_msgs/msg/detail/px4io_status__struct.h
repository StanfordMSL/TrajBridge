// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/Px4ioStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__PX4IO_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__PX4IO_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Px4ioStatus in the package px4_msgs.
typedef struct px4_msgs__msg__Px4ioStatus
{
  uint64_t timestamp;
  uint16_t free_memory_bytes;
  float voltage_v;
  float rssi_v;
  bool status_arm_sync;
  bool status_failsafe;
  bool status_fmu_initialized;
  bool status_fmu_ok;
  bool status_init_ok;
  bool status_outputs_armed;
  bool status_raw_pwm;
  bool status_rc_ok;
  bool status_rc_dsm;
  bool status_rc_ppm;
  bool status_rc_sbus;
  bool status_rc_st24;
  bool status_rc_sumd;
  bool status_safety_button_event;
  bool alarm_pwm_error;
  bool alarm_rc_lost;
  bool arming_failsafe_custom;
  bool arming_fmu_armed;
  bool arming_fmu_prearmed;
  bool arming_force_failsafe;
  bool arming_io_arm_ok;
  bool arming_lockdown;
  bool arming_termination_failsafe;
  uint16_t pwm[8];
  uint16_t pwm_disarmed[8];
  uint16_t pwm_failsafe[8];
  uint16_t pwm_rate_hz[8];
  uint16_t raw_inputs[18];
} px4_msgs__msg__Px4ioStatus;

// Struct for a sequence of px4_msgs__msg__Px4ioStatus.
typedef struct px4_msgs__msg__Px4ioStatus__Sequence
{
  px4_msgs__msg__Px4ioStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__Px4ioStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__PX4IO_STATUS__STRUCT_H_
