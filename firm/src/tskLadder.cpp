#include <globals.h>
#include <tskLadder.h>
#include <ladder.h>
#include "FS.h"
#include "FFat.h"

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
      FFat.begin(false,"/ffat",1);

      if (FFat.exists(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram])){
        Serial.print("TaskLadder - File ");
        Serial.print(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram]);
        Serial.println(" exists. Will be loaded to RAM");

        File userProgramFile = FFat.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"r");
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
        File userProgramFile = FFat.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"w");
        userProgramFile.write((uint8_t *)&Networks, sizeof(Networks));
        userProgramFile.close();
      }
   
      FFat.end();
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

    //----------------------------------------------------------------
    // Shift All networks down on RAM and SPIFSS
    // Creates an empty Network in the selected Network by shifting the rest up (number)
    // The last network has to be checked empty before enable this code
    // 1 - Performs the RAM shift in one scan (all required networks)
    // 2 - Delete showingNetwork Network because it gets duplicated
    // 3 - Save the complete program to SPIFSS
    //----------------------------------------------------------------

    if (moveNetworksInsert > 0){
      uint16_t startNetwork = moveNetworksInsert - 1;

      for (uint16_t net = settings.ladder.NetworksQuantity-1; net > startNetwork; net--){
        Networks[net] = Networks[net-1];
      }
      Networks[startNetwork] = emptyNetwork;

      FFat.begin(false,"/ffat",1);
      File userProgramFile = FFat.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"w");
      size_t StatusWrite = userProgramFile.write((uint8_t *)&Networks, sizeof(Networks));
      userProgramFile.close();

      Serial.print("   - Status of File Write operation for INSERT: ");
      Serial.println(StatusWrite);
      Serial.print("   - Info FFAT Total Bytes: ");
      Serial.println(FFat.totalBytes());
      Serial.print("   - Info FFAT Free Bytes: ");
      Serial.println(FFat.freeBytes());
      
      FFat.end();

      moveNetworksInsert = 0;
    }

    //----------------------------------------------------------------
    // Shift All networks up on RAM and SPIFSS
    // Delete the current selected Network and shift the rest down (number)
    // 1 - Performs the RAM shift in one scan (all required networks)
    // 2 - Delete last Network because it gets duplicated
    // 3 - Save the complete program to SPIFSS
    //----------------------------------------------------------------

    if(moveNetworksDelete > 0){
      uint16_t startNetwork = moveNetworksDelete - 1;

      for (uint16_t net = startNetwork; net < settings.ladder.NetworksQuantity-1; net++){
        Networks[net] = Networks[net+1];
      }
      Networks[settings.ladder.NetworksQuantity-1] = emptyNetwork;
      editingNetwork = Networks[startNetwork]; // It is already shifted

      FFat.begin(false,"/ffat",1);
      File userProgramFile = FFat.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"w");
      size_t StatusWrite = userProgramFile.write((uint8_t *)&Networks, sizeof(Networks));
      userProgramFile.close();

      Serial.print("   - Status of File Write operation for DELETE: ");
      Serial.println(StatusWrite);
      Serial.print("   - Info FFAT Total Bytes: ");
      Serial.println(FFat.totalBytes());
      Serial.print("   - Info FFAT Free Bytes: ");
      Serial.println(FFat.freeBytes());

      FFat.end();

      moveNetworksDelete = 0;
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
