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

  double hz = 1.0;
  udpLoop = nh.createTimer(ros::Duration(1.0/hz),&Teleop_IRoad::udp_cb, this);

}

void Teleop_IRoad::joy_cb(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;

  accel = (float) -(joy->axes[accel_id]-1.0)/2.0;
  steer = (float) steer_scale*joy->axes[steer_id];
  ct_input = (float) -(joy->axes[ct_input_id]-1.0)/2.0;

  PRNDL_vr = (float) joy->buttons[PRNDL_vr_id];
  PRNDL_ct = (float) joy->buttons[PRNDL_ct_id];
  pk_brake = (float) joy->buttons[pk_brake_id];

  cout << "accel: " << accel << endl;
  cout << "steer: " << steer << endl;
  cout << "ct_input: " << ct_input << endl;

  cout << "PRNDL_vr: " << PRNDL_vr << endl;
  cout << "PRNDL_ct: " << PRNDL_ct << endl;
  cout << "pk_brake: " << pk_brake << endl;
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
    serv.sin_port = htons(25000);
    serv.sin_addr.s_addr = inet_addr("192.168.140.1");

    // Populate data packet
    char data[92];
    memcpy(&data[5],  &steer, sizeof(steer));
    memcpy(&data[13], &ct_input, sizeof(ct_input));
    memcpy(&data[25], &accel, sizeof(accel));
    memcpy(&data[37], &pk_brake, sizeof(pk_brake));
    memcpy(&data[41], &PRNDL_vr, sizeof(PRNDL_vr));
    memcpy(&data[48], &PRNDL_ct, sizeof(PRNDL_ct));

    // Send Packet    
    sendto(sockfd,data,sizeof(data),0,(struct sockaddr *) &serv,sizeof(serv));         
  
    close(sockfd);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Teleop_IRoad");
  Teleop_IRoad teleop_iRoad;

  ros::spin();
  return 0;
}
