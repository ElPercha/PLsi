#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs page
//--------------------------------------------------------------------------------

void pageScanWiFi (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawScanWiFi();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchScanWiFi(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs draw 
//--------------------------------------------------------------------------------

void drawScanWiFi (void){
  tft.fillScreen(YELLOW);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("Scanning for SSIDs");
}

//--------------------------------------------------------------------------------
// WiFi Scanning SSIDs page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchScanWiFi(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_ConfigNetwork;
}

