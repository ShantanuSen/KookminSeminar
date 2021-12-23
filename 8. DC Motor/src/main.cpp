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
#include "iFMotors.h"

iFLED         ifLed;
iFMotors      ifMotors;

void setup()
{ 
  Serial.begin(115200);

  ///////////////////////////////////////////////////////
  // Color LED
  ifLed.init();  
  ifLed.setMode( BLINK );


  ///////////////////////////////////////////////////////
  // Motor
  ifMotors.init();  
  ifMotors.move( 450, 450);      
}

void loop() {

}