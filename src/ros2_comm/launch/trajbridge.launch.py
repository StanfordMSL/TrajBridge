from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='sfti_ros_com',
            executable='state_machine.py',
            name='state_machine_0',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'wp_ready': [  0.0,  0.0, -5.0,  0.0]},
            ]
        )
    ])
