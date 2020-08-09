#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Wait for tskDisk to load the User Settings  
//--------------------------------------------------------------------------------

void hmiWaitSettings (void){
  Serial.println("TskHMI - Waiting for Settings to be loaded");
  while (bootSequence != 1){
    delay(10); // forces to update bootSequence global variable
  }
  Serial.println("TskHMI - Settings loaded correctly");
}