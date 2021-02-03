#include <bridge_px4/sp_pos_e_node.h>


SetpointPublisher::SetpointPublisher(ros::NodeHandle *nh, const std::string& traj_id, const float& t_fs_i, const float& err_tol_i)
{
    // ROS Initialization
    pose_sp_pub = nh->advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    state_sub   = nh->subscribe("mavros/state",1,&SetpointPublisher::state_cb,this);
    pose_sub    = nh->subscribe("mavros/local_position/pose",1,&SetpointPublisher::pose_cb,this);
    land_client = nh->serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land");
    tune_client = nh->serviceClient<mavros_msgs::ParamSet>("mavros/param/set");

    ROS_INFO("ROS Components Initialized");

    MatrixXd m_pose = load_trajectory(traj_id);
    N_traj = m_pose.cols();
    int N_x = m_pose.rows();

    traj.block(0,0,N_x,N_traj) = m_pose;

    // Setpoint Stream Initialization
    sp_status = SP_STREAM_READY;

    // Counter and Time Initialization
    count_main = 0;
    count_traj = 0;
    count_loop = 0;
    ROS_INFO("Counters Initialized.");

    // Drone Parameters
    t_fs = t_fs_i;
    err_tol = err_tol_i;
    ROS_INFO("Tuning Parameters Loaded.");

    ROS_INFO("Setpoint Publisher Ready.");
}

void SetpointPublisher::state_cb(const mavros_msgs::State::ConstPtr& msg){
    mode_curr = *msg;

    if ((mode_curr.mode == "OFFBOARD") && sp_status == SP_STREAM_READY) {
        sp_status = SP_STREAM_ACTIVE;

        t_start = ros::Time::now();
        pose_0 = pose_curr;
        count_traj = 0;

        ROS_INFO("Trajectory Activated.");
        cout << "Heading to: \n" << pose_sp.pose.position << endl;
    } else if (mode_curr.mode != "OFFBOARD") {
        // Reset sp stream.
        sp_status = SP_STREAM_READY;
    }
}

void SetpointPublisher::pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_curr = *msg;
}

void SetpointPublisher::update_setpoint()
{   
    ros::Duration t_now = ros::Time::now() - t_start;
    
    //cout << sp_status << endl;

    switch (sp_status)
    {
    case SP_STREAM_READY:
    {
        pose_sp = pose_curr;
    }
    break;
    case SP_STREAM_ACTIVE:
    {
        ros::Duration t_wp = ros::Duration(traj(0,count_traj)) + ros::Duration(count_loop*traj(0,N_traj-1));

        //cout << t_wp << endl;
        //cout << count_loop << endl;

        if ((t_now > t_wp) && (count_traj < N_traj))
        {
            pose_sp.pose.position.x = traj(1, count_traj) + pose_0.pose.position.x;
            pose_sp.pose.position.y = traj(2, count_traj) + pose_0.pose.position.y;
            pose_sp.pose.position.z = traj(3, count_traj) + pose_0.pose.position.z;

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
        else if ((t_now > t_wp) && (count_traj >= N_traj)) {
            count_traj = 0;
            count_loop++;
        }
        else
        {
            // Still Tracking Waypoints
        }
        
        if (t_now > ros::Duration(t_fs)) {
            pose_sp.pose.position.x = pose_curr.pose.position.x;
            pose_sp.pose.position.y = pose_curr.pose.position.y;
            pose_sp.pose.position.z = pose_curr.pose.position.z;

            sp_status = SP_STREAM_COMPLETE;
        }
    }
    break;
    case SP_STREAM_COMPLETE:
    {
        mavros_msgs::CommandTOL srv_land;
        if (land_client.call(srv_land) && srv_land.response.success)
        {
            ROS_INFO("Land Sent %d", srv_land.response.success);
        }
    }
    break;
    default:
    {
        pose_sp.pose.position.x = 0.0f;
        pose_sp.pose.position.y = 0.0f;
        pose_sp.pose.position.z = 0.0f;

        pose_sp.pose.orientation.w = 1.0f;
        pose_sp.pose.orientation.x = 0.0f;
        pose_sp.pose.orientation.y = 0.0f;
        pose_sp.pose.orientation.z = 0.0f;
    }
    }

    pose_sp.header.stamp = ros::Time::now();
    pose_sp.header.seq   = count_main;
    pose_sp.header.frame_id = 1;
    count_main++;

    pose_sp_pub.publish(pose_sp);
}

void SetpointPublisher::param_update() {
    mavros_msgs::ParamSet srv_tune;
//    srv_tune.request.param_id = "MPC_XY_P";
    srv_tune.request.param_id = "MC_PITCH_P";
    srv_tune.request.value.integer = 0;
    srv_tune.request.value.real = 6.5;
    
    if (tune_client.call(srv_tune) && srv_tune.response.success) {
        // Service sent.
    }    
}

MatrixXd SetpointPublisher::load_trajectory(const std::string& input)
{
    MatrixXd m_pose = MatrixXd::Zero(5,1);

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
        m_pose.resize(rows,cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols ; j++) {
                m_pose(i,j) = parsedCsv[i][j];
            }
        }
    } else {
        cout << "Trajectory does not exist. Defaulting to Origin." << endl;
    }
    
    return m_pose;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");

    string traj_id;
    float t_fs;
    float err_tol;

    ros::param::get("~traj_id", traj_id);
    ros::param::get("~t_fs", t_fs);
    ros::param::get("~err_tol",err_tol);
    ros::NodeHandle nh;

    SetpointPublisher sp = SetpointPublisher(&nh,traj_id,t_fs,err_tol);

    ros::Rate rate(50);
    while(ros::ok()){
        //sp.param_update();
        sp.update_setpoint();
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
