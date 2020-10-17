#include <globals.h>
#include <main.h>



#include <tskDisk.h>
#include <disk.h>

#include "FS.h"
#include "SD.h"
#include "FFat.h"

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
    ,  80000  // Networks structure size is 76000 leaving 4K free
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