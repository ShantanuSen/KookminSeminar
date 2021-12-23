/******************************************************************************
iFVL53L1X.h - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFZero, iFLine, iFBalance
******************************************************************************/

#pragma once

#include <Arduino.h>
#include <vl53lx_class.h>

class iFVL53LX {

    private:
        static uint32_t     m_nDistance;
        static TaskHandle_t taskHandle;
        static portTickType delayTask; 
        static VL53LX       vl53lx;

        static volatile int interruptCount;

        int interruptPin  = 9;
    public:
        static SemaphoreHandle_t xMutex;

    public:
        iFVL53LX();

        void init();
        void begin();

        static void onHandler();
        static void taskProcess(void *pvParameter);
        static void calcDistance();
        static uint32_t getDistance();
};