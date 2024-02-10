from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='px4_comm',
            executable='spline2velocity_node.py',
            name='spline2velocity_node_0',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'trajectory': "line"},
            ]
        )
    ])
