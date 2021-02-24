/*
Copyright (c) 2019 Prieto Lucas. All rights reserved.
This file is part of the PLsi project.

PLsi is free software and hardware: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
PLsi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
