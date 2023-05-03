// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ObstacleDistance.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__OBSTACLE_DISTANCE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__OBSTACLE_DISTANCE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MAV_FRAME_GLOBAL'.
enum
{
  px4_msgs__msg__ObstacleDistance__MAV_FRAME_GLOBAL = 0
};

/// Constant 'MAV_FRAME_LOCAL_NED'.
enum
{
  px4_msgs__msg__ObstacleDistance__MAV_FRAME_LOCAL_NED = 1
};

/// Constant 'MAV_FRAME_BODY_FRD'.
enum
{
  px4_msgs__msg__ObstacleDistance__MAV_FRAME_BODY_FRD = 12
};

/// Constant 'MAV_DISTANCE_SENSOR_LASER'.
enum
{
  px4_msgs__msg__ObstacleDistance__MAV_DISTANCE_SENSOR_LASER = 0
};

/// Constant 'MAV_DISTANCE_SENSOR_ULTRASOUND'.
enum
{
  px4_msgs__msg__ObstacleDistance__MAV_DISTANCE_SENSOR_ULTRASOUND = 1
};

/// Constant 'MAV_DISTANCE_SENSOR_INFRARED'.
enum
{
  px4_msgs__msg__ObstacleDistance__MAV_DISTANCE_SENSOR_INFRARED = 2
};

/// Constant 'MAV_DISTANCE_SENSOR_RADAR'.
enum
{
  px4_msgs__msg__ObstacleDistance__MAV_DISTANCE_SENSOR_RADAR = 3
};

// Struct defined in msg/ObstacleDistance in the package px4_msgs.
typedef struct px4_msgs__msg__ObstacleDistance
{
  uint64_t timestamp;
  uint8_t frame;
  uint8_t sensor_type;
  uint16_t distances[72];
  float increment;
  uint16_t min_distance;
  uint16_t max_distance;
  float angle_offset;
} px4_msgs__msg__ObstacleDistance;

// Struct for a sequence of px4_msgs__msg__ObstacleDistance.
typedef struct px4_msgs__msg__ObstacleDistance__Sequence
{
  px4_msgs__msg__ObstacleDistance * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ObstacleDistance__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__OBSTACLE_DISTANCE__STRUCT_H_
