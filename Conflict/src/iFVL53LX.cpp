#include <Arduino.h>
#include "iFVL53LX.h"

uint32_t iFVL53LX::m_nDistance = 0;
TaskHandle_t iFVL53LX::taskHandle = NULL;
portTickType iFVL53LX::delayTask = 100; 
SemaphoreHandle_t iFVL53LX::xMutex = NULL;
volatile int iFVL53LX::interruptCount = 0;
VL53LX      iFVL53LX::vl53lx;

void  iFVL53LX::onHandler ()
{
    if (xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE){       
      interruptCount++;
    }
    xSemaphoreGive( xMutex );
}

iFVL53LX::iFVL53LX(){
}

void iFVL53LX::taskProcess(void *pvParameter) {
  portTickType delay = *(portTickType*)pvParameter;

  while(1) {    
    if (xSemaphoreTake( xMutex, portMAX_DELAY ) == pdTRUE){      
      calcDistance();
    }
    xSemaphoreGive( xMutex );
    vTaskDelay( delay / portTICK_RATE_MS );
  }
}

void iFVL53LX::calcDistance(){
  VL53LX_MultiRangingData_t MultiRangingData;
  VL53LX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;
  uint8_t NewDataReady = 0;
  int no_of_object_found = 0, j;

  //if( interruptCount > 0 )
  {
    int status = vl53lx.VL53LX_GetMeasurementDataReady(&NewDataReady);

    if((!status)&&(NewDataReady!=0))
    {
      status = vl53lx.VL53LX_GetMultiRangingData(pMultiRangingData);
      no_of_object_found=pMultiRangingData->NumberOfObjectsFound;
      for(j=0;j<no_of_object_found;j++)
      {
        m_nDistance = pMultiRangingData->RangeData[j].RangeMilliMeter;
      }

      if (status==0)
      {
        status = vl53lx.VL53LX_ClearInterruptAndStartMeasurement();
      }  
    }
  }
}

uint32_t iFVL53LX::getDistance(){
    return m_nDistance;
}

void iFVL53LX::init(){
  //pinMode(interruptPin, INPUT_PULLUP);
  //attachInterrupt(interruptPin, onHandler, FALLING);

  // Configure VL53LX satellite component.
  vl53lx.begin();
  vl53lx.InitSensor(0x52);

  // Start Measurements
  vl53lx.VL53LX_StartMeasurement();
  vl53lx.VL53LX_ClearInterruptAndStartMeasurement();    
}

void iFVL53LX::begin(){  
    xMutex = xSemaphoreCreateMutex();
    xTaskCreatePinnedToCore(&taskProcess, 
                          "taskProcessVL53L1X", 
                          2048, 
                          (void*)&delayTask, 
                          uxTaskPriorityGet(NULL), 
                          &taskHandle, 
                          0);     
}