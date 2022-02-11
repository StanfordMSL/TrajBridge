#include <bridge_iroad/iroad_closedloop.h>

Teleop_IRoad::Teleop_IRoad():
  accel_id(5),
  steer_id(0),
  ct_input_id(2),
  PRNDL_vr_id(1),
  PRNDL_ct_id(2),
  pk_brake_id(0),
  cl_act_id(3),
  steer_scale(15),
  accel(0.0),
  steer(0.0),
  udp_hz(100),
  lat_0(37.429929),
  lon_0(-122.183598),
  p_tx(0.0),
  p_ty(0.0),
  d_thres(5.0),
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
  nh.param("lat_0", lat_0, lat_0);
  nh.param("lon_0", lon_0, lon_0);
  nh.param("p_tx", p_tx, p_tx);
  nh.param("p_ty", p_ty, p_ty);
  nh.param("d_thres", d_thres, d_thres);

  joy_sub_ = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Teleop_IRoad::joy_cb, this); 
  imu_sub_ = nh.subscribe<sensor_msgs::Imu>("gx5/imu/data", 10, &Teleop_IRoad::imu_cb, this);
  gps_sub_ = nh.subscribe<sensor_msgs::NavSatFix>("gx5/gps/fix", 10, &Teleop_IRoad::gps_cb,this);

  udpLoop = nh.createTimer(ros::Duration(1.0/udp_hz),&Teleop_IRoad::udp_cb, this);

  p_0 = gcs2cart(lat_0,lon_0);
  p_t(0,0) = p_tx;
  p_t(1,0) = p_ty;
  p_t(3,0) = 0.0;
  
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
  Matrix<double,3,1> r_t;       // Relative position of target in body frame
  r_t = quatrot((p_t-pose.block(0,0,3,1)));
  double d_t = r_t.norm();      // l2-norm of relative position

  Matrix<double,3,1> r_f;       // Front vector in body frame
  r_f << 0,1,0;
  steer = deg2rad(acos(r_t.dot(r_f)/d_t));

  if (r_t(0,0) > 0) {
    steer = -steer;
  } else {
    // Carry On
  }

  cmd_out = cmd_joy;
  if (cl_act_chk) {
    cmd_out.steer = steer_scale*steer;

    if (cmd_out.steer > 30.0) {
      cmd_out.steer = 30.0;
    } else if (cmd_out.steer < -30.0) {
      cmd_out.steer = -30.0;
    }

    if (d_t >= d_thres) {
      cmd_out.PRNDL_ct = 1;
      cmd_out.accel = 0.5;
     //cmd_struct.accel = min(distance/100.0,1.0); 
    } else {
      cmd_out.accel = 0.0; //debug 
    }
  } else {
    // Follow joystick input.
  }

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
  Matrix<double,3,1> v;
  double lat = gps->latitude;
  double lon = gps->longitude;

  v = gcs2cart(lat,lon)-p_0;
  pose.block<3,1>(0,0) = v;
}

Matrix<double,3,1> Teleop_IRoad::quatrot(const Vector3d& v) {
    // const Matrix<double,4,1>& q,const Matrix<double,3,1>& v
    
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

Matrix<double,3,1> Teleop_IRoad::gcs2cart(const double lat,const double lon) {
  Matrix<double,3,1> pos;
  double R = 6367449.0;

  pos(0,0) = R*cos(rad2deg(lat))*cos(rad2deg(lon));
  pos(1,0) = R*cos(rad2deg(lat))*sin(rad2deg(lon));
  pos(2,0) = 0.0;

  return pos;
}
double Teleop_IRoad::deg2rad(const double theta_d) {
    return((M_PI/180.0)*theta_d);
}

double Teleop_IRoad::rad2deg(const double theta_r) {
    return((180.0/M_PI)*theta_r);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Teleop_IRoad");
  Teleop_IRoad teleop_iRoad;

  ros::spin();
  return 0;
}
