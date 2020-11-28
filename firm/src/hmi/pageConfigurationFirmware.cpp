#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// System Configuration Page Firmware Upgrade
//--------------------------------------------------------------------------------

void pageConfigFirmware (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigFirmware();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchConfigFirmware(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// System Configuration firmware Upgrade draw 
//--------------------------------------------------------------------------------

void drawConfigFirmware (void){
  tft.fillScreen(MAGENTA);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Update Firmware");
}

//--------------------------------------------------------------------------------
// System configuration page - Firmware Update
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigFirmware(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_MainConfig;
}

