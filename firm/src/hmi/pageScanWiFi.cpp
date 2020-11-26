#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <wifi.h>

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs page
//--------------------------------------------------------------------------------

void pageScanWiFi (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){

  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawNetworksScan();
    }

  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchScanWiFi(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// WiFi Turning of WiFi message
//--------------------------------------------------------------------------------

void drawNetworksScan (void){
  #define VIEW_NET_Y 40

  // If WiFi is enabled but not connected, has to be disconencted before to scan
  if (!WiFi.isConnected() && settings.wifi.enabled){
    settings.wifi.enabled = 0;
    saveSettings();
    drawDisconnectingWiFi();
    delay(1000); // Wait for Wifi disconnection in WiFi Task
  }

  drawScanningWiFi();
  int16_t numSSID = WiFi.scanNetworks();

  if (numSSID <= WIFI_SCAN_FAILED){
    drawWiFiScanFailed();
  }
  else{

    // Limited to show the best  networks 
    //  - for 240 Y display 5 Networks
    //  - for 320 Y display 7 Networks
    // An improvement would be to have a second page and show 5 more
    uint16_t networksPerPage = (TFT_PIXELS_Y / VIEW_NET_Y) - 1; // lucas multi page implementation
    if (numSSID < networksPerPage){
      networksPerPage = numSSID; 
    } 

    for (uint16_t thisNetwork = 0; thisNetwork < networksPerPage; thisNetwork++) {
      drawNetworkInfo(thisNetwork, thisNetwork);
    } 
  }
}

//--------------------------------------------------------------------------------
// WiFi Turning of WiFi message
//--------------------------------------------------------------------------------

void drawDisconnectingWiFi (void){
  tft.fillScreen(BLUE1);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Turning OFF WiFi...");
}

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs message
//--------------------------------------------------------------------------------

void drawScanningWiFi (void){
  tft.fillScreen(BLUE1);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Scanning Networks...");
}

//--------------------------------------------------------------------------------
// WiFi Scanning Failed message
//--------------------------------------------------------------------------------

void drawWiFiScanFailed (void){
  tft.fillScreen(BLUE1);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("Scan Failed !");
  tft.setCursor(10, 30);
  tft.print("Turn OFF WiFi");
  tft.setCursor(10, 50);
  tft.print("and try again...");
}

//--------------------------------------------------------------------------------
// WiFi draw Network information
//--------------------------------------------------------------------------------

void drawNetworkInfo (uint16_t netIndex, uint16_t pageIndex){
  String SSID;
  uint8_t encryptionType, *BSSID;
  uint16_t wifiPower;
  int32_t RSSI, channel;
  uint32_t auxColor;

  WiFi.getNetworkInfo(netIndex, SSID, encryptionType, RSSI, BSSID, channel);

  wifiPower = convertDbm(RSSI);
  if(wifiPower > 60){      // equivalent to: < -66dBm
    auxColor = TFT_DARKGREEN;
  }
  else if(wifiPower > 50){ // equivalent to: < -70 dBm
    auxColor = ORANGE;
  }
  else{
    auxColor = TFT_RED;
  }

  // Box for each detected network
  tft.fillRect(1, 1 + VIEW_NET_Y * pageIndex, TFT_PIXELS_X-2, VIEW_NET_Y - 2, auxColor);
  tft.drawRect(1, 1 + VIEW_NET_Y * pageIndex, TFT_PIXELS_X-2, VIEW_NET_Y - 2, WHITE2);

  // Power in % + SSID Name
  tft.setTextColor(WHITE2);
  tft.setTextSize(2);
  tft.setCursor(10, 7 + VIEW_NET_Y * pageIndex);
  tft.print(String(wifiPower) + "%  " + SSID);
   
  // Network info: Power in dBm + Channel + Encryption type + AP MAC address
  // Example:
  // -60dBm  CH: 5  WPA-PSK  AA-BB-CC-DD-EE-FF
  tft.setTextSize(1);
  tft.setCursor(10, 27 + VIEW_NET_Y * pageIndex);

  String netInfo = "";
  String encryptionString = "?";

  if(encryptionType == WIFI_AUTH_OPEN){
    encryptionString = "OPEN";
  }
  else if (encryptionType == WIFI_AUTH_WEP){
    encryptionString = "WEP";
  }
  else if (encryptionType == WIFI_AUTH_WPA_PSK){
    encryptionString = "WPA-PSK";
  }
  else if (encryptionType == WIFI_AUTH_WPA2_PSK){
    encryptionString = "WPA2-PSK";
  }
  else if (encryptionType == WIFI_AUTH_WPA_WPA2_PSK){
    encryptionString = "WPA-WPA2-PSK";
  }
  else if (encryptionType == WIFI_AUTH_WPA2_ENTERPRISE){
    encryptionString = "WPA2-ENTERPR";
  }
  else if (encryptionType == WIFI_AUTH_MAX){
    encryptionString = "MAX";
  }

  netInfo = netInfo + String(RSSI) + "dBm  CH: " + String(channel) + "  " + encryptionString + "  ";

  char macOctet[3];
  for (uint16_t i = 0; i < 6; i++){
    sprintf(macOctet,"%02X",BSSID[i]);
    netInfo = netInfo + String(macOctet);
    if(i < 5){
      netInfo = netInfo + ":";
    }
  }
  tft.print(netInfo);
}

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchScanWiFi(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_ConfigNetwork;
}






