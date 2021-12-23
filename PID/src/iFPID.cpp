/******************************************************************************
iFPID.h - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFZero, iFLine, iFBalance
******************************************************************************/

#include <Arduino.h>
#include "iFPID.h"

iFPID::iFPID(){
    calcParameter( 65, 0.18); // 2020.09.21
}

void iFPID::calcParameter(int Ku, double Pu){

    Kp = 0.6 * Ku;

    // classic PID double Ti = 0.5 * Pu;        Ki = Kp / Ti; // Pessen Integral Rule     Kd = Kp * Pu / 6.3 ; // Kd = Kp * Pu / 8; }
    
}
     

void iFPID::init(){
    timeLast = timeCurrent = millis();
}

void iFPID::init(double Kp, double Ki, double Kd){
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
   
    timeLast = timeCurrent = millis();
}


void iFPID::calc(){
    timeCurrent = millis();

    dt = (double) ( timeCurrent - timeLast ) * 0.001 ; 

    error = setpoint - input;

    // Integral term
     errorI += error * dt; 
     if (errorI> outMax) errorI = outMax; 
     else if (errorI <outMin) errorI = outMin;
    
     

    // Differential term
    errorD = (input - inputLast) / dt;

    ////////////////////////////////////////////////
    // 
    output = Kp*error + Ki*errorI - Kd*errorD;

    if(output > outMax) output = outMax;
    else if(output < outMin) output = outMin;    

    inputLast = input;
    timeLast = timeCurrent;
}

void iFPID::calc(double in, double* pMotorValues){
    setInput( in );

    calc();
    pMotorValues[0] = -output;  // Left Motor
    pMotorValues[1] = output;   // Right Motor

}

void iFPID::setPoint(double setpoint){
    this->setpoint = setpoint;
}

void iFPID::setInput(double input){
    this->input = input;
}

double iFPID::outInput(){
    return output;
}

void iFPID::SetOutputLimits(double outMin, double outMax){
    this->outMin = outMin;
    this->outMax = outMax;
}