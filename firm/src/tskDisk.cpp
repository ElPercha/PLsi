#include <globals.h>
#include <plsi.h>
#include <tskDisk.h>
#include <disk.h>

#include <TFT_eSPI.h> // Lucas borrar
#include <hmi.h> // Lucas borrar

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
  

  clearEmptyNetwork();
  
  //----------------------------------------------------
  // Task Main loop 
  //----------------------------------------------------

  while(1){

    //----------------------------------------------------
    // Update Newtork currently in edition mode to disk
    //----------------------------------------------------

    if(updateSelectedProgramDisk){
      SPIFFS.begin();
      File userProgramFile = SPIFFS.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"r+");
      userProgramFile.seek(showingNetwork * sizeof(onlineNetwork));
      userProgramFile.write((uint8_t *)&onlineNetwork, sizeof(onlineNetwork));
      userProgramFile.close();
      SPIFFS.end();
      updateSelectedProgramDisk = 0;
    }















    //----------------------------------------------------
    // LUCAS TESTING FUNCTIONS
    //----------------------------------------------------

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

      settings.ladder.PLCstate = PLCERROR_SPIFFS_FORMAT_ERROR;
      
      delay(4000);
    }

    if (I[1]){
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

    if (I[4] && editionMode){
      onlineNetwork.Cells[0][0].Data++;

      if(showingNetwork == 499){
        onlineNetwork.Cells[0][0].Code = 3;
        onlineNetwork.Cells[0][0].Data = 2999;
        onlineNetwork.Cells[0][0].Type = 0;

        onlineNetwork.Cells[4][5].Code = 7;
        onlineNetwork.Cells[4][5].Data = 1999;
        onlineNetwork.Cells[4][5].Type = 0;
      }    
      Serial.println("TaskDisk - Program changed to test edition: ");
    }

    if(I[5]){


      delay(1000);
    }


    //----------------------------------------------------
    // LUCAS TESTING FUNCTIONS END
    //----------------------------------------------------






    delay(5);
 }
}