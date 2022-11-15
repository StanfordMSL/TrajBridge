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
  TrigAC.srv
  SendXU.srv
)

catkin_python_setup()

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

add_executable(mocap_gen src/mocap_gen.cpp)
target_link_libraries(mocap_gen ${catkin_LIBRARIES})

add_executable(auto_rc src/auto_rc.cpp)
target_link_libraries(auto_rc ${catkin_LIBRARIES})

catkin_install_python(PROGRAMS src/gcs.py src/controller.py DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
