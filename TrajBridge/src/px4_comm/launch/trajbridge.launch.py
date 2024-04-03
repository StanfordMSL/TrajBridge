from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='px4_comm',
            executable='state_machine_node.py',
            name='state_machine_0',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'auto_start': False},
                {'auto_land': False},
                {'wp_ready': [  0.00,  0.00, -1.00,  0.00]},
            ]
        )
    ])
