// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/EstimatorInnovations.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ESTIMATOR_INNOVATIONS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ESTIMATOR_INNOVATIONS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/EstimatorInnovations in the package px4_msgs.
typedef struct px4_msgs__msg__EstimatorInnovations
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  float gps_hvel[2];
  float gps_vvel;
  float gps_hpos[2];
  float gps_vpos;
  float ev_hvel[2];
  float ev_vvel;
  float ev_hpos[2];
  float ev_vpos;
  float rng_vpos;
  float baro_vpos;
  float aux_hvel[2];
  float aux_vvel;
  float flow[2];
  float terr_flow[2];
  float heading;
  float mag_field[3];
  float gravity[3];
  float drag[2];
  float airspeed;
  float beta;
  float hagl;
  float hagl_rate;
} px4_msgs__msg__EstimatorInnovations;

// Struct for a sequence of px4_msgs__msg__EstimatorInnovations.
typedef struct px4_msgs__msg__EstimatorInnovations__Sequence
{
  px4_msgs__msg__EstimatorInnovations * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__EstimatorInnovations__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ESTIMATOR_INNOVATIONS__STRUCT_H_
