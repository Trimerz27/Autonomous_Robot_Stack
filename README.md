# Autonomous Robot Stack

![ROS 2](https://img.shields.io/badge/ROS%202-Jazzy-blue)
![Ubuntu](https://img.shields.io/badge/Ubuntu-24.04-orange)
![Language](https://img.shields.io/badge/Language-C++-brightgreen)
![Build](https://img.shields.io/badge/Build-CMake-red)

A modular, multi-agent ROS 2 robotics platform built in C++ using CMake, designed as a foundation for autonomous mobile robot development, cooperative swarm simulation, and closed-loop control tracking within space-themed low-gravity environments.

---

# Project Overview

This repository demonstrates the development of a complete multi-robot software stack using modern ROS 2 practices.

The project features a coordinated Ground-to-Aerial Swarm Tracking Loop running inside modern Gazebo Sim:

1. Ground Rover Target: A 4-wheeled planetary rover chassis running a continuous circular cruise trajectory over dark cosmic soil.

2. Aerial Escort Jet: A hybrid metallic-silver fixed-wing VTOL airframe utilizing a zero-gravity hardware physics lock to maintain a stable flight altitude ceiling while continuously tracking the rover directly from above.
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
| Network Layer | ros_gz_bridge (Asynchronous Telemetry/Actuation Mapping) |

---

# Repository Structure

```text
Autonomous_Robot_Stack/
│
└── src/
    ├── robot_bringup/
    │   └── launch/
    │       └── vtol_simulation.launch.py   # Full multi-agent swarm deployment launch file
    │
    ├── robot_control/
    │   ├── CMakeLists.txt                  # Authorized link references to standard nav_msgs
    │   ├── package.xml                     # Integrated package dependencies manifest
    │   └── src/
    │       ├── motor_controller_node.cpp    # Ground vehicle circular cruising node (C++)
    │       └── vtol_flight_node.cpp         # 2D relative closed-loop proportional flight tracker (C++)
    │
    ├── robot_description/
    │   ├── meshes/
    │   │   ├── ground_vehicle/             # Omnidirectional vehicle spatial geometry files
    │   │   └── x8_wing.dae                  # Metallic silver VTOL airframe CAD asset
    │   └── urdf/
    │       └── inspection_robot.urdf.xacro  # Level, self-tracking aerial airframe description
    │
    └── robot_simulation/
        ├── CMakeLists.txt                  # Directory distribution and data sharing rules
        └── worlds/
            └── space_target.sdf             # Embedded dark cosmic ground world configuration
```

---

# Current Robot Model

The current robot is a differential-drive style mobile platform.

1. Ground Robotics Mode
   Physics Framework: Leverages the native gz-sim-velocity-control-system plugin embedded directly inside the      world file to actuate its wheels.

   Telemetry Broadcasting: Utilizes an integrated gz-sim-odometry-publisher-system to feed live location           tracking information to the network bridge on the /model/ground_robot/odometry channel.

    Actuation Loop: Driven by motor_controller_node.cpp to run an ongoing, automated circular track across the      ground plane.

3. Aerial Robotics Mode (VTOL Jet)
  Altitude Stabilization: Configured with a <gravity>0</gravity> hardware physics override to eliminate           vertical drift, allowing the drone to stay floating level at its designated spawn altitude of 2.5 meters.

   Proportional (P) Flight Control: The C++ vtol_flight_node subscribes asynchronously to both the ground rover's odometry and the jet's own telemetry tracking frames. It continuously calculates the exact relative distance gap between the two robots to adjust steering outputs on-the-fly:
   {Error}_{x}=X_{target}}-X_{jet}
   {Velocityx}=K_{p}\times {Error}_{x}
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

Robotics & Autonomous Systems Software Engineer Portfolio Project
