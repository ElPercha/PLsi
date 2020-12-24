#include <globals.h>
#include <plsi.h>
#include <tskDisk.h>
#include <disk.h>
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

    delay(5);
 }
}