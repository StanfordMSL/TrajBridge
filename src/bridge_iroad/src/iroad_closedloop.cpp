#include <bridge_iroad/iroad_closedloop.h>

Teleop_IRoad::Teleop_IRoad():
  accel_id(5),
  steer_id(0),
  ct_input_id(2),
  PRNDL_vr_id(1),
  PRNDL_ct_id(2),
  pk_brake_id(0),
  cl_act_id(3),
  steer_scale(11.8),
  accel(0.0),
  steer(0.0),
  udp_hz(100),
  lat0(37.4299484),
  lon0(-122.1836507),
  ptx(0.0),
  pty(0.0),
  dthres(5.0),
  cl_act_chk(0)
{
  nh.param("accel_id", accel_id, accel_id);
  nh.param("steer_id", steer_id, steer_id);
  nh.param("ct_input_id", ct_input_id, ct_input_id);
  nh.param("PRNDL_vr_id", PRNDL_vr_id, PRNDL_vr_id);
  nh.param("PRNDL_ct_id", PRNDL_ct_id, PRNDL_ct_id);
  nh.param("pk_brake_id", pk_brake_id, pk_brake_id);
  nh.param("cl_act_id", cl_act_id, cl_act_id);
  nh.param("steer_scale", steer_scale, steer_scale);
  nh.param("lat0", lat0, lat0);
  nh.param("lon0", lon0, lon0);
  nh.param("ptx", ptx, ptx);
  nh.param("pty", pty, pty);
  nh.param("dthres", dthres, dthres);

  joy_sub_ = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Teleop_IRoad::joy_cb, this); 
  imu_sub_ = nh.subscribe<sensor_msgs::Imu>("gx5/imu/data", 10, &Teleop_IRoad::imu_cb, this);
  gps_sub_ = nh.subscribe<sensor_msgs::NavSatFix>("gx5/gps/fix", 10, &Teleop_IRoad::gps_cb,this);
  udpLoop = nh.createTimer(ros::Duration(1.0/udp_hz),&Teleop_IRoad::udp_cb, this);

  // cout << "Lat: " << lat_0 << " Lon: " << lon_0 << endl;
  // cout << " ==================== " << endl;
  pt(0,0) = ptx;
  pt(1,0) = pty;
  pt(2,0) = 0.0;
  
  p0 = gcs2ecef(lat0,lon0);
  Re2e = Re2e_gen(lat0,lon0);
  
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
  cmd_joy.steer = (float) steer_scale*joy->axes[steer_id];
  cmd_joy.accel = (float) -(joy->axes[accel_id]-1.0)/2.0;
  cmd_joy.PRNDL_vr = (float) joy->buttons[PRNDL_vr_id];
  cmd_joy.PRNDL_ct = (float) joy->buttons[PRNDL_ct_id];
  cmd_joy.ct_input = (float) -(joy->axes[ct_input_id]-1.0)/2.0;
  cmd_joy.pk_brake = (float) joy->buttons[pk_brake_id];

  cl_act_chk = (bool) joy->buttons[cl_act_id];
}

void Teleop_IRoad::udp_cb(const ros::TimerEvent& event) {
  Matrix<double,3,1> r_tW;        // Relative position of target in world frame.
  Matrix<double,3,1> r_tb;        // Relative position of target in body frame.
  r_tW = pt-pose.block(0,0,3,1);
  r_tb = quatrot(r_tW);

  double d_t = r_tb.norm();      // l2-norm of relative position

  Matrix<double,3,1> r_f;       // Front vector in body frame
  r_f << 0.0,1.0,0.0;
  steer = rad2deg(acos(r_tb.dot(r_f)/d_t));

  steer = min(steer, 30.0);

  if (r_tb(0,0) < 0) {
    steer = -steer;
  } else {
    // Carry On
  }

  cmd_out = cmd_joy;
  if (cl_act_chk) {
    cmd_out.steer = steer_scale*steer;

    if (cmd_out.steer > 350.0) {
      cmd_out.steer = 350.0;
    } else if (cmd_out.steer < -350.0) {
      cmd_out.steer = -350.0;
    }

    if (d_t >= dthres) {
      cmd_out.PRNDL_ct = 1;
      cmd_out.accel = 0.5;
     //cmd_struct.accel = min(distance/100.0,1.0); 
    } else {
      cmd_out.accel = 0.0; //debug 
    }
  } else {
    // Follow joystick input.
  }
  // cout << "Pose (World): \n" << pose << endl;
  cout << "Relative Position (World):\n" << r_tW << endl;
  cout << "Relative Position (Body):\n" << r_tb << endl;
  cout << "Steering:" << steer << endl;
  cout << "===========================================" << endl;

  // Send Packet
  sendto(socket_desc, &cmd_out, sizeof(cmd_out), MSG_CONFIRM, (const struct sockaddr *)&client_addr, sizeof(client_addr));
}

void Teleop_IRoad::imu_cb(const sensor_msgs::Imu::ConstPtr& imu) {
    pose(3,0) = imu->orientation.w;
    pose(4,0) = imu->orientation.x;
    pose(5,0) = imu->orientation.y;
    pose(6,0) = imu->orientation.z;
}

void Teleop_IRoad::gps_cb(const sensor_msgs::NavSatFix::ConstPtr& gps) {
  Matrix<double,3,1> p_ecef;
  
  double lat = gps->latitude;
  double lon = gps->longitude;
  p_ecef = gcs2ecef(lat,lon);

  pose.block<3,1>(0,0) = Re2e*(p_ecef-p0);

  // cout << "x: " << pose(0,0) << " y: " << pose(1,0) << " z: " << pose(2,0) << endl;
  // cout << " ==================== " << endl;
}

double Teleop_IRoad::deg2rad(const double theta_d) {
    return((M_PI/180.0)*theta_d);
}

double Teleop_IRoad::rad2deg(const double theta_r) {
    return((180.0/M_PI)*theta_r);
}

Matrix<double,3,1> Teleop_IRoad::quatrot(const Vector3d& v) {    
    double qw = pose(3,0);
    double qx = pose(4,0);
    double qy = pose(5,0);
    double qz = pose(6,0);

    Matrix<double,3,3> R;
    R << (qw*qw + qx*qx - qy*qy - qz*qz), (2*qx*qy-2*qw*qz), (2*qx*qz-2*qw*qy), 
         (2*qx*qy+2*qw*qz), (qw*qw - qx*qx + qy*qy - qz*qz), (2*qy*qz-2*qw*qx), 
         (2*qx*qz+2*qw*qy), (2*qy*qz+2*qw*qx), (qw*qw - qx*qx - qy*qy + qz*qz);

    Matrix<double,3,1> vp;
    vp = R*v;

    return vp;
}

Matrix<double,3,1> Teleop_IRoad::gcs2ecef(const double lat,const double lon) {
  Matrix<double,3,1> p_ecef;

  double R = 6367449.0;
  double phi = deg2rad(lat);
  double lam = deg2rad(lon);

  p_ecef(0,0) = R*cos(phi)*cos(lam);
  p_ecef(1,0) = R*cos(phi)*sin(lam);
  p_ecef(2,0) = R*sin(phi);

  return p_ecef;
}

Matrix<double,3,3> Teleop_IRoad::Re2e_gen(const double lat,const double lon) {
  double phi = deg2rad(lat);
  double lam = deg2rad(lon);

  Matrix<double,3,3> R;
  R << -sin(lam),           cos(lam),          0.0,
       -sin(phi)*cos(lam), -sin(phi)*sin(lam), cos(phi),
        cos(phi)*cos(lam),  cos(phi)*sin(lam), sin(phi);

  return R;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Teleop_IRoad");
  Teleop_IRoad teleop_iRoad;

  ros::spin();
  return 0;
}
