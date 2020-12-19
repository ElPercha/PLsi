#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// System Configuration Page
//--------------------------------------------------------------------------------

void pageConfigSystem (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigSystem();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigSystem(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// System Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigSystem (void){
  tft.fillScreen(MAGENTA);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("System !");
}

//--------------------------------------------------------------------------------
// System configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigSystem(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_MainConfig;
}

