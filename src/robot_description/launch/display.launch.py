from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command


def generate_launch_description():

    robot_description = Command([
        "xacro ",
        "src/robot_description/urdf/inspection_robot.urdf.xacro"
    ])

    return LaunchDescription([

        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            parameters=[
                {
                    "robot_description": robot_description
                }
            ],
            output="screen"
        ),

        Node(
            package="joint_state_publisher",
            executable="joint_state_publisher",
            output="screen"
        ),

        Node(
            package="rviz2",
            executable="rviz2",
            output="screen"
        )

    ])
