#include <globals.h>
#include <plsi.h>
#include <tskDisk.h>
#include <disk.h>
#include "FS.h"
#include "SD.h"
#include "SPIFFS.h"

//--------------------------------------------------------------------------------
// Disk Task 
// Controls SPIFSS memory and SD Card files
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskDisk(void *pvParameters)
{
  (void) pvParameters;

  //------------------------------------------------------
  // Regular boot:
  //   Load saved settings and defined User program Slot
  // First boot:
  //   Load default settings and demo User program 
  //------------------------------------------------------
  
    loadDisk();         
    loadSettings();

  //----------------------------------------------------
  // Task Main loop 
  //----------------------------------------------------

  while(1){
    Serial.println  ("TskDisk - running.");
    delay(4000);
  }
}