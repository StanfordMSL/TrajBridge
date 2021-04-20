#include <bridge_px4/GCSVel.h>

GCSVel::GCSVel()
{
    ros::param::get("~t_final", t_final);
    ros::param::get("~hover_x", hover_x);
    ros::param::get("~hover_y", hover_y);
    ros::param::get("~hover_z", hover_z);

    // ROS Initialization
    for (int i=0; i<n_dr; i++) {
        
        // Subscribe
        string drone_topic_sub = "drone" + to_string(i+1) + "/mavros/vision_pose/pose";
        pose_curr_sub[i] = nh.subscribe(drone_topic_sub,1,&SetpointPublisher::pose_curr_cb,this);

        // Publish
        string drone_topic_pub = "drone" + to_string(i+1) + "/gcs/setpoint/velocity";
        velocity_sp_pub[i] = nh.advertise<geometry_msgs::Twist>(drone_topic_pub,1);
    }

    ROS_INFO("ROS Publishers Initialized");

    // Initialize Gains
    kp = 1.0;
    ki = 1.0;
    kd = 1.0;

    integral_term = 0.0;
    n_dr = 7;

    vel_angular.x = 0;
    vel_angular.y = 0;
    vel_angular.z = 0;

    // Relevant Times
    t_start = ros::Time::now();
    t_prev = ros::Time::now();

    // Initialize Counter
    k_main = 0;

    ROS_INFO("Counters Initialized.");
}

GCSVel::~GCSVel()
{
  ROS_WARN("Terminating Publisher");
}

void GCSVel::compute_integral(double &integral_term, double prev_val, double curr_val, double dt_secs)
{
    double max_integral = 1.0;

    integral_term += (prev_val + curr_val)*dt_secs/2.0;

    if (integral_term >= max_integral)     // account for windup
    {
        integral_term = max_integral;
    }
}

void GCSVel::update_setpoint()
{
    // Time
    ros::Duration t_now = ros::Time::now() - t_start;
    ros::Duration dt = t_now - t_prev;
    ros::Duration t_prev = ros::Time::now() - t_start;
    double dt_secs = dt.toSec();

    // Error vectors
    vector<double> err_x(n_dr,0.0);
    vector<double> err_y(n_dr,0.0);
    vector<double> err_z(n_dr,0.0);
    vector<double> err_x_prev(n_dr,0.0);
    vector<double> err_y_prev(n_dr,0.0);
    vector<double> err_z_prev(n_dr,0.0);

    // integral term
    vector<double> integral_x(n_dr, 0.0);
    vector<double> integral_y(n_dr, 0.0);
    vector<double> integral_z(n_dr, 0.0);

    // Update Veloctiy Setpoints
    if (t_now <= ros::Duration(t_final))
    {
        for (int i = 0; i < n_dr; i++)
        {
            // Compute errors
            err_x[i] = hover_x - pose_curr_sub[i].pose.position.x;
            err_y[i] = hover_y - pose_curr_sub[i].pose.position.y;
            err_z[i] = hover_z - pose_curr_sub[i].pose.position.z;

            compute_integral(integral_x[i], err_x[i], err_x_prev[i], dt_secs);
            compute_integral(integral_y[i], err_y[i], err_y_prev[i], dt_secs);
            compute_integral(integral_z[i], err_z[i], err_z_prev[i], dt_secs);

            vel_sp[i].twist.linear.x = kp*err_x[i]
                                     + ki*integral_x[i]
                                     + kd*(err_x_prev[i] - err_x[i])/dt_secs;

            vel_sp[i].twist.linear.y = kp*err_y[i]
                                     + ki*integral_y[i]
                                     + kd*(err_y_prev[i] - err_y[i])/dt_secs;

            vel_sp[i].twist.linear.z = kp*err_z[i]
                                     + ki*integral_z[i]
                                     + kd*(err_z_prev[i] - err_z[i])/dt_secs;

            vel_sp[i].twist.angular = vel_angular;

            // Assign previous time step errors
            err_x_prev[i] = err_x[i];
            err_y_prev[i] = err_y[i];
            err_z_prev[i] = err_z[i];

            // Publish
            velocity_sp_pub[i].publish(vel_sp[i]);
        }

    }
    k_main++;
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
