#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
//Ladder Details main Page
//--------------------------------------------------------------------------------

void pageEditLadderInstructions3 (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawEditLadderInstructions3();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchEditLadderInstructions3(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Edit Ladder Instructions Page full draw 
//--------------------------------------------------------------------------------

void drawEditLadderInstructions3 (void){
  tft.fillScreen(TFT_GOLD);
  tft.setTextColor(BLACK);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Edit Instructions 3");
}

//--------------------------------------------------------------------------------
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchEditLadderInstructions3(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_LadderEditor;
}