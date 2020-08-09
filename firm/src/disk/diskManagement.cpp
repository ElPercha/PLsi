#include <globals.h>
#include <plsi.h>
#include <tskDisk.h>
#include <disk.h>
#include "FS.h"
#include "SD.h"
#include "SPIFFS.h"

//--------------------------------------------------------------------------------
// Mount Disk
//    If it is the first boot of PLC: Format SPIFSS memory
//    On fail: Send PLC to ERROR
//--------------------------------------------------------------------------------

void loadDisk (void) {
  if (!SPIFFS.begin()){
    Serial.println("TskDisk - Mount SPIFFS failed. Will retry with FormatOnFail = true ...");
    unsigned long StartTime = micros();
    if (SPIFFS.begin(true)){
      unsigned long CurrentTime = micros();
      Serial.println("TskDisk - Disk formatted because regular mount failed.");
      Serial.println("TskDisk - If it is the first boot, this is not a problem.");
      Serial.println("TskDisk - If it is not the first boot, try reloading the whole firmware including partition table.");
      Serial.print  ("TskDisk - Time taken to Format 1Mb: ");
      Serial.println(CurrentTime - StartTime);
      bootSequence = 1;
    }
    else{
      Serial.print  ("TskDisk - SPIFSS Format Failed - System error or Partition file issue. Try reloading the whole firmware including partition table.");
      PLCstate = PLCERROR_SPIFFS_FORMAT_ERROR;
      bootSequence = 0;
    } 
  }
  else{
    Serial.println("TskDisk - SPIFFS Disk successfully mounted");
    bootSequence = 1;
  }
}

//--------------------------------------------------------------------------------
// Load user settings at boot
//--------------------------------------------------------------------------------

void loadSettings(void){
  // if(bootSequence == 1){
  //   if(fileexist && filesize == struct size){





  //   }
  //   else{
  //     loadDefaultSettings();
  //   }
 // }
}

//--------------------------------------------------------------------------------
// Load user default settings at first boot.
// Creates "Settings.PLsi" file
// Loads the default settings on his structure
//--------------------------------------------------------------------------------

void loadDefaultSettings(void){

  
}

//--------------------------------------------------------------------------------
// Save user settings to non volatile memory Disk (SPIFFS)
//--------------------------------------------------------------------------------

void saveSettings(void){

 
}

//--------------------------------------------------------------------------------
// Load user program at boot.
// If program files are not created, create Demo program
//--------------------------------------------------------------------------------

void loadUserProgram (void) {
  delay(1000);
  //bootSequence = 1000;
  // if(!fileexist){loadDemoProgram()}
  loadDemoProgram();
}

//--------------------------------------------------------------------------------
// Fist boot
//    Create files *.PLsi for all program slots
//    Load Demo program
//--------------------------------------------------------------------------------

void loadDemoProgram (void) {
  delay(1000);
  //bootSequence = 1000;
}

