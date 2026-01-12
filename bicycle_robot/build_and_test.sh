#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}================================================${NC}"
echo -e "${GREEN}  Bicycle Robot - Build and Test Script${NC}"
echo -e "${GREEN}================================================${NC}"

# Check if we're in the right directory
if [ ! -d "src/bicycle_control" ]; then
    echo -e "${RED}Error: Must run from workspace root (bicycle_robot/)${NC}"
    exit 1
fi

# Source ROS2
echo -e "\n${YELLOW}[1/5] Sourcing ROS2 Jazzy...${NC}"
source /opt/ros/jazzy/setup.bash
echo -e "${GREEN}✓ ROS2 sourced${NC}"

# Clean previous build
echo -e "\n${YELLOW}[2/5] Cleaning previous build...${NC}"
rm -rf build install log
echo -e "${GREEN}✓ Clean complete${NC}"

# Build workspace
echo -e "\n${YELLOW}[3/5] Building workspace...${NC}"
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
BUILD_STATUS=$?

if [ $BUILD_STATUS -eq 0 ]; then
    echo -e "${GREEN}✓ Build successful${NC}"
else
    echo -e "${RED}✗ Build failed${NC}"
    exit 1
fi

# Source workspace
echo -e "\n${YELLOW}[4/5] Sourcing workspace...${NC}"
source install/setup.bash
echo -e "${GREEN}✓ Workspace sourced${NC}"

# Run tests
echo -e "\n${YELLOW}[5/5] Running unit tests...${NC}"
colcon test --packages-select bicycle_control
TEST_STATUS=$?

echo -e "\n${YELLOW}Test results:${NC}"
colcon test-result --all --verbose

if [ $TEST_STATUS -eq 0 ]; then
    echo -e "\n${GREEN}================================================${NC}"
    echo -e "${GREEN}  ✓ All tests passed!${NC}"
    echo -e "${GREEN}================================================${NC}"
else
    echo -e "\n${RED}================================================${NC}"
    echo -e "${RED}  ✗ Some tests failed${NC}"
    echo -e "${RED}================================================${NC}"
    exit 1
fi

# Display summary
echo -e "\n${GREEN}Build Summary:${NC}"
echo -e "  Packages: bicycle_control_interfaces, bicycle_control"
echo -e "  Build type: Release"
echo -e "  Tests: Passed"

echo -e "\n${YELLOW}Next Steps:${NC}"
echo -e "  1. Terminal 1: ${GREEN}ros2 launch bicycle_control visualize.launch.py${NC}"
echo -e "  2. Terminal 2: ${GREEN}ros2 run bicycle_control path_follower_node${NC}"
echo -e "  3. Terminal 3: ${GREEN}ros2 action send_goal /follow_path bicycle_control_interfaces/action/FollowPath \"{}\"${NC}"

echo -e "\n${GREEN}================================================${NC}"
echo -e "${GREEN}  Build completed successfully!${NC}"
echo -e "${GREEN}================================================${NC}"
