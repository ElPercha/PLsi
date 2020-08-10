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
  // Regular boot: Mount SPIFFS Disk
  // First boot: Format disk (SPIFFS)
  //------------------------------------------------------

  loadDisk();         

  //------------------------------------------------------
  // Regular boot: Load saved settings from SPIFFS Disk
  // First boot: Load default settings and Save to Disk
  //------------------------------------------------------

  loadSettings();
    
  //----------------------------------------------------
  // Override default setting of Serial console speed
  //----------------------------------------------------
  
  serialPortInit();

  //----------------------------------------------------
  // Task Main loop 
  //----------------------------------------------------

  while(1){
    Serial.println  ("TaskDisk - running.");
    delay(4000);

    
    if (I[1]){ // Lucas delete
        Serial.print("Info SPIFFS Total Bytes: ");
        Serial.println(SPIFFS.totalBytes());
        Serial.print("Info SPIFFS Used Bytes: ");
        Serial.println(SPIFFS.usedBytes());
      delay(2000);
    }
    
    if (I[2]){
        Serial.println("Formatting SPIFFS...");
        SPIFFS.end();
        SPIFFS.format();
        SPIFFS.begin();
        Serial.print("Info SPIFFS Total Bytes: ");
        Serial.println(SPIFFS.totalBytes());
        Serial.print("Info SPIFFS Used Bytes: ");
        Serial.println(SPIFFS.usedBytes());
      delay(4000);
    }

  }
}