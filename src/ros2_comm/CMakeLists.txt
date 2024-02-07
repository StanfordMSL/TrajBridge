cmake_minimum_required(VERSION 3.5)
project(ros2_comm)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(eigen3_cmake_module REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(px4_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# # Generate ROS2 messages
# rosidl_generate_interfaces(${PROJECT_NAME}
#   "msg/HorizonSetpoint.msg"
# )

# Include Cpp "include" directory
include_directories(include)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# Install Mission files
install(DIRECTORY
  DESTINATION lib/${PROJECT_NAME}
)
# Install Launch files
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

# Install Python executables
install(PROGRAMS
  scripts/setpoint_position.py
  scripts/state_machine.py
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
