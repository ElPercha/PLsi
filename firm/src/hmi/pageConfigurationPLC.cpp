#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// PLC Configuration Page
//--------------------------------------------------------------------------------

void pageConfigPLC (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawConfigPLC();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchConfigPLC(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// PLC Configuration Menu
//--------------------------------------------------------------------------------

void drawConfigPLC (void){
}

//--------------------------------------------------------------------------------
// PLC configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigPLC(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = PAGE_MainMenu;

}

