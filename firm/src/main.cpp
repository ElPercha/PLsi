#include <Arduino.h>
#include <main.h>

void setup() {
  Serial.begin(115200);

  // RTOS Tasks configuration:
  xTaskCreatePinnedToCore(
    TaskHMI
    ,  "HMIDisplay"
    ,  4096   // Stack size
    ,  NULL
    ,  3      // Priority 3=highest 0=lowest
    ,  NULL 
    ,  0);    // Processor Core 
  
  xTaskCreatePinnedToCore(
    TaskWeb
    ,  "WebServer"
    ,  100000 // up to 113000
    ,  NULL
    ,  1
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore(
    TaskLadder
    ,  "LadderLogic"
    ,  8196
    ,  NULL
    ,  3
    ,  NULL 
    ,  1);
}

void loop() {
    delay(1000);
}