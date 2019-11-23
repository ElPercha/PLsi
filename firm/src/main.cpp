#include <Arduino.h>
#include <main.h>

void setup() {
  Serial.begin(115200);

  // RTOS Tasks configuration:
  xTaskCreatePinnedToCore(
    TaskHMI
    ,  "HMIDisplay"
    ,  4096   // Stack size up to 113000
    ,  NULL
    ,  3      // Priority 3=highest 0=lowest
    ,  NULL 
    ,  0);    // Processor Core 
  
  xTaskCreatePinnedToCore(
    TaskDisk
    ,  "Disk management"
    ,  4096 
    ,  NULL
    ,  1
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore( 
    TaskLadder
    ,  "LadderLogic"
    ,  110000
    ,  NULL
    ,  3
    ,  NULL 
    ,  1);
}

void loop() {
    delay(1000);
}