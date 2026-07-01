# 🤖 Autonomous Robot Stack

![ROS 2](https://img.shields.io/badge/ROS%202-Jazzy-blue)
![Ubuntu](https://img.shields.io/badge/Ubuntu-24.04-orange)
![Language](https://img.shields.io/badge/Language-C++-brightgreen)
![Build](https://img.shields.io/badge/Build-CMake-red)

A modular ROS 2 robotics platform built in **C++** using **CMake**, designed as a foundation for autonomous mobile robot development, simulation, perception, and navigation.

---

# 📌 Project Overview

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
| Simulation (Planned) | Gazebo |
| Navigation (Planned) | Nav2 |
| Control (Planned) | ros2_control |

---

# Repository Structure

```text
Autonomous_Robot_Stack/
│
├── src/
│   │
│   ├── robot_bringup/
│   │   └── Launch and startup configuration
│   │
│   ├── robot_control/
│   │   │
│   │   └── src/
│   │       └── motor_controller_node.cpp
│   │
│   ├── robot_description/
│   │   │
│   │   ├── urdf/
│   │   │   └── inspection_robot.urdf.xacro
│   │   │
│   │   └── launch/
│   │       └── display.launch.py
│   │
│   ├── robot_navigation/
│   │   └── Navigation stack (planned)
│   │
│   └── robot_perception/
│       └── Sensor processing (planned)
│
└── README.md
```

---

# Current Robot Model

The current robot is a differential-drive style mobile platform.

Current components:

- Base chassis
- Left wheel
- Right wheel
- Wheel joints
- Robot coordinate frames

TF structure:

```text
              base_link
              /       \
     left_wheel     right_wheel
```

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
- colcon

---

## Clone Repository

```bash
git clone https://github.com/Trimerz27/Autonomous_Robot_Stack.git

cd Autonomous_Robot_Stack
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
