/******************************************************************************
main.cpp - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFBalance
******************************************************************************/

#include <Arduino.h>
#include "iFLED.h"
#include "iFMixer.h"
#include "iFEncoder.h"
#include "MPU9250.h"
#include "iFPID.h"

#define SerialDebug   false  // Set to true to get Serial output for debugging
#define I2Cclock      400000
#define MPU_INT_PIN   5 // Interrupt Pin definitions

iFLED         ifLed;
iFMixer       ifMixer;
iFEncoder     ifEncoder;
MPU9250       ifMpu;
iFPID         ifPid;


void setup()
{ 
  Serial.begin( 115200 );

  Wire.begin(21, 22, I2Cclock);

  ifMpu.selectFilter( QuatFilterSel::MADGWICK);
  ifMpu.setup(0x68);  // change to your own address
  delay(2000);      // to get stable data of MPU9250

  ///////////////////////////////////////////////////////
  // Color LED
  ifLed.init();  
  ifLed.setMode( BLINK );

  ifMixer.init();
  ifPid.init();
  ifPid.SetOutputLimits( -ifMixer.getMaxOutput(), ifMixer.getMaxOutput());


  ///////////////////////////////////////////////////////
  // Encoder
  ifEncoder.init(25, 14, 13, 15);  

}

void loop() {

  if (ifMpu.update()) {
    
    double motorVals[2];

    ifPid.calc(ifMpu.getPitch(), &motorVals[0]);
    ifMixer.run( &motorVals[0]);

  }
}