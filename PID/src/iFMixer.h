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
#include "iFMotors.h"

#define MAXMOTORS   2

#define LEFT_F      7
#define LEFT_R      8  
#define LEFT_F_CH   (0)
#define LEFT_R_CH   (1)

#define RIGHT_F     27
#define RIGHT_R     26   
#define RIGHT_F_CH  (2)
#define RIGHT_R_CH  (3)

class  iFMixer {

    private:

        // iFMotor motors[2] = { 
        //     iFMotor(LEFT_F, LEFT_R, LEFT_F_CH, LEFT_R_CH), 
        //     iFMotor(RIGHT_F, RIGHT_R, RIGHT_F_CH, RIGHT_R_CH), 
        // };

        iFMotors ifMotors;

    public:        
 
    public:
        iFMixer();

        void init();
        void writeMotor(uint8_t index, int value);
        void stop(void);
        void run(double *motorVals);

        int getMaxOutput();
};