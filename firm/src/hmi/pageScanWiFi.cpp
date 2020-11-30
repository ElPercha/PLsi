#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <wifi.h>

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs page
//--------------------------------------------------------------------------------

void pageConfigScanWiFi (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){

  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      tft.fillScreen(COLOR_WIFI_SCAN_BACK);
      drawWiFiScanButtons();
      scanWiFiNetworks();
      networksScanPage = 0;
    }

  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchConfigScanWiFi(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// WiFi Turning of WiFi message
//--------------------------------------------------------------------------------

void scanWiFiNetworks (void){

  // If WiFi is enabled but not connected, has to be disconencted before to scan
  if (!WiFi.isConnected() && settings.wifi.enabled){
    settings.wifi.enabled = 0;
    saveSettings();
    drawDisconnectingWiFi();
    delay(1000); // Wait for Wifi disconnection in WiFi Task
  }

  drawScanningWiFi();
  networksFound = WiFi.scanNetworks();

  if (networksFound <= WIFI_SCAN_FAILED){
    drawWiFiScanFailed();
  }
  else{
    drawNetworksFound();
  }
}

//--------------------------------------------------------------------------------
// WiFi Turning of WiFi message
//--------------------------------------------------------------------------------

void drawDisconnectingWiFi (void){
  tft.fillRect(0, 0, TFT_PIXELS_X, TFT_PIXELS_Y - VIEW_NET_Y, COLOR_WIFI_SCAN_BACK);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Turning OFF WiFi...");
}

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs message
//--------------------------------------------------------------------------------

void drawScanningWiFi (void){
  tft.fillRect(0, 0, TFT_PIXELS_X, TFT_PIXELS_Y - VIEW_NET_Y, COLOR_WIFI_SCAN_BACK);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Scanning Networks...");
}

//--------------------------------------------------------------------------------
// WiFi Scanning Failed message
//--------------------------------------------------------------------------------

void drawWiFiScanFailed (void){
  tft.fillRect(0, 0, TFT_PIXELS_X, TFT_PIXELS_Y - VIEW_NET_Y, COLOR_WIFI_SCAN_BACK);
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
// draw 3 buttons in the bottom CANCEL - RESCAN - MORE
//--------------------------------------------------------------------------------

void drawWiFiScanButtons(){
  #define BORDERWIFI       1
  #define SPACINGWIFI      2
  #define BUTTON_H_WIFI    VIEW_NET_Y - BORDERWIFI * 2
  #define BUTTON_W_WIFI    (TFT_PIXELS_X - SPACINGWIFI * 4) / 3
  #define BUTTON_Y_WIFI    TFT_PIXELS_Y - VIEW_NET_Y + BORDERWIFI // Y where the button starts

  tft.fillRoundRect(SPACINGWIFI, BUTTON_Y_WIFI, BUTTON_W_WIFI, BUTTON_H_WIFI, 8, COLOR_WIFI_SCAN_CANCEL);
  tft.drawRoundRect(SPACINGWIFI, BUTTON_Y_WIFI, BUTTON_W_WIFI, BUTTON_H_WIFI, 8, COLOR_WIFI_SCAN_BORDER);

  tft.fillRoundRect(SPACINGWIFI*2 + BUTTON_W_WIFI, BUTTON_Y_WIFI, BUTTON_W_WIFI, BUTTON_H_WIFI, 8, COLOR_WIFI_SCAN_DO);
  tft.drawRoundRect(SPACINGWIFI*2 + BUTTON_W_WIFI, BUTTON_Y_WIFI, BUTTON_W_WIFI, BUTTON_H_WIFI, 8, COLOR_WIFI_SCAN_BORDER);

  tft.fillRoundRect(SPACINGWIFI*3 + BUTTON_W_WIFI*2, BUTTON_Y_WIFI, BUTTON_W_WIFI, BUTTON_H_WIFI, 8, COLOR_WIFI_SCAN_MORE);
  tft.drawRoundRect(SPACINGWIFI*3 + BUTTON_W_WIFI*2, BUTTON_Y_WIFI, BUTTON_W_WIFI, BUTTON_H_WIFI, 8, COLOR_WIFI_SCAN_BORDER);

  tft.setTextSize(2);
  tft.setTextColor(COLOR_BUTTON_FONT_INSTRUC_EDITOR);

  String auxString;
  auxString = "CANCEL";
  tft.setCursor(SPACINGWIFI + BUTTON_W_WIFI/2 - auxString.length()*6, BUTTON_Y_WIFI + 13);
  tft.print(auxString);

  auxString = "SCAN";
  tft.setCursor(SPACINGWIFI*2 + BUTTON_W_WIFI + BUTTON_W_WIFI/2 - auxString.length()*6, BUTTON_Y_WIFI + 13);
  tft.print(auxString);

  auxString = "MORE";
  tft.setCursor(SPACINGWIFI*3 + BUTTON_W_WIFI*2 + BUTTON_W_WIFI/2 - auxString.length()*6, BUTTON_Y_WIFI + 13);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// WiFi Scanning - Draw Networks found
//--------------------------------------------------------------------------------

void drawNetworksFound(void){
  if(networksFound > NETWORKS_PER_PAGE * (networksScanPage + 1)){
    networksToShow = NETWORKS_PER_PAGE;
  }
  else{
    networksToShow = networksFound % NETWORKS_PER_PAGE;
  }

  tft.fillRect(0, 0, TFT_PIXELS_X, TFT_PIXELS_Y - VIEW_NET_Y, COLOR_WIFI_SCAN_BACK);

  for (uint16_t thisNetwork = 0; thisNetwork < networksToShow; thisNetwork++) {
    drawNetworkInfo(thisNetwork + networksScanPage * NETWORKS_PER_PAGE, thisNetwork);
  } 
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

  // 3 colors code for power signal
  wifiPower = convertDbm(RSSI);
  if(wifiPower > 60){      // higher than -66 dBm
    auxColor = COLOR_WIFI_SIGNAL_GOOD;
  }
  else if(wifiPower < 50){ // lower than -70 dBm
    auxColor = COLOR_WIFI_SIGNAL_BAD;
  }
  else{                    // between -66 to -70 dBm
    auxColor = COLOR_WIFI_SIGNAL_MED; 
  }

  // Box for each detected network
  tft.fillRect(1, 1 + VIEW_NET_Y * pageIndex, TFT_PIXELS_X-2, VIEW_NET_Y - 2, auxColor);
  tft.drawRect(1, 1 + VIEW_NET_Y * pageIndex, TFT_PIXELS_X-2, VIEW_NET_Y - 2, COLOR_WIFI_BOX_BORDER);

  // Power in % + SSID Name
  tft.setTextColor(COLOR_WIFI_BOX_TEXT);
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

void touchConfigScanWiFi(uint16_t ts_x, uint16_t ts_y){

  // Buttons selection
  if (ts_y > TFT_PIXELS_Y - VIEW_NET_Y){
    // MORE button
    if (ts_x > SPACINGWIFI*3 + BUTTON_W_WIFI*2){
      if (networksFound > NETWORKS_PER_PAGE * (networksScanPage + 1)){
        networksScanPage++;
      }
      else{
        networksScanPage = 0;
      }
      drawNetworksFound();
    }
    // CANCEL button
    else if (ts_x < SPACINGWIFI*2 + BUTTON_W_WIFI){
      HMI_Page = PAGE_ConfigWiFi;
    }
    // SCAN button
    else{
      scanWiFiNetworks();
    }
  }
  // User selects a network
  else{
    uint16_t indexNetworkSelected = ts_y / uint16_t(VIEW_NET_Y);

    if (indexNetworkSelected < networksToShow){
      textValueAccepted = 1;
      wifiEditionField = EDITING_WIFI_SSID;
      textValue = WiFi.SSID(indexNetworkSelected);
      HMI_Page = PAGE_ConfigWiFi;
    } 
  }
}

