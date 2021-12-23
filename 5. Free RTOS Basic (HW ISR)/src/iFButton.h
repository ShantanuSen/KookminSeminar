/******************************************************************************
iFButton.h - iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFBalance
******************************************************************************/

#pragma once

#include <Arduino.h> 

class iFButton
{
    private:     
        TaskHandle_t taskHandle;

        static volatile bool bPressed;
        static gpio_num_t pin;

    private:
        static void IRAM_ATTR onHandler();
 
    public:  
        static portMUX_TYPE spinlock;

    public:  
        iFButton(){};
        void init(gpio_num_t pin, int core);
        static void taskFunc(void *pvParameters);

    public:  
        static bool isPressed();
        static void setRelease(bool state);
};