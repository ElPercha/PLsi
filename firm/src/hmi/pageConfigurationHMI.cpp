#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// HMI Configuration Page
//--------------------------------------------------------------------------------

void pageConfigHMI (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigHMI();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigHMI(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// HMI Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigHMI (void){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("HMI config");
  tft.setCursor(10, 30);
  tft.print("not yet available!");
}

//--------------------------------------------------------------------------------
// HMI configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigHMI(uint16_t ts_x, uint16_t ts_y){
  hmiPage = PAGE_MainConfig;
}

