/******************************************************************************
iFMixer.h - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFZero, iFLine, iFBalance
******************************************************************************/

#include <Arduino.h>
#include "iFMixer.h"

iFMixer::iFMixer(){

}

void iFMixer::init(){
    ifMotors.init();
}

void iFMixer::writeMotor(uint8_t index, int value){
    // motors[index].move( value );
}

void iFMixer::run(double *motorVals)
{

    ifMotors.move(motorVals[0], motorVals[1]);
    // for (uint8_t i = 0; i < MAXMOTORS; i++) {
    //     writeMotor(i, (int)motorVals[i]);
    // }
    

}

void iFMixer::stop(void)
{
    for (uint8_t i = 0; i < MAXMOTORS; i++) {
        writeMotor(i, 0);
    }
}

int iFMixer::getMaxOutput(){
    // return motors[0].getMaxSpeed();
    return 1023;
}