#!/bin/bash

# Quick demo script for bicycle robot

echo "========================================="
echo "  Bicycle Robot - Quick Demo"
echo "========================================="
echo ""
echo "This script will start all necessary components."
echo "Press Ctrl+C to stop."
echo ""

# Source workspace
source /opt/ros/jazzy/setup.bash
source install/setup.bash

# Function to cleanup on exit
cleanup() {
    echo ""
    echo "Shutting down..."
    kill $(jobs -p) 2>/dev/null
    wait
    exit 0
}

trap cleanup SIGINT SIGTERM

# Start RViz in background
echo "[1/3] Starting RViz..."
ros2 launch bicycle_control visualize.launch.py &
RVIZ_PID=$!
sleep 3

# Start path follower node
echo "[2/3] Starting path follower node..."
ros2 run bicycle_control path_follower_node &
FOLLOWER_PID=$!
sleep 2

# Send goal
echo "[3/3] Sending goal to action server..."
sleep 1
ros2 action send_goal /follow_path bicycle_control_interfaces/action/FollowPath "{}" --feedback &

echo ""
echo "========================================="
echo "  Demo Running!"
echo "========================================="
echo "Watch RViz to see the robot follow the path"
echo "Press Ctrl+C to stop all nodes"
echo ""

# Wait for user interrupt
wait
