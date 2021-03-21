#include <bridge_px4/GCS.h>

GCS::GCS()
{
    ros::param::get("~traj_id", traj_id);
    ros::param::get("~t_final", t_final);

    traj = load_traj(traj_id);
    n_dr = traj.size();
    n_fr = 
    drone_ids = 


    // ROS Initialization
    for (int i=0; i<n_dr; i++) {
        pose_sp_pub[i] = nh.advertise<geometry_msgs::PoseStamped>(drone_id[i]+"/gcs/setpoint/pose",1);
    }

    ROS_INFO("ROS Components Initialized");

    vector<vector<double>> traj_dr = load_traj(traj_id);
    int n_r = traj_dr.rows();
    int n_c = traj_dr.cols();
    
    N_traj = n_c;
    traj.resize(n_r+1,n_c+1);
    traj.block(0,0,n_r,n_c) = m_pose;

    // Counter and Time Initialization
    count_main = 0;
    count_traj = 0;
    count_loop = 0;

    t_start = ros::Time::now();

    ROS_INFO("Counters Initialized.");
}

GCS::~GCS()
{
  ROS_WARN("Terminating Publisher");
}

void GCS::update_setpoint()
{   
    ros::Duration t_now = ros::Time::now() - t_start;
    ros::Duration t_wp = ros::Duration(traj(0,count_traj)) + ros::Duration(count_loop*traj(0,N_traj-1));

    if ((t_now > t_wp) && (count_traj < N_traj))
    {
        pose_sp.pose.position.x = traj(1, count_traj);
        pose_sp.pose.position.y = traj(2, count_traj);
        pose_sp.pose.position.z = traj(3, count_traj);

        double roll = 0.0f;
        double pitch = 0.0f;
        double yaw = traj(4, count_traj);

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

        count_traj++;
    }
    else if ((t_now > t_wp) && (count_traj >= N_traj))
    {
        count_traj = 0;
        count_loop++;
    }
    else
    {
        // Still Tracking Waypoints
    }

    if (t_now <= ros::Duration(t_final))
    {
        pose_sp.header.stamp = ros::Time::now();
        pose_sp.header.seq = count_main;
        pose_sp.header.frame_id = "map";
        count_main++;

        pose_sp_pub.publish(pose_sp);
        cout << "Traj Time " << t_now << endl;
        cout << "Heading to: \n " << pose_sp.pose.position << endl;
    }
    else
    {
        // Don't publish anymore.
    }
    
}

vector<vector<vector<double>>>  GCS::load_trajectory(const std::string& input)
{   
    vector<vector<vector<double>>>drone_traj;
    ifstream data(input);
    if (data.is_open()) {
        int rows = 0;
        int cols = 0;
        
        string line;
        vector<vector<double>> parsedCsv;

        while(getline(data,line))
        {
            stringstream lineStream(line);
            string cell;
            vector<double> parsedRow;
            while(getline(lineStream,cell,','))
            {
                parsedRow.push_back(stod(cell));
            
                if (rows == 0) {
                    cols += 1;
                }
            }
            parsedCsv.push_back(parsedRow);
            rows += 1;
        }
        
        int n_dr = (rows-1)/4;
        int n_fr = cols;
    
        for (int i=0 ; i<n_dr ; i++) {
            for (int j=0 ; j<4 ; j++) {
                for (int k=0 ; k<n_fr ; k++) {
                }
            }
        }

    } else {
        cout << "Trajectory does not exist." << endl;
    }
    
    return drone_traj;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_node");

    GCS gcs;

    ros::Rate rate(100);
    while(ros::ok()){
        //sp.param_update();
        gcs.update_setpoint();
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
