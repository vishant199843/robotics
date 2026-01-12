cmake_minimum_required(VERSION 3.8)
project(bicycle_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(bicycle_control_interfaces REQUIRED)

# Include directories
include_directories(include)

# Bicycle model library
add_library(bicycle_model src/bicycle_model.cpp)
target_include_directories(bicycle_model PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Bezier planner library
add_library(bezier_planner src/bezier_planner.cpp)
target_include_directories(bezier_planner PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Pure pursuit library
add_library(pure_pursuit src/pure_pursuit.cpp)
target_include_directories(pure_pursuit PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Path follower node
add_executable(path_follower_node src/path_follower_node.cpp)
ament_target_dependencies(path_follower_node
  rclcpp
  rclcpp_action
  geometry_msgs
  nav_msgs
  visualization_msgs
  bicycle_control_interfaces)
target_link_libraries(path_follower_node
  bicycle_model
  bezier_planner
  pure_pursuit)

# Install targets
install(TARGETS
  bicycle_model
  bezier_planner
  pure_pursuit
  path_follower_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME})

# Install include files
install(DIRECTORY include/
  DESTINATION include/)

# Install launch files
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

# Install rviz config
install(DIRECTORY rviz
  DESTINATION share/${PROJECT_NAME})

# Testing
if(BUILD_TESTING)
  # find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  
  # Add gtest
  ament_add_gtest(test_bicycle_model test/test_bicycle_model.cpp)
  target_link_libraries(test_bicycle_model bicycle_model)
  
  # Linting
  # ament_lint_auto_find_test_dependencies()
endif()


# Testing
# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   find_package(ament_cmake_gtest REQUIRED)
  
#   # Add gtest
#   ament_add_gtest(test_bicycle_model test/test_bicycle_model.cpp)
#   if(TARGET test_bicycle_model)
#     # Link to your libraries
#     target_link_libraries(test_bicycle_model
#       bicycle_model
#       bezier_planner
#       pure_pursuit
#     )

#     # Include the headers
#     target_include_directories(test_bicycle_model PUBLIC
#       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#       $<INSTALL_INTERFACE:include>
#     )

#     # Dependencies
#     ament_target_dependencies(test_bicycle_model
#       rclcpp
#       rclcpp_action
#       geometry_msgs
#       nav_msgs
#       visualization_msgs
#       bicycle_control_interfaces
#     )
#   endif()

#   # Linting
#   ament_lint_auto_find_test_dependencies()
# endif()

ament_package()
