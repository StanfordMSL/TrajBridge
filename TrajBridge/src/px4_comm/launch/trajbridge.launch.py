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
                {'drone_name':"drone3"},
                {'auto_start': False},
                {'auto_land': False},
                {'wp_ready': [-2.80,  0.00, -0.50,  0.00]},
            ]
        )
    ])
