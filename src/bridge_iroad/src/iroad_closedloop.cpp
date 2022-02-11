#include <bridge_iroad/iroad_closedloop.h>

Teleop_IRoad::Teleop_IRoad():
  accel_id(5),
  steer_id(0),
  ct_input_id(2),
  PRNDL_vr_id(1),
  PRNDL_ct_id(2),
  pk_brake_id(0),
  steer_scale(350),
  origin_lat(37.429929), //map lat: 37.42999
  origin_lon(-122.183598), //map lon: -122.18363
  origin_alt(5.594),
  cl_activation_id(3)
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
  
  r2d = M_PI/180.0;
  R = 6367449.0;

  xOrig(0,0) = R*cos(r2d*origin_lat)*cos(r2d*origin_lon); //distance in meters from the point of origin, perpendicular to the equator
  xOrig(1,0) = R*cos(r2d*origin_lat)*sin(r2d*origin_lon); //distance in meters from the point of origin, parallel to the equator
  xOrig(2,0) = 0.0;

  // xGoal(0,0) = 4.0; //custom, manually set goal
  // xGoal(1,0) = -20.0;
  xGoal(0,0) = -20.0; //custom, manually set goal
  xGoal(1,0) = 0.0;
  xGoal(2,0) = 0.0;
  
  xCurr = xOrig;
  distance = 0.0; //initialize to a real value
  dist_thres = 5.0; //sensor position uncertainty radius is 2m, supposedly

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
  
  cmd_in.steer = (float) steer_scale*joy->axes[steer_id];
  cmd_in.accel = (float) -(joy->axes[accel_id]-1.0)/2.0;
  cmd_in.PRNDL_vr = (float) joy->buttons[PRNDL_vr_id];
  cmd_in.PRNDL_ct = (float) joy->buttons[PRNDL_ct_id];
  cmd_in.ct_input = (float) -(joy->axes[ct_input_id]-1.0)/2.0;
  cmd_in.pk_brake = (float) joy->buttons[pk_brake_id];

  cl_act_chk = (bool) joy->buttons[cl_activation_id];
}

void Teleop_IRoad::udp_cb(const ros::TimerEvent& event) {
    //memset(server_message, '\0', sizeof(server_message));
    //memset(client_message, '\0', sizeof(client_message));
    cmd_out = cmd_in;

    if (cl_act_chk) {
      if (psi(0,1) > 30.0) {
        cmd_out.steer = (float) -steer_scale;
      } else if (psi(0,1) < -30.0) {
        cmd_out.steer = (float) steer_scale;
      } else {
        cmd_out.steer = (float) -steer_scale*psi(0,1)/30.0;
    }

    if (distance <= dist_thres) {
      cmd_out.accel = 0.0;
    } else {
      //cmd_struct.accel = 0.0; //debug
      cmd_out.PRNDL_ct = 1;
      cmd_out.accel = 0.5; //debug
      //cmd_struct.accel = min(distance/100.0,1.0); 
    }
    // cout << "Closed loop control active!" << endl;
  } else {
    // Do Nothing
  }

  // cout << "accel: " << cmd_out.accel << endl;
  // cout << "steer: " << cmd_out.steer << endl;
  // cout << "ct_input: " << cmd_out.ct_input << endl;

  // cout << "PRNDL_vr: " << cmd_out.PRNDL_vr << endl;
  // cout << "PRNDL_ct: " << cmd_out.PRNDL_ct << endl;
  // cout << "pk_brake: " << cmd_out.pk_brake << endl;
  // cout << endl;
    // Send Packet    
    sendto(socket_desc, &cmd_out, sizeof(cmd_out),MSG_CONFIRM, (const struct sockaddr *)&client_addr,sizeof(client_addr));
  
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

    VectorXd xRela(3);
    xRela = xGoal - xCurr;
    distance = xRela.norm();
    // cout << xRela << endl;

    psi(0,0) = (180/M_PI)*acos(vHx.dot(xRela)/distance);
    psi(0,1) = (180/M_PI)*acos(vHxp.dot(xRela)/distance);
    psi(0,2) = (180/M_PI)*acos(vHy.dot(xRela)/distance);
    psi(0,3) = (180/M_PI)*acos(vHyp.dot(xRela)/distance);
    
    double c = 0.0;
    if ( (vHyp(0,0) > 0) && (vHyp(1,0) > 0) ) {
      c = 1.0;
    } else if ( (vHyp(0,0) < 0) && (vHyp(1,0) > 0) ) {
      c = 1.0;
    } else if ( (vHyp(0,0) > 0) && (vHyp(1,0) < 0) ) {
      c = -1.0;
    } else if ( (vHyp(0,0) < 0) && (vHyp(1,0) < 0) ) {
      c = -1.0;
    }  
    psi(0,3) = c*psi(0,3);
    
    cout << output << endl;
    cout << "===========================================" << endl;
    cout << psi << endl;
    cout << "===========================================" << endl;
    //cout << "one = " << vHead.norm() << ", heading: " << vHead(1,0) << endl;
    // cout << "distance to goal: " << distance << "m, current altitude: " << xCurr(2,0) << endl;
}

void Teleop_IRoad::gps_cb(const sensor_msgs::NavSatFix::ConstPtr& gps) {
  double deg_lat = gps->latitude;
  double deg_lon = gps->longitude;
  
  Matrix<double,3,1> xGlob;
  xGlob(0,0) = R*cos(r2d*deg_lat)*cos(r2d*deg_lon); //distance in meters from the point of origin, perpendicular to the equator
  xGlob(1,0) = R*cos(r2d*deg_lat)*sin(r2d*deg_lon); //distance in meters from the point of origin, parallel to the equator
  xGlob(2,0) = 0.0;

  xCurr = xOrig - xGlob;
  
  // cout << xCurr << endl;
  // cout << "===============" << endl;
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
