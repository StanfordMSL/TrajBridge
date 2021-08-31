#include <bridge_px4/hr_control.h>

const string HR_Control::states[] = {
    "px","py","pz",
    "vx","vy","vz",
    "qw","qx","qy","qz"};

HR_Control::HR_Control()
:   pxy_slim_(1.0),pz_slim_(0.5),v_slim_(0.5),q_slim_(0.3),
    ep_lim_(3.0),eq_lim_(0.6)
{
    ros::param::get("~pxy_slim", pxy_slim_);
    ros::param::get("~pz_slim", pz_slim_);
    ros::param::get("~v_slim", v_slim_);
    ros::param::get("~q_slim", q_slim_);

    ros::param::get("~ep_lim", ep_lim_);
    ros::param::get("~eq_lim", eq_lim_);

    // ROS Initialization
    pose_curr_sub = nh.subscribe("mavros/local_position/pose",1,&HR_Control::pose_curr_cb,this);
    vel_curr_sub = nh.subscribe("mavros/local_position/velocity_local",1,&HR_Control::vel_curr_cb,this);    
    att_sp_pub  = nh.advertise<mavros_msgs::AttitudeTarget>("setpoint/attitude",1);    
    
    traj_server = nh.advertiseService("setpoint/TrajTransfer", &HR_Control::transfer,this);
    traj_sub    = nh.subscribe("setpoint/TrajUpdate",1,&HR_Control::traj_upd_cb,this);

    // Initialize Remainder of Parameters
    att_sp_out.header.frame_id = "map";
    att_sp_out.type_mask = att_sp_out.IGNORE_ATTITUDE;

    // Initialize Limits Vector
    del_slim(0,0) = del_slim(1,0) = pxy_slim_;
    del_slim(2,0) = pz_slim_;
    del_slim(3,0) = del_slim(4,0) = del_slim(5,0) = v_slim_;
    del_slim(6,0) = del_slim(7,0) = del_slim(8,0) = del_slim(9,0) = q_slim_;

    /*
    cout << "pos_xy safety limit: " << pxy_slim_ << endl;
    cout << "pos_z safety limit: " << pz_slim_ << endl;
    cout << "vel safety limit: " << v_slim_ << endl;
    cout << "quat safety limit: " << q_slim_ << endl;
    */

    err_lim(0,0) = err_lim(1,0) = err_lim(2,0) = ep_lim_;
    err_lim(3,0) = err_lim(4,0) = err_lim(5,0) = err_lim(6,0) = eq_lim_;

    /*
    cout << "pos integral limit: " << ep_lim_ << endl;
    cout << "quat integral limit: " << eq_lim_ << endl;
    */
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
    res.t_start = ros::Time::now();

    // Start closed loop controller. Rate is fixed to t_dt across all frames.
    closedLoop = nh.createTimer(ros::Duration(t_dt),&HR_Control::clc_cb, this);
    k_main = 0;

    // Reset Integral Error Terms
    x_curr.tail(7) = Matrix<float,7,1>::Zero();

    return true;
}

bool HR_Control::policy_update()
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
        
        for (int i = 0; i < 17; i++)        // Feedback Matrix
        {
            for (int j = 0; j < 4; j++)
            {
                idx = (k_main*68)+(4*i)+j;
                L_curr(j, i) = L_arr[idx];
            }
        }

        for (int j = 0; j < 17; j++)        // Nominal State
        {
            idx = (k_main * 17) + j;
            x_bar(j, 0) = x_arr[idx];
        }
        
        // Increment Counter
        k_main += 1;

        return true;
    } else 
    {
        // Policy Complete
        closedLoop.stop();
        
        //cout << "Integral Errors:" << endl;
        //cout << x_curr.tail(7) << endl;

        return false;
    }

    return false;
}

void HR_Control::delta_update()
{
    // Update the integral deltas
    del_z << (x_curr.head(3)-x_bar.head(3)), (x_curr.segment(6,4)-x_bar.segment(6,4));

    // Update the integral error
    for (int i=0 ; i<7 ; i++) {
        int idx = i+10;
        float cand = x_curr(idx,0) + t_dt*del_z(i,0);

        if (abs(cand) < err_lim(i,0)) {
            x_curr(idx,0) = cand;
        } else {
            // Limit hit. Don't update.  
        }
    }

    // Update the state deltas
    del_x = x_curr - x_bar;     

}

bool HR_Control::limit_check()
{
    for (int i = 0; i < 10; i++) {
        if (abs(del_x(i,0)) > del_slim(i,0)) {
            cout << "Limit Triggered by State: " << states[i] << " at " << k_main*t_dt << "s." << endl;
            cout << "Limit was: " << del_slim(i,0) << ", but I had: " << del_x(i,0) << endl;
            return false;
        }
    }

    return true;
}

void HR_Control::controller()
{
    // Generate Policy Output
    u_br = u_curr + L_curr * del_x;

    if (limit_check() == true) {
        // Still within bounds.
        att_sp_out.thrust = u_br(0, 0);
        att_sp_out.body_rate.x = u_br(1, 0);
        att_sp_out.body_rate.y = u_br(2, 0);
        att_sp_out.body_rate.z = u_br(3, 0);

        att_sp_out.header.stamp = ros::Time::now();
        att_sp_out.header.seq = k_main;

        att_sp_pub.publish(att_sp_out);
        // cout << "hr_control: " << att_sp_out.thrust << endl;
    } else {
        // Trigger failsafe.
        closedLoop.stop();
        
        //cout << "Integral Errors:" << endl;
        //cout << x_curr.tail(7) << endl;
    }

}
void HR_Control::clc_cb(const ros::TimerEvent& event) {
    if (policy_update() == true) {
        delta_update();
        controller();
    };
}

void HR_Control::traj_upd_cb(const bridge_px4::TrajUpdate::ConstPtr& msg){
    // k_init is the index when the update was initially called.
    // k_main is where the trajectory is currently at.
    // k_<> is the stitching point on the original trajectory.
    // n_<> is the stitching point on the updated trajectory.
    // N_<> is the new end point on the total (original+updated) trajectory. 
    
    int k_init = msg->k;

    if (k_main < N) {
        auto k_u = u_arr.begin() + 4 * k_main;
        auto k_x = x_arr.begin() + 17 * k_main;
        auto k_L = L_arr.begin() + 4 * 17 * k_main;

        auto K_u = u_arr.end();
        auto K_x = x_arr.end();
        auto K_L = L_arr.end();

        auto n_u = msg->u_arr.begin() + 4 * (k_main - k_init);
        auto n_x = msg->x_arr.begin() + 17 * (k_main - k_init);
        auto n_L = msg->L_arr.begin() + 4 * 17 * (k_main - k_init);

        auto N_u = msg->u_arr.end();
        auto N_x = msg->x_arr.end();
        auto N_L = msg->L_arr.end();

        u_arr.erase(k_u, K_u);
        x_arr.erase(k_x, K_x);
        L_arr.erase(k_L, K_L);

        u_arr.insert(k_u, n_u, N_u);
        x_arr.insert(k_x, n_x, N_x);
        L_arr.insert(k_L, n_L, N_L);

        // Update the remainder of the trajectory parameters
        t_dt = 1.0/(msg->hz);
        N  = msg->N;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "hr_node");

    HR_Control HR_Control;

    ros::spin();
    return 0;
}
