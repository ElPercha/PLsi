// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Configuration Menu Page
//--------------------------------------------------------------------------------

void pageMainConfig (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawMainConfig();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchMainConfig(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Main Configuration Page full draw 
//--------------------------------------------------------------------------------

void drawMainConfig (void){
  #define CONFIG_BUTTON_ROW          3
  #define CONFIG_BUTTON_COL          2          
  #define CONFIG_BUTTON_SPACE        5           
  #define CONFIG_BUTTON_W           (TFT_PIXELS_X - (CONFIG_BUTTON_SPACE * (CONFIG_BUTTON_COL + 1))) / CONFIG_BUTTON_COL
  #define CONFIG_BUTTON_H           (TFT_PIXELS_Y - (CONFIG_BUTTON_SPACE * (CONFIG_BUTTON_ROW + 1))) / CONFIG_BUTTON_ROW

  const String configLabels[6] = {"PLC","HMI","I/O","Network","System","Home"};

  tft.fillScreen(COLOR_CONFIG_MAIN_BACK);
  tft.setTextSize(1);
  tft.setTextColor(COLOR_CONFIG_MAIN_TEXT);

  for (uint16_t row = 0; row < CONFIG_BUTTON_ROW; row++){
    for (uint16_t col = 0; col < CONFIG_BUTTON_COL; col++){
      uint16_t i = col + row * CONFIG_BUTTON_COL;
      uint16_t x = CONFIG_BUTTON_SPACE + col * (CONFIG_BUTTON_W + CONFIG_BUTTON_SPACE);
      uint16_t y = CONFIG_BUTTON_SPACE + row * (CONFIG_BUTTON_H + CONFIG_BUTTON_SPACE);
      
      tft.drawRoundRect(x, y, CONFIG_BUTTON_W, CONFIG_BUTTON_H, 10, COLOR_CONFIG_MAIN_BORDER);

      tft.setFreeFont(FSS12);
      tft.drawCentreString(configLabels[i], x + CONFIG_BUTTON_W/2, y + 28, GFXFF);
    }
  }
  tft.setTextFont(1);
}

//--------------------------------------------------------------------------------
// Main Configuration Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchMainConfig(uint16_t ts_x, uint16_t ts_y){
  if(ts_y < 80){
    if(ts_x < 160){
      //hmiPage = PAGE_ConfigPLC;      
      hmiPage = PAGE_ConfigProgram;      
    }
    else{
      hmiPage = PAGE_ConfigHMI;      
    }
  }
  else if(ts_y < 160){
    if(ts_x < 160){
      //hmiPage = PAGE_ConfigIO;      
      hmiPage = PAGE_ConfigIOlocal;      
    }
    else{
      hmiPage = PAGE_ConfigNetwork;
      //hmiPage = PAGE_ConfigWiFi;
    }
  }
  else{
    if(ts_x < 160){
      //hmiPage = PAGE_ConfigSystem;      
      hmiPage = PAGE_ConfigFirmware;      
    }
    else{
      hmiPage = PAGE_MainMenu;
    }
  }
}