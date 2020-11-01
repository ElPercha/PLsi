#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// IO Configuration Page
//--------------------------------------------------------------------------------

void pageConfigIO (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // Draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigIO();
    }
    
  //-------------------------------
  // Update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchConfigIO(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// IO Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigIO (void){
  tft.fillScreen(MAGENTA);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("IO !");
}

//--------------------------------------------------------------------------------
// IO configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigIO(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_MainConfig;
}

