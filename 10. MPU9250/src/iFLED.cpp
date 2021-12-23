/******************************************************************************
iFLED.cpp - iFLine, iFBalance Arduino Library 
hkkim@koreaits.com ( KITS Lab )
original creation date: April 3, 2020

Development environment specifics:
Arduino IDE 1.8.x
iFZero, iFLine, iFBalance
******************************************************************************/

#include <Arduino.h>
#include "iFLED.h"

NeoPixelBusType strip(NUM_OF_LEDS, GPIO_NUM_2 );
NeoPixelBusType& iFLED::_strip = strip;//

bool iFLED::_isBlink = 0;
uint8_t iFLED::_mode = ALL_OFF;
uint32_t iFLED::_counter = 0;

TaskHandle_t iFLED :: taskHandle = NULL ; 
SemaphoreHandle_t iFLED :: xMutex = NULL ; 
portTickType delayTasks = 1000 ;

RgbColor RED(MAX_SATURATION, 0, 0);
RgbColor GREEN(0, MAX_SATURATION, 0);
RgbColor BLUE(0, 0, MAX_SATURATION);
RgbColor WHITE(MAX_SATURATION);
RgbColor BLACK(0);

iFLED::iFLED(){
   
}

void iFLED::setAllBlack()
{
    for (int i = 0; i < NUM_OF_LEDS; i++)
        _strip.SetPixelColor(i, BLACK);
    _strip.Show();
}


void iFLED::taskColorLED(void *pvParameter) {

    while(1){
        if (xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE){      

            if (_mode == RAINBOW ) {
                strip.SetPixelColor(_counter % 4, RED);
                strip.SetPixelColor((_counter + 1) % 4, BLUE);
                strip.SetPixelColor((_counter + 2) % 4, GREEN);
                strip.SetPixelColor((_counter + 3) % 4, WHITE);
                strip.Show();
                ++_counter;
            } 
            else if (_mode == BLINK) {
                for (float i = 0; i < 1; i += 0.01f) {
                    strip.SetPixelColor(_counter % 4, RED.LinearBlend(RED, BLACK, i));
                    strip.SetPixelColor((_counter + 1) % 4, BLUE.LinearBlend(BLUE, BLACK, i));
                    strip.SetPixelColor((_counter + 2) % 4, GREEN.LinearBlend(GREEN, BLACK, i));
                    strip.SetPixelColor((_counter + 3) % 4, WHITE.LinearBlend(WHITE, BLACK, i));
                    strip.Show();
                    delay(10);
                }
                ++_counter;
                delay(500);
            } 
            else if (_mode == RANDOM) {
                RgbColor arr[] = {RED, GREEN, BLUE, BLACK};
                int r = rand();
                uint8_t i = r & 0xFF;
                uint8_t j = (r >> 8) & 0xFF;
                float k = (r % 100) * 0.01f;
                strip.SetPixelColor(i & 0x3, RED.LinearBlend(arr[(j & 0x3)], arr[(j & 0xC)], k));
                strip.SetPixelColor(i & 0xC, BLUE.LinearBlend(arr[(j & 0xC)], arr[(j & 0x30)], k));
                strip.SetPixelColor(i & 0x30, GREEN.LinearBlend(arr[(j & 0x30)], arr[(j & 0xC0)], k));
                strip.SetPixelColor(i & 0xC0, WHITE.LinearBlend(arr[(j & 0xC0)], arr[(j & 0x3)], k));
                strip.Show();
                delay(50);
                setAllBlack();
                delay(10);
            } 
            else {
                setAllBlack();
            }
        }
        xSemaphoreGive( xMutex );
          
        vTaskDelay ( 1000 );   
    } 
}



void iFLED::init(){         
    ////////////////////////////////////////////////////////////////
    // 
    _strip.Begin();
    for (int i = 0; i < NUM_OF_LEDS; i++)
        strip.SetPixelColor(i, BLACK);
    strip.Show(); // Send the updated pixel colors to the hardware.                               

    xMutex = xSemaphoreCreateMutex();
    xTaskCreatePinnedToCore(&taskColorLED, 
                          "taskColorLED", 
                          1024, 
                          (void*)&delayTasks, 
                          uxTaskPriorityGet(NULL), 
                          &taskHandle, 
                          1);     
}

void iFLED::setColor(uint8_t pos, uint8_t color ){

    switch( color ){
        case 1: _strip.SetPixelColor(pos, BLACK); break;
        case 2: _strip.SetPixelColor(pos, BLUE); break;
        case 3: _strip.SetPixelColor(pos, RED); break;
        case 4: _strip.SetPixelColor(pos, GREEN); break;
        case 5: _strip.SetPixelColor(pos, WHITE); break;                        
    }
    _strip.Show();        
    
}

void iFLED::setMode(uint8_t mode)
{
    if (xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE){        
        switch (mode) {
            case RAINBOW:
            case BLINK:
                _counter = 0;
                break;
        }
        _mode = mode;
    }
    xSemaphoreGive( xMutex );
}