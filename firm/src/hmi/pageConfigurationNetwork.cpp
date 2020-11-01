#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Network Configuration Page
//--------------------------------------------------------------------------------

void pageConfigNetwork (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigNetwork();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchConfigNetwork(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Network Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigNetwork (void){
  tft.fillScreen(MAGENTA);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("NETWORKS !");
}

//--------------------------------------------------------------------------------
// Network configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigNetwork(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_MainConfig;
}

