#pragma once

#include <Arduino.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "driver/mcpwm.h"  

//#define DEFAULT_VREF 0 //Use adc2_vref_to_gpio() to obtain a better estimate
#define DEFAULT_VREF 1100 //Use adc2_vref_to_gpio() to obtain a better estimate
#define SENSOR_COUNT 7

class iFIRSensor{
    private:

        uint8_t m_nPins[ SENSOR_COUNT ];

        
        static  TaskHandle_t taskHandle;
        static  uint16_t         m_nADCRaw[ SENSOR_COUNT ];   
        static  adc1_channel_t   m_channels[ SENSOR_COUNT ];
     
    public:        
        static  portMUX_TYPE mux;
        static  SemaphoreHandle_t xMutex;
        static  portTickType delayTasks;
    private:
        adc_bits_width_t m_adcBit;
        const   adc_atten_t atten = ADC_ATTEN_DB_6;    // 1/1
        const   adc_unit_t unit = ADC_UNIT_1;
        esp_adc_cal_characteristics_t adc_chars;    

    public:
        iFIRSensor();
        iFIRSensor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5, uint8_t pin6, uint8_t pin7,
                   adc_bits_width_t bit = ADC_WIDTH_12Bit){ 
            m_nPins[0] = pin1;
            m_nPins[1] = pin2;
            m_nPins[2] = pin3;
            m_nPins[3] = pin4;
            m_nPins[4] = pin5;
            m_nPins[5] = pin6;
            m_nPins[6] = pin7;

            m_adcBit = bit;
        }

        void init();
        void setPin(const int id, uint8_t pin){
            m_nPins[id] = pin; 
        }

        void setADCBits(adc_bits_width_t bit = ADC_WIDTH_12Bit){
            m_adcBit = bit;        
        }

        static void calc();
        static void taskSensor(void *pvParameter);

        uint16_t get(int id);

        int analogRead(int id);
        adc1_channel_t getChannelforADC1(int gpio);
};