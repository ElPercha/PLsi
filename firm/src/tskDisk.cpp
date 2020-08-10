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
  // Disable WDT Core 0 for Task in Lock State
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
  // Task Main loop 
  //----------------------------------------------------

  while(1){
    //Serial.println("TaskDisk is alive");


    if (I[0]){
      SPIFFS.begin();
      File root = SPIFFS.open("/");
      File file = root.openNextFile();
      while(file){
        Serial.print("FILE: ");
        Serial.print(file.name());
        Serial.print("       SIZE: ");
        Serial.println(file.size());
        file = root.openNextFile();
      }
      SPIFFS.end();
      delay(4000);
    }

    if (I[1]){ // Lucas delete
        SPIFFS.begin();
        Serial.print("Info SPIFFS Total Bytes: ");
        Serial.println(SPIFFS.totalBytes());
        Serial.print("Info SPIFFS Used Bytes: ");
        Serial.println(SPIFFS.usedBytes());
        SPIFFS.end();
      delay(2000);
    }
    
    if (I[2]){
        Serial.println("Formatting SPIFFS...");
        SPIFFS.begin();
        SPIFFS.format();
        SPIFFS.end();
        Serial.print("Info SPIFFS Total Bytes: ");
        Serial.println(SPIFFS.totalBytes());
        Serial.print("Info SPIFFS Used Bytes: ");
        Serial.println(SPIFFS.usedBytes());
      delay(4000);
    }

    if (I[3]){
      settings.ladder.UserProgram ++;
      if (settings.ladder.UserProgram > 7){
        settings.ladder.UserProgram = 0;
      }
      saveSettings();
      loadSelectedProgram = 1;
      delay(4000);
      Serial.print("Program changed to: ");
      Serial.println(settings.ladder.UserProgram);
    }








    delay(5);
 }
}