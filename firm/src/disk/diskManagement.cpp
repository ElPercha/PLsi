// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <plsi.h>
#include <tskDisk.h>
#include <disk.h>

#include "FS.h"
#include "SD.h"
#include "FFat.h"

//--------------------------------------------------------------------------------
// Mount Disk
//    If it is the first boot of PLC: Format SPIFSS memory
//    On fail: Send PLC to ERROR
//--------------------------------------------------------------------------------

void loadDisk (void) {
  if (!FFat.begin(false,"/ffat",1)){
    Serial.println("TaskDisk - Mount FFAT failed. Disk will be Formatted...");
    unsigned long StartTime = micros();
    if (FFat.begin(true,"/ffat",1)){
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
      settings.ladder.PLCstate = PLCERROR_FFAT_FORMAT_ERROR;
      bootSequence = BOOT_DISK_ERROR;
    } 
  }
  else{
    Serial.println("TaskDisk - FFAT Disk successfully mounted");
    bootSequence = BOOT_DISK_LOADED;
  }
  FFat.end();
}

//--------------------------------------------------------------------------------
// Load user settings at boot
//--------------------------------------------------------------------------------

void loadSettings(void){
  if(bootSequence == BOOT_DISK_LOADED){
    FFat.begin(false,"/ffat",1);
    if (FFat.exists(FILENAME_SETTINGS)){
      Serial.println("TaskDisk - File settings.bin exists.");    
      File settingsFile = FFat.open(FILENAME_SETTINGS,"r");
        if (settingsFile.size() == sizeof(settings)){
          Serial.println("TaskDisk - File settings.bin exists with same size. Settings to be loaded from Disk...");    
          settingsFile.read((uint8_t *)&settings, sizeof(settings));
          settingsFile.close();
          FFat.end();
          bootSequence = BOOT_SETTINGS_LOADED;
        }
        else{
          Serial.println("TaskDisk - File settings.bin exists but has different size. Loading default settings...");    
          settingsFile.close();
          FFat.end();
          loadDefaultSettings();
          bootSequence = BOOT_SETTINGS_LOADED;
        }
    }
    else{
      Serial.println("TaskDisk - File settings.bin does not exist. Creating file and loading default settings...");    
      FFat.end();
      loadDefaultSettings();
      bootSequence = BOOT_SETTINGS_LOADED;
    }
  }
}

//--------------------------------------------------------------------------------
// Load user default settings at first boot.
// Creates "Settings.PLsi" file
// Loads the default settings on his structure
//--------------------------------------------------------------------------------

void loadDefaultSettings(void){
  settings.general.firstRun = 0;
  settings.general.verbosityLevel = 0;
  settings.general.firmware = FIRMWARE_ACCEPTED;

  settings.ladder.NetworksQuantity = TOTAL_NETWORKS;
  settings.ladder.PLCstate = STOPPED;
  settings.ladder.UserProgram = DEMO_PROGRAM_SLOT;

  settings.io.localInputs[0] = IO_TYPE_DIGITAL;
  settings.io.localInputs[1] = IO_TYPE_DIGITAL;
  settings.io.localInputs[2] = IO_TYPE_DIGITAL;
  settings.io.localInputs[3] = IO_TYPE_DIGITAL;
  settings.io.localInputs[4] = IO_TYPE_DIGITAL;
  settings.io.localInputs[5] = IO_TYPE_DIGITAL;
  settings.io.localInputs[6] = IO_TYPE_DIGITAL;
  settings.io.localInputs[7] = IO_TYPE_DIGITAL;
  settings.io.localOutputs[0] = IO_TYPE_DIGITAL;
  settings.io.localOutputs[1] = IO_TYPE_DIGITAL;
  settings.io.localOutputs[2] = IO_TYPE_DIGITAL;
  settings.io.localOutputs[3] = IO_TYPE_DIGITAL;
  settings.io.localOutputs[4] = IO_TYPE_DIGITAL;
  settings.io.localOutputs[5] = IO_TYPE_DIGITAL;

  settings.hmi.ts.leftX = TS_LEFT_X;
  settings.hmi.ts.rightX = TS_RIGHT_X;
  settings.hmi.ts.topY = TS_TOP_Y;
  settings.hmi.ts.bottomY = TS_BOTTOM_Y;
  settings.hmi.switchesIndex = 500;
  settings.hmi.buttonsIndex = 510;
  settings.hmi.potentiometersIndex = 500;
  settings.hmi.analogIndicatorsIndex = 510;
  settings.hmi.digitalIndicatorsIndex = 520;

  snprintf(settings.wifi.ssid, SSID_LENGTH, WIFI_SSID);
  snprintf(settings.wifi.password, PASS_LENGTH, WIFI_PASS);
  settings.wifi.enabled = 0;

  settings.comm.modbusTCPserver.enabled = 1;
  settings.comm.modbusTCPserver.offset_0x = 0;
  settings.comm.modbusTCPserver.offset_1x = 0;
  settings.comm.modbusTCPserver.offset_3x = 0;
  settings.comm.modbusTCPserver.offset_4x = 0;
  settings.comm.modbusTCPserver.plsiOffset_0x = 0;
  settings.comm.modbusTCPserver.plsiOffset_1x = 0;
  settings.comm.modbusTCPserver.plsiOffset_3x = 0;
  settings.comm.modbusTCPserver.plsiOffset_4x = 0;
  settings.comm.modbusTCPserver.length_0x = 10;
  settings.comm.modbusTCPserver.length_1x = 10;
  settings.comm.modbusTCPserver.length_3x = 10;
  settings.comm.modbusTCPserver.length_4x = 10;

  saveSettings();
} 

//--------------------------------------------------------------------------------
// Save user settings to non volatile memory FFAT Disk 
//--------------------------------------------------------------------------------

void saveSettings(void){
  FFat.begin(false,"/ffat",1);
  File settingsFile = FFat.open(FILENAME_SETTINGS,"w");
  settingsFile.write((uint8_t *)&settings, sizeof(settings));
  settingsFile.close();
  FFat.end();
}

//--------------------------------------------------------------------------------
// Copy user program from PLC to SD
//--------------------------------------------------------------------------------

void copyProgramFromPLCtoSD(uint16_t programNumber){
  if (!SD.begin (SD_CS)){
    Serial.println("Card not present");
  }
  else{
    Serial.println("Card is present");
    
    File sourceFile;
    File destFile;

    FFat.begin(false,"/ffat",1);

    if (FFat.exists(FILENAME_USER_PROGRAMS[programNumber])){
      Serial.print("TaskLadder - File ");
      Serial.print(FILENAME_USER_PROGRAMS[programNumber]);
      Serial.println(" exists. Will be used to transfer to SD");

      sourceFile = FFat.open(FILENAME_USER_PROGRAMS[programNumber],"r");

      destFile  = SD.open(FILENAME_USER_PROGRAMS[programNumber], FILE_WRITE);
            
      static uint8_t buf[512];
      while( sourceFile.read( buf, 512) ) {
      destFile.write( buf, 512 );
      }
      Serial.print("User Program: ");
      Serial.print(FILENAME_USER_PROGRAMS[programNumber]);
      Serial.print(" transferred from PLC to SD");
    }
    else{
      Serial.print("TaskDisk - File: ");
      Serial.print(FILENAME_USER_PROGRAMS[programNumber]);
      Serial.println(" does not exists in PLC. Use first the file in PLC by selecting it in the configuration menu before transfer to SD");
    }

    destFile.close();
    sourceFile.close();
    FFat.end();
  }
  SD.end();
}

//--------------------------------------------------------------------------------
// Copy user program from SD to PLC
//--------------------------------------------------------------------------------

void copyProgramFromSDtoPLC(uint16_t programNumber){
  if (!SD.begin (SD_CS)){   
    Serial.println("Card not present");
  }
  else{
    Serial.println("Card is present");
    
    File sourceFile;
    File destFile;

    FFat.begin(false,"/ffat",1);

    if (SD.exists(FILENAME_USER_PROGRAMS[programNumber])){
      Serial.print("TaskDisk - Backup Files exists in SD, can be transferred to PLC: ");
      Serial.print(FILENAME_USER_PROGRAMS[programNumber]);

      sourceFile = SD.open(FILENAME_USER_PROGRAMS[programNumber],"r");
    
      if (FFat.exists(FILENAME_USER_PROGRAMS[programNumber])){
        Serial.print("TaskDisk - File ");
        Serial.print(FILENAME_USER_PROGRAMS[programNumber]);
        Serial.println(" exists. Will be used to transfer from SD to PLC");

        destFile = FFat.open(FILENAME_USER_PROGRAMS[programNumber],"w");

        static uint8_t buf[512];
        while( sourceFile.read( buf, 512) ) {
        destFile.write( buf, 512 );
        }

        Serial.print("User Program: ");
        Serial.print(FILENAME_USER_PROGRAMS[programNumber]);
        Serial.print(" transferred from SD to PLC");
      }
      else{
        Serial.print("TaskDisk - File: ");
        Serial.print(FILENAME_USER_PROGRAMS[programNumber]);
        Serial.println(" does not exists in PLC. Use first the file in PLC by selecting it in the configuration menu before transfer from SD to PLC");
      }
    }
    else{
      Serial.print("Backup Files does not exists in SD, will NOT be transferred to PLC: ");
      Serial.print(FILENAME_USER_PROGRAMS[programNumber]);
    }
    destFile.close();
    sourceFile.close();
    FFat.end();
  }
  SD.end();
}










