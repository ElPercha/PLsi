#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <WiFi.h>

//--------------------------------------------------------------------------------
// System Configuration Page Firmware Upgrade
//--------------------------------------------------------------------------------

void pageConfigFirmware (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigFirmware();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    if (millis() - auxTimerFirmwareBar > 1000 && configFirmwareEnabled){
      auxTimerFirmwareBar = millis();
      drawFirmwareStatusBar();
    }

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigFirmware(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// System Configuration firmware Upgrade draw 
//--------------------------------------------------------------------------------

void drawConfigFirmware (void){

  #define FIRMWARE_ENABLE_X            25
  #define FIRMWARE_ENABLE_Y            25
  #define FIRMWARE_ENABLE_W            TFT_PIXELS_X - FIRMWARE_ENABLE_X*2
  #define FIRMWARE_ENABLE_H            50 
  #define FIRMWARE_CANCEL_X             5
  #define FIRMWARE_CANCEL_Y            TFT_PIXELS_Y - 45
  #define FIRMWARE_CANCEL_W            TFT_PIXELS_X - FIRMWARE_CANCEL_X*2
  #define FIRMWARE_CANCEL_H            40 
  #define FIRMWARE_BAR_X               FIRMWARE_ENABLE_X
  #define FIRMWARE_BAR_Y               FIRMWARE_ENABLE_Y + FIRMWARE_ENABLE_H + 10
  #define FIRMWARE_BAR_W               FIRMWARE_ENABLE_W
  #define FIRMWARE_BAR_H               FIRMWARE_CANCEL_Y - (FIRMWARE_BAR_Y) - 10

  // Title
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setFreeFont(FSS9);
  tft.drawCentreString("Firmware Update", TFT_PIXELS_X/2, 3, GFXFF);

  // Enable button
  drawFirmwareEnableButton();

  // Status Bar
  drawFirmwareStatusBar();

  // Cancel Button
  tft.fillRoundRect(FIRMWARE_CANCEL_X, FIRMWARE_CANCEL_Y, FIRMWARE_CANCEL_W, FIRMWARE_CANCEL_H, 10 , COLOR_FIRMWARE_CANCEL);
  tft.setTextColor(COLOR_FIRMWARE_CANCEL_FONT);
  tft.setFreeFont(FSS12);
  tft.drawCentreString("CANCEL", TFT_PIXELS_X/2, TFT_PIXELS_Y - 36, GFXFF);

  tft.setTextFont(1);
}

//--------------------------------------------------------------------------------
// Draw Enable button
//--------------------------------------------------------------------------------

void drawFirmwareEnableButton (void){
  uint16_t color, fontcolor;
  String str;

  if(configFirmwareEnabled){
    color = COLOR_FIRMWARE_ENABLED;
    fontcolor = COLOR_FIRMWARE_ENABLED_FONT;
    str = "ENABLED";
  }
  else{
    color = COLOR_FIRMWARE_DISABLED;
    fontcolor = COLOR_FIRMWARE_DISABLED_FONT;
    str = "ENABLE";
  }

  tft.fillRoundRect(FIRMWARE_ENABLE_X, FIRMWARE_ENABLE_Y, FIRMWARE_ENABLE_W, FIRMWARE_ENABLE_H, 10 , color);
  tft.setTextColor(fontcolor);
  tft.setFreeFont(FSS12);
  tft.drawCentreString(str, TFT_PIXELS_X/2, FIRMWARE_ENABLE_Y + 18, GFXFF);
  tft.setTextFont(1);
}

//--------------------------------------------------------------------------------
// Draw status bar
//--------------------------------------------------------------------------------

void drawFirmwareStatusBar(void){

  tft.fillRoundRect(FIRMWARE_BAR_X, FIRMWARE_BAR_Y, FIRMWARE_BAR_W, FIRMWARE_BAR_H, 10 , COLOR_FIRMWARE_BAR);
  tft.setTextColor(COLOR_FIRMWARE_BAR_FONT);
  tft.setFreeFont(FSS9);

  if(!WiFi.isConnected() || settings.ladder.PLCstate != STOPPED){
    tft.drawCentreString("Before to start:", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 10, GFXFF);
    tft.drawCentreString("Connect Wi-Fi Network", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 30, GFXFF);
    tft.drawCentreString("and", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 50, GFXFF);
    tft.drawCentreString("STOP the PLC", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 70, GFXFF);
  }
  else{
    if(configFirmwareEnabled){
      tft.drawCentreString(firmwareUpdateStatus, TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 10, GFXFF);
      tft.drawCentreString(firmwareUpdateFilename, TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 30, GFXFF);

      if (settings.general.firmware == FIRMWARE_UPDATED){ // 100% when completed because firmwareUpdateSize = MAX AVAILABLE SIZE
        tft.drawCentreString("100%", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 50, GFXFF);
      }
      else if (firmwareUpdateSize > 0){
        tft.drawCentreString(String(uint16_t(firmwareUpdateProgress*100/firmwareUpdateSize)) + "%", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 50, GFXFF);
      }
    }
    else{
      tft.drawCentreString("ENABLE process and go to:", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 10, GFXFF);
      tft.drawCentreString(WiFi.localIP().toString(), TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 30, GFXFF);
      tft.drawCentreString("Current Firmware Version:", TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 50, GFXFF);
      tft.drawCentreString(FIRMWARE, TFT_PIXELS_X/2, FIRMWARE_BAR_Y + 70, GFXFF);
    }
  }
  tft.setTextFont(1);
}

//--------------------------------------------------------------------------------
// System configuration page - Firmware Update
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigFirmware(uint16_t ts_x, uint16_t ts_y){
  // Enable button
  if (ts_y < FIRMWARE_BAR_Y){
    if (!configFirmwareEnabled && WiFi.isConnected() && settings.ladder.PLCstate == STOPPED){
      configFirmwareEnabled = 1;
    }
    else if(configFirmwareEnabled){
      configFirmwareEnabled = 0;
    }
    else{
      messageCode = MESSAGE_OTA_NOT_POSSIBLE;
      HMI_PageMemory = HMI_Page;
      HMI_Page = PAGE_DialogMessage;
    }
    drawFirmwareEnableButton();
    drawFirmwareStatusBar();
  }
  // Cancel button
  else if(ts_y > FIRMWARE_CANCEL_Y){
    configFirmwareEnabled = 0;
    //HMI_Page = PAGE_ConfigPLC; // To be used when full navigation is implemented for this menu
    HMI_Page = PAGE_MainConfig;
  }
}

