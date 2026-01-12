# Bicycle Model Robot - ROS2 Jazzy Implementation

## Overview
This project implements a bicycle model robot with trajectory planning and path following capabilities using ROS2 Jazzy.

## Components
1. **Bicycle Model**: Forward kinematics for a bicycle model vehicle
2. **Bézier Trajectory Planner**: Generates smooth cubic Bézier curve trajectories
3. **Pure Pursuit Controller**: Path following controller using ROS2 action server

## Prerequisites
- Docker
- Git

## Quick Start

### 1. Build Docker Image
```bash
cd bicycle_robot
docker build -t bicycle_robot:jazzy .
```

### 2. Run Docker Container
```bash
sudo docker run -it --rm \
  --name bicycle_robot \
  -v $(pwd):/workspace \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  --network host \
  bicycle_robot:jazzy
```

### 3. Build the Workspace
```bash
cd /workspace
colcon build --symlink-install
source install/setup.bash
```

### 4. Run Unit Tests
```bash
colcon test
colcon test-result --all --verbose
```

### 5. Run the Demo

#### Terminal 1: Launch RViz
```bash
sudo docker exec -it bicycle_robot bash
source install/setup.bash
ros2 launch bicycle_control visualize.launch.py
```

#### Open Terminal 2: Run Path Following Action Server
```bash
sudo docker exec -it bicycle_robot bash
source install/setup.bash
ros2 run bicycle_control path_follower_node
```

#### Terminal 3: Send Goal (in a new terminal inside the container)
```bash
sudo docker exec -it bicycle_robot bash
source install/setup.bash
ros2 action send_goal /follow_path bicycle_control_interfaces/action/FollowPath "{}"
```

## Project Structure
```
bicycle_robot/
├── src/
│   ├── bicycle_control/          # Main control package
│   │   ├── include/bicycle_control/
│   │   │   ├── bicycle_model.hpp
│   │   │   ├── bezier_planner.hpp
│   │   │   └── pure_pursuit.hpp
│   │   ├── src/
│   │   │   ├── bicycle_model.cpp
│   │   │   ├── bezier_planner.cpp
│   │   │   ├── pure_pursuit.cpp
│   │   │   ├── path_follower_node.cpp
│   │   │   └── trajectory_publisher_node.cpp
│   │   ├── test/
│   │   │   └── test_bicycle_model.cpp
│   │   ├── launch/
│   │   │   └── visualize.launch.py
│   │   ├── rviz/
│   │   │   └── config.rviz
│   │   ├── CMakeLists.txt
│   │   └── package.xml
│   └── bicycle_control_interfaces/ # Custom message/action definitions
│       ├── action/
│       │   └── FollowPath.action
│       ├── CMakeLists.txt
│       └── package.xml
├── Dockerfile
└── README.md
```

## Section 1: Bicycle Model

### Continuous-Time Forward Kinematics
The bicycle model uses the following continuous-time equations:

```
ẋ = v * cos(θ)
ẏ = v * sin(θ)
θ̇ = (v / L) * tan(δ)
```

Where:
- `(x, y)` is the position of the rear wheel
- `θ` is the heading angle
- `v` is the linear velocity
- `L` is the wheelbase
- `δ` is the steering angle

### Discrete-Time Update Equations
Using Euler integration with time step `dt`:

```
x_{k+1} = x_k + v * cos(θ_k) * dt
y_{k+1} = y_k + v * sin(θ_k) * dt
θ_{k+1} = θ_k + (v / L) * tan(δ) * dt
```

### Physical Constraints
- Maximum steering angle: ±45° (±0.785 rad)
- Minimum turning radius: `L / tan(δ_max)`
- Wheelbase: 2.0 m (default)

## Section 2: Bézier Trajectory Planner

Generates a smooth cubic Bézier curve from start pose `(0, 0, 0°)` to goal pose `(10, 5, 45°)`.

### Features
- Cubic Bézier curve with 4 control points
- Smooth velocity profile
- Bounded curvature
- RViz visualization with path markers

### Control Points Calculation
- P0: Start position
- P1: Start position + offset in start heading direction
- P2: Goal position - offset in goal heading direction
- P3: Goal position

## Section 3: Pure Pursuit Controller

Implements a pure pursuit algorithm for path following with ROS2 action server.

### Features
- Lookahead distance: 1.0 m (adjustable)
- Target velocity: 1.0 m/s
- Action feedback: distance to goal
- Real-time path tracking visualization

### Action Server
- **Action**: `bicycle_control_interfaces/action/FollowPath`
- **Topic**: `/follow_path`
- **Feedback**: Current distance to goal
- **Result**: Success status and final distance



## Testing

Unit tests cover:
- ✅ Straight line motion
- ✅ Left turn
- ✅ Right turn
- ✅ Edge cases (zero velocity, max steering)
- ✅ Physical constraints validation

Run tests:
```bash
colcon test --packages-select bicycle_control
colcon test-result --verbose
colcon test --packages-select bicycle_control --event-handlers console_direct+   #  results with output 

```









## License
MIT License

## Author
C++ Robotics Software Engineer Assignment Solution
