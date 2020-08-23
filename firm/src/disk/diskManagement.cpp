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
  SPIFFS.end();
}

//--------------------------------------------------------------------------------
// Load user settings at boot
//--------------------------------------------------------------------------------

void loadSettings(void){
  if(bootSequence == BOOT_DISK_LOADED){
    SPIFFS.begin();
    if (SPIFFS.exists(FILENAME_SETTINGS)){
      Serial.println("TaskDisk - File settings.bin exists.");    
      File settingsFile = SPIFFS.open(FILENAME_SETTINGS,"r");
        if (settingsFile.size() == sizeof(settings)){
          Serial.println("TaskDisk - File settings.bin exists with same size. Settings to be loaded from Disk...");    
          settingsFile.read((uint8_t *)&settings, sizeof(settings));
          settingsFile.close();
          SPIFFS.end();
        }
        else{
          Serial.println("TaskDisk - File settings.bin exists but has different size. Loading default settings...");    
          settingsFile.close();
          SPIFFS.end();
          loadDefaultSettings();
        }
    }
    else{
      Serial.println("TaskDisk - File settings.bin does not exist. Creating file and loading default settings...");    
      SPIFFS.end();
      loadDefaultSettings();
    }
  }
  bootSequence = BOOT_TASK_UNLOCKED;
}

//--------------------------------------------------------------------------------
// Load user default settings at first boot.
// Creates "Settings.PLsi" file
// Loads the default settings on his structure
//--------------------------------------------------------------------------------

void loadDefaultSettings(void){
  settings.general.firstRun = 0;
  settings.general.verbosityLevel = 0;

  settings.ladder.NetworksQuantity = TOTAL_NETWORKS;
  settings.ladder.PLCbootState = STOPPED;
  settings.ladder.UserProgram = DEMO_PROGRAM_SLOT;

  settings.hmi.ts.leftX = TS_LEFT_X;
  settings.hmi.ts.rightX = TS_RIGHT_X;
  settings.hmi.ts.topY = TS_TOP_Y;
  settings.hmi.ts.bottomY = TS_BOTTOM_Y;

  snprintf(settings.wifi.ssid, SSID_LENGTH, WIFI_SSID);
  snprintf(settings.wifi.password, PASS_LENGTH, WIFI_PASS);

  saveSettings();
} 

//--------------------------------------------------------------------------------
// Save user settings to non volatile memory Disk (SPIFFS)
//--------------------------------------------------------------------------------

void saveSettings(void){
  SPIFFS.begin();
  File settingsFile = SPIFFS.open(FILENAME_SETTINGS,"w");
  settingsFile.write((uint8_t *)&settings, sizeof(settings));
  settingsFile.close();
  SPIFFS.end();
}
