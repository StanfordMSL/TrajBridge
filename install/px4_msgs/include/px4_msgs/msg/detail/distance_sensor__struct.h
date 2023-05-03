// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/DistanceSensor.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__DISTANCE_SENSOR__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__DISTANCE_SENSOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MAV_DISTANCE_SENSOR_LASER'.
enum
{
  px4_msgs__msg__DistanceSensor__MAV_DISTANCE_SENSOR_LASER = 0
};

/// Constant 'MAV_DISTANCE_SENSOR_ULTRASOUND'.
enum
{
  px4_msgs__msg__DistanceSensor__MAV_DISTANCE_SENSOR_ULTRASOUND = 1
};

/// Constant 'MAV_DISTANCE_SENSOR_INFRARED'.
enum
{
  px4_msgs__msg__DistanceSensor__MAV_DISTANCE_SENSOR_INFRARED = 2
};

/// Constant 'MAV_DISTANCE_SENSOR_RADAR'.
enum
{
  px4_msgs__msg__DistanceSensor__MAV_DISTANCE_SENSOR_RADAR = 3
};

/// Constant 'ROTATION_YAW_0'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_0 = 0
};

/// Constant 'ROTATION_YAW_45'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_45 = 1
};

/// Constant 'ROTATION_YAW_90'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_90 = 2
};

/// Constant 'ROTATION_YAW_135'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_135 = 3
};

/// Constant 'ROTATION_YAW_180'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_180 = 4
};

/// Constant 'ROTATION_YAW_225'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_225 = 5
};

/// Constant 'ROTATION_YAW_270'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_270 = 6
};

/// Constant 'ROTATION_YAW_315'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_YAW_315 = 7
};

/// Constant 'ROTATION_FORWARD_FACING'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_FORWARD_FACING = 0
};

/// Constant 'ROTATION_RIGHT_FACING'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_RIGHT_FACING = 2
};

/// Constant 'ROTATION_BACKWARD_FACING'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_BACKWARD_FACING = 4
};

/// Constant 'ROTATION_LEFT_FACING'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_LEFT_FACING = 6
};

/// Constant 'ROTATION_UPWARD_FACING'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_UPWARD_FACING = 24
};

/// Constant 'ROTATION_DOWNWARD_FACING'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_DOWNWARD_FACING = 25
};

/// Constant 'ROTATION_CUSTOM'.
enum
{
  px4_msgs__msg__DistanceSensor__ROTATION_CUSTOM = 100
};

// Struct defined in msg/DistanceSensor in the package px4_msgs.
typedef struct px4_msgs__msg__DistanceSensor
{
  uint64_t timestamp;
  uint32_t device_id;
  float min_distance;
  float max_distance;
  float current_distance;
  float variance;
  int8_t signal_quality;
  uint8_t type;
  float h_fov;
  float v_fov;
  float q[4];
  uint8_t orientation;
} px4_msgs__msg__DistanceSensor;

// Struct for a sequence of px4_msgs__msg__DistanceSensor.
typedef struct px4_msgs__msg__DistanceSensor__Sequence
{
  px4_msgs__msg__DistanceSensor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__DistanceSensor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__DISTANCE_SENSOR__STRUCT_H_
