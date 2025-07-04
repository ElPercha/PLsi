// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <main.h>

//--------------------------------------------------------------------------------
// Standard setup
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
    ,  1);    // Ladders Logic runs on Core 1
}

//--------------------------------------------------------------------------------
// Standard loop not used
//--------------------------------------------------------------------------------

void loop() {
    delay(1000);
}
