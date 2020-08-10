#include <globals.h>
#include <tskLadder.h>
#include <ladder.h>

#include "disk.h"
#include "FS.h"
#include "SD.h"
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
  clearMemory();
  clearProgram(Networks); //not really needed  lcuas to delete

  DebugCreateNetworks(Networks); // Lucas to delete

  //--------------------------------------------------
  // Task Main Loop
  //--------------------------------------------------

  while(1){
    
    //------------------------------------------------------
    // Regular boot:
    //   Load saved program indicated in Settings
    // First boot:
    //   Load demo User program and create empty slots files
    //------------------------------------------------------
    
    if(loadSelectedProgram){
      loadUserProgram();
      loadSelectedProgram = 0;
    }

    //------------------------------------------------------
    // PLC ladder and I/O evaluation
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
