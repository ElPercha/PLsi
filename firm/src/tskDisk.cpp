#include <globals.h>
#include <plsi.h>
#include <tskDisk.h>
#include <disk.h>
#include "FS.h"
#include "SD.h"
#include "FFat.h"

#include <TFT_eSPI.h> //lucas to delete
#include "hmi.h" //lucas to delete

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

    if (I[0] && I[1] && I[2]){
        Serial.println("Formatting FFAT...");
        FFat.format();
        FFat.begin(false,"/ffat",1);
        Serial.print("Info FFAT Total Bytes: ");
        Serial.println(FFat.totalBytes());
        Serial.print("Info FFAT Used Bytes: ");
        Serial.println(FFat.freeBytes());
        FFat.end();
      delay(1000);
    }

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
      delay(1000);
    }

    if (I[1]){
        FFat.begin(false,"/ffat",1);
        Serial.print("Info FFAT Total Bytes: ");
        Serial.println(FFat.totalBytes());
        Serial.print("Info FFAT Free Bytes: ");
        Serial.println(FFat.freeBytes());
        FFat.end();

        Serial.print("   - Free ESP Miniumn memory ever available: ");
        Serial.println (esp_get_minimum_free_heap_size());
        Serial.print("   - Free ESP memory xPort: ");
        Serial.println(xPortGetFreeHeapSize());
      delay(1000);
    }
    
    if (I[2]){

      delay(1000);
    }

    if (I[3]){

      delay(1000);
    }

    if (I[4]){
      
      textValue = "2203Alden";     
      HMI_PageMemory =  HMI_Page;        
      HMI_Page = PAGE_Keyboard;        

      delay(1000);
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