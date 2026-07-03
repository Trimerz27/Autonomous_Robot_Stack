import os
import subprocess
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    # 1. Track down folder locations inside the workspace execution share
    pkg_description = get_package_share_directory('robot_description')
    
    # Locate the exact xacro file we wrote earlier
    xacro_file = os.path.join(pkg_description, 'urdf', 'inspection_robot.urdf.xacro')

    # Convert Xacro file directly to a temporary flat URDF string
    robot_desc_content = subprocess.check_output(['xacro', xacro_file]).decode('utf-8')

    # Get the modern Gazebo Sim launch directory
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')
    gazebo_launch = os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')

    # 2. Start robot state publisher node
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description': robot_desc_content,
            'use_sim_time': True
        }]
    )

    # 3. Start Gazebo Sim with an empty world (-r runs it immediately)
    start_gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(gazebo_launch),
        launch_arguments={'gz_args': '-r empty.sdf'}.items()
    )

    # 4. Spawn the VTOL wing into modern Gazebo Sim using the XML text argument
    spawn_vtol = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=['-string', robot_desc_content, '-name', 'standard_vtol', '-z', '0.5'],
        output='screen'
    )

    # 5. Start your C++ flight controller node
    run_flight_controller = Node(
        package='robot_control',
        executable='vtol_flight_node',
        output='screen',
        parameters=[{'use_sim_time': True}]
    )

    return LaunchDescription([
        robot_state_publisher,
        start_gazebo,
        spawn_vtol,
        run_flight_controller
    ])
