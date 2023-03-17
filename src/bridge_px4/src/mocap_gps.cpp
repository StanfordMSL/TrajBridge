#include <bridge_px4/mocap_gps.h>

MocapGPS::MocapGPS()
{
    ros::param::get("~drone_name", drone_name);
    ros::param::get("~x_init", x_init);
    ros::param::get("~y_init", y_init);

    // Subscribe to mavros/local_position/pose
    pose_curr_sub = nh.subscribe("/vrpn_client_node/" + drone_name + "/pose",1,&MocapGPS::pose_cb,this);

    // Publish to mavros/vision_pose/pose
    string drone_topic = drone_name + "/mavros/vision_pose/pose";
    pose_curr_pub = nh.advertise<geometry_msgs::PoseStamped>(drone_topic,1);

    ROS_INFO("ROS Publishers Initialized");
}

MocapGPS::~MocapGPS()
{
  ROS_WARN("Terminating Publisher");
}

void MocapGPS::pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_curr_out = *msg;

    pose_curr_out.pose.position.x -= x_init;
    pose_curr_out.pose.position.y -= y_init;

    pose_curr_pub.publish(pose_curr_out);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "mocap_gps_node");

    MocapGPS mocap_gps;

    // ROS_INFO("SET OFFBOARD");
    // mavros_msgs::SetMode offb_set_mode;
    // offb_set_mode.request.custom_mode = "OFFBOARD";
    //
    // mavros_msgs::CommandBool arm_cmd;
    // arm_cmd.request.value = true;

    ros::Rate rate(100);
    while(ros::ok()){
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
