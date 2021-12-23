/******************************************************************************
iFPID.h - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFZero, iFLine, iFBalance
******************************************************************************/

#pragma once

#include <Arduino.h>
#include <NeoPixelBus.h>


class iFPID {

    private:
        double setpoint = 0.0;

        double input;
        double output;

        double Kp = 20.0;
        double Ki = 1.0;
        double Kd = 0.5;

        unsigned long timeCurrent, timeLast ;
        double outMin, outMax;

    public:        

        // 5 ms => 0.005 sec : smapling time
        double dt = 0.005;  

         double error = 0.0;

        // Integral term 
        double errorI = 0.0 ;
        

        // Differential term
        double errorD = 0.0; 
        double inputLast = 0.0; // previous time errorK

    public:
        iFPID();

        void init();
        void init(double Kp, double Ki, double Kd);
        void calcParameter(int Ku, double Pu);
        
        void calc();
        void calc(double in, double* pMotorValues);

        void setPoint(double sp);
        void setInput(double in);
        double outInput();

        void SetOutputLimits(double outMin, double outMax); 
};