#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <buttons.h>

//--------------------------------------------------------------------------------
// HMI Menu main Page
//--------------------------------------------------------------------------------

void pageMainHMI (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  
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

  if (touchType == HMI_TOUCHED){
    touchMainHMIpress(ts_x, ts_y); 
  } 
  if (touchType == HMI_RELEASED){
    touchMainHMIrelease(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Main Configuration Page full draw 
//--------------------------------------------------------------------------------

void drawMainHMI (void){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE2);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  //tft.print("HMI soon :)");

  tft.setSwapBytes(true);

  uint8_t i = 0;
  for (uint8_t r = 1; r < 3; r++){
    for (uint8_t c = 0; c < 4; c++){
      i = c + (r-1)*4; 
      if (!button[i]){
        tft.pushImage(8 + c*80, 8 + r*80, 64, 64, iconRed64_on);
      }
      else
      {
        tft.pushImage(8 + c*80, 8 + r*80, 64, 64, iconGreen64_on);
      }
    }
  }
}

//--------------------------------------------------------------------------------
// Main HMI Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchMainHMIpress(uint16_t ts_x, uint16_t ts_y){

  if(ts_y < 80){
    HMI_Page = 0;
  }
  else if(ts_y < 160){
    if(ts_x > 240){
      button[3] = 1;
    }
    else if(ts_x > 160){
      button[2] = 1;
    }
    else if(ts_x > 80){
      button[1] = 1;
    }
    else{
      button[0] = 1;
    }
  }
  else{
    if(ts_x > 240){
      button[7] = 1;
    }
    else if(ts_x > 160){
      button[6] = 1;
    }
    else if(ts_x > 80){
      button[5] = 1;
    }
    else{
      button[4] = 1;
    }
  }
  drawMainHMI();

  M[0] = button[0];
  M[1] = button[1];
  M[2] = button[2];
  M[3] = button[3];
  M[4] = button[4];
  M[5] = button[5];
  M[6] = button[6];
  M[7] = button[7];
}
void touchMainHMIrelease(uint16_t ts_x, uint16_t ts_y){

  if(ts_y < 80){
    HMI_Page = 0;
  }
  else if(ts_y < 160){
    if(ts_x > 240){
      button[3] = 0;
    }
    else if(ts_x > 160){
      button[2] = 0;
    }
    else if(ts_x > 80){
      button[1] = 0;
    }
    else{
      button[0] = 0;
    }
  }
  else{
    if(ts_x > 240){
      button[7] = 0;
    }
    else if(ts_x > 160){
      button[6] = 0;
    }
    else if(ts_x > 80){
      button[5] = 0;
    }
    else{
      button[4] = 0;
    }
  }
  drawMainHMI();

  M[0] = button[0];
  M[1] = button[1];
  M[2] = button[2];
  M[3] = button[3];
  M[4] = button[4];
  M[5] = button[5];
  M[6] = button[6];
  M[7] = button[7];
}
