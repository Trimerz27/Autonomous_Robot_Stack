from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, PathJoinSubstitution

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    robot_description = Command([
        "xacro ",
        PathJoinSubstitution([
            FindPackageShare("robot_description"),
            "urdf",
            "inspection_robot.urdf.xacro"
        ])
    ])

    world = PathJoinSubstitution([
        FindPackageShare("robot_simulation"),
        "worlds",
        "empty.sdf"
    ])
		
    gazebo = IncludeLaunchDescription(
    	PythonLaunchDescriptionSource(
        	PathJoinSubstitution([
                    FindPackageShare("ros_gz_sim"),
                    "launch",
                    "gz_sim.launch.py"
                ])
         ),
   	 launch_arguments={
       		 "gz_args": ["-r ", world]
   	 }.items()
    ) 

    

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{
            "robot_description": robot_description
        }]
    )

    spawn_robot = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-topic",
            "robot_description",
            "-name",
            "inspection_robot",
            "-x", "0",
            "-y", "0",
            "-z", "0.5"
        ]
    )

    return LaunchDescription([
        gazebo,
        robot_state_publisher,
        spawn_robot
    ])
