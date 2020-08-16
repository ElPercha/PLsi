#include <globals.h>
#include <main.h>

//--------------------------------------------------------------------------------
// Standard Arduino setup
//--------------------------------------------------------------------------------

void setup() {

//--------------------------------------------------------------------------------
// Serial Console initialization
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
    ,  2      // Priority 3=highest 0=lowest
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
    TaskWiFi
    ,  "WiFi communications"
    ,  4096 
    ,  NULL
    ,  1
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore( 
    TaskLadder
    ,  "Ladder Logic"
    ,  110000  // Networks structure size is 95000 leaving 15K for the rest
    ,  NULL
    ,  3
    ,  NULL 
    ,  1);
}

//--------------------------------------------------------------------------------
// Standard Arduino loop not used
//--------------------------------------------------------------------------------

void loop() {
    delay(1000);
}