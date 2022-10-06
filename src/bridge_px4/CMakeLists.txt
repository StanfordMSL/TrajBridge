cmake_minimum_required(VERSION 3.0.2)
project(bridge_px4)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    mavros
    mavros_extras
    mavros_msgs
    mavlink
    message_generation
    )

find_package(Eigen3 REQUIRED)

add_message_files(
   FILES
   FlatSpline.msg
)

add_service_files(
  FILES
  SetACMode.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
   CATKIN_DEPENDS message_runtime std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

add_executable(setpoint_publisher src/setpoint_publisher.cpp)
target_link_libraries(setpoint_publisher ${catkin_LIBRARIES})