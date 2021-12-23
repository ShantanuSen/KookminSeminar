#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "iFEncoder.h"

int8_t iFEncoder :: m_nLeA = GPIO_NUM_13; 
int8_t iFEncoder :: m_nLeB = GPIO_NUM_15; 
int8_t iFEncoder :: m_nReA = GPIO_NUM_25; 
int8_t iFEncoder :: m_nReB = GPIO_NUM_14;

volatile bool iFEncoder::lastLeftA = false;
volatile bool iFEncoder::lastLeftB = false;
volatile bool iFEncoder::lastRightA = false;
volatile bool iFEncoder::lastRightB = false;

volatile bool iFEncoder::errorLeft = false;
volatile bool iFEncoder::errorRight = false;

volatile int32_t iFEncoder::countRight = 0;
volatile int32_t iFEncoder::lastCountR = 0;
volatile int32_t iFEncoder::countLeft = 0;
volatile int32_t iFEncoder::lastCountL = 0;

portMUX_TYPE iFEncoder::muxl = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE iFEncoder::muxr = portMUX_INITIALIZER_UNLOCKED;

int32_t iFEncoder::prevSpeed = 0;

void IRAM_ATTR iFEncoder::leftISR()
{
    bool newLeftB, newLeftA;

    portENTER_CRITICAL (& muxl); 
    newLeftB = digitalRead (m_nLeB); 
    newLeftA = digitalRead (m_nLeA); // ^ lastLeftB;

    countLeft += (lastLeftA ^ newLeftB) - (newLeftA ^ lastLeftB);

    if ((lastLeftA ^ newLeftA) & (lastLeftB ^ newLeftB)) {
        errorLeft = true;
    }

    lastLeftA = newLeftA;
    lastLeftB = newLeftB;

    portEXIT_CRITICAL(&muxl);
}

void IRAM_ATTR iFEncoder::rightISR()
{
    bool newRightB, newRightA;

    portENTER_CRITICAL(&muxr);
    newRightB = digitalRead(m_nReB);
    newRightA = digitalRead(m_nReA);// ^ lastRightB;

    countRight += (newRightA ^ lastRightB) - (lastRightA ^ newRightB); // countRight + = (lastRightA ^ newRightB) - (newRightA ^ lastRightB); if ((lastRightA ^ newRightA) & (lastRightB ^ newRightB)) {         errorRight = true ;     }     lastRightA = newRightA;     lastRightB = newRightB;
  
    





    portEXIT_CRITICAL(&muxr);
}

void iFEncoder::taskSpeedNotification(void *pvParameters)
{
  uint32_t speed;
  for (;;)
  {  
    speed = (abs(getCountLeftReset()) + abs(getCountRightReset())) / 2;
    // Serial.print("speed: ");
    // Serial.println(String(speed));
    prevSpeed = speed;
    delay(1000);
  }
}


void iFEncoder::init(int8_t leA, int8_t leB, int8_t reA, int8_t reB)
{ 
    m_nLeA = leA; 
    m_nLeB = leB; 
    m_nReA = reA; 
    m_nReB = reB;

    pinMode(m_nLeA, INPUT_PULLDOWN);
    pinMode(m_nLeB, INPUT_PULLDOWN);
    pinMode(m_nReA, INPUT_PULLDOWN);
    pinMode(m_nReB, INPUT_PULLDOWN);

    attachInterrupt(m_nLeA, leftISR, CHANGE);
    attachInterrupt(m_nLeB, leftISR, CHANGE);
    attachInterrupt(m_nReA, rightISR, CHANGE);
    attachInterrupt(m_nReB, rightISR, CHANGE);

    xTaskCreatePinnedToCore( taskSpeedNotification, "taskSpeedNotification", 
            2048, 
            NULL, 
            uxTaskPriorityGet(NULL), 
            NULL, 
            0);
}

int32_t iFEncoder::getCountLeft() {
    int32_t c = countLeft;
    return c;
}

int32_t iFEncoder::getCountRight() {
    int32_t c = countRight;
    return c;
}

void iFEncoder::resetCountLeft(){
  portENTER_CRITICAL(&muxl);
    countLeft = 0;
  portEXIT_CRITICAL(&muxl);
}
void iFEncoder::resetCountRight(){
  portENTER_CRITICAL(&muxr);
    countRight = 0;
  portEXIT_CRITICAL(&muxr);
}

int32_t iFEncoder::getCountLeftReset(){
  portENTER_CRITICAL(&muxl);
    int32_t c = countLeft;
    countLeft = 0;
  portEXIT_CRITICAL(&muxl);
  return c;
}

int32_t iFEncoder::getCountRightReset(){
  portENTER_CRITICAL(&muxr);
    int32_t c = countRight;  
    countRight = 0;
  portEXIT_CRITICAL(&muxr);
  return c;  
}

void iFEncoder::resetCounts(){
    resetCountLeft();
    resetCountRight();
}