#include <bridge_iroad/iroad_closedloop.h>

Teleop_IRoad::Teleop_IRoad():
  accel_id(5),
  steer_id(0),
  ct_input_id(2),
  PRNDL_vr_id(1),
  PRNDL_ct_id(2),
  pk_brake_id(0),
  steer_scale(350),
  origin_lat(37.4303024),
  origin_lon(-122.1839708),
  origin_alt(0.0)
{
  nh.param("accel_id", accel_id, accel_id);
  nh.param("steer_id", steer_id, steer_id);
  nh.param("ct_input_id", ct_input_id, ct_input_id);
  nh.param("PRNDL_vr_id", PRNDL_vr_id, PRNDL_vr_id);
  nh.param("PRNDL_ct_id", PRNDL_ct_id, PRNDL_ct_id);
  nh.param("pk_brake_id", pk_brake_id, pk_brake_id);
  nh.param("steer_scale", steer_scale, steer_scale);
  nh.param("origin_lat", origin_lat, origin_lat);
  nh.param("origin_lon", origin_lon, origin_lon);
  nh.param("origin_alt", origin_alt, origin_alt);

  joy_sub_ = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Teleop_IRoad::joy_cb, this); 
  imu_sub_ = nh.subscribe<sensor_msgs::Imu>("gx5/imu/data", 10, &Teleop_IRoad::imu_cb, this);
  gps_sub_ = nh.subscribe<sensor_msgs::NavSatFix>("gx5/gps/fix", 10, &Teleop_IRoad::gps_cb,this);

  double hz = 100.0;

  xCurr(0,0) = 0.0;
  xCurr(1,0) = 0.0;
  xCurr(2,0) = 0.0;
  xGoal = xCurr;
  xOrig = xCurr;

  udpLoop = nh.createTimer(ros::Duration(1.0/hz),&Teleop_IRoad::udp_cb, this);

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
      
}

void Teleop_IRoad::joy_cb(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;

  cmd_struct.accel = (float) -(joy->axes[accel_id]-1.0)/2.0;
  // cmd_struct.steer = (float) steer_scale*joy->axes[steer_id];
  cmd_struct.steer = (float) steer_scale*psi(0,1);
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
    //memset(server_message, '\0', sizeof(server_message));
    //memset(client_message, '\0', sizeof(client_message));
    
    // Send Packet    
    sendto(socket_desc, &cmd_struct, sizeof(cmd_struct),MSG_CONFIRM, (const struct sockaddr *)&client_addr,sizeof(client_addr));
  
    //close(sockfd);

    //cout << "hoho" << endl;
}

void Teleop_IRoad::imu_cb(const sensor_msgs::Imu::ConstPtr& imu) {
    //memset(server_message, '\0', sizeof(server_message));
    //memset(client_message, '\0', sizeof(client_message));

    float qw = imu->orientation.w;
    float qx = imu->orientation.x;
    float qy = imu->orientation.y;
    float qz = imu->orientation.z;

    float qwp = qw;
    float qxp = -qx;
    float qyp = -qy;
    float qzp = -qz;
    
    vHx(0,0) = qw*qw + qx*qx - qy*qy - qz*qz;
    vHx(1,0) = 2.0*(qx*qy + qw*qz);
    vHx(2,0) = 2.0*(qx*qz - qw*qy);

    vHxp(0,0) = qwp*qwp + qxp*qxp - qyp*qyp - qzp*qzp;
    vHxp(1,0) = 2.0*(qxp*qyp + qwp*qzp);
    vHxp(2,0) = 2.0*(qxp*qzp - qwp*qyp);

    vHy(0,0) = 2.0*(qx*qy - qw*qz);
    vHy(1,0) = qw*qw - qx*qx + qy*qy - qz*qz;
    vHy(2,0) = 2.0*(qw*qx + qy*qz);

    vHyp(0,0) = 2.0*(qxp*qyp - qwp*qzp);
    vHyp(1,0) = qwp*qwp - qxp*qxp + qyp*qyp - qzp*qzp;
    vHyp(2,0) = 2.0*(qwp*qxp + qyp*qzp);

    Matrix<double,3,4> output;
    output.col(0) = vHx;
    output.col(1) = vHxp;
    output.col(2) = vHy;
    output.col(3) = vHyp;

    VectorXd r(3);
    r(0) = 1000.0;
    r(1) = 0.0;
    r(2) = 0.0;
    double rn = r.norm();

    psi(0,0) = (180/M_PI)*acos(vHx.dot(r)/rn);
    psi(0,1) = (180/M_PI)*acos(vHxp.dot(r)/rn);
    psi(0,2) = (180/M_PI)*acos(vHy.dot(r)/rn);
    psi(0,3) = (180/M_PI)*acos(vHyp.dot(r)/rn);
    
    double c = 0.0;
    if ( (vHxp(0,0) > 0) && (vHxp(1,0) > 0) ) {
      c = 1.0;
    } else if ( (vHxp(0,0) < 0) && (vHxp(1,0) > 0) ) {
      c = 1.0;
    } else if ( (vHxp(0,0) > 0) && (vHxp(1,0) < 0) ) {
      c = -1.0;
    } else if ( (vHxp(0,0) < 0) && (vHxp(1,0) < 0) ) {
      c = -1.0;
    }  
    psi(0,1) = c*psi(0,1);
    
    cout << output << endl;
    cout << "===========================================" << endl;
    cout << psi << endl;
    cout << "===========================================" << endl;
    //cout << "one = " << vHead.norm() << ", heading: " << vHead(1,0) << endl;
}

void Teleop_IRoad::gps_cb(const sensor_msgs::NavSatFix::ConstPtr& gps) {
  double deg_lat = gps->latitude;
  double deg_lon = gps->longitude;
  
  xCurr(0,0) = (deg_lat - origin_lat)*60.0*1852.0;
  xCurr(1,0) = (deg_lon - origin_lon)*(M_PI/10800.0)*6367449.0*cos(deg_lat*M_PI/180);
  xCurr(2,0)  = gps->altitude;

  // xGoal = xOrig;
  // xGoal(1,0) += 1;
  // Matrix<double,3,1>xRela = xCurr - xGoal;
  // xRela(0,0) = 0;
  // xRela(1,0) = 1000;
  // xRela(2,0) = 0;
  // //cout << xRela.norm() << endl;
  // Matrix<double,3,1> a = xRela;
  // Matrix<double,3,1> b = vH;
  
  // double num = a.transpose()*b;
  // double den = a.norm();

  // double theta = (180/M_PI)*acos(num/den);
  // //cout << "theta value: " << theta << endl;
  // cout << vHead << endl;
  // cout << "||vHead|| = " << vHead.norm() << endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Teleop_IRoad");
  Teleop_IRoad teleop_iRoad;

  ros::spin();
  return 0;
}
