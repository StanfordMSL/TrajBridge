/**************************************************************************
  File Name    : visualizer.cpp
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Mar 31, 2021.
  Description  : Converts the posestamped msgs to path msgs for rviz
**************************************************************************/
#include <bridge_px4/visualizer.h>

Visualizer::Visualizer()
{
  ros::param::get("~n_dr", n_dr);
  ros::param::get("~dt", dt);    
  ros::param::get("~t_hist", t_hist);

  n_fr = t_hist/dt;

  for (int i=0; i<n_dr; i++) {
    string drone_des_topic = "drone" + to_string(i+1) + "/gcs/setpoint/pose";
    drone_des_sub[i] = nh.subscribe<geometry_msgs::PoseStamped>(drone_des_topic,1,boost::bind(&Visualizer::des_cb,this,_1,i));

    string drone_act_topic = "drone" + to_string(i+1) + "/mavros/vision_pose/pose";
    drone_act_sub[i] = nh.subscribe<geometry_msgs::PoseStamped>(drone_act_topic,1,boost::bind(&Visualizer::act_cb,this,_1,i));

    string vis_des_topic = "drone" + to_string(i+1) + "/gcs/visualization/path_des";
    path_des_pub[i] = nh.advertise<nav_msgs::Path>(vis_des_topic,1);

    string vis_act_topic = "drone" + to_string(i+1) + "/gcs/visualization/path_act";
    path_act_pub[i] = nh.advertise<nav_msgs::Path>(vis_act_topic,1);

  }

  updateLoop = nh.createTimer(ros::Duration(dt),&Visualizer::update_cb, this);
}

Visualizer::~Visualizer() {
  ROS_WARN("Terminating Visualizer");
}

void Visualizer::des_cb(const geometry_msgs::PoseStamped::ConstPtr& msg, const int idx){
    pose_des[idx] = *msg;
}

void Visualizer::act_cb(const geometry_msgs::PoseStamped::ConstPtr& msg, const int idx){
    pose_act[idx] = *msg;
}

void Visualizer::update_cb(const ros::TimerEvent& event) {
  ros::Time t_stamp = ros::Time::now();
  for (int i=0; i<n_dr; i++)
  {
    // Generate Headers
    path_act[i].header.stamp = t_stamp;
    path_act[i].header.frame_id = "world";
    path_des[i].header.stamp = t_stamp;
    path_des[i].header.frame_id = "world";

    // Update Paths
    path_des[i].poses.push_back(pose_des[i]);
    path_act[i].poses.push_back(pose_act[i]);

    // Keep Responsible Path Size
    if (path_des[i].poses.size() > n_fr) {
      path_des[i].poses.erase(path_des[i].poses.begin());
    }
    if (path_act[i].poses.size() > n_fr) {
      path_act[i].poses.erase(path_act[i].poses.begin());
    }

    // Publish Paths
    path_des_pub[i].publish(path_des[i]);
    path_act_pub[i].publish(path_act[i]);
  }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "visualizer_node");

    Visualizer vis;

    ros::spin();
    return 0;
}




 