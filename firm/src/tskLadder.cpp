#include <globals.h>
#include <tskLadder.h>
#include <ladder.h>

void TaskLadder(void *pvParameters)
{
  (void) pvParameters;
  
  Network Networks[TOTAL_NETWORKS];

  waitSettings();
  configureLocal_IO();
  clearMemory();
  clearProgram(Networks);
  
  //loadUserProgram();
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
