#include <globals.h>
#include <wifi_plsi.h>

//--------------------------------------------------------------------------------
// Wait for tskDisk to load the User Settings  
//--------------------------------------------------------------------------------

void wifiWaitSettings (void){
  Serial.println("TskWiFi - Waiting for Settings to be loaded");
  while (bootSequence != 1){
    delay(10); // forces to update bootSequence global variable
  }
  Serial.println("TskWifi - Settings loaded correctly");
}