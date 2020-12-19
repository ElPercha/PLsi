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

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigNetwork(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Network Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigNetwork (void){

}

//--------------------------------------------------------------------------------
// Network configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigNetwork(uint16_t ts_x, uint16_t ts_y){

}
