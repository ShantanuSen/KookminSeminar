#include <Arduino.h>


#define app_cpu   1

// Globals
static int shared_var = 0;
static SemaphoreHandle_t mutex;
TaskHandle_t  taskHandle;


//*****************************************************************************
// Tasks

// Increment shared variable (the wrong way)
void incTask(void *parameters) {

  int local_var;

  // Loop forever
  while (1) {

    // Take mutex prior to critical section
      // Critical section (poor demonstration of "shared_var++")

      local_var = shared_var;
      local_var++;
      vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
      shared_var = local_var;
      
      // Print out new shared variable
      // This is different than in the video--print shared_var inside the
      // critical section to avoid having it be changed by the other task.
      Serial.println(shared_var);
  
      // Give mutex after critical section
      xSemaphoreGive(mutex);
  }
}

// Increment shared variable (the right way)
// void incTask(void *parameters) {

//   int local_var;

//   // Loop forever
//   while (1) {

//     // Take mutex prior to critical section
//     if (xSemaphoreTake(mutex, 0) == pdTRUE) {

//       // Critical section (poor demonstration of "shared_var++")
//       local_var = shared_var;
//       local_var++;
//       vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
//       shared_var = local_var;
      
//       // Print out new shared variable
//       // This is different than in the video--print shared_var inside the
//       // critical section to avoid having it be changed by the other task.
//       Serial.println(shared_var);
  
//       // Give mutex after critical section
//       xSemaphoreGive(mutex);

//     } else {
//       // Do something else
//     }
//   }
// }

//*****************************************************************************
// Main (runs as its own task on core 1)

void setup() {
  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Race Condition Demo---");

  // Create mutex before starting tasks
  mutex = xSemaphoreCreateMutex();

  // Start task 1
  xTaskCreatePinnedToCore(incTask,
                          "Increment Task 1",
                          1024,
                          NULL,
                          uxTaskPriorityGet(taskHandle),
                          NULL,
                          app_cpu);

  // Start task 2
  xTaskCreatePinnedToCore(incTask,
                          "Increment Task 2",
                          1024,
                          NULL,
                          uxTaskPriorityGet(taskHandle),
                          NULL,
                          app_cpu);           
}

void loop() {
  // Execution should never get here
}