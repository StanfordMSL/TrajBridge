#include <bridge_iroad/iroad_teleop_can.h>

Teleop_Can::Teleop_Can():
  //st_conv(M_PI/2100.0), //Factor to convert commanded steering setting to radians ([-350,350] corresponding to [-30deg,30deg])
  st_conv(M_PI/2880.0), //Factor to convert commanded steering setting to radians ([-480,480] corresponding to [-30deg,30deg])
  sp_conv(1.0), //Factor to convert vehicle speed signal to meters per second
  //ln_conv(1.0), //Factor to convert vehicle lean signal to radians
  whlbase(1.695) //vehicle wheelbase, in meters
{
  n.param("whlbase",whlbase,whlbase);

  can_pub_ = n.advertise<geometry_msgs::Twist>("can_movement", 10);
  sft_pub_ = n.advertise<u_int32_t>("can_shiftpos", 10);
  str_pub_ = n.advertise<int32_t>("can_steering", 10);
  acl_pub_ = n.advertise<u_int32_t>("can_accelped", 10);
  brk_pub_ = n.advertise<bool>("can_brakeped", 10);
  hzd_pub_ = n.advertise<u_int32_t>("can_turnhazd", 10);
  dct_pub_ = n.advertise<bool>("can_dooropen", 10);
  sbt_pub_ = n.advertise<bool>("can_seatbelt", 10);

  double hz = 1.0;
  printLoop = n.createTimer(ros::Duration(1.0/hz),&Teleop_Can::print_cb, this);

  // Creating socket file descriptor
  if ( (socket_desc = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Filling server/client information
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("192.168.140.2");

  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(PORT);
  client_addr.sin_addr.s_addr = inet_addr("192.168.140.3");

  if ( bind(socket_desc, (const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0 ) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  /* Connect to the UDP socket to avoid the need to explicitly check the remote address each time a datagram is received */
  //NOTE: Enables the use of recv or read instead of recvfrom in reading incoming UDP datagrams
  /*if (connect(socket_desc,client_addr.sin_addr.s_addr,sizeof(client_addr.sin_addr.s_addr))==-1){ //NOTE: This call will succeed even if the remote machine is unreachable or nonexistent
    die("%s",strerror(errno));
  }*/
      
}

void Teleop_Can::print_cb(const ros::TimerEvent& event) {
    /* Print received information to serve as monitor */
    cout << "CAN feedback clock signal: " << can_feedback.can_clck << endl;
    cout << "Shift Position: " << can_feedback.can_sftps << endl;
    cout << "Steering: " << can_feedback.can_steer << endl;
    cout << "Accelerator Pedal Position: " << can_feedback.can_accel << endl;
    cout << "Brake Pedal Engagement: " << can_feedback.can_brkpd << endl;
    cout << "Instantaneous Vehicle Speed: " << can_feedback.can_vspd << endl;
    cout << "Vehicle Lean Angle: " << can_feedback.can_lean << endl;
    cout << "Turn/Hazard Light Engagement: " << can_feedback.can_hzdl << endl;
    cout << "Door Open Indication: " << can_feedback.can_dcty << endl;
    cout << "Seat Belt Engagement: " << can_feedback.can_stbt << endl;
    //cout << "Parking Brake ON: " << can_feedback.can_pkon << endl;
    //cout << "Parking Brake OFF: " << can_feedback.can_pkoff << endl;
    cout << "===========================================" << endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Teleop_Can");
  Teleop_Can teleop_can;  

  while (ros::ok())
  {
    /* Process UDP info */
    socklen_t len = sizeof(teleop_can.client_addr);
    ssize_t count=recvfrom(teleop_can.socket_desc, (char *)teleop_can.buffer,sizeof(teleop_can.can_feedback),0,(struct sockaddr*)&teleop_can.client_addr,&len); //call blocks until a UDP datagram is received
    memcpy(&teleop_can.can_feedback,teleop_can.buffer,sizeof(teleop_can.can_feedback)); //Transcribe data from buffer into area of memory assigned for CAN feedback structure

    /* Calculate twist from info received via UDP datagram */
    //NOTE: This twist describes the current maneuver taken by the vehicle but discounts the effects of vehicle lean, only accounting for vehicle speed and turn rate
    teleop_can.can_twist.linear.y = teleop_can.can_feedback.can_vspd; //y-axis of body frame aims in the forward direction of the vehicle
    teleop_can.can_twist.angular.z = -teleop_can.can_feedback.can_vspd*teleop_can.sp_conv*tan(teleop_can.can_feedback.can_steer*teleop_can.st_conv)/teleop_can.whlbase; //z-axis of body frame aims downwards into the ground, tilt effects are discounted for now

    /* Publish calculated twist */
    teleop_can.can_pub_.publish(teleop_can.can_twist);

    /* Convert seat belt, door and brake engagement values to boolean for publishing */
    teleop_can.can_doors = (bool) teleop_can.can_feedback.can_dcty;
    teleop_can.can_seatb = (bool) teleop_can.can_feedback.can_stbt;
    teleop_can.can_brake = (bool) teleop_can.can_feedback.can_brkpd;
    
    /*Publish vehicle status data*/
    teleop_can.sft_pub_.publish(teleop_can.can_feedback.can_sftps);
    teleop_can.acl_pub_.publish(teleop_can.can_feedback.can_accel);
    teleop_can.brk_pub_.publish(teleop_can.can_brake);
    teleop_can.hzd_pub_.publish(teleop_can.can_feedback.can_hzdl);
    teleop_can.dct_pub_.publish(teleop_can.can_doors);
    teleop_can.sbt_pub_.publish(teleop_can.can_seatb);
    teleop_can.str_pub_.publish(teleop_can.can_feedback.can_steer)

    ros::spinOnce(); //NOTE: comment out if there are no callbacks associated with CAN feedback reception
  }

  return 0;
}
