// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/EstimatorStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESTIMATOR_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ESTIMATOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'GPS_CHECK_FAIL_GPS_FIX'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_GPS_FIX = 0
};

/// Constant 'GPS_CHECK_FAIL_MIN_SAT_COUNT'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MIN_SAT_COUNT = 1
};

/// Constant 'GPS_CHECK_FAIL_MAX_PDOP'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_PDOP = 2
};

/// Constant 'GPS_CHECK_FAIL_MAX_HORZ_ERR'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_HORZ_ERR = 3
};

/// Constant 'GPS_CHECK_FAIL_MAX_VERT_ERR'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_VERT_ERR = 4
};

/// Constant 'GPS_CHECK_FAIL_MAX_SPD_ERR'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_SPD_ERR = 5
};

/// Constant 'GPS_CHECK_FAIL_MAX_HORZ_DRIFT'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_HORZ_DRIFT = 6
};

/// Constant 'GPS_CHECK_FAIL_MAX_VERT_DRIFT'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_VERT_DRIFT = 7
};

/// Constant 'GPS_CHECK_FAIL_MAX_HORZ_SPD_ERR'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_HORZ_SPD_ERR = 8
};

/// Constant 'GPS_CHECK_FAIL_MAX_VERT_SPD_ERR'.
enum
{
  px4_msgs__msg__EstimatorStatus__GPS_CHECK_FAIL_MAX_VERT_SPD_ERR = 9
};

/// Constant 'CS_TILT_ALIGN'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_TILT_ALIGN = 0
};

/// Constant 'CS_YAW_ALIGN'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_YAW_ALIGN = 1
};

/// Constant 'CS_GPS'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_GPS = 2
};

/// Constant 'CS_OPT_FLOW'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_OPT_FLOW = 3
};

/// Constant 'CS_MAG_HDG'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_MAG_HDG = 4
};

/// Constant 'CS_MAG_3D'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_MAG_3D = 5
};

/// Constant 'CS_MAG_DEC'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_MAG_DEC = 6
};

/// Constant 'CS_IN_AIR'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_IN_AIR = 7
};

/// Constant 'CS_WIND'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_WIND = 8
};

/// Constant 'CS_BARO_HGT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_BARO_HGT = 9
};

/// Constant 'CS_RNG_HGT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_RNG_HGT = 10
};

/// Constant 'CS_GPS_HGT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_GPS_HGT = 11
};

/// Constant 'CS_EV_POS'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_EV_POS = 12
};

/// Constant 'CS_EV_YAW'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_EV_YAW = 13
};

/// Constant 'CS_EV_HGT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_EV_HGT = 14
};

/// Constant 'CS_BETA'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_BETA = 15
};

/// Constant 'CS_MAG_FIELD'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_MAG_FIELD = 16
};

/// Constant 'CS_FIXED_WING'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_FIXED_WING = 17
};

/// Constant 'CS_MAG_FAULT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_MAG_FAULT = 18
};

/// Constant 'CS_ASPD'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_ASPD = 19
};

/// Constant 'CS_GND_EFFECT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_GND_EFFECT = 20
};

/// Constant 'CS_RNG_STUCK'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_RNG_STUCK = 21
};

/// Constant 'CS_GPS_YAW'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_GPS_YAW = 22
};

/// Constant 'CS_MAG_ALIGNED'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_MAG_ALIGNED = 23
};

/// Constant 'CS_EV_VEL'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_EV_VEL = 24
};

/// Constant 'CS_SYNTHETIC_MAG_Z'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_SYNTHETIC_MAG_Z = 25
};

/// Constant 'CS_VEHICLE_AT_REST'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_VEHICLE_AT_REST = 26
};

/// Constant 'CS_GPS_YAW_FAULT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_GPS_YAW_FAULT = 27
};

/// Constant 'CS_RNG_FAULT'.
enum
{
  px4_msgs__msg__EstimatorStatus__CS_RNG_FAULT = 28
};

// Struct defined in msg/EstimatorStatus in the package px4_msgs.
typedef struct px4_msgs__msg__EstimatorStatus
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  float output_tracking_error[3];
  uint16_t gps_check_fail_flags;
  uint64_t control_mode_flags;
  uint32_t filter_fault_flags;
  float pos_horiz_accuracy;
  float pos_vert_accuracy;
  uint16_t innovation_check_flags;
  float mag_test_ratio;
  float vel_test_ratio;
  float pos_test_ratio;
  float hgt_test_ratio;
  float tas_test_ratio;
  float hagl_test_ratio;
  float beta_test_ratio;
  uint16_t solution_status_flags;
  uint8_t reset_count_vel_ne;
  uint8_t reset_count_vel_d;
  uint8_t reset_count_pos_ne;
  uint8_t reset_count_pod_d;
  uint8_t reset_count_quat;
  float time_slip;
  bool pre_flt_fail_innov_heading;
  bool pre_flt_fail_innov_vel_horiz;
  bool pre_flt_fail_innov_vel_vert;
  bool pre_flt_fail_innov_height;
  bool pre_flt_fail_mag_field_disturbed;
  uint32_t accel_device_id;
  uint32_t gyro_device_id;
  uint32_t baro_device_id;
  uint32_t mag_device_id;
  uint8_t health_flags;
  uint8_t timeout_flags;
} px4_msgs__msg__EstimatorStatus;

// Struct for a sequence of px4_msgs__msg__EstimatorStatus.
typedef struct px4_msgs__msg__EstimatorStatus__Sequence
{
  px4_msgs__msg__EstimatorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__EstimatorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ESTIMATOR_STATUS__STRUCT_H_
