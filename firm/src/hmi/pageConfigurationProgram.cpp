#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// PLC Configuration Page
//--------------------------------------------------------------------------------

void pageConfigProgram (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
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

  if (touchType){
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
    HMI_Page = PAGE_MainConfig;
  }
  else if (settings.ladder.PLCstate != STOPPED){
      messageCode = MESSAGE_PLC_MUST_BE_IN_STOP;
      HMI_PageMemory = HMI_Page;
      HMI_Page = PAGE_DialogMessage;
  }
  else{
    settings.ladder.UserProgram = selectedProgram;
    drawConfigPLC();
    saveSettings();
    loadSelectedProgram = 1;
    delay(500); // For user to see that program has been changed (turns green)
    HMI_Page = PAGE_MainConfig;
  }
}

