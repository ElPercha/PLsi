#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Input Number Page display (Numeric Keyboard)
//--------------------------------------------------------------------------------

void pageInputNumber(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawNumericKeyboard();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchInputNumber(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Main Configuration Page full draw 
//--------------------------------------------------------------------------------

void drawNumericKeyboard (void){
  tft.fillScreen(MAGENTA);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("NUMERIC KEYBOARD ALMOST");
}

//--------------------------------------------------------------------------------
// Main Configuration Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchInputNumber(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = 0;
}