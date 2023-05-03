// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/UwbDistance.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__UWB_DISTANCE__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__UWB_DISTANCE__BUILDER_HPP_

#include "px4_msgs/msg/detail/uwb_distance__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_UwbDistance_position
{
public:
  explicit Init_UwbDistance_position(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::UwbDistance position(::px4_msgs::msg::UwbDistance::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_aoafirst
{
public:
  explicit Init_UwbDistance_aoafirst(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_position aoafirst(::px4_msgs::msg::UwbDistance::_aoafirst_type arg)
  {
    msg_.aoafirst = std::move(arg);
    return Init_UwbDistance_position(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_nlos
{
public:
  explicit Init_UwbDistance_nlos(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_aoafirst nlos(::px4_msgs::msg::UwbDistance::_nlos_type arg)
  {
    msg_.nlos = std::move(arg);
    return Init_UwbDistance_aoafirst(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_anchor_distance
{
public:
  explicit Init_UwbDistance_anchor_distance(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_nlos anchor_distance(::px4_msgs::msg::UwbDistance::_anchor_distance_type arg)
  {
    msg_.anchor_distance = std::move(arg);
    return Init_UwbDistance_nlos(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_status
{
public:
  explicit Init_UwbDistance_status(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_anchor_distance status(::px4_msgs::msg::UwbDistance::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_UwbDistance_anchor_distance(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_time_offset
{
public:
  explicit Init_UwbDistance_time_offset(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_status time_offset(::px4_msgs::msg::UwbDistance::_time_offset_type arg)
  {
    msg_.time_offset = std::move(arg);
    return Init_UwbDistance_status(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_sessionid
{
public:
  explicit Init_UwbDistance_sessionid(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_time_offset sessionid(::px4_msgs::msg::UwbDistance::_sessionid_type arg)
  {
    msg_.sessionid = std::move(arg);
    return Init_UwbDistance_time_offset(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_counter
{
public:
  explicit Init_UwbDistance_counter(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_sessionid counter(::px4_msgs::msg::UwbDistance::_counter_type arg)
  {
    msg_.counter = std::move(arg);
    return Init_UwbDistance_sessionid(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_time_uwb_ms
{
public:
  explicit Init_UwbDistance_time_uwb_ms(::px4_msgs::msg::UwbDistance & msg)
  : msg_(msg)
  {}
  Init_UwbDistance_counter time_uwb_ms(::px4_msgs::msg::UwbDistance::_time_uwb_ms_type arg)
  {
    msg_.time_uwb_ms = std::move(arg);
    return Init_UwbDistance_counter(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

class Init_UwbDistance_timestamp
{
public:
  Init_UwbDistance_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UwbDistance_time_uwb_ms timestamp(::px4_msgs::msg::UwbDistance::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_UwbDistance_time_uwb_ms(msg_);
  }

private:
  ::px4_msgs::msg::UwbDistance msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::UwbDistance>()
{
  return px4_msgs::msg::builder::Init_UwbDistance_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__UWB_DISTANCE__BUILDER_HPP_
