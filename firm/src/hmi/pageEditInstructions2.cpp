#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
//Ladder Details main Page
//--------------------------------------------------------------------------------

void pageEditLadderInstructions2 (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawEditLadderInstructions2();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchEditLadderInstructionsNavigation(ts_x, ts_y);
    touchEditLadderInstructions2(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Edit Ladder Instructions Page full draw 
//--------------------------------------------------------------------------------

void drawEditLadderInstructions2 (void){
  tft.fillScreen(COLOR_LADDER_INSTRUC_BACKGROUND);
  drawLadderEditorInstructionsNavigation();

  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Edit Instructions 2");
}

//--------------------------------------------------------------------------------
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchEditLadderInstructions2(uint16_t ts_x, uint16_t ts_y){

}