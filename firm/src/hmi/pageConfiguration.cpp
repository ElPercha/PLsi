#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Configuration Menu Page
//--------------------------------------------------------------------------------

void pageMainConfig (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawMainConfig();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchMainConfig(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Main Configuration Page full draw 
//--------------------------------------------------------------------------------

void drawMainConfig (void){
  tft.fillScreen(MAGENTA);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("CONFIG coming!");
}

//--------------------------------------------------------------------------------
// Main Configuration Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchMainConfig(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = 0;
}