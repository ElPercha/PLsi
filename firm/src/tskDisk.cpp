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

  if (loadDisk()){         // Regular boot
    loadSettings();
    loadUserProgram();
  }
  else                     // First boot
  {
    loadDefaultSettings();
    loadDemoProgram();
  }

  
  while(1){
    Serial.println  ("TskDisk - running.");
    delay(4000);
  }
}