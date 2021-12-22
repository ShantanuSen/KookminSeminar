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

#define SerialDebug   false  // Set to true to get Serial output for debugging
#define PRO_CPU 0
#define APP_CPU 1

iFLED ifLed;

void setup() {
  Serial.begin( 115200 );
  delay(1000);
  
  ifLed.init( GPIO_NUM_4, PRO_CPU);
}

void loop() {
  // Do nothing
}