// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/EstimatorStatusFlags.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESTIMATOR_STATUS_FLAGS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ESTIMATOR_STATUS_FLAGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/EstimatorStatusFlags in the package px4_msgs.
typedef struct px4_msgs__msg__EstimatorStatusFlags
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  uint32_t control_status_changes;
  bool cs_tilt_align;
  bool cs_yaw_align;
  bool cs_gps;
  bool cs_opt_flow;
  bool cs_mag_hdg;
  bool cs_mag_3d;
  bool cs_mag_dec;
  bool cs_in_air;
  bool cs_wind;
  bool cs_baro_hgt;
  bool cs_rng_hgt;
  bool cs_gps_hgt;
  bool cs_ev_pos;
  bool cs_ev_yaw;
  bool cs_ev_hgt;
  bool cs_fuse_beta;
  bool cs_mag_field_disturbed;
  bool cs_fixed_wing;
  bool cs_mag_fault;
  bool cs_fuse_aspd;
  bool cs_gnd_effect;
  bool cs_rng_stuck;
  bool cs_gps_yaw;
  bool cs_mag_aligned_in_flight;
  bool cs_ev_vel;
  bool cs_synthetic_mag_z;
  bool cs_vehicle_at_rest;
  bool cs_gps_yaw_fault;
  bool cs_rng_fault;
  bool cs_inertial_dead_reckoning;
  bool cs_wind_dead_reckoning;
  bool cs_rng_kin_consistent;
  bool cs_fake_pos;
  bool cs_fake_hgt;
  bool cs_gravity_vector;
  uint32_t fault_status_changes;
  bool fs_bad_mag_x;
  bool fs_bad_mag_y;
  bool fs_bad_mag_z;
  bool fs_bad_hdg;
  bool fs_bad_mag_decl;
  bool fs_bad_airspeed;
  bool fs_bad_sideslip;
  bool fs_bad_optflow_x;
  bool fs_bad_optflow_y;
  bool fs_bad_vel_n;
  bool fs_bad_vel_e;
  bool fs_bad_vel_d;
  bool fs_bad_pos_n;
  bool fs_bad_pos_e;
  bool fs_bad_pos_d;
  bool fs_bad_acc_bias;
  bool fs_bad_acc_vertical;
  bool fs_bad_acc_clipping;
  uint32_t innovation_fault_status_changes;
  bool reject_hor_vel;
  bool reject_ver_vel;
  bool reject_hor_pos;
  bool reject_ver_pos;
  bool reject_yaw;
  bool reject_airspeed;
  bool reject_sideslip;
  bool reject_hagl;
  bool reject_optflow_x;
  bool reject_optflow_y;
} px4_msgs__msg__EstimatorStatusFlags;

// Struct for a sequence of px4_msgs__msg__EstimatorStatusFlags.
typedef struct px4_msgs__msg__EstimatorStatusFlags__Sequence
{
  px4_msgs__msg__EstimatorStatusFlags * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__EstimatorStatusFlags__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ESTIMATOR_STATUS_FLAGS__STRUCT_H_
