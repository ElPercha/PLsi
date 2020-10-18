#include <globals.h>
#include <plsi.h>
#include <tskDisk.h>
#include <disk.h>

#include <TFT_eSPI.h> // Lucas borrar
#include <hmi.h> // Lucas borrar

#include "FS.h"
#include "SD.h"
#include "FFat.h"

//--------------------------------------------------------------------------------
// Disk Task 
// Controls SPIFSS memory and SD Card files
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskDisk(void *pvParameters)
{
  (void) pvParameters;

  //------------------------------------------------------
  // Regular boot: Mount FFAT Disk
  // First boot: Format FFAT disk
  //------------------------------------------------------
  
  loadDisk();         

  //------------------------------------------------------
  // Regular boot: Load saved settings from FFAT Disk
  // First boot: Load default settings and Save to Disk
  //------------------------------------------------------

  loadSettings();
  
  //------------------------------------------------------
  // Clear auxiliary networks and Unlock tasks
  //------------------------------------------------------

  clearEmptyNetwork();

//----------------------------------------------------
  // Task Main loop 
  //----------------------------------------------------

  while(1){

    //----------------------------------------------------
    // Update Newtork currently in edition mode to disk
    //----------------------------------------------------

    if(updateSelectedProgramDisk){
      FFat.begin(false,"/ffat",1);
      File userProgramFile = FFat.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"r+");
      userProgramFile.seek(showingNetwork * sizeof(onlineNetwork));
      userProgramFile.write((uint8_t *)&onlineNetwork, sizeof(onlineNetwork));
      userProgramFile.close();
      FFat.end();
      updateSelectedProgramDisk = 0;
    }















    //----------------------------------------------------
    // LUCAS TESTING FUNCTIONS
    //----------------------------------------------------

    if (I[0]){
      FFat.begin(false,"/ffat",1);
      File root = FFat.open("/");
      File file = root.openNextFile();
      while(file){
        Serial.print("FILE: ");
        Serial.print(file.name());
        Serial.print("       SIZE: ");
        Serial.println(file.size());
        file = root.openNextFile();
      }

      FFat.end();

      settings.ladder.PLCstate = PLCERROR_FFAT_FORMAT_ERROR;
      
      delay(4000);
    }

    if (I[1]){
        FFat.begin(false,"/ffat",1);
        Serial.print("Info FFAT Total Bytes: ");
        Serial.println(FFat.totalBytes());
        Serial.print("Info FFAT Free Bytes: ");
        Serial.println(FFat.freeBytes());
        FFat.end();
      delay(2000);
    }
    
    if (I[2]){
        Serial.println("Formatting FFAT...");
        FFat.format();
        FFat.begin(false,"/ffat",1);
        Serial.print("Info FFAT Total Bytes: ");
        Serial.println(FFat.totalBytes());
        Serial.print("Info FFAT Used Bytes: ");
        Serial.println(FFat.freeBytes());
        FFat.end();
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