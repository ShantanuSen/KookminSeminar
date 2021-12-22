#include <Arduino.h>

#include "iFLED.h"
#include "iFMotors.h"
#include "iFEncoder.h"
#include "MPU9250.h"

#define SerialDebug   false  // Set to true to get Serial output for debugging
#define I2Cclock      400000
#define MPU_INT_PIN   5 // Interrupt Pin definitions


iFLED ifLed; 
iFMotors ifMotors; 
iFEncoder ifEncoder; 

MPU9250 mpu;

long  _nCurTime, _nPrevTime;
int   _nLoopTime;

void setup()
{ 
  // serial monitor speed change to 115200
  Serial.begin( 115200 );

  Wire.begin(21, 22, I2Cclock);

  ///////////////////////////////////////////////////////
  // MPU 9250
  
  mpu.selectFilter( QuatFilterSel::MADGWICK);
  mpu.setup(0x68);  // change to your own address
  delay(2000);      // to get stable data of MPU9250

  ///////////////////////////////////////////////////////
  // Color LED

  ifLed.init();  
  ifLed.setMode( BLINK );

  ///////////////////////////////////////////////////////
  // Motor
  ifMotors.init();

  ///////////////////////////////////////////////////////
  // Encoder
  ifEncoder.init(25, 14, 13, 15);

  _nCurTime = _nPrevTime = millis();
}

void loop() {
  _nCurTime = millis();
  _nLoopTime = _nCurTime - _nPrevTime;    

  if( _nLoopTime < 5) return;

  if (mpu.update()) {
    
    //////////////////////////////////////////
    // Roll, Pitch, Yaw

    // Serial.println("P = " + String(mpu.getPitch()) + " R = " + String(mpu.getRoll()) + 
    //                " Y = " + String(mpu.getYaw()) + " T = " + String(_nLoopTime) );
    // Serial.println();
    

    //////////////////////////////////////////
    // X-axis aceel, Y-axis aceel, Z-axis aceel

    // Serial.println("ax = " + String(mpu.getAccX()) + "g," + 
    //               " ay = " + String(mpu.getAccY()) + "g," +
    //               " az = " + String(mpu.getAccZ()) + "g," +
    //               " T = " + String(_nLoopTime) );
    // Serial.println();



    //////////////////////////////////////////
    // X-axis gyro, Y-axis gyro, Z-axis gyro

    Serial.println("gx = " + String(mpu.getGyroX()) + "deg/sec," + 
                  " gy = " + String(mpu.getGyroY()) + "deg/sec," +
                  " gz = " + String(mpu.getGyroZ()) + "deg/sec," +
                  " T = " + String(_nLoopTime) );
    Serial.println();


    //////////////////////////////////////////
    // X-axis magneto, Y-axis magneto, Z-axis magneto

    // Serial.println("mx = " + String(mpu.getMagX()) + "uT," + 
    //               " my = " + String(mpu.getMagY()) + "uT," +
    //               " mz = " + String(mpu.getMagZ()) + "uT," +
    //               " T = " + String(_nLoopTime));
    // Serial.println();


    _nPrevTime = _nCurTime; 
  } 
}