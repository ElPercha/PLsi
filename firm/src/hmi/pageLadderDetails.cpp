// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
//Ladder Details main Page
//--------------------------------------------------------------------------------

void pageLadderDetails (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawLadderDetails();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchLadderDetails(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Ladder Details Page full draw 
//--------------------------------------------------------------------------------

void drawLadderDetails (void){
  tft.fillScreen(TFT_ORANGE);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Ladder Details on Instructions");
}

//--------------------------------------------------------------------------------
// Ladder Details Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchLadderDetails(uint16_t ts_x, uint16_t ts_y){
  hmiPage = hmiPageMemory;
}