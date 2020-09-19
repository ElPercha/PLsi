#include <globals.h>
#include <tskLadder.h>
#include <ladder.h>
//#include <disk.h>

#include "FS.h"
#include "SPIFFS.h"

//--------------------------------------------------------------------------------
// Ladder logic execution Task 
// Running on Core 1 
//--------------------------------------------------------------------------------

void TaskLadder(void *pvParameters)
{
  (void) pvParameters;

  //----------------------------------------------------
  // Task lock / unlock
  //----------------------------------------------------

  ladderWaitSettings();
  
  //----------------------------------------------------
  // Ladder Logic initializations
  //----------------------------------------------------

  Network Networks[TOTAL_NETWORKS];

  configureLocal_IO();
  
  //--------------------------------------------------
  // Task Main Loop
  //--------------------------------------------------

  while(1){
    
    //----------------------------------------------------------------
    // Load saved program indicated in settings.ladder.UserProgram
    //    If file doesnt exist creates the empty file
    //    If User Proggram number is 0, load Demo to this slot
    //    this assumes that is the first boot
    //----------------------------------------------------------------
    
    if(loadSelectedProgram){
      //settings.ladder.PLCstate = STOPPED;
      SPIFFS.begin();

      if (SPIFFS.exists(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram])){
        Serial.print("TaskLadder - File ");
        Serial.print(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram]);
        Serial.println(" exists. Will be loaded to RAM");

        File userProgramFile = SPIFFS.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"r");
        userProgramFile.read((uint8_t *)&Networks, sizeof(Networks));
        userProgramFile.close();
      }
      else{
        Serial.print("TaskLadder - File ");
        Serial.print(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram]);
        Serial.println(" does not exists. Program file is going to be created");

        clearProgram(Networks);      
        if(settings.ladder.UserProgram == DEMO_PROGRAM_SLOT){
          loadDemoUserPogram(Networks);
        }
        File userProgramFile = SPIFFS.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"w");
        userProgramFile.write((uint8_t *)&Networks, sizeof(Networks));
        userProgramFile.close();
      }
   
      SPIFFS.end();
      clearMemory();
      //settings.ladder.PLCstate = RUNNING;
      loadSelectedProgram = 0;
    }

    //----------------------------------------------------------------
    // Update RAM Networks image with DiskLoad saved program indicated in settings.ladder.UserProgram
    //    If file doesnt exist creates the empty file
    //    If User Proggram number is 0, load Demo to this slot
    //    this assumes that is the first boot
    //----------------------------------------------------------------

    if(updateSelectedProgramRAM){
      Serial.print("Task Ladder - Network ");
      Serial.print(showingNetwork);
      Serial.println(" saved to RAM");

      Networks[showingNetwork] = onlineNetwork;
      updateSelectedProgramRAM = 0;
    }

    //------------------------------------------------------
    // PLC ladder Program SCAN
    //     Read Inputs
    //     Evaluate Logic
    //     Write Outputs
    //------------------------------------------------------

    scanTime();
    
    readInputsLocal();
    readInputsRemote();

    execScanPLC(Networks); 
    savePreviousValues();

    writeOutputsLocal();
    writeOutputsRemote();
  }
}
