// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// ModbusTCP Main Configuration Page
//--------------------------------------------------------------------------------

void pageConfigModbusTCP (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigModbusTCP();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigModbusTCP(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Modbus TCP Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigModbusTCP (void){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("Modbus TCP config");
  tft.setCursor(10, 30);
  tft.print("not yet available!");
}

//--------------------------------------------------------------------------------
// Modbus TCP configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigModbusTCP(uint16_t ts_x, uint16_t ts_y){
  hmiPage = PAGE_ConfigNetwork;
}

