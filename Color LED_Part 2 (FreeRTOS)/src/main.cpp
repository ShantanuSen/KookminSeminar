/******************************************************************************
main.cpp - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFZero, iFLine, iFBalance
******************************************************************************/

#include <Arduino.h>
#include "iFLED.h"

iFLED         ifLed;

void setup()
{ 
  Serial.begin(115200);

  ///////////////////////////////////////////////////////
  // Color LED
  ifLed.init();  
  ifLed.setMode( BLINK );
  
}

void loop() {

}