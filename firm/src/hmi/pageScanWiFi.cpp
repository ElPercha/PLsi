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
    uint16_t networksPerPage = (TFT_PIXELS_Y / VIEW_NET_Y) - 1; 
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
// WiFi Scanning Failed message
//--------------------------------------------------------------------------------

void drawNetworkInfo (uint16_t netIndex, uint16_t pageIndex){
  String SSID;
  uint8_t encryptionType, *BSSID;
  int32_t RSSI, channel;
  
  WiFi.getNetworkInfo(netIndex, SSID, encryptionType, RSSI, BSSID, channel);

  Serial.print("Network number: ");
  Serial.println(netIndex);
  Serial.print("    - SSID: ");
  Serial.println(SSID);
  Serial.print("    - encryptionType: ");
  Serial.println(encryptionType);
  Serial.print("    - RSSD: ");
  Serial.println(RSSI);
  Serial.print("    - channel: ");
  Serial.println(channel);

  Serial.print("    - BSSID: ");
  Serial.print(BSSID[0],HEX);
  Serial.print(":");
  Serial.print(BSSID[1],HEX);
  Serial.print(":");
  Serial.print(BSSID[2],HEX);
  Serial.print(":");
  Serial.print(BSSID[3],HEX);
  Serial.print(":");
  Serial.print(BSSID[4],HEX);
  Serial.print(":");
  Serial.println(BSSID[5],HEX);

  char macOctet[3];
  String netInfo = "";

  for (uint16_t i = 0; i < 6; i++){
    sprintf(macOctet,"%02X",BSSID[i]);
    netInfo = netInfo + String(macOctet);
    if(i < 5){
      netInfo = netInfo + ":";
    }
  }
  Serial.println("AP MAC: " + netInfo);

}

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchScanWiFi(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_ConfigNetwork;
}






