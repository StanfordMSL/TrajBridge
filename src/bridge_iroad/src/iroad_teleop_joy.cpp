#include <bridge_iroad/iroad_teleop_joy.h>

Teleop_IRoad::Teleop_IRoad():
  accel_id(5),
  steer_id(0),
  ct_input_id(2),
  PRNDL_vr_id(1),
  PRNDL_ct_id(2),
  pk_brake_id(0),
  steer_scale(350)
{
  nh.param("accel_id", accel_id, accel_id);
  nh.param("steer_id", steer_id, steer_id);
  nh.param("ct_input_id", ct_input_id, ct_input_id);
  nh.param("PRNDL_vr_id", PRNDL_vr_id, PRNDL_vr_id);
  nh.param("PRNDL_ct_id", PRNDL_ct_id, PRNDL_ct_id);
  nh.param("pk_brake_id", pk_brake_id, pk_brake_id);

  nh.param("steer_scale", steer_scale, steer_scale);

  joy_sub_ = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Teleop_IRoad::joy_cb, this); 

  double hz = 100.0;
  udpLoop = nh.createTimer(ros::Duration(1.0/hz),&Teleop_IRoad::udp_cb, this);

}

void Teleop_IRoad::joy_cb(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;

  cmd_struct.accel = (float) -(joy->axes[accel_id]-1.0)/2.0;
  cmd_struct.steer = (float) steer_scale*joy->axes[steer_id];
  cmd_struct.ct_input = (float) -(joy->axes[ct_input_id]-1.0)/2.0;

  cmd_struct.PRNDL_vr = (float) joy->buttons[PRNDL_vr_id];
  cmd_struct.PRNDL_ct = (float) joy->buttons[PRNDL_ct_id];
  cmd_struct.pk_brake = (float) joy->buttons[pk_brake_id];

  cout << "accel: " << cmd_struct.accel << endl;
  cout << "steer: " << cmd_struct.steer << endl;
  cout << "ct_input: " << cmd_struct.ct_input << endl;

  cout << "PRNDL_vr: " << cmd_struct.PRNDL_vr << endl;
  cout << "PRNDL_ct: " << cmd_struct.PRNDL_ct << endl;
  cout << "pk_brake: " << cmd_struct.pk_brake << endl;
  cout << endl;
}

void Teleop_IRoad::udp_cb(const ros::TimerEvent& event) {
    // Creating socket file descriptor
    int sockfd;
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in serv;

    // Filling server information
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    //serv.sin_addr.s_addr = inet_addr("192.168.140.1");
    serv.sin_addr.s_addr = INADDR_ANY;

    // Populate data packet
  
    // Send Packet    
    sendto(sockfd, &cmd_struct, sizeof(cmd_struct),MSG_CONFIRM, (const struct sockaddr *)&serv,sizeof(serv));
  
    close(sockfd);

    //cout << "hoho" << endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Teleop_IRoad");
  Teleop_IRoad teleop_iRoad;

  ros::spin();
  return 0;
}
