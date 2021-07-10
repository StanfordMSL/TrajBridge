#include <bridge_px4/mocap_gen.h>

MocapGen::MocapGen()
{
    // Subscribe to mavros/local_position/pose
    //pose_curr_sub = nh.subscribe("mavros/local_position/pose",1,&MocapGen::pose_sp_cb,this);
    pose_curr_sub = nh.subscribe("gazebo/model_states/pose",1,&MocapGen::pose_cb,this);

    // Publish to mavros/vision_pose/pose
    string drone_topic = "mavros/vision_pose/pose";
    pose_curr_pub = nh.advertise<geometry_msgs::PoseStamped>(drone_topic,1);

    ROS_INFO("ROS Publishers Initialized");
}

MocapGen::~MocapGen()
{
  ROS_WARN("Terminating Publisher");
}

void MocapGen::pose_cb(const gazebo_msgs::ModelStates::ConstPtr& msg){
    pose_curr_in = msg->pose[2];
}

void MocapGen::update_setpoint()
{
    pose_curr_out.header.stamp = ros::Time::now();
    pose_curr_out.header.seq   = k_main;
    pose_curr_out.header.frame_id = "world";

    pose_curr_out.pose = pose_curr_in;
    // ROS_INFO("PUBLISH MOCAP");
    pose_curr_pub.publish(pose_curr_out);

    k_main += 1;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "mocap_gen_node");

    MocapGen mocap_gen;

    // ROS_INFO("SET OFFBOARD");
    // mavros_msgs::SetMode offb_set_mode;
    // offb_set_mode.request.custom_mode = "OFFBOARD";
    //
    // mavros_msgs::CommandBool arm_cmd;
    // arm_cmd.request.value = true;

    ros::Rate rate(100);
    while(ros::ok()){

        mocap_gen.update_setpoint();

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
