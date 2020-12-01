#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <buttons.h>

//--------------------------------------------------------------------------------
// HMI Menu main Page
//--------------------------------------------------------------------------------

void pageMainHMI (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
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

  if (touchType){
    touchMainHMI(ts_x, ts_y); 
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

  uint8_t toggle = 0;
  uint8_t i = 0;

  for (uint8_t r = 1; r < 3; r++){
    for (uint8_t c = 0; c < 4; c++){
      i = c + (r-1)*4; 

      toggle = !toggle;
      if(toggle){
        if (button[i]){
          tft.pushImage(8 + c*80, 8 + r*80, 64, 64, iconRed64_on);
        }
        else
        {
          tft.pushImage(8 + c*80, 8 + r*80, 64, 64, iconRed64_off);
        }
      }
      else{
        if (button[i]){
          tft.pushImage(8 + c*80, 8 + r*80, 64, 64, iconGreen64_on);
        }
        else
        {
          tft.pushImage(8 + c*80, 8 + r*80, 64, 64, iconGreen64_off);
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------
// Main HMI Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchMainHMI(uint16_t ts_x, uint16_t ts_y){

  if(ts_y < 80){
    HMI_Page = 0;
  }
  else if(ts_y < 160){
    if(ts_x > 240){
      button[3] = !button[3];
    }
    else if(ts_x > 160){
      button[2] = !button[2];
    }
    else if(ts_x > 80){
      button[1] = !button[1];
    }
    else{
      button[0] = !button[0];
    }
  }
  else{
    if(ts_x > 240){
      button[7] = !button[7];
    }
    else if(ts_x > 160){
      button[6] = !button[6];
    }
    else if(ts_x > 80){
      button[5] = !button[5];
    }
    else{
      button[4] = !button[4];
    }
  }
  drawMainHMI();
}
