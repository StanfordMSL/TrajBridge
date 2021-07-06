#include <bridge_px4/hr_control.h>

HR_Control::HR_Control()
{
    // ROS Initialization
    pose_curr_sub = nh.subscribe("mavros/local_position/pose",1,&HR_Control::pose_curr_cb,this);
    pose_curr_sub = nh.subscribe("mavros/local_position/velocity",1,&HR_Control::vel_curr_cb,this);    
    raw_att_pub  = nh.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude",1);    
    
    traj_server = nh.advertiseService("setpoint/traj_transfer", &HR_Control::traj_transfer,this);

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

bool HR_Control::traj_transfer(bridge_px4::traj_transfer::Request& req,bridge_px4::traj_transfer::Response& res)
{
    t_dt = 1.0/req.hz;
    N  = req.N;

    l_arr = req.l_arr;    
    L_arr = req.L_arr;

    k_main += 1;

    return true;
}

void HR_Control::trajectory_execute()
{
    ros::Time t_now = ros::Time::now();

    // Update Feedback and Feedforward Variables
    if ((t_now >= t_next) && (k_main <= N))
    {
        int idx = 0;

        for (int i = 0 ; i < 4 ; i++) {
            idx = (k_main*4)+i;
            l_curr(i,0) = l_arr[idx];

            for (int j = 0 ; j < 10 ; j++) {
                idx = (k_main*4)+(j*4)+i;
                L_curr(i,j) = L_arr[idx];
            }
        }

        t_next = t_next + ros::Duration(t_dt);
        k_main += 1;
    }

    // Generate Command Output
    if (k_main >=0 && k_main <= N)
    {
        u_br = l_curr + L_curr*x_curr;

        att_sp_out.thrust = u_br(0,0);
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
