// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/Mission.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MISSION__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__MISSION__BUILDER_HPP_

#include "px4_msgs/msg/detail/mission__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_Mission_current_seq
{
public:
  explicit Init_Mission_current_seq(::px4_msgs::msg::Mission & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::Mission current_seq(::px4_msgs::msg::Mission::_current_seq_type arg)
  {
    msg_.current_seq = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::Mission msg_;
};

class Init_Mission_count
{
public:
  explicit Init_Mission_count(::px4_msgs::msg::Mission & msg)
  : msg_(msg)
  {}
  Init_Mission_current_seq count(::px4_msgs::msg::Mission::_count_type arg)
  {
    msg_.count = std::move(arg);
    return Init_Mission_current_seq(msg_);
  }

private:
  ::px4_msgs::msg::Mission msg_;
};

class Init_Mission_dataman_id
{
public:
  explicit Init_Mission_dataman_id(::px4_msgs::msg::Mission & msg)
  : msg_(msg)
  {}
  Init_Mission_count dataman_id(::px4_msgs::msg::Mission::_dataman_id_type arg)
  {
    msg_.dataman_id = std::move(arg);
    return Init_Mission_count(msg_);
  }

private:
  ::px4_msgs::msg::Mission msg_;
};

class Init_Mission_timestamp
{
public:
  Init_Mission_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Mission_dataman_id timestamp(::px4_msgs::msg::Mission::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_Mission_dataman_id(msg_);
  }

private:
  ::px4_msgs::msg::Mission msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::Mission>()
{
  return px4_msgs::msg::builder::Init_Mission_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__MISSION__BUILDER_HPP_
