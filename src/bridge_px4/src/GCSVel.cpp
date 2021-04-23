#include <bridge_px4/GCSVel.h>

GCSVel::GCSVel()
{
    ros::param::get("~t_final", t_final);
    ros::param::get("~drone_id", drone_id);
    ros::param::get("~hover_x", hover_x);
    ros::param::get("~hover_y", hover_y);
    ros::param::get("~hover_z", hover_z);
    ros::param::get("~kp", kp);
    ros::param::get("~ki", ki);
    ros::param::get("~kd", kd);
    ros::param::get("~max_integral", max_integral);

    // ROS Initialization
    string drone_topic_sub = drone_id + "/mavros/vision_pose/pose";
    string drone_topic_pub = drone_id + "/setpoint/velocity";
    pose_curr_sub = nh.subscribe(drone_topic_sub,1,&GCSVel::pose_curr_cb,this);
    vel_sp_pub = nh.advertise<geometry_msgs::TwistStamped>(drone_topic_pub,1);

    ROS_INFO("ROS Publishers Initialized");

    // Error terms
    err_x = 0.0;
    err_y = 0.0;
    err_z = 0.0;
    err_x_prev = 0.0;
    err_y_prev = 0.0;
    err_z_prev = 0.0;

    // integral term
    integral_x = 0.0;
    integral_y = 0.0;
    integral_z = 0.0;

    vel_angular.x = 0;
    vel_angular.y = 0;
    vel_angular.z = 0;

    // Relevant Times
    t_start = ros::Time::now();
    t_prev = t_start - ros::Time::now();

    // Initialize Counter
    k_main = 0;

    ROS_INFO("Counters Initialized.");
}

GCSVel::~GCSVel()
{
  ROS_WARN("Terminating Publisher");
}

void GCSVel::pose_curr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    // ROS_INFO("Pose Callback");
    pose_t_curr = *msg;
}

void GCSVel::compute_integral(double &integral_term, double prev_val, double curr_val, double dt_secs)
{
    // ROS_INFO("Comptue Integral");
    integral_term += (prev_val + curr_val)*dt_secs/2.0;
    if (abs(integral_term) >= max_integral)     // account for windup
    {
        integral_term = copysign(max_integral, integral_term);
    }
}

void GCSVel::update_setpoint()
{
    // Time
    ros::Duration t_now = ros::Time::now() - t_start;
    ros::Duration dt = t_now - t_prev;
    t_prev = ros::Time::now() - t_start;
    double dt_secs = dt.toSec();

    // Update Veloctiy Setpoints
    if (t_now <= ros::Duration(t_final))
    {

        // Compute errors
        err_x = hover_x - pose_t_curr.pose.position.x;
        err_y = hover_y - pose_t_curr.pose.position.y;
        err_z = hover_z - pose_t_curr.pose.position.z;

        compute_integral(integral_x, err_x_prev, err_x, dt_secs);
        compute_integral(integral_y, err_y_prev, err_y, dt_secs);
        compute_integral(integral_z, err_z_prev, err_z, dt_secs);

        vel_sp.twist.linear.x = kp*err_x
                           + ki*integral_x
                           + kd*(err_x_prev - err_x)/dt_secs;

        vel_sp.twist.linear.y = kp*err_y
                           + ki*integral_y
                           + kd*(err_y_prev - err_y)/dt_secs;

        vel_sp.twist.linear.z = kp*err_z
                           + ki*integral_z
                           + kd*(err_z_prev - err_z)/dt_secs;

        vel_sp.twist.angular = vel_angular;

        // Assign previous time step errors
        err_x_prev = err_x;
        err_y_prev = err_y;
        err_z_prev = err_z;

        ros::Time t_stamp = ros::Time::now();
        vel_sp.header.stamp = t_stamp;
        vel_sp.header.seq = k_main;
        vel_sp.header.frame_id = "world";

        // Publish
        vel_sp_pub.publish(vel_sp);
        k_main++;
    }

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_vel_node");

    GCSVel gcs_vel;

    ros::Rate rate(100);
    while(ros::ok()){
        gcs_vel.update_setpoint();

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
