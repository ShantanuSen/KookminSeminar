/******************************************************************************
iFButton.cpp - iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFBalance
******************************************************************************/

#include "Arduino.h"
#include "iFButton.h"

gpio_num_t iFButton::pin = GPIO_NUM_0;

portMUX_TYPE iFButton::spinlock = portMUX_INITIALIZER_UNLOCKED;
volatile bool iFButton::bPressed = false;

void IRAM_ATTR iFButton::onHandler()
{  
  portENTER_CRITICAL(&spinlock);
    setRelease( true );
  portEXIT_CRITICAL(&spinlock);
}

void iFButton::taskFunc(void *pvParameters)
{
  for (;;)
  {  
    if( isPressed() ){
      // setRelease( false );

      Serial.println("iFButton pressed !!! " );
    }
    delay(1);
  }
}

bool iFButton::isPressed(){
  bool isPressed = false;

  portENTER_CRITICAL(&spinlock);
    isPressed = bPressed;
  portEXIT_CRITICAL(&spinlock);

  return isPressed; 
}

void iFButton::setRelease(bool state){ 
  bPressed = state; 
}

void iFButton::init(gpio_num_t io, int core)
{
  pin = io;

  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt( pin ), onHandler, FALLING);
 
  xTaskCreatePinnedToCore( taskFunc, "taskFunc", 
          2048, 
          NULL, 
          uxTaskPriorityGet(NULL), 
          NULL, 
          core);

  int16_t level = digitalRead( pin );
  Serial.println("iFButton level : " + String( level ));
}