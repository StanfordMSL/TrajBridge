// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/AdcReport.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__ADC_REPORT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__ADC_REPORT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/AdcReport in the package px4_msgs.
typedef struct px4_msgs__msg__AdcReport
{
  uint64_t timestamp;
  uint32_t device_id;
  int16_t channel_id[12];
  int32_t raw_data[12];
  uint32_t resolution;
  float v_ref;
} px4_msgs__msg__AdcReport;

// Struct for a sequence of px4_msgs__msg__AdcReport.
typedef struct px4_msgs__msg__AdcReport__Sequence
{
  px4_msgs__msg__AdcReport * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__AdcReport__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__ADC_REPORT__STRUCT_H_
