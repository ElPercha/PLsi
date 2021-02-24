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
// PLC Configuration Page
//--------------------------------------------------------------------------------

void pageConfigProgram (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigProgram();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigProgram(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// PLC Configuration - Program selection draw 
//--------------------------------------------------------------------------------

void drawConfigProgram (void){
  #define PROGRAM_BUTTON_ROW          2
  #define PROGRAM_BUTTON_COL          2          
  #define PROGRAM_BUTTON_SPACE        5           
  #define PROGRAM_BUTTON_Y            20
  #define PROGRAM_BUTTON_W           (TFT_PIXELS_X - (PROGRAM_BUTTON_SPACE * (PROGRAM_BUTTON_COL + 1))) / PROGRAM_BUTTON_COL
  #define PROGRAM_BUTTON_H           (TFT_PIXELS_Y - PROGRAM_BUTTON_Y - (PROGRAM_BUTTON_SPACE * (PROGRAM_BUTTON_ROW + 1))) / PROGRAM_BUTTON_ROW

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setFreeFont(FSS9);
  tft.drawCentreString("Select Program to Excecute", TFT_PIXELS_X/2, 3, GFXFF);

  for (uint16_t row = 0; row < PROGRAM_BUTTON_ROW; row++){
    for (uint16_t col = 0; col < PROGRAM_BUTTON_COL; col++){
      uint16_t i = col + row * PROGRAM_BUTTON_COL;
      uint16_t x = PROGRAM_BUTTON_SPACE + col * (PROGRAM_BUTTON_W + PROGRAM_BUTTON_SPACE);
      uint16_t y = PROGRAM_BUTTON_SPACE + row * (PROGRAM_BUTTON_H + PROGRAM_BUTTON_SPACE) + PROGRAM_BUTTON_Y;
      uint16_t color;

      if (settings.ladder.UserProgram == i){
        color = TFT_DARKGREEN;
      }
      else{
        color = CYANL;
      }

      tft.fillRoundRect(x, y, PROGRAM_BUTTON_W, PROGRAM_BUTTON_H, 10, color);

      String str = FILENAME_USER_PROGRAMS[i];
      str = str.substring(1, str.length());
      tft.drawCentreString(str, x + PROGRAM_BUTTON_W/2, y + PROGRAM_BUTTON_H/2 - 10, GFXFF);
    }
  }
  tft.setTextFont(1);
}

//--------------------------------------------------------------------------------
// PLC configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigProgram(uint16_t ts_x, uint16_t ts_y){
  uint16_t selectedProgram = 0;  
  
  if (ts_x < TFT_PIXELS_X/2){
    if (ts_y < TFT_PIXELS_Y/2 + PROGRAM_BUTTON_Y){
      selectedProgram = 0;
    }
    else{
      selectedProgram = 2;
    }
  }
  else{
    if (ts_y < TFT_PIXELS_Y/2 + PROGRAM_BUTTON_Y){
      selectedProgram = 1;
    }
    else{
      selectedProgram = 3;
    }
  }

  if(selectedProgram == settings.ladder.UserProgram){
    hmiPage = PAGE_MainConfig;
  }
  else if (settings.ladder.PLCstate != STOPPED){
      messageCode = MESSAGE_PLC_MUST_BE_IN_STOP;
      hmiPageMemory = hmiPage;
      hmiPage = PAGE_DialogMessage;
  }
  else{
    settings.ladder.UserProgram = selectedProgram;
    drawConfigProgram();
    saveSettings();
    loadSelectedProgram = 1;
    delay(500); // For user to see that program has been changed (turns green)
    hmiPage = PAGE_MainConfig;
  }
}

