/** 1. No connection between VL53Lx XSHUT pin and iFZero GPIO.
 *  2. Modify existing constructor.
 *  3. Use software_reset() and comment VL53LX_Off() and VL53LX_On().
 *  4. Make a wrapper class.
 *  5. Full tutorial at http://indifrog.com/2021/03/08/iFBalance-%E1%84%80%E1%85%A2%E1%84%87%E1%85%A1%E1%86%AF%E1%84%80%E1%85%A1%E1%86%BC%E1%84%8C%E1%85%AA_08/
**/ 

#include <Arduino.h>
#include "iFVL53LX.h"

#define SerialDebug   false  // Set to true to get Serial output for debugging
#define I2Cclock      400000

iFVL53LX ifVL53LX;

void setup() {
  Serial.begin(115200);
  
  Wire.begin(21, 22, I2Cclock);

  ifVL53LX.init();
}

void loop() {
  uint32_t distance = 0;
  ifVL53LX.calcDistance();
  distance = ifVL53LX.getDistance();

  Serial.println("Distance: " + String(distance) + " mm");
  delay(1000);
}