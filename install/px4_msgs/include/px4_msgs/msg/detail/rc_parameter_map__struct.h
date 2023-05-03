// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/RcParameterMap.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__RC_PARAMETER_MAP__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__RC_PARAMETER_MAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'RC_PARAM_MAP_NCHAN'.
enum
{
  px4_msgs__msg__RcParameterMap__RC_PARAM_MAP_NCHAN = 3
};

/// Constant 'PARAM_ID_LEN'.
enum
{
  px4_msgs__msg__RcParameterMap__PARAM_ID_LEN = 16
};

// Struct defined in msg/RcParameterMap in the package px4_msgs.
typedef struct px4_msgs__msg__RcParameterMap
{
  uint64_t timestamp;
  bool valid[3];
  int32_t param_index[3];
  uint8_t param_id[51];
  float scale[3];
  float value0[3];
  float value_min[3];
  float value_max[3];
} px4_msgs__msg__RcParameterMap;

// Struct for a sequence of px4_msgs__msg__RcParameterMap.
typedef struct px4_msgs__msg__RcParameterMap__Sequence
{
  px4_msgs__msg__RcParameterMap * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__RcParameterMap__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__RC_PARAMETER_MAP__STRUCT_H_
