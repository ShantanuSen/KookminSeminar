/******************************************************************************
iFLED.cpp - iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFBalance
******************************************************************************/

#include "Arduino.h"
#include "iFLED.h"

gpio_num_t iFLED::pin = GPIO_NUM_4;

void iFLED::taskFunc(void *pvParameters)
{
  portTickType delay = *(portTickType*)pvParameters;

  while(1) {
    digitalWrite(pin, HIGH);
    vTaskDelay(delay / portTICK_PERIOD_MS);

    digitalWrite(pin, LOW);
    vTaskDelay(delay / portTICK_PERIOD_MS);
  }
}

void iFLED::init(gpio_num_t io, int core)
{ 
  pin = io;

  // Configure pin
  pinMode(pin, OUTPUT);

  xTaskCreatePinnedToCore( taskFunc, "taskFunc", 
          2048, 
          (void*)&timeDelay, 
          uxTaskPriorityGet(NULL), 
          &taskHandle, 
          core);

  Serial.println("taskHandle ID: " + String( uxTaskPriorityGet( taskHandle ) ) );          
}