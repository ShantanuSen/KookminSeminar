/******************************************************************************
iFLED.h - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFZero, iFLine, iFBalance
******************************************************************************/

#ifndef iFLED_v1_h
#define iFLED_v1_h
#define iFLED_LIBRARY_VERSION	1.1.1

#include <Arduino.h>
#include <NeoPixelBus.h>

typedef  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>  NeoPixelBusType;

#define COLOR_BLACK     1
#define COLOR_BLUE      2
#define COLOR_RED       3
#define COLOR_GREEN     4
#define COLOR_ORANGE    5
#define COLOR_WHITE     6

#define NUM_OF_LEDS     4
#define MAX_SATURATION  128


typedef enum {
    ALL_OFF,
    RAINBOW,
    BLINK,
    RANDOM,
    CUSTOM,
} iFLED_MODE;

class iFLED {

    private:
        static NeoPixelBusType& _strip;
        static NeoPixelBusType& _stripB;

        static bool     _isBlink;
        static uint8_t  _mode;
        static uint32_t _counter;

        static TaskHandle_t taskHandle;
    public:        
        static SemaphoreHandle_t xMutex;
 
    public:
        iFLED();

        static void init();
        static void taskColorLED(void *pvParameter);
 
        static void setColor(uint8_t pos, uint8_t color );   

        static void setAllBlack();
        static void setMode(uint8_t mode);


};

#endif