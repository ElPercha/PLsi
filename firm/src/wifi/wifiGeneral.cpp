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
    Serial.print(" dBm - Channel: ");
    Serial.println(WiFi.channel(thisNet));
    //WiFi.getNetworkInfo(); //gets all info at once
  }
}

//--------------------------------------------------------------------------------
// WiFi Call back back for disconnection reasons
// Disconnection Reasons:
//
// WIFI_REASON_UNSPECIFIED              = 1,
// WIFI_REASON_AUTH_EXPIRE              = 2,
// WIFI_REASON_AUTH_LEAVE               = 3,
// WIFI_REASON_ASSOC_EXPIRE             = 4,
// WIFI_REASON_ASSOC_TOOMANY            = 5,
// WIFI_REASON_NOT_AUTHED               = 6,
// WIFI_REASON_NOT_ASSOCED              = 7,
// WIFI_REASON_ASSOC_LEAVE              = 8,
// WIFI_REASON_ASSOC_NOT_AUTHED         = 9,
// WIFI_REASON_DISASSOC_PWRCAP_BAD      = 10,
// WIFI_REASON_DISASSOC_SUPCHAN_BAD     = 11,
// WIFI_REASON_IE_INVALID               = 13,
// WIFI_REASON_MIC_FAILURE              = 14,
// WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT   = 15,
// WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT = 16,
// WIFI_REASON_IE_IN_4WAY_DIFFERS       = 17,
// WIFI_REASON_GROUP_CIPHER_INVALID     = 18,
// WIFI_REASON_PAIRWISE_CIPHER_INVALID  = 19,
// WIFI_REASON_AKMP_INVALID             = 20,
// WIFI_REASON_UNSUPP_RSN_IE_VERSION    = 21,
// WIFI_REASON_INVALID_RSN_IE_CAP       = 22,
// WIFI_REASON_802_1X_AUTH_FAILED       = 23,
// WIFI_REASON_CIPHER_SUITE_REJECTED    = 24,
// WIFI_REASON_BEACON_TIMEOUT           = 200,
// WIFI_REASON_NO_AP_FOUND              = 201,
// WIFI_REASON_AUTH_FAIL                = 202,
// WIFI_REASON_ASSOC_FAIL               = 203,
// WIFI_REASON_HANDSHAKE_TIMEOUT        = 204,
//--------------------------------------------------------------------------------
