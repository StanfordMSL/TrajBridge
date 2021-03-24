#include <bridge_px4/GCS.h>

GCS::GCS()
{
    ros::param::get("~traj_id", traj_id);
    ros::param::get("~t_final", t_final);

    load_trajectory(traj_id);
    
    n_dr = st_traj.size();
    n_fr = st_traj[0][0].size();
    ROS_INFO("Trajectory Loaded");
    
    // ROS Initialization
    for (int i=0; i<n_dr; i++) {
        string drone_topic = "drone" + to_string(i+1) + "/gcs/setpoint/pose";
        pose_sp_pub[i] = nh.advertise<geometry_msgs::PoseStamped>(drone_topic,1);
    }
    ROS_INFO("ROS Publishers Initialized");

    // Counters and Time Initialization
    k_main = 0;
    k_traj = 0;
    k_loop = 0;

    t_start = ros::Time::now();
    t_end   = t_traj[n_fr-1];
    t_final = ros::Duration(t_final);

    ROS_INFO("Counters Initialized.");
}

GCS::~GCS()
{
  ROS_WARN("Terminating Publisher");
}

void GCS::update_setpoint()
{
    ros::Duration t_now = ros::Time::now() - t_start;
    ros::Duration t_wp = ros::Duration(t_traj[k_traj]);

    if (t_now <= t_final)
    {
        ros::Duration t_loop = t_now-ros::Duration(k_loop*t_end);

        if ((k_traj < n_fr) && (t_loop > t_wp))
        {
            for (int i = 0; i < n_dr; i++)
            {
                pose_sp[i].pose.position.x = st_traj[i][0][k_traj];
                pose_sp[i].pose.position.y = st_traj[i][1][k_traj];
                pose_sp[i].pose.position.z = st_traj[i][2][k_traj];

                double roll = 0.0f;
                double pitch = 0.0f;
                double yaw = st_traj[i][3][k_traj];

                double cy = cos(yaw * 0.5);
                double sy = sin(yaw * 0.5);
                double cp = cos(pitch * 0.5);
                double sp = sin(pitch * 0.5);
                double cr = cos(roll * 0.5);
                double sr = sin(roll * 0.5);

                pose_sp[i].pose.orientation.w = cr * cp * cy + sr * sp * sy;
                pose_sp[i].pose.orientation.x = sr * cp * cy - cr * sp * sy;
                pose_sp[i].pose.orientation.y = cr * sp * cy + sr * cp * sy;
                pose_sp[i].pose.orientation.z = cr * cp * sy - sr * sp * cy;
            }
            k_traj++;
        }
        else if ((k_traj >= n_fr))
        {
            k_traj = 0;
            k_loop++;
        }

        for (int i = 0; i < n_dr; i++)
        {
            pose_sp[i].header.stamp = ros::Time::now();
            pose_sp[i].header.seq = k_main;
            pose_sp[i].header.frame_id = "map";

            pose_sp_pub[i].publish(pose_sp[i]);
        }

        k_main++;
    }
    else
    {
        // Don't publish anymore.
    }
}

void GCS::load_trajectory(const string& input)
{   
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
        int k_dr, k_st;

        t_traj = vector<double>(n_fr);
        for (int i=1 ; i<cols ; i++) {
            t_traj[i] = parsedCsv[0][i];
        }

        st_traj = vector<vector<vector<double>>>(n_dr, vector<vector<double>>(4, vector<double>(n_fr)));
        for (int i=1 ; i<rows ; i++) {
            for (int j=0 ; j<cols ; j++) {
                k_dr = floor((i-1)/4);
                k_st = (i-1)-(k_dr*4);

                st_traj[k_dr][k_st][j] = parsedCsv[i][j];
            }
        }
    } else {
        cout << "Trajectory does not exist." << endl;
    }
    
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_node");

    GCS gcs;

    ros::Rate rate(100);
    while(ros::ok()){
        gcs.update_setpoint();
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
