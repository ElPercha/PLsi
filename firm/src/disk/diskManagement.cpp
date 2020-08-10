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
    Serial.println("TaskDisk - Mount SPIFFS failed. Will retry with FormatOnFail = true ...");
    unsigned long StartTime = micros();
    if (SPIFFS.begin(true)){
      unsigned long CurrentTime = micros();
      Serial.println("TaskDisk - Disk formatted because regular mount failed.");
      Serial.println("TaskDisk - If it is the first boot, this is not a problem.");
      Serial.println("TaskDisk - If it is not the first boot, try reloading the whole firmware including partition table.");
      Serial.print  ("TaskDisk - Time taken to Format 1Mb: ");
      Serial.println(CurrentTime - StartTime);
      bootSequence = BOOT_DISK_LOADED;
    }
    else{
      Serial.print  ("TaskDisk - SPIFSS Format Failed - System error or Partition file issue. Try reloading the whole firmware including partition table.");
      PLCstate = PLCERROR_SPIFFS_FORMAT_ERROR;
      bootSequence = BOOT_DISK_ERROR;
    } 
  }
  else{
    Serial.println("TaskDisk - SPIFFS Disk successfully mounted");
    bootSequence = BOOT_DISK_LOADED;
  }
}

//--------------------------------------------------------------------------------
// Load user settings at boot
//--------------------------------------------------------------------------------

void loadSettings(void){
  if(bootSequence == BOOT_DISK_LOADED){
    if (SPIFFS.exists(PATH_SETTINGS)){
      Serial.println("TaskDisk - File settings.bin exists. Loading settings from disk");    
      File settingsFile = SPIFFS.open(PATH_SETTINGS,"r+");
        if (settingsFile.size() == sizeof(settings)){
          Serial.println("TaskDisk - File settings.bin exists with same size. Settings to be loaded from Disk...");    
          settingsFile.read((uint8_t *)&settings, sizeof(settings));
          settingsFile.close();
        }
        else{
          Serial.println("TaskDisk - File settings.bin exists but has different size. Loading default settings...");    
          loadDefaultSettings();
        }
    }
    else{
      Serial.println("TaskDisk - File settings.bin does not exist. Creating file and loading default settings...");    
      loadDefaultSettings();
    }
  }
  bootSequence = BOOT_SETTINGS_LOADED;
}

//--------------------------------------------------------------------------------
// Load user default settings at first boot.
// Creates "Settings.PLsi" file
// Loads the default settings on his structure
//--------------------------------------------------------------------------------

void loadDefaultSettings(void){
  settings.general.firstRun = 0;
  settings.general.baudRate = BAUD_RATE;
  settings.general.verbosityLevel = 0;
  settings.general.value2 = 0;

  settings.ladder.NetworksQuantity = TOTAL_NETWORKS;
  settings.ladder.PLCbootState = STOPPED;
  settings.ladder.value2 = 0;

  snprintf(settings.wifi.ssid, SSID_LENGTH, WIFI_SSID);
  snprintf(settings.wifi.password, PASS_LENGTH, WIFI_PASS);

  File settingsFile = SPIFFS.open(PATH_SETTINGS,"w");
  settingsFile.write((uint8_t *)&settings, sizeof(settings));
  settingsFile.close();
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
  PLCstate = STOPPED;


  //bootSequence = 1000;
  // if(!fileexist){loadDemoProgram()}
  loadDemoProgram();





  PLCstate = RUNNING;
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

