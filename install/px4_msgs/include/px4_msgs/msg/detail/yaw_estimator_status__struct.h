// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/YawEstimatorStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__YAW_ESTIMATOR_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__YAW_ESTIMATOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/YawEstimatorStatus in the package px4_msgs.
typedef struct px4_msgs__msg__YawEstimatorStatus
{
  uint64_t timestamp;
  uint64_t timestamp_sample;
  float yaw_composite;
  float yaw_variance;
  bool yaw_composite_valid;
  float yaw[5];
  float innov_vn[5];
  float innov_ve[5];
  float weight[5];
} px4_msgs__msg__YawEstimatorStatus;

// Struct for a sequence of px4_msgs__msg__YawEstimatorStatus.
typedef struct px4_msgs__msg__YawEstimatorStatus__Sequence
{
  px4_msgs__msg__YawEstimatorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__YawEstimatorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__YAW_ESTIMATOR_STATUS__STRUCT_H_
