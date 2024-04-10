from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription(
        [
        Node(
            package='vrpn_mocap',
            executable='client_node',
            name='vrpn_client_0',
            namespace='vrpn_mocap',
            output='screen',
            emulate_tty=True,
            parameters=[{'server': 'mocap.local',
                         'port': 3883}]
            ),
        Node(
            package='px4_comm',
            executable='mocap_node.py',
            name='mocap_0',
            output='screen',
            emulate_tty=True,
            parameters=[
                {'asset_limit': 7},
                {'hz_topic_search': 0.5}
            ]
            )
        ]
        )
