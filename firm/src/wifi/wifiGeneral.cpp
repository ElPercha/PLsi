// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

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