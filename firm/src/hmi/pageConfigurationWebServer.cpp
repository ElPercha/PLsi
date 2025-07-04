// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// WebServer Main Configuration Page
//--------------------------------------------------------------------------------

void pageConfigWebServer (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigWebServer ();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigWebServer(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// WebServer Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigWebServer (void){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("WebServer config");
  tft.setCursor(10, 30);
  tft.print("not yet available!");
}

//--------------------------------------------------------------------------------
// WebServer configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigWebServer(uint16_t ts_x, uint16_t ts_y){
  hmiPage = PAGE_ConfigNetwork;
}

