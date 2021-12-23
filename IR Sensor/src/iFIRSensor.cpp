#include <Arduino.h>
#include "iFIRSensor.h"

TaskHandle_t iFIRSensor::taskHandle = NULL;
portMUX_TYPE iFIRSensor::mux = portMUX_INITIALIZER_UNLOCKED;
SemaphoreHandle_t iFIRSensor::xMutex;
uint16_t         iFIRSensor::m_nADCRaw[ SENSOR_COUNT ];   
adc1_channel_t   iFIRSensor::m_channels[ SENSOR_COUNT ];
portTickType iFIRSensor::delayTasks = 1000;



iFIRSensor::iFIRSensor(){
  m_adcBit = ADC_WIDTH_12Bit;
}

uint16_t iFIRSensor::get(const int id){
    return m_nADCRaw[id];
}

void iFIRSensor::calc(){

    digitalWrite( 5, HIGH );  // LL, CC, RR
    digitalWrite( 20, LOW );
    digitalWrite( 4, LOW ); 
    delayMicroseconds( 100 );
      m_nADCRaw[0] = adc1_get_raw((adc1_channel_t)m_channels[0]);
      m_nADCRaw[3] = adc1_get_raw((adc1_channel_t)m_channels[3]);
      m_nADCRaw[6] = adc1_get_raw((adc1_channel_t)m_channels[6]);


    digitalWrite( 5, LOW );
    digitalWrite( 20, LOW );
    digitalWrite( 4, HIGH );  // LB, RF
    delayMicroseconds( 100 );   
     
    m_nADCRaw[2] = adc1_get_raw((adc1_channel_t)m_channels[2]);
    m_nADCRaw[4] = adc1_get_raw((adc1_channel_t)m_channels[4]);


    digitalWrite( 5, LOW );
    digitalWrite( 20, HIGH ); // LF, RB
    digitalWrite( 4, LOW ); 
    delayMicroseconds( 100 );   
    
    m_nADCRaw[1] = adc1_get_raw((adc1_channel_t)m_channels[1]);
    m_nADCRaw[5] = adc1_get_raw((adc1_channel_t)m_channels[5]);
    
    digitalWrite( 20, LOW ); // LF, RB
}

void iFIRSensor::taskSensor(void *pvParameter) {

    while(1){

        calc();
        vTaskDelay( 4 );
    }
}

int iFIRSensor::analogRead(int id)
{
   m_nADCRaw[id] = adc1_get_raw((adc1_channel_t)m_channels[id]);

   return m_nADCRaw[id];
}



void iFIRSensor::init(){         
  // initialize ADC

  pinMode( 5, OUTPUT);
  pinMode( 20, OUTPUT);
  pinMode( 4, OUTPUT);

  digitalWrite( 5, LOW );
  digitalWrite( 20, LOW );
  digitalWrite( 4, HIGH );

  
    for(int i=0; i<SENSOR_COUNT; i++){
      pinMode(m_nPins[i], INPUT_PULLDOWN);  
      m_channels[i] = getChannelforADC1( m_nPins[i] );
      adc1_config_channel_atten((adc1_channel_t)m_channels[i], atten);
    }

    adc1_config_width( m_adcBit );

    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(
        unit,
        atten,
        m_adcBit,
        DEFAULT_VREF,
        &adc_chars);

    xTaskCreatePinnedToCore(&taskSensor, 
                          "taskSensor", 
                          1024, 
                          (void*)&delayTasks, 
                          uxTaskPriorityGet(NULL),
                          &taskHandle, 
                          0);     

    printf("val_type = %d  \n", val_type);                            
}

adc1_channel_t iFIRSensor::getChannelforADC1(int gpio){
    adc1_channel_t channel = ADC1_CHANNEL_0;
    switch( gpio ){
        case GPIO_NUM_36: channel = ADC1_CHANNEL_0; break;
        case GPIO_NUM_37: channel = ADC1_CHANNEL_1; break;
        case GPIO_NUM_38: channel = ADC1_CHANNEL_2; break;
        case GPIO_NUM_39: channel = ADC1_CHANNEL_3; break;
        case GPIO_NUM_32: channel = ADC1_CHANNEL_4; break;
        case GPIO_NUM_33: channel = ADC1_CHANNEL_5; break;
        case GPIO_NUM_34: channel = ADC1_CHANNEL_6; break;
        case GPIO_NUM_35: channel = ADC1_CHANNEL_7; break;
    }

    return channel;
}