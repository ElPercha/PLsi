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

void pageEditLadderInstructions2 (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{

  //-------------------------------
  // capture input Value command
  //-------------------------------

  if (numericValueAccepted){
    if(instructionFieldSelection == 1){
      // Validate that the Memory address is in a valid range for the given Type
      if (uint16_t(numericValue) <= getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type)){
        editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data = uint16_t(numericValue);
      } 
    }
    else if(instructionFieldSelection == 2){
      if (uint16_t(numericValue) <= 32767){
        editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Data = uint16_t(numericValue);
      } 
    }
    numericValueAccepted = 0;
  }

  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      // Define if it is a Timer or Counter 
      // Preload the Data Type for Timer or Counter
      if (editingInstructionCode == TON || editingInstructionCode == TOFF || editingInstructionCode == TP){
        timerSelected = 1;
        editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeT;
      }
      else{ // is Counter
        timerSelected = 0;
        editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeC;
      }

      // Validate that the Memory address is in a valid range for the given Type
      if (editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data > getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type)){
        editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data = getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type);
      } 

      drawEditLadderInstructions2();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchEditLadderInstructionsNavigation(ts_x, ts_y);
    touchEditLadderInstructions2(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Edit Ladder Instructions Page full draw 
//--------------------------------------------------------------------------------

void drawEditLadderInstructions2 (void){
  #define TIMER_BORDER      5
  #define TIMER_H         175
  #define TIMER_W         170 
 
  #define TIMER_TEXT       11
  #define TIMER_BUTTON_Y   30
  #define TIMER_BUTTON_H   45
  #define TIMER_BUTTON_W  160

  //clear the screen and draw the buttons at bottom of page
  tft.fillScreen(COLOR_LADDER_INSTRUC_BACKGROUND);
  drawLadderEditorInstructionsNavigation();

  // Print base rectangle "Instruction box"
  tft.fillRoundRect(TFT_PIXELS_X/2-TIMER_W/2, TIMER_BORDER, TIMER_W, TIMER_H, 8, COLOR_TIMER_EDITION);
  
  // Print Header - Instruction Mnemonic
  tft.setTextColor(COLOR_TIMER_EDITION_TEXT);
  tft.setTextSize(2);
  String auxString = MnemonicsCodes[editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code];
  tft.setCursor(TFT_PIXELS_X/2 - auxString.length()*6, TIMER_TEXT);
  tft.print(auxString);

  // Draw first Field
  updateTimerCounterNumber();
  
  // Draw second Field
  updateTimerCounterSetPoint();

  // Draw third Field
  if (timerSelected){
    updateTimerBaseTime();
  } 
  else{
    updateCounterField();
  }
}

//--------------------------------------------------------------------------------
// Update Timer Base Time 
//--------------------------------------------------------------------------------

void updateTimerBaseTime(void){
  uint16_t indexTimer = 10;
  for (uint16_t i = 0; i < 5; i++){
    if (editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type == timerBaseTime[i]){
      indexTimer = i;
    }
  }
  if (indexTimer == 10){
    editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type = timerBaseTime[3]; // Default to Seconds
    indexTimer = 3;
  }

  tft.fillRoundRect(TFT_PIXELS_X/2-TIMER_BUTTON_W/2, TIMER_BUTTON_Y + (TIMER_BORDER+TIMER_BUTTON_H)*2, TIMER_BUTTON_W, TIMER_BUTTON_H, 8, COLOR_TIMER_FIELDS);

  tft.setTextSize(3);
  tft.setTextColor(COLOR_TIMER_COUNTER_TEXT);
  String auxString = timerBaseTimeText[indexTimer];
  tft.setCursor(TFT_PIXELS_X/2 - auxString.length() * 9, TIMER_BUTTON_Y + (TIMER_BORDER+TIMER_BUTTON_H)*2 + 15);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Print "counts when instruction is a counter
//--------------------------------------------------------------------------------

void updateCounterField(void){
  tft.fillRoundRect(TFT_PIXELS_X/2-TIMER_BUTTON_W/2, TIMER_BUTTON_Y + (TIMER_BORDER+TIMER_BUTTON_H)*2, TIMER_BUTTON_W, TIMER_BUTTON_H, 8, COLOR_TIMER_FIELDS);

  tft.setTextSize(3);
  tft.setTextColor(COLOR_TIMER_COUNTER_TEXT);
  tft.setCursor(TFT_PIXELS_X/2 - 6 * 9, TIMER_BUTTON_Y + (TIMER_BORDER+TIMER_BUTTON_H)*2 + 15);
  tft.print("counts");
}

//--------------------------------------------------------------------------------
// Update first field with Number of Timer
//--------------------------------------------------------------------------------

void updateTimerCounterNumber(void){
  //String auxString;
  tft.fillRoundRect(TFT_PIXELS_X/2-TIMER_BUTTON_W/2, TIMER_BUTTON_Y , TIMER_BUTTON_W, TIMER_BUTTON_H, 8, COLOR_TIMER_FIELDS);

  tft.setTextSize(3);
  tft.setTextColor(COLOR_TIMER_COUNTER_TEXT);
  String auxString = MnemonicsTypes[editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type] + String(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data);
  tft.setCursor(TFT_PIXELS_X/2 - auxString.length() * 9, TIMER_BUTTON_Y + 15);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Update second field with SetPoint for Timer or Counter
//--------------------------------------------------------------------------------

void updateTimerCounterSetPoint(void){
  tft.fillRoundRect(TFT_PIXELS_X/2-TIMER_BUTTON_W/2, TIMER_BUTTON_Y + TIMER_BORDER+TIMER_BUTTON_H, TIMER_BUTTON_W, TIMER_BUTTON_H, 8, COLOR_TIMER_FIELDS);

  tft.setTextSize(3);
  tft.setTextColor(COLOR_TIMER_COUNTER_TEXT);
  String auxString = String(editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Data);
  tft.setCursor(TFT_PIXELS_X/2 - auxString.length() * 9, TIMER_BUTTON_Y + TIMER_BORDER+TIMER_BUTTON_H + 15);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchEditLadderInstructions2(uint16_t ts_x, uint16_t ts_y){
  if (ts_y < TIMER_BUTTON_Y + TIMER_BORDER+TIMER_BUTTON_H){
    instructionFieldSelection = 1;
    updateTimerCounterNumber();
    hmiPageMemory = hmiPage;  
    hmiPage = PAGE_InputNumber;
  }
  else if (ts_y < TIMER_BUTTON_Y + (TIMER_BORDER+TIMER_BUTTON_H)*2){
    instructionFieldSelection = 2;
    updateTimerCounterSetPoint();
    hmiPageMemory = hmiPage;  
    hmiPage = PAGE_InputNumber;
  }
  else if (ts_y < TIMER_BUTTON_Y + (TIMER_BORDER+TIMER_BUTTON_H)*3){ // Only for timers
    if (timerSelected){
      changeTimerBaseTime();
      updateTimerBaseTime();
    } 
  }
}






