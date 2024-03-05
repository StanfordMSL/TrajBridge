from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='px4_comm',
            executable='mocap_node.py',
            name='mocap_0',
            output='screen',
            emulate_tty=True,
        )
    ])
