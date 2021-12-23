#include <Arduino.h>

#define ledPin GPIO_NUM_4  

void setup() {

  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}


void loop() {

  digitalWrite(ledPin, 1);
  int out = digitalRead(ledPin);
  Serial.println("LED Status: " + String(out));
  delay(1000);

  digitalWrite(ledPin, 0);
  out = digitalRead(ledPin);
  Serial.println("LED Status: " + String(out));
  delay(1000);
}