#include <bridge_px4/GCSVelTraj.h>

GCSVelTraj::GCSVelTraj()
{
    ros::param::get("~t_final", t_final);
    ros::param::get("~traj_id", traj_id);
    ros::param::get("~drone_id", drone_id);

    load_trajectory(traj_id);

    n_fr = st_traj[0].size();
    t_end   = t_traj[n_fr-1];

    ROS_INFO("Trajectory Loaded");

    // ROS Initialization
    string targetPose_topic = drone_id + "/command/pose";
    string targetTwist_topic = drone_id + "/command/twist";
    pose_sp_pub = nh.advertise<geometry_msgs::PoseStamped>(targetPose_topic,1);
    vel_sp_pub = nh.advertise<geometry_msgs::TwistStamped>(targetTwist_topic,1);

    ROS_INFO("ROS Publishers Initialized");

    // Counters and Time Initialization
    k_main = 0;
    k_traj = 0;
    k_loop = 0;

    t_start = ros::Time::now();

    ROS_INFO("Counters Initialized.");
}

GCSVelTraj::~GCSVelTraj()
{
  ROS_WARN("Terminating Publisher");
}

void GCSVelTraj::update_setpoint()
{
    // Time
    ros::Duration t_now = ros::Time::now() - t_start;
    ros::Duration t_wp = ros::Duration(t_traj[k_traj]);

    if (t_now <= ros::Duration(t_final))
    {
        ros::Duration t_loop = t_now - ros::Duration(k_loop*t_end);

        if ((k_traj < n_fr) && (t_loop > t_wp))
        {
            pose_sp.pose.position.x = st_traj[0][k_traj];
            pose_sp.pose.position.y = st_traj[1][k_traj];
            pose_sp.pose.position.z = st_traj[2][k_traj];

            double roll = 0.0f;
            double pitch = 0.0f;
            double yaw = st_traj[3][k_traj];

            double cy = cos(yaw * 0.5);
            double sy = sin(yaw * 0.5);
            double cp = cos(pitch * 0.5);
            double sp = sin(pitch * 0.5);
            double cr = cos(roll * 0.5);
            double sr = sin(roll * 0.5);

            pose_sp.pose.orientation.w = cr * cp * cy + sr * sp * sy;
            pose_sp.pose.orientation.x = sr * cp * cy - cr * sp * sy;
            pose_sp.pose.orientation.y = cr * sp * cy + sr * cp * sy;
            pose_sp.pose.orientation.z = cr * cp * sy - sr * sp * cy;

            vel_sp.twist.linear.x = st_traj[4][k_traj];
            vel_sp.twist.linear.y = st_traj[5][k_traj];
            vel_sp.twist.linear.z = st_traj[6][k_traj];
            vel_sp.twist.angular.z = st_traj[7][k_traj];

            k_traj++;
        }
        else if ((k_traj >= n_fr))
        {
            k_traj = 0;
            k_loop++;
        }

        ros::Time t_stamp = ros::Time::now();

        // Publish Pose
        pose_sp.header.stamp = t_stamp;
        pose_sp.header.seq = k_main;
        pose_sp.header.frame_id = "map";
        pose_sp_pub.publish(pose_sp);

        // Publish Twist
        vel_sp.header.stamp = t_stamp;
        vel_sp.header.seq = k_main;
        vel_sp.header.frame_id = "map";
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

        st_traj = vector< vector<double> >(8, vector<double>(n_fr));
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
