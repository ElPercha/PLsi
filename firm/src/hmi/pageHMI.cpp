#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// HMI Menu main Page
//--------------------------------------------------------------------------------

void pageMainHMI (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawMainHMI();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchMainHMI(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Main Configuration Page full draw 
//--------------------------------------------------------------------------------

void drawMainHMI (void){
  tft.fillScreen(YELLOW);
  tft.setTextColor(BLACK);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("HMI soon :)");
}

//--------------------------------------------------------------------------------
// Main HMI Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchMainHMI(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = 0;
}
