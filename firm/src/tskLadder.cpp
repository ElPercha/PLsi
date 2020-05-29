#include <globals.h>
#include <tskLadder.h>
#include <ladder.h>

//--------------------------------------------------------------------------------
// Ladder logic execution Task 
// Running on Core 1 
//--------------------------------------------------------------------------------

void TaskLadder(void *pvParameters)
{
  (void) pvParameters;
  
  Network Networks[TOTAL_NETWORKS];

  configureLocal_IO();
  clearMemory();
  clearProgram(Networks); //not really needed 

  waitSettings();      
  waitUserProgram();
  DebugCreateNetworks(Networks);

  while(1){
    scanTime();
    
    readInputsLocal();
    readInputsRemote();

    execScanPLC(Networks); 
    savePreviousValues();

    writeOutputsLocal();
    writeOutputsRemote();
  }
}
