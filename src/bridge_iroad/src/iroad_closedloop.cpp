#include <bridge_iroad/iroad_closedloop.h>

Teleop_IRoad::Teleop_IRoad():
  accel_id(5), //ID of controller axis for accelerator
  steer_id(0), //ID of controller axis for steering control
  ct_input_id(2),
  PRNDL_vr_id(1), //ID of controller button for "Reverse" setting on transmission
  PRNDL_ct_id(2), //ID of controller button for "Drive" setting on transmission
  pk_brake_id(0), //ID of controller button for motor driver controlling parking brake
  cl_act_id(3),
  steer_scale(350), //rescales [-1,1] to resolution expected by MABx firmware
  accel(0.0), //variable for accelerator value
  steer(0.0), //variable for steering value
  udp_hz(100), //frequency in Hz of sending UDP messages for vehicle control
  lat0(37.4299484), //latitude of point of origin
  lon0(-122.1836507), //longitude of point of origin
  ptx(0.0), //difference in longitude (in meters) from target location to point of origin
  pty(0.0), //difference in latitude (in meters) from target location to point of origin
  dthres(5.0), //radius around goal location within which closed-loop controls deactivate, in meters
  cl_act_chk(0),
  v_max(2.2222222), //maximum permissible vehicle speed, in meters per second
  st_conv(M_PI/2880.0), //Factor to convert commanded steering setting to radians
  //ctrl_k1(1.0), //tunable constant for feedback control (velocity and steering), must be greater than zero to ensure convergence
  ctrl_k2(1.0), //tunable constant for feedback control (steering), must be greater than zero to ensure convergence
  //ctrl_k3(1.0), //tunable constant for feedback control (steering for target heading), must be greater than zero to ensure convergence
  max_steer(30), //magnitude of maximum angle achievable by steering mechanism (in degrees)
  accel_frac(240.0/(0.26*380.0)), //rescales [0,1] accelerator signal into acceleration rate (in meters per second squared)
  whlbase(1.695) //vehicle wheelbase, in meters
{
  nh.param("accel_id", accel_id, accel_id);
  nh.param("steer_id", steer_id, steer_id);
  nh.param("ct_input_id", ct_input_id, ct_input_id);
  nh.param("PRNDL_vr_id", PRNDL_vr_id, PRNDL_vr_id);
  nh.param("PRNDL_ct_id", PRNDL_ct_id, PRNDL_ct_id);
  nh.param("pk_brake_id", pk_brake_id, pk_brake_id);
  nh.param("cl_act_id", cl_act_id, cl_act_id);
  nh.param("steer_scale", steer_scale, steer_scale);
  nh.param("accel_frac", accel_frac, accel_frac);
  nh.param("lat0", lat0, lat0);
  nh.param("lon0", lon0, lon0);
  nh.param("ptx", ptx, ptx);
  nh.param("pty", pty, pty);
  nh.param("dthres", dthres, dthres);
  nh.param("v_max",v_max,v_max);
  //nh.param("ctrl_k1",ctrl_k1,ctrl_k1);
  nh.param("ctrl_k2",ctrl_k2,ctrl_k2);
  //nh.param("ctrl_k3",ctrl_k3,ctrl_k3);
  nh.param("whlbase",whlbase,whlbase);
  nh.param("max_steer",max_steer,max_steer);

  joy_sub_ = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Teleop_IRoad::joy_cb, this); //subscribe to joypad input
  imu_sub_ = nh.subscribe<sensor_msgs::Imu>("gx5/imu/data", 10, &Teleop_IRoad::imu_cb, this); //subscribe to data from GX5 IMU
  gps_sub_ = nh.subscribe<sensor_msgs::NavSatFix>("gx5/gps/fix", 10, &Teleop_IRoad::gps_cb,this); //subscribe to data from GX5 GPS
  cmd_pub_ = nh.advertise<geometry_msgs::Twist>("cmd_input", 10); //prepare to publish movement instructions sent to MABx
  udpLoop = nh.createTimer(ros::Duration(1.0/udp_hz),&Teleop_IRoad::udp_cb, this);

  can_sub_ = nh.subscribe<geometry_msgs::Twist>("can_movement",10, &Teleop_IRoad::can_cb, this); //subscribe to movement indicated by feedback from vehicle CAN
  sft_sub_ = nh.subscribe<u_int32_t>("can_shiftpos", 10, &Teleop_IRoad::shift_cb, this);
  brk_sub_ = nh.subscribe<bool>("can_brakeped", 10, &Teleop_IRoad::brake_cb, this);

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

void Teleop_IRoad::can_cb(const geometry_msgs::Twist::ConstPtr& twist)
{
  can_speed = twist.linear.y;
}

void Teleop_IRoad::shift_cb(const u_int32_t& prndl)
{
  can_shift = prndl;
}

void Teleop_IRoad::brake_cb(const bool& brake)
{
  can_brake = brake;
}

void Teleop_IRoad::udp_cb(const ros::TimerEvent& event) {
  Matrix<double,3,1> r_tW;        // Relative position of target in world frame.
  Matrix<double,3,1> r_tb;        // Relative position of target in body frame.
  r_tW = pt-pose.block(0,0,3,1);
  r_tb = quatrot(r_tW);

  double d_t = r_tb.norm();      // l2-norm of relative position

  Matrix<double,3,1> r_f;       // Front vector in body frame
  r_f << 0.0,1.0,0.0;
  
  /*steer = rad2deg(acos(r_tb.dot(r_f)/d_t)); //debug: steering setting is equal to angle between vehicle heading and goal direction

  steer = min(steer, max_steer);
  steer /= max_steer;

  if (r_tb(0,0) < 0) {
    steer = -steer;
  } else {
    // Carry On
  }

  */

  double alpha = acos(r_tb.dot(r_f)/d_t); //angle between vehicle heading and direction of goal (in radians)
  if (r_tb(0,0) < 0){
    alpha = -alpha; //accounting for the difference between left and right turns
  }
  //double delta; //angle between vehicle heading and desired vehicle heading at target (in radians), not yet implemented

  double omega = ctrl_k2*alpha; //feedback control law dictates this angular velocity value (in terms of the vehicle's heading) to target the goal location, without a specific final heading (with respect to the world frame)
  //double omega = ctrl_k2*alpha + ctrl_k1*sin(alpha)*cos(alpha)*(alpha + ctrl_k3*delta)/alpha; //instantaneous angular velocity required by feedback control law, if goal position includes a target heading

  steer = rad2deg(atan2(whlbase*omega,v_const)); //conversion of required angular velocity of vehicle to steering angle that will result in that angular velocity
  steer /= max_steer; //rescale steer value to be a proportion of maximum extent of steering mechanism

  cmd_out = cmd_joy;
  if (cl_act_chk) {
    cmd_out.steer = steer_scale*steer; //rescaling the steering angle to resolution required by MABx firmware

    // Clip values to be within the range that can be requested of MABx [-350,350]
    if (cmd_out.steer > 350.0) {
      cmd_out.steer = 350.0;
    } else if (cmd_out.steer < -350.0) {
      cmd_out.steer = -350.0;
    }

    if (d_t >= dthres) {
      cmd_out.PRNDL_ct = 1;
      cmd_out.accel = 1.0; //Approximately 52% throttle commanded
    } else {
      cmd_out.accel = 0.0; //stop accelerating once goal is reached
    }
  } else {
    // Follow joystick input.
  }
  // cout << "Pose (World): \n" << pose << endl;
  /*cout << "Relative Position (World):\n" << r_tW << endl;
  cout << "Relative Position (Body):\n" << r_tb << endl;
  cout << "Steering:" << steer << endl;
  cout << "===========================================" << endl;*/

  // Send Packet
  sendto(socket_desc, &cmd_out, sizeof(cmd_out), MSG_CONFIRM, (const struct sockaddr *)&client_addr, sizeof(client_addr));

  // Calculate and publish twist commanded by control system, for observability by the rest of the autonomy stack
  geometry_msgs::Twist cmd_vel;
  
  if (!can_brake){
    if(can_shift == 1){
      cmd_vel.linear.y = min(v_max, can_speed + (accel_frac*cmd_out.accel/udp_hz)); //y-axis of body frame aims in the forward direction of the vehicle
    } else if (can_shift == 2){
      cmd_vel.linear.y = max(-v_max, can_speed - (accel_frac*cmd_out.accel/udp_hz)); //assuming max vehicle speed applies in forward and reverse
    }
    cmd_vel.angular.z = -can_speed*tan(cmd_out.steer*st_conv)/whlbase; //z-axis of body frame aims downwards into the ground, vehicle tilting mechanism is discounted
  } //else cmd_vel.linear.y = 0; //brake pedal engaged or PRNDL is neutral
  
  cmd_pub_.publish(cmd_vel);
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
