#include <bridge_px4/hr_control.h>

HR_Control::HR_Control()
{
    // ROS Initialization
    pose_curr_sub = nh.subscribe("mavros/local_position/pose",1,&HR_Control::pose_curr_cb,this);
    vel_curr_sub = nh.subscribe("mavros/local_position/velocity_local",1,&HR_Control::vel_curr_cb,this);    
    att_sp_pub  = nh.advertise<mavros_msgs::AttitudeTarget>("setpoint/attitude",1);    
    
    traj_server = nh.advertiseService("setpoint/TrajTransfer", &HR_Control::transfer,this);

    t_start = ros::Time::now();

    k_main = -1;

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
    t_dt = 1.0/req.hz;
    N  = req.N;

    u_arr = req.u_arr;      // note the difference u and l. this is because matlab rosmsg makes l <->L the same. so u is used to keep it happy.  
    L_arr = req.L_arr;
    x_arr = req.x_arr;     
    k_main = 0;

    float sum_x = accumulate(x_arr.begin(), x_arr.end(), sum_x);
    float sum_l = accumulate(u_arr.begin(), u_arr.end(), sum_l);
    float sum_L = accumulate(L_arr.begin(), L_arr.end(), sum_L);
    res.checksum = sum_l + sum_L;

    t_next = ros::Time::now();

    return true;
}

void HR_Control::trajectory_execute()
{
    ros::Time t_now = ros::Time::now();

    // Update Feedback and Feedforward Variables
    if ((t_now >= t_next) && (k_main <= N) && (k_main >= 0))
    {
        int idx = 0;

        for (int i = 0 ; i < 4 ; i++) {
            idx = (k_main*4)+i;
            u_curr(i,0) = u_arr[idx];
        }

        for (int j = 0 ; j < 10 ; j++) {
            idx = (k_main*10)+j;
            x_bar(j,0) = x_arr[idx];
        }

        for (int i = 0 ; i < 10 ; i++) {
            for (int j = 0 ; j < 4 ; j++) {
                idx = (k_main*40)+(4*i)+j;
                L_curr(j,i) = L_arr[idx];
            }
        }

        t_next = t_next + ros::Duration(t_dt);
        
        k_main += 1;
    }

    // Generate Command Output
    if (k_main >=0 && k_main <= N)
    {
        u_br = u_curr + L_curr*(x_curr - x_bar);
        //u_br = l_curr;

        //float err_z = x_curr(2,0) - x_bar(2,0);
        //std::cout << "Z error is: " << err_z << std::endl;

        att_sp_out.thrust = u_br(0,0);
        att_sp_out.body_rate.x = u_br(1,0);
        att_sp_out.body_rate.y = u_br(2,0);
        att_sp_out.body_rate.z = u_br(3,0);

        att_sp_out.header.stamp = ros::Time::now();
        att_sp_out.header.seq   = k_main;
        
        att_sp_pub.publish(att_sp_out);
        
    } else {
        // Do nothing
    }


}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "hr_node");

    HR_Control HR_Control;

    ros::Rate rate(200);
    while(ros::ok()){
        HR_Control.trajectory_execute();

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
