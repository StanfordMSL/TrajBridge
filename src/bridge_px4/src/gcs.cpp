#include <bridge_px4/gcs.h>

GCS::GCS()
{
    ros::param::get("~drone_id", drone_id);

    pos_sp_pub  = nh.advertise<geometry_msgs::PointStamped>(drone_id+"/setpoint/position",1);
    vel_sp_pub  = nh.advertise<geometry_msgs::Vector3Stamped>(drone_id+"/setpoint/velocity",1);
    att_sp_pub  = nh.advertise<geometry_msgs::QuaternionStamped>(drone_id+"/setpoint/attitude",1);
    rat_sp_pub  = nh.advertise<geometry_msgs::Vector3Stamped>(drone_id+"/setpoint/bodyrate",1);
    thr_sp_pub  = nh.advertise<mavros_msgs::Thrust>(drone_id+"/setpoint/throttle",1);
    ROS_INFO("ROS Components Initialized.");

    // Counters and Time Initialization
    pos_sp.header.frame_id = "map";
    vel_sp.header.frame_id = "map";
    att_sp.header.frame_id = "map";
    rat_sp.header.frame_id = "map";
    thr_sp.header.frame_id = "map";

    k_main = 0;

    ROS_INFO("Counters Initialized.");
}

GCS::~GCS()
{
  ROS_WARN("Terminating Publisher");
}

void GCS::update_setpoint()
{
    ros::Time t_now = ros::Time::now();

    pos_sp.header.seq = k_main;
    pos_sp.header.stamp = t_now;
    pos_sp.point.x = 0.5;
    pos_sp.point.y = 0.5;
    pos_sp.point.z = 0.5;

    vel_sp.header.seq = k_main;
    vel_sp.header.stamp = t_now;
    vel_sp.vector.x = 0.5;
    vel_sp.vector.y = 0.5;
    vel_sp.vector.z = 0.5;

    att_sp.header.seq = k_main;
    att_sp.header.stamp = t_now;
    att_sp.quaternion.w = 0.0;
    att_sp.quaternion.x = 1.0;
    att_sp.quaternion.y = 0.0;
    att_sp.quaternion.z = 0.0;

    rat_sp.header.seq = k_main;
    rat_sp.header.stamp = t_now;
    rat_sp.vector.x = 0.5;
    rat_sp.vector.y = 0.5;
    rat_sp.vector.z = 0.5;

    thr_sp.header.seq = k_main;
    thr_sp.header.stamp = t_now;
    thr_sp.thrust = 0.5;

    pos_sp_pub.publish(pos_sp);
    // vel_sp_pub.publish(vel_sp);
    att_sp_pub.publish(att_sp);
    // rat_sp_pub.publish(rat_sp);
    // thr_sp_pub.publish(thr_sp);

    k_main += 1;

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_node");

    GCS gcs;

    ros::Rate rate(20);
    while(ros::ok()){
        gcs.update_setpoint();

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
