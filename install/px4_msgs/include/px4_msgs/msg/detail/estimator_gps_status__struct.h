// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/EstimatorGpsStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESTIMATOR_GPS_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ESTIMATOR_GPS_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/EstimatorGpsStatus in the package px4_msgs.
typedef struct px4_msgs__msg__EstimatorGpsStatus
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  bool checks_passed;
  bool check_fail_gps_fix;
  bool check_fail_min_sat_count;
  bool check_fail_max_pdop;
  bool check_fail_max_horz_err;
  bool check_fail_max_vert_err;
  bool check_fail_max_spd_err;
  bool check_fail_max_horz_drift;
  bool check_fail_max_vert_drift;
  bool check_fail_max_horz_spd_err;
  bool check_fail_max_vert_spd_err;
  float position_drift_rate_horizontal_m_s;
  float position_drift_rate_vertical_m_s;
  float filtered_horizontal_speed_m_s;
} px4_msgs__msg__EstimatorGpsStatus;

// Struct for a sequence of px4_msgs__msg__EstimatorGpsStatus.
typedef struct px4_msgs__msg__EstimatorGpsStatus__Sequence
{
  px4_msgs__msg__EstimatorGpsStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__EstimatorGpsStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ESTIMATOR_GPS_STATUS__STRUCT_H_
