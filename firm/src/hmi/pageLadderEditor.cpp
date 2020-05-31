#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
//Ladder Editor main Page
//--------------------------------------------------------------------------------

void pageLadderEditor (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawLadderEditor();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchLadderEditor(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Ladder Editor Page full draw 
//--------------------------------------------------------------------------------

void drawLadderEditor (void){
  tft.fillScreen(TFT_OLIVE);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Ladder Editor!");
}

//--------------------------------------------------------------------------------
// Ladder Editor Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchLadderEditor(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = 0;
}