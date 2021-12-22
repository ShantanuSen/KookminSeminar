/******************************************************************************
iFLED.h - iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFBalance
******************************************************************************/

#pragma once

#include <Arduino.h> 

class  iFLED
 { 
     private : 
        int32_t timeDelay = 500 ;         TaskHandle_t taskHandle;
        static  gpio_num_t pin;

    public:  
        iFLED(){};
        void init(gpio_num_t io, int core);
    
        static void taskFunc(void *pvParameters);

};