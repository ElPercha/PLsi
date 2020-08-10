#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Wait for tskDisk to load the User Settings  
//--------------------------------------------------------------------------------

void hmiWaitSettings (void){
  Serial.println("TaskHMI - Waiting for Unlock");
  while (bootSequence != BOOT_TASK_UNLOCKED){
    delay(10); // forces to update bootSequence global variable
  }
  Serial.println("TaskHMI - Task Unlocked");
}