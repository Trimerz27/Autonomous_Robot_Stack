# Autonomous Robot Stack

![ROS 2](https://img.shields.io/badge/ROS%202-Jazzy-blue)
![Ubuntu](https://img.shields.io/badge/Ubuntu-24.04-orange)
![Language](https://img.shields.io/badge/Language-C++-brightgreen)
![Build](https://img.shields.io/badge/Build-CMake-red)

A modular ROS 2 robotics platform built in C++ using CMake, designed as a foundation for autonomous mobile robot development, aerial simulation, perception, and navigation.

---

# Project Overview

This repository demonstrates the development of a complete robotics software stack using modern ROS 2 practices.

The project currently includes:

- Robot description and modeling
- URDF/Xacro-based robot design
- ROS 2 package architecture
- C++ control nodes
- TF coordinate system management
- RViz visualization
- Launch system
- Modular workspace structure

The long-term goal is to evolve this into a complete autonomous robot platform.

---

# Technologies Used

| Category | Technology |
|---|---|
| Robotics Framework | ROS 2 Jazzy |
| Programming | C++ |
| Build System | CMake + colcon |
| OS | Ubuntu 24.04 LTS |
| Robot Modeling | URDF / Xacro |
| Visualization | RViz2 |
| Simulation | Gazebo |
| Navigation (Planned) | Nav2 |
| Control (Planned) | ros2_control |

---

# Repository Structure

```text
Autonomous_Robot_Stack/
│
Autonomous_Robot_Stack/
│
└── src/
    ├── robot_bringup/
    │   └── launch/
    │       └── vtol_simulation.launch.py   # Full system launch (Gz Sim + Robot State + Controllers)
    │
    ├── robot_control/
    │   └── src/
    │       ├── motor_controller_node.cpp    # Ground differential actuation hub
    │       └── vtol_flight_node.cpp         # Autonomous 3D state machine flight controller (C++)
    │
    ├── robot_description/
    │   ├── meshes/
    │   │   └── x8_wing.dae                  # Metallic silver VTOL airframe CAD asset
    │   └── urdf/
    │       └── inspection_robot.urdf.xacro  # Level, scaled, 3D aerial kinematic configuration
    │
    ├── robot_navigation/                    # Navigation and behavioral tracking (planned)
    └── robot_perception/                    # Live sensor pipelines and transformations (planned)
```

---

# Current Robot Model

The current robot is a differential-drive style mobile platform.

1. Ground Robotics Mode
   Kinematic Framework: Differential-drive mobile platform.
   Actuation Profiles: Twin isolated wheel joint velocity limits.
   TF Structure:text
   base_link / \ left_wheel right_wheel

2. Aerial Robotics Mode (VTOL Jet)
   Airframe Asset: Highly detailed silver X8 flying wing fuselage mesh layout.
   Spatial Constants: Scaled natively to metric workspace units (scale="0.001 0.001 0.001").
   Default State: Starts level, parallel to the ground grid, elevated at a 2-foot floating altitude.
   Simulation Physics: Controlled via the libgazebo_ros_planar_move.so 3D movement engine plugin.
---

# ROS 2 Architecture

Current system:

```text
        URDF / Xacro
             |
             v
  robot_state_publisher
             |
             v
            TF
             |
             v
           RViz2
```

Control foundation:

```text
motor_controller_node
          |
          v
    ROS 2 Topics
          |
          v
   Robot Hardware / Simulation
```

---

# Build Instructions

## Requirements

- Ubuntu 24.04
- ROS 2 Jazzy
- Gazebo Sim (Modern ros_gz_sim components)

---

## Clone Repository

```bash
# Clone the repository
git clone https://github.com/Trimerz27/Autonomous_Robot_Stack.git
cd Autonomous_Robot_Stack

# Set up global ROS environment 
source /opt/ros/jazzy/setup.zsh

# Compile with developer symlink optimization
colcon build --symlink-install

# Source local package installations
source install/setup.zsh
```

---

## Source ROS 2

```bash
source /opt/ros/jazzy/setup.bash
```

---

## Build Workspace

```bash
colcon build
```

---

## Source Workspace

```bash
source install/setup.bash
```

---

# Running the Robot Visualization

Launch the robot:

```bash
ros2 launch robot_description display.launch.py
```

This starts:

- robot_state_publisher
- joint_state_publisher
- RViz2

---

# Running the Controller

Start the controller node:

```bash
ros2 run robot_control motor_controller_node
```

Example:

```text
[INFO] Motor Controller started
[INFO] Max speed: 1.00
```

---

# Debugging Commands

Check active nodes:

```bash
ros2 node list
```

Check topics:

```bash
ros2 topic list
```

Check robot description:

```bash
ros2 topic echo /robot_description --once
```

Check TF:

```bash
ros2 run tf2_tools view_frames
```

---

# Development Roadmap

## Completed

- [x] ROS 2 Jazzy workspace
- [x] CMake package structure
- [x] C++ ROS 2 nodes
- [x] URDF/Xacro robot model
- [x] robot_state_publisher setup
- [x] TF tree
- [x] RViz visualization
- [x] Launch system

---

## In Progress

- [ ] Gazebo simulation
- [ ] ros2_control integration
- [ ] Differential drive controller
- [ ] Sensor integration

---

## Future Goals

- [ ] LiDAR perception
- [ ] Camera processing
- [ ] SLAM mapping
- [ ] Localization
- [ ] Nav2 autonomous navigation
- [ ] Obstacle avoidance
- [ ] Real hardware interface

---

# Project Purpose

This project is built to demonstrate practical robotics software engineering skills:

- ROS 2 development
- C++ programming
- Robot modeling
- Autonomous systems concepts
- Robotics software architecture

Designed as a portfolio project for robotics software engineering opportunities.

---

# Author

Joel Trimmer

Robotics / Autonomous Systems Portfolio Project
