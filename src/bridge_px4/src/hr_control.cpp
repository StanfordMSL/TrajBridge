#include <bridge_px4/hr_control.h>

HR_Control::HR_Control()
{
    ros::param::get("~r_safety", r_safety);


    // ROS Initialization
    pose_curr_sub = nh.subscribe("mavros/local_position/pose",1,&HR_Control::pose_curr_cb,this);
    vel_curr_sub = nh.subscribe("mavros/local_position/velocity_local",1,&HR_Control::vel_curr_cb,this);    
    att_sp_pub  = nh.advertise<mavros_msgs::AttitudeTarget>("setpoint/attitude",1);    
    
    traj_server = nh.advertiseService("setpoint/TrajTransfer", &HR_Control::transfer,this);

    // Initialize Remainder of Parameters
    att_sp_out.header.frame_id = "map";
    att_sp_out.type_mask = att_sp_out.IGNORE_ATTITUDE;
}

HR_Control::~HR_Control()
{
  ROS_WARN("Terminating High Rate Controller");
}

void HR_Control::pose_curr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    x_curr(0,0) = msg->pose.position.x;
    x_curr(1,0) = msg->pose.position.y;
    x_curr(2,0) = msg->pose.position.z;
    x_curr(6,0) = msg->pose.orientation.w;
    x_curr(7,0) = msg->pose.orientation.x;
    x_curr(8,0) = msg->pose.orientation.y;
    x_curr(9,0) = msg->pose.orientation.z;
}

void HR_Control::vel_curr_cb(const geometry_msgs::TwistStamped::ConstPtr& msg){
    x_curr(3,0) = msg->twist.linear.x;
    x_curr(4,0) = msg->twist.linear.y;
    x_curr(5,0) = msg->twist.linear.z;
}

bool HR_Control::transfer(bridge_px4::TrajTransfer::Request& req, bridge_px4::TrajTransfer::Response& res)
{
    // Load the Trajectory
    t_dt = 1.0/req.hz;
    N  = req.N;

    u_arr = req.u_arr;      // note the difference u and l. this is because matlab rosmsg makes l <->L the same. so u is used to keep it happy.  
    L_arr = req.L_arr;
    x_arr = req.x_arr;     
    
    // Return checksum for verification (not completed/verified, still TODO)
    float sum_x = accumulate(x_arr.begin(), x_arr.end(), sum_x);
    float sum_l = accumulate(u_arr.begin(), u_arr.end(), sum_l);
    float sum_L = accumulate(L_arr.begin(), L_arr.end(), sum_L);
    res.checksum = sum_l + sum_L;

    // Start closed loop controller. Rate is fixed to t_dt across all frames.
    closedLoop = nh.createTimer(ros::Duration(t_dt),&HR_Control::clc_cb, this);
    k_main = 0;

    return true;
}

void HR_Control::policy_update()
{
    int idx = 0;

    if (k_main < N-1)
    {
        // Update Policy Terms
        for (int i = 0; i < 4; i++)         // Open Loop Term
        {
            idx = (k_main*4)+i;
            u_curr(i, 0) = u_arr[idx];
        }
        
        for (int i = 0; i < 10; i++)        // Feedback Matrix
        {
            for (int j = 0; j < 4; j++)
            {
                idx = (k_main*40)+(4*i)+j;
                L_curr(j, i) = L_arr[idx];
            }
        }

        for (int j = 0; j < 10; j++)        // Nominal State
        {
            idx = (k_main * 10) + j;
            x_bar(j, 0) = x_arr[idx];
        }

        // Generate Policy Output 
        del_x = x_curr - x_bar;            
        u_br = u_curr + L_curr*del_x;

        cout << del_x << endl;
        cout << " ohoh " << endl;
        cout << L_curr*del_x << endl;
        cout << " ohoh " << endl;
        cout << u_curr(1) << endl;
        cout << " ohoh " << endl;
        // Increment Counter
        k_main += 1;
    } else 
    {
        // Policy Complete
        closedLoop.stop();
    }
}

void HR_Control::clc_cb(const ros::TimerEvent& event) {
    policy_update();

    // Check for Divergence (ball radius)
    float pos_err = del_x.head(3).norm();

    if (pos_err < r_safety) {
        // Still within bounds.
        att_sp_out.thrust = u_br(0, 0);
        att_sp_out.body_rate.x = u_br(1, 0);
        att_sp_out.body_rate.y = u_br(2, 0);
        att_sp_out.body_rate.z = u_br(3, 0);

        att_sp_out.header.stamp = ros::Time::now();
        att_sp_out.header.seq = k_main;

        att_sp_pub.publish(att_sp_out);
    } else {
        // Trigger failsafe.
        cout << "Failsafe Triggered (" << r_safety << "m) at Frame " << k_main << endl;
        closedLoop.stop();
    }

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "hr_node");

    HR_Control HR_Control;

    ros::spin();
    return 0;
}
