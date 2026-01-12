# CMake generated Testfile for 
# Source directory: /workspace/src/bicycle_control
# Build directory: /workspace/build/bicycle_control
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_bicycle_model "/usr/bin/python3" "-u" "/opt/ros/jazzy/share/ament_cmake_test/cmake/run_test.py" "/workspace/build/bicycle_control/test_results/bicycle_control/test_bicycle_model.gtest.xml" "--package-name" "bicycle_control" "--output-file" "/workspace/build/bicycle_control/ament_cmake_gtest/test_bicycle_model.txt" "--command" "/workspace/build/bicycle_control/test_bicycle_model" "--gtest_output=xml:/workspace/build/bicycle_control/test_results/bicycle_control/test_bicycle_model.gtest.xml")
set_tests_properties(test_bicycle_model PROPERTIES  LABELS "gtest" REQUIRED_FILES "/workspace/build/bicycle_control/test_bicycle_model" TIMEOUT "60" WORKING_DIRECTORY "/workspace/build/bicycle_control" _BACKTRACE_TRIPLES "/opt/ros/jazzy/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/jazzy/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;95;ament_add_test;/opt/ros/jazzy/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/workspace/src/bicycle_control/CMakeLists.txt;84;ament_add_gtest;/workspace/src/bicycle_control/CMakeLists.txt;0;")
subdirs("gtest")
