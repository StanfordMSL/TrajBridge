/* copyright[2021] <msl> <kunal shah>
**************************************************************************
  File Name    : pid.cpp
  Author       : Kunal Shah
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : k2shah@stanford.edu
  Create Time  : Apr 26, 2021.
  Description  : generic PID class with feed forward support 
**************************************************************************/

#include<bridge_px4/pid.h>
#include<iostream>
#include<exception>

PID::PID(){
    _error = 0.f;
    _prevError = 0.f;
    _dt =0.f;
}

PID::~PID(){
}

void PID::setGains(const float p, const float i, const float d){
    _k.p = p;
    _k.i = i;
    _k.d = d;
}

void PID::setIntegralLimit(const float value){
    _integralLimit = value;
}

float PID::effort(float state, float setpoint, float dt, float feedforward){
    // update internals
    _prevError = _error;
    _error = setpoint - state;
    _dt = dt;
    std::cout << "error: " << _error <<std::endl;
    if (_dt == 0.0f){
        throw std::runtime_error("dt is zero");
    }

    // compute each term
    // p
    _pValue = _k.p * _error;
    // i
    _iValue = _k.i * updateIntegral();
    // d
    _dValue = _k.d * (_error - _prevError)/dt;
    std::cout << " P: " << _pValue;
    std::cout << " I: " << _iValue;
    std::cout << " D: " << _dValue << std::endl;

    return _pValue + _iValue + _dValue + feedforward;
}

float PID::updateIntegral(){
    // update value
    _integral += _error;
    // check limits
    // upper
    _integral = (_integral > _integralLimit)? _integralLimit : _integral;
    // lower
    _integral = (_integral < -_integralLimit)? -_integralLimit : _integral;
    return _integral;
}

PID4d::PID4d(){
}

PID4d::~PID4d(){
}

void PID4d::setGains(const float p, const float i, const float d){
    x.setGains(p, i, d);
    y.setGains(p, i, d);
    z.setGains(p, i, d);
    yaw.setGains(p, i, d);
}

void PID4d::setIntegralLimit(const float value){
    x.setIntegralLimit(value);
    y.setIntegralLimit(value);
    z.setIntegralLimit(value);
    yaw.setIntegralLimit(value);
}