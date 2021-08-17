/* copyright[2021] <msl> <kunal shah>
**************************************************************************
  File Name    : pid.h
  Author       : Kunal Shah
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : k2shah@stanford.edu
  Create Time  : Apr 26, 2021.
  Description  : generic PID class with feed forward support 
**************************************************************************/

#ifndef __PID_H__
#define __PID_H__

struct gains{
  float p;
  float i;
  float d;
};

class PID {
 public:
    PID();
    ~PID();
    
    // setters
    void setGains(const float p, const float i, const float d);
    void setIntegralLimit(const float value);

    // methods
    float effort(float state, float setpoint, float dt, float feedforward=0.f);

 private:
    gains _k;
    float _error;
    float _prevError;
    float _dt;
    float _integral;
    float _integralLimit;

    float _pValue;
    float _dValue;
    float _iValue;

    float updateIntegral();
};

class PID4d {
 public:
    PID4d();
    ~PID4d();

    PID x;
    PID y;
    PID z;
    PID yaw;

    void setGains(const float p, const float i, const float d);
    void setIntegralLimit(const float value);

};
#endif