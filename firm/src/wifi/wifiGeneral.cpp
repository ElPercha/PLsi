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
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <ModbusIP.h>
#include <disk.h>
#include <wifi_plsi.h>

//--------------------------------------------------------------------------------
// Wait for tskDisk to load the User Settings  
//--------------------------------------------------------------------------------

void wifiWaitSettings (void){
  Serial.println("TaskWiFi - Waiting for Unlock");
  while (bootSequence != BOOT_TASK_UNLOCKED){
    delay(10); // forces to update bootSequence global variable
  }
  Serial.println("TaskWifi - Task Unlocked");
}

//--------------------------------------------------------------------------------
// Get free heap current and historical minimim
//--------------------------------------------------------------------------------

void printAvailableMemory (void){
  Serial.print("      - Free ESP Miniumn memory ever available: ");
  Serial.println (esp_get_minimum_free_heap_size());
  Serial.print("      - Free ESP memory xPort: ");
  Serial.println(xPortGetFreeHeapSize());
  Serial.print("      - Memory allocated: ");
  Serial.println(previousFreeMemory - xPortGetFreeHeapSize());

  previousFreeMemory = xPortGetFreeHeapSize(); 
}