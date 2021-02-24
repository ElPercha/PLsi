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