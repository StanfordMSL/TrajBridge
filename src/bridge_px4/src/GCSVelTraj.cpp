#include <bridge_px4/GCSVelTraj.h>

GCSVelTraj::GCSVelTraj()
{
    ros::param::get("~t_final", t_final);
    ros::param::get("~drone_id", drone_id);
    ros::param::get("~kp_lin", kp_lin);
    ros::param::get("~ki_lin", ki_lin);
    ros::param::get("~kd_lin", kd_lin);
    ros::param::get("~kp_ang", kp_ang);
    ros::param::get("~ki_ang", ki_ang);
    ros::param::get("~kd_ang", kd_ang);
    ros::param::get("~max_integral", max_integral);
    ros::param::get("~traj_id", traj_id);

    load_trajectory(traj_id);

    n_fr = st_traj[0].size();
    t_end   = t_traj[n_fr-1];

    ROS_INFO("Trajectory Loaded");

    // ROS Initialization
    string drone_topic_sub = drone_id + "/mavros/vision_pose/pose";
    string drone_topic_pub = drone_id + "/setpoint/velocity";

    pose_curr_sub = nh.subscribe(drone_topic_sub,1,&GCSVelTraj::pose_curr_cb,this);
    vel_sp_pub = nh.advertise<geometry_msgs::TwistStamped>(drone_topic_pub,1);

    ROS_INFO("ROS Publishers Initialized");

    // Error terms
    err_x = 0.0;
    err_y = 0.0;
    err_z = 0.0;
    err_yaw = 0.0;

    err_x_prev = 0.0;
    err_y_prev = 0.0;
    err_z_prev = 0.0;
    err_yaw_prev = 0.0;

    // integral term
    integral_x = 0.0;
    integral_y = 0.0;
    integral_z = 0.0;
    integral_yaw = 0.0;

    vel_angular.x = 0.0;
    vel_angular.y = 0.0;
    vel_angular.z = 0.0;

    // Relevant Times
    t_start = ros::Time::now();
    t_prev = t_start - ros::Time::now();

    // Initialize Counter
    k_main = 0;
    k_traj = 0;
    k_loop = 0;

    ROS_INFO("Counters Initialized.");
}

GCSVelTraj::~GCSVelTraj()
{
  ROS_WARN("Terminating Publisher");
}

void GCSVelTraj::pose_curr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    // ROS_INFO("Pose Callback");
    pose_t_curr = *msg;
}

void GCSVelTraj::compute_integral(double &integral_term, double prev_val, double curr_val, double dt_secs)
{
    ROS_INFO("Comptue Integral");
    if ((integral_term >= max_integral && curr_val <= 0.0) ||
        (integral_term <= -max_integral && curr_val >= 0.0) ||
        (integral_term < max_integral && integral_term > -max_integral))     // account for windup
    {
        // ROS_INFO("INCREASE INTEGRAL");
        integral_term += (prev_val + curr_val)*dt_secs/2.0;
    }
}

void GCSVelTraj::update_setpoint()
{
    // Time
    ros::Duration t_now = ros::Time::now() - t_start;
    ros::Duration dt = t_now - t_prev;
    ros::Duration t_wp = ros::Duration(t_traj[k_traj]);
    t_prev = ros::Time::now() - t_start;
    double dt_secs = dt.toSec();

    // Update Veloctiy Setpoints
    if (t_now <= ros::Duration(t_final))
    {
        ros::Duration t_loop = t_now - ros::Duration(k_loop*t_end);
        if ((k_traj < n_fr) && (t_loop > t_wp))
        {
            // Compute position errors
            err_x = st_traj[0][k_traj] - pose_t_curr.pose.position.x;
            err_y = st_traj[1][k_traj] - pose_t_curr.pose.position.y;
            err_z = st_traj[2][k_traj] - pose_t_curr.pose.position.z;

            // Compute yaw error
            double qw = pose_t_curr.pose.orientation.w;
            double qx = pose_t_curr.pose.orientation.x;
            double qy = pose_t_curr.pose.orientation.y;
            double qz = pose_t_curr.pose.orientation.z;
            double yaw_curr = atan2(2*(qw*qz + qx*qy), 1 - 2*(qy*qy + qz*qz));
            err_yaw = st_traj[3][k_traj] - yaw_curr;

            // Compute integral terms
            compute_integral(integral_x, err_x_prev, err_x, dt_secs);
            compute_integral(integral_y, err_y_prev, err_y, dt_secs);
            compute_integral(integral_z, err_z_prev, err_z, dt_secs);
            compute_integral(integral_yaw, err_yaw_prev, err_yaw, dt_secs);

            // Velocity Setpoints
            vel_sp.twist.linear.x = kp_lin*err_x
                               + ki_lin*integral_x
                               + kd_lin*(err_x_prev - err_x)/dt_secs;

            vel_sp.twist.linear.y = kp_lin*err_y
                               + ki_lin*integral_y
                               + kd_lin*(err_y_prev - err_y)/dt_secs;

            vel_sp.twist.linear.z = kp_lin*err_z
                               + ki_lin*integral_z
                               + kd_lin*(err_z_prev - err_z)/dt_secs;

            vel_sp.twist.angular = vel_angular;

            vel_sp.twist.angular.z = kp_ang*err_yaw
                                   + ki_ang*integral_yaw
                                   + kd_ang*(err_yaw_prev - err_yaw)/dt_secs;

            // Assign previous time step errors
            err_x_prev = err_x;
            err_y_prev = err_y;
            err_z_prev = err_z;
            err_yaw_prev = err_yaw;

            k_traj++;
        }
        else if ((k_traj >= n_fr))
        {
            k_traj = 0;
            k_loop++;
        }

        ros::Time t_stamp = ros::Time::now();
        vel_sp.header.stamp = t_stamp;
        vel_sp.header.seq = k_main;
        vel_sp.header.frame_id = "world";

        // Publish
        vel_sp_pub.publish(vel_sp);

        k_main++;
    }
    else
    {
        // Don't publish anymore.
    }

}

void GCSVelTraj::load_trajectory(const string& input)
{
    ifstream data(input.c_str());
    if (data.is_open()) {
        int rows = 0;
        int cols = 0;

        string line;
        vector< vector<double> > parsedCsv;

        while(getline(data,line))
        {
            stringstream lineStream(line);
            string cell;
            vector<double> parsedRow;
            while(getline(lineStream,cell,','))
            {
                parsedRow.push_back(strtod(cell.c_str(), NULL));

                if (rows == 0) {
                    cols += 1;
                }
            }
            parsedCsv.push_back(parsedRow);
            rows += 1;
        }

        int n_fr = cols;

        t_traj = vector<double>(n_fr);
        for (int i=1 ; i<cols ; i++) {
            t_traj[i] = parsedCsv[0][i];
        }

        st_traj = vector< vector<double> >(4, vector<double>(n_fr));
        for (int i=1 ; i<rows ; i++) {
            for (int j=0 ; j<cols ; j++) {
                st_traj[i-1][j] = parsedCsv[i][j];
            }
        }
    } else {
        cout << "Trajectory does not exist." << endl;
    }

    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_vel_traj_node");

    GCSVelTraj gcs_vel_traj;

    ros::Rate rate(100);
    while(ros::ok()){
        gcs_vel_traj.update_setpoint();

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
