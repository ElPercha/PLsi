#include <globals.h>
#include <WiFi.h>
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
// Wait for tskDisk to load the User Settings  
// dBm Reference values
// -30 dBm	Amazing	Max achievable signal strength. The client can only be a few feet from the AP to achieve this. Not typical or desirable in the real world.	N/A
// -67 dBm	Very Good	Minimum signal strength for applications that require very reliable, timely delivery of data packets.	VoIP/VoWiFi, streaming video
// -70 dBm	Okay	Minimum signal strength for reliable packet delivery.	Email, web
// -80 dBm	Not Good	Minimum signal strength for basic connectivity. Packet delivery may be unreliable.	N/A
// -90 dBm	Unusable	Approaching or drowning in the noise floor. Any functionality is highly unlikely.	N/A
//--------------------------------------------------------------------------------

void scanNetworks(void) {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("SSID List:");
  Serial.println(numSsid);
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") Network: ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print(" - Power : ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dB - Channel: ");
    Serial.println(WiFi.channel(thisNet));
    //WiFi.getNetworkInfo(); //gets all info at once
  }
}