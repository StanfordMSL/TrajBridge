#include <bridge_px4/homing_pose.h>

HomingPose::HomingPose()
{
    ros::param::get("~drone_id", gquad_id);
    ros::param::get("~tf_x", tf_grasper.position.x);
    ros::param::get("~tf_y", tf_grasper.position.y);
    ros::param::get("~tf_z", tf_grasper.position.z);
    ros::param::get("~tf_qw", tf_grasper.orientation.w);
    ros::param::get("~tf_qx", tf_grasper.orientation.x);
    ros::param::get("~tf_qy", tf_grasper.orientation.y);
    ros::param::get("~tf_qz", tf_grasper.orientation.z);

    ros::param::get("~l2_tracking", l2_tracking);
    ros::param::get("~l2_pitbull", l2_pitbull);
    ros::param::get("~dt_pitbull", dt_pitbull);
    ros::param::get("~pos_offset", pos_offset);
    
    // ROS Initialization
    string pose_sp_topic    = "drone" + to_string(gquad_id) + "/gcs/setpoint/pose";
    string pose_gquad_topic = "drone" + to_string(gquad_id) + "/mavros/vision_pose/pose";
    string pose_targ_topic  = "target/mavros/vision_pose/pose";

    pose_sp_pub     = nh.advertise<geometry_msgs::PoseStamped>(pose_sp_topic,1);
    pose_gquad_sub  = nh.subscribe(pose_gquad_topic,1,&HomingPose::pose_gquad_cb,this);    
    pose_targ_sub   = nh.subscribe(pose_targ_topic,1,&HomingPose::pose_targ_cb,this);
    checkupLoop     = nh.createTimer(ros::Duration(1.0),&HomingPose::checkup_cb, this);

    ROS_INFO("ROS Components Initialized");

    // State Machine Initialization
    gquad_state    = PRELOCK;

    // Constants Initialized
    quat_forward.w = 1;
    quat_forward.x = 0;
    quat_forward.y = 0;
    quat_forward.z = 0;
}

HomingPose::~HomingPose() {
  ROS_WARN("Terminating Publisher");
}

void HomingPose::pose_gquad_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_t_gquad = *msg;
}

void HomingPose::pose_targ_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_t_targ = *msg;
}

Vector3d HomingPose::pos_rel_calc(geometry_msgs::Point a,geometry_msgs::Point b) {
    Vector3d err_pos;
    err_pos(0) = a.x - b.x;
    err_pos(1) = a.y - b.y;
    err_pos(2) = a.z - b.z;

    return err_pos;
}
void HomingPose::checkup_cb(const ros::TimerEvent& event) {
    Vector3d err_pos = pos_rel_calc(pose_t_gquad.pose.position,pose_sa.position);
    double l2_sa = err_pos.norm();

    if (l2_sa >= 0.2) {
        pose_sa.position = pose_t_gquad.pose.position;
        pose_sa.orientation = quat_forward;
    }
}

void HomingPose::update_setpoint()
{
switch (gquad_state)
    {
    case PRELOCK:
    {
        pose_t_sp_out.pose = pose_sa;
        pose_t_sp_out.pose.position.z = 2.0;

        Vector3d gquad2targ = pos_rel_calc(pose_t_gquad.pose.position,pose_t_targ.pose.position);
        double l2_prelock = gquad2targ.norm();

        if (l2_prelock <= l2_tracking) {
            gquad_state = TRACKING;
            ROS_INFO("Lock acquired. Proceeding to track");
        }
    }
    break;
    case TRACKING:
    {
        pose_t_sp_out.pose.position.x = pose_t_targ.pose.position.x;
        pose_t_sp_out.pose.position.y = pose_t_targ.pose.position.y;
        pose_t_sp_out.pose.position.z = pose_t_targ.pose.position.z + 0.5;

        Vector3d gquad2targ = pos_rel_calc(pose_t_gquad.pose.position,pose_t_targ.pose.position);

        double psi = atan2(gquad2targ[0],gquad2targ[1]);
        quaternionTFToMsg(createQuaternionFromYaw(psi),pose_t_sp_out.pose.orientation);

        double l2_tracking = gquad2targ.norm();

        if (l2_tracking <= l2_pitbull) {
            t_pitbull = ros::Time::now();
            gquad_state = PITBULL;
            ROS_INFO("GQuad going pitbull");
        }
    }
    break;
    case PITBULL:
    {   
        Vector3d gquad2targ = pos_rel_calc(pose_t_gquad.pose.position,pose_t_targ.pose.position);
        Vector3d pos_des = 1.1*gquad2targ;
        
        pose_t_sp_out.pose.position.x = pos_des[0];
        pose_t_sp_out.pose.position.y = pos_des[1];
        pose_t_sp_out.pose.position.z = pos_des[2];

        ros::Time t_now = ros::Time::now();
        if ( (t_now - t_pitbull) >= ros::Duration(dt_pitbull) ) {
            ROS_INFO("Trajectory Complete");
            gquad_state = COMPLETE;
        }
    }
    break;
    case COMPLETE:
    {
        pose_t_sp_out.pose = pose_sa;
        pose_t_sp_out.pose.position.z = 1.0;
    }
    break;
    default:
    {
        pose_t_sp_out.pose = pose_t_gquad.pose;
        pose_t_sp_out.pose.position.z = 0.0;
    }
    }

    pose_t_sp_out.header.stamp = ros::Time::now();
    pose_t_sp_out.header.seq   = k_main;
    pose_t_sp_out.header.frame_id = "map";
    k_main++;

    pose_sp_pub.publish(pose_t_sp_out);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_node");

    HomingPose hp;

    ros::Rate rate(100);
    while(ros::ok()){
        hp.update_setpoint();
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
