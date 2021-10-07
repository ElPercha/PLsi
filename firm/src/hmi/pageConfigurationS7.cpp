/*
Copyright (c) 2019 Prieto Lucas. All rights reserved.
This file is part of the PLsi project.

PLsi is free software and hardware: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
PLsi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// ModbusTCP Main Configuration Page
//--------------------------------------------------------------------------------

void pageConfigS7 (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigS7();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigS7(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// S7 Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigS7 (void){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("S7 config");
  tft.setCursor(10, 30);
  tft.print("not yet available!");
}

//--------------------------------------------------------------------------------
// S7 configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigS7(uint16_t ts_x, uint16_t ts_y){
  hmiPage = PAGE_ConfigNetwork;
}

