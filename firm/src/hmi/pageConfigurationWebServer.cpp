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

