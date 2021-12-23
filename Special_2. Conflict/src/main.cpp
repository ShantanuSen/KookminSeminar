#include <Arduino.h>
#include "iFVL53LX.h"
#include "iFIRSensor.h"
#include "MPU9250.h"

#define I2Cclock      400000


MPU9250 ifMpu;
iFVL53LX ifVL53LX; 



///////////////////////////////////////////////////////
// for IR Sensor
iFIRSensor    ifIRSensor( 37, 34, 36, 32, 35, 33, 38, ADC_WIDTH_BIT_12);
uint16_t      m_irValue[7];

void setup()
{
  Serial.begin(115200);

  Wire.begin(21, 22, I2Cclock);

  ///////////////////////////////////////////////////////
  // MPU 9250
  ifMpu.selectFilter( QuatFilterSel::MADGWICK);
  ifMpu.setup(0x68);  // change to your own address
  delay(2000);      // to get stable data of MPU9250

  ///////////////////////////////////////////////////////
  // ToF Sensor
  ifVL53LX.init();
  ifVL53LX.begin();


  ///////////////////////////////////////////////////////
  // IR Sensor
  ifIRSensor.init(); 
}


int irLoop = 0;


void loop() {

  bool isIMUUpdate = false;
  uint32_t distance = 0;
  if (xSemaphoreTake( iFVL53LX::xMutex, portMAX_DELAY ) == pdTRUE){ 
    isIMUUpdate = ifMpu.update();
    distance = ifVL53LX.getDistance();
  }
  xSemaphoreGive( iFVL53LX::xMutex );

  if (isIMUUpdate) {    

    ///////////////////////////////////////////////////////
    // Serial can slow the process 
    if( irLoop++ > 50 ){
      irLoop = 0;
      for( int i=0; i<7; i++){
        m_irValue[i] = ifIRSensor.get(i);
        Serial.printf("[%d]= %d ", i , m_irValue[i]);
      }
      Serial.println(" ");
    }

  }
}