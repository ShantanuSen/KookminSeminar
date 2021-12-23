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
#include "iFEncoder.h"

iFLED         ifLed;
iFMotors      ifMotors;
iFEncoder     ifEncoder;

// Encoder Count
int32_t      _nCurLeft = 0, _nCurRight = 0;

void getEncoderSpeed(){     
    portENTER_CRITICAL(&ifEncoder.muxr);  
    _nCurLeft = ifEncoder.getCountLeftReset();          
    _nCurRight = ifEncoder.getCountRightReset();          
    portEXIT_CRITICAL(&ifEncoder.muxr);
}

void setup()
{ 
  Serial.begin( 115200 );

  ///////////////////////////////////////////////////////
  // Color LED
  ifLed.init();  
  ifLed.setMode( BLINK );


  ///////////////////////////////////////////////////////
  // Motor
  ifMotors.init();  
  ifMotors.move( 400, 400);    

  ///////////////////////////////////////////////////////
  // Encoder : Cable is crossed !!!
  ifEncoder.init(25, 14, 13, 15);  
}

void loop() {

}