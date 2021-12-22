#include <Arduino.h>

#define SerialDebug  false

#define PRO_CPU 0
#define APP_CPU 1

static const int pinBlueLED = GPIO_NUM_4;

void taskToggleBlueLED(void *pvParameter) {

  portTickType delay = *(portTickType*)pvParameter;

  while(1) {
    digitalWrite(pinBlueLED, HIGH);
    vTaskDelay(delay/portTICK_PERIOD_MS);
    digitalWrite(pinBlueLED, LOW);
    vTaskDelay(delay/portTICK_PERIOD_MS);
  }
}

//////////////////////////////////////////////////////
// First comment below, then uncomment


void taskToggleBlueLED2(void *pvParameter) {

  portTickType delay = *(portTickType*)pvParameter;

  digitalWrite(pinBlueLED, LOW);
  vTaskDelay(delay/portTICK_PERIOD_MS);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(pinBlueLED, OUTPUT);
  int32_t timeDelay = 500;
  TaskHandle_t taskHandle;


  //////////////////////////////////////////////////////
  // First comment below, then uncomment

  int32_t timeDelay2 = 323;
  TaskHandle_t taskHandle2;

  xTaskCreatePinnedToCore(          // Use xTaskCreate() in vanilla FreeRTOS
              taskToggleBlueLED,    // Function to be called
              "Toggle BLUE LED",    // Name of task
              1024,                 // Stack size (bytes in ESP32, words in FreeRTOS)
              (void*)&timeDelay,         // Parameter to pass to function
              uxTaskPriorityGet(NULL),   // Task priority (0 to configMAX_PRIORITIES - 1)
              &taskHandle,         // Task handle
              PRO_CPU);     // core No.


  //////////////////////////////////////////////////////
  // First comment below, then uncomment

  xTaskCreatePinnedToCore(taskToggleBlueLED2,
                          "Toggle Blue LED2", 
                          1024, 
                          (void*)&timeDelay2, 
                          uxTaskPriorityGet(NULL), 
                          &taskHandle, 
                          APP_CPU);   // change to PRO_CPU. What will happen?

  Serial.println("taskHandle ID: " + String(uxTaskPriorityGet(taskHandle)));

  //////////////////////////////////////////////////////
  // First comment below, then uncomment

  Serial.println("taskHandle2 ID: " + String(uxTaskPriorityGet(taskHandle2)));
}

void loop() {
  // DO nothing
}