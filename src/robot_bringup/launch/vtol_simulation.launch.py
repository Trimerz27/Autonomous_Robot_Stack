import os
import subprocess
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    pkg_description = get_package_share_directory('robot_description')
    pkg_simulation = get_package_share_directory('robot_simulation')
    
    xacro_file = os.path.join(pkg_description, 'urdf', 'inspection_robot.urdf.xacro')
    space_world = os.path.join(pkg_simulation, 'worlds', 'space_target.sdf')

    robot_desc_content = subprocess.check_output(['xacro', xacro_file]).decode('utf-8')

    model_path_env = SetEnvironmentVariable(
        name='GZ_SIM_RESOURCE_PATH',
        value=os.path.join(pkg_description, 'meshes')
    )

    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')
    gazebo_launch = os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_desc_content, 'use_sim_time': True}]
    )

    start_gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(gazebo_launch),
        launch_arguments={'gz_args': f'-r {space_world}'}.items()
    )

    spawn_vtol = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=['-string', robot_desc_content, '-name', 'standard_vtol', '-z', '3.0'],
        output='screen'
    )

    # Core parameter network bridge connecting ROS 2 and Gazebo topics directly
    ros_gz_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            '/model/standard_vtol/cmd_vel@geometry_msgs/msg/Twist]gz.msgs.Twist',
            '/model/standard_vtol/odometry@nav_msgs/msg/Odometry[gz.msgs.Odometry', # ADDED THIS TRACKER LINK
            '/model/ground_robot/cmd_vel@geometry_msgs/msg/Twist]gz.msgs.Twist',
            '/model/ground_robot/odometry@nav_msgs/msg/Odometry[gz.msgs.Odometry'
        ],
        output='screen'
    )

    run_ground_controller = Node(
        package='robot_control',
        executable='motor_controller_node',
        output='screen',
        parameters=[{'use_sim_time': True}]
    )

    run_flight_controller = Node(
        package='robot_control',
        executable='vtol_flight_node',
        output='screen',
        parameters=[{'use_sim_time': True}]
    )

    return LaunchDescription([
        model_path_env,
        robot_state_publisher,
        start_gazebo,
        spawn_vtol,
        ros_gz_bridge,
        run_ground_controller,
        run_flight_controller
    ])
