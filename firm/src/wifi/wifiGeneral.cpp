#include <globals.h>
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