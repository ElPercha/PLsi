#include <globals.h>
#include <main.h>

void setup() {

//--------------------------------------------------------------------------------
// Serial Console 
//--------------------------------------------------------------------------------

  Serial.begin(BAUD_RATE);

//--------------------------------------------------------------------------------
// RTOS tasks configuration and setup
//--------------------------------------------------------------------------------
  
  xTaskCreatePinnedToCore(
    TaskHMI
    ,  "HMI display"
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
    ,  0
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore( 
    TaskLadder
    ,  "Ladder Logic"
    ,  110000
    ,  NULL
    ,  3
    ,  NULL 
    ,  1);
}

void loop() {
    delay(1000);
}