#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <WiFi.h>

//--------------------------------------------------------------------------------
// Network Configuration Page
//--------------------------------------------------------------------------------

void pageConfigNetwork (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){

  //-------------------------------
  // Keyboard input
  //-------------------------------
  
  if (textValueAccepted){
    textValueAccepted = 0;
    if (wifiEditionField == EDITING_WIFI_SSID && textValue.compareTo(String(settings.wifi.ssid))){
      textValue.toCharArray(settings.wifi.ssid, SSID_LENGTH);
      settings.wifi.enabled = 0; // Turn Off WiFi if value has been changed
      saveSettings();
    }
    if (wifiEditionField == EDITING_WIFI_PASSWORD && textValue.compareTo(String(settings.wifi.password))){
      textValue.toCharArray(settings.wifi.password, PASS_LENGTH);
      settings.wifi.enabled = 0; // Turn Off WiFi if value has been changed
      saveSettings();
    }
  }

  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigNetwork();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

  if (millis() - timerRefreshWifiStatus > 2000){
    drawNetworkConfigStatus();
    timerRefreshWifiStatus = millis();
  }

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchConfigNetwork(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Network Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigNetwork (void){
  #define CONFIG_NETWORK_SPACE        4           
  #define CONFIG_NETWORK_BUTTON_W    60
  #define CONFIG_NETWORK_BUTTON_H     (TFT_PIXELS_Y - (CONFIG_NETWORK_SPACE * 5)) / 4
  #define CONFIG_NETWORK_BAR_W        TFT_PIXELS_X - CONFIG_NETWORK_BUTTON_W - CONFIG_NETWORK_SPACE * 3          
  #define CONFIG_NETWORK_BAR_H        CONFIG_NETWORK_BUTTON_H
  #define CONFIG_NETWORK_STAT_W       CONFIG_NETWORK_BAR_W          
  #define CONFIG_NETWORK_STAT_H       CONFIG_NETWORK_BUTTON_H * 2 + CONFIG_NETWORK_SPACE           

  tft.fillScreen(TFT_BLACK);

  drawNetworkConfigSSID();
  drawNetworkConfigPass();
  drawNetworkConfigStatus();
  drawNetworkConfigButtons();
  drawNetworkWifiOnOffButton();
}

//--------------------------------------------------------------------------------
// Draw SSID bar
//--------------------------------------------------------------------------------

void drawNetworkConfigSSID (void){
  tft.fillRoundRect(CONFIG_NETWORK_SPACE, CONFIG_NETWORK_SPACE, CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_BAR_H, 7, WHITE2);

  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);

  String auxString = String(settings.wifi.ssid);

  // Max Length = SSID_LENGTH-1
  if(textValue.length() <= 19){
    tft.drawString(auxString, CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE + 20);
  }
  else{
    tft.drawString(auxString.substring(0, 19), CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE + 11);
    tft.drawString(auxString.substring(19, textValue.length()),  CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE + 31);
  }  
}

//--------------------------------------------------------------------------------
// Draw Pass bar
//--------------------------------------------------------------------------------

void drawNetworkConfigPass (void){
  tft.fillRoundRect(CONFIG_NETWORK_SPACE, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_H, CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_BAR_H, 7, WHITE2);

  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);

  String auxString = String(settings.wifi.password);

  // Max Length = PASS_LENGTH-1
  if(textValue.length() <= 19){
    tft.drawString(auxString, CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_H + 20);
  }
  else if(textValue.length() <= 38){
    tft.drawString(auxString.substring(0, 19), CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_H + 11);
    tft.drawString(auxString.substring(19, textValue.length()),  CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_H + 31);
  }  
  else{
    tft.setTextSize(1);
    tft.drawString(auxString.substring(0, 32), CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_H + 11);
    tft.drawString(auxString.substring(32, textValue.length()),  CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_H + 31);
  }  
}

//--------------------------------------------------------------------------------
// Draw Status bar
//--------------------------------------------------------------------------------

void drawNetworkConfigStatus (void){
  if (WiFi.status() == WL_CONNECTED && settings.wifi.enabled){
    tft.fillRoundRect(CONFIG_NETWORK_SPACE, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BAR_H * 2, CONFIG_NETWORK_STAT_W, CONFIG_NETWORK_STAT_H, 7, TFT_GREEN);
  }
  else{
    tft.fillRoundRect(CONFIG_NETWORK_SPACE, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BAR_H * 2, CONFIG_NETWORK_STAT_W, CONFIG_NETWORK_STAT_H, 7, TFT_LIGHTGREY);
  }
  
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);

  tft.setCursor(CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BAR_H * 2 + 8);
  if (!settings.wifi.enabled){
    tft.print("Disabled");
  }
  else if (WiFi.status() == WL_IDLE_STATUS){
    tft.print("Idle");
  }
  else if (WiFi.status() == WL_NO_SSID_AVAIL){
    tft.print("No SSID available");
  }
  else if (WiFi.status() == WL_SCAN_COMPLETED){
    tft.print("Scan completed");
  }
  else if (WiFi.status() == WL_CONNECTED){
    tft.print("Connected");
  }
  else if (WiFi.status() == WL_CONNECT_FAILED){
    tft.print("Connection failed");
  }
  else if (WiFi.status() == WL_CONNECTION_LOST){
    tft.print("Connection lost");
  }
  else if (WiFi.status() == WL_DISCONNECTED){
    tft.print("Disconnected");
  }
    
  tft.setCursor(CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BAR_H * 2 + 31);
  tft.print(WiFi.localIP());

  tft.setCursor(CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BAR_H * 2 + 54);

  uint16_t auxSignal = convertDbm(int32_t(WiFi.RSSI()));

  if (WiFi.status() == WL_CONNECTED){
    tft.print("Signal: " + String(auxSignal) + "%");
  }
  else{
    tft.print("Signal: --");
  }

  tft.setCursor(CONFIG_NETWORK_SPACE + 10, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BAR_H * 2 + 77);
  tft.print("Channel: " + String(WiFi.channel()));

  tft.setCursor(CONFIG_NETWORK_SPACE + 15, TFT_PIXELS_Y - 17);
  tft.setTextSize(1);
  tft.print(WiFi.macAddress() + "   Power: " + String(WiFi.RSSI()) + " dBm");
}

//--------------------------------------------------------------------------------
// Draw Buttons
//--------------------------------------------------------------------------------

void drawNetworkConfigButtons (void){

  tft.fillRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BUTTON_H, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_DARKCYAN);
  tft.drawRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BUTTON_H, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_WHITE);

  tft.fillRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BUTTON_H * 2, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_DARKCYAN);
  tft.drawRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BUTTON_H * 2, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_WHITE);

  tft.fillRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE * 4 + CONFIG_NETWORK_BUTTON_H * 3, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_DARKCYAN);
  tft.drawRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE * 4 + CONFIG_NETWORK_BUTTON_H * 3, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_WHITE);
  
  // Text on buttons
  tft.setTextSize(2);
  tft.setTextColor(WHITE2);
  
  tft.setCursor(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W + 7, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BUTTON_H + 10);
  tft.print("SSID");
  tft.setCursor(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W + 7, CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BUTTON_H + 30);
  tft.print("SCAN");

  tft.setCursor(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W + 7, CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BUTTON_H * 2 + 20);
  tft.print("BACK");

  tft.setCursor(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W + 7, CONFIG_NETWORK_SPACE * 4 + CONFIG_NETWORK_BUTTON_H * 3 + 20);
  tft.print("HOME");
}

void drawNetworkWifiOnOffButton (void){
  tft.setTextSize(2);
  tft.setTextColor(WHITE2);

  if(settings.wifi.enabled){
    tft.fillRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_DARKGREEN);
  }
  else{
    tft.fillRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_DARKCYAN);
  }
  tft.drawRoundRect(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W, CONFIG_NETWORK_SPACE, CONFIG_NETWORK_BUTTON_W, CONFIG_NETWORK_BUTTON_H, 7, TFT_WHITE);

  tft.setCursor(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W + 7, CONFIG_NETWORK_SPACE + 10);
  tft.print("WiFi");
  if(settings.wifi.enabled){
    tft.setCursor(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W + 17, CONFIG_NETWORK_SPACE + 30);
    tft.print("ON");
  }
  else{
    tft.setCursor(CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W + 12, CONFIG_NETWORK_SPACE + 30);
    tft.print("OFF");
  }
}

//--------------------------------------------------------------------------------
// Wi Fi Network configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigNetwork(uint16_t ts_x, uint16_t ts_y){
  if (ts_x > CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BAR_W){
    // ON/OFF button
    if (ts_y < CONFIG_NETWORK_SPACE + CONFIG_NETWORK_BUTTON_H){
      if(settings.wifi.enabled){
        settings.wifi.enabled = 0;
        drawNetworkConfigStatus();
      } 
      else{
        settings.wifi.enabled = 1;
      }   
      drawNetworkWifiOnOffButton();
      saveSettings();
    }
    // WIFI Scan Networks buton
    else if (ts_y < CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BUTTON_H * 2){
      HMI_PageMemory =  HMI_Page;        
      HMI_Page = PAGE_ScanWiFi;
    }
    // BACK button
    else if (ts_y < CONFIG_NETWORK_SPACE * 3 + CONFIG_NETWORK_BUTTON_H * 3){
      HMI_Page = PAGE_MainConfig;
    }
    // HOME button
    else{ 
      HMI_Page = PAGE_MainMenu;
    }
  }
  else {
    // SSID Bar
    if (ts_y < CONFIG_NETWORK_SPACE + CONFIG_NETWORK_BUTTON_H){
      wifiEditionField = EDITING_WIFI_SSID;
      textValue = settings.wifi.ssid;     
      textMaxLength = SSID_LENGTH - 1;     
      HMI_PageMemory =  HMI_Page;        
      HMI_Page = PAGE_Keyboard;        
    }
    // Password Bar
    else if (ts_y < CONFIG_NETWORK_SPACE * 2 + CONFIG_NETWORK_BUTTON_H * 2){
      wifiEditionField = EDITING_WIFI_PASSWORD;
      textValue = settings.wifi.password;     
      textMaxLength = PASS_LENGTH - 1;     
      HMI_PageMemory =  HMI_Page;        
      HMI_Page = PAGE_Keyboard;        
    }
    // Status Bar
    else{
      // No function yet    
    }
  }
}

//--------------------------------------------------------------------------------
// Convert dBm to %
// -50dBm = 100%  
// -90dBm = 1%
//
// dBm Reference values
// -30 dBm	Amazing	Max achievable signal strength. The client can only be a few feet from the AP to achieve this. Not typical or desirable in the real world.	N/A
// -67 dBm	Very Good	Minimum signal strength for applications that require very reliable, timely delivery of data packets.	VoIP/VoWiFi, streaming video
// -70 dBm	Okay	Minimum signal strength for reliable packet delivery.	Email, web
// -80 dBm	Not Good	Minimum signal strength for basic connectivity. Packet delivery may be unreliable.	N/A
// -90 dBm	Unusable	Approaching or drowning in the noise floor. Any functionality is highly unlikely.	N/A
//--------------------------------------------------------------------------------

uint16_t convertDbm (int32_t signalWifi){
  double auxSignal = (90 + signalWifi) * 100.0/40.0; 
  if (auxSignal > 100){
    auxSignal = 100;
  }
  if (auxSignal < 1){
    auxSignal = 1;
  }
  return uint16_t(auxSignal);
}


