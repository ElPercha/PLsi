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
      tft.fillScreen(COLOR_HMI_BACK);
      drawHMImenu();
      drawHMImatrix();
      hmiPageLoaded = 0;
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_IDLE){
    hmiPageLoaded = 1; // To avoid any action when user keep pressing the touch and release once the page is loaded
  }

  if (touchType == HMI_TOUCHED){
    touchHMImenu(ts_x, ts_y);
    touchHMImatrix(ts_x, ts_y, 1); 
  } 
  if (hmiPageLoaded && touchType == HMI_RELEASED){
    touchHMImatrix(ts_x, ts_y, 0); 
  } 
}

//--------------------------------------------------------------------------------
// HMI top menu
//--------------------------------------------------------------------------------

void drawHMImenu(void){
  String hmiMenu[HMI_MENU_BUT-1] = {"SW", "BUT", "POT", "STAT", "LEDS"};

  tft.setTextColor(COLOR_HMI_FONT);
  tft.setTextFont(1);
  tft.setTextSize(1);

  for (uint16_t i = 0; i < HMI_MENU_BUT; i++){
    tft.fillRect(HMI_MENU_W*i, 0, HMI_MENU_W, HMI_MENU_H, DARKGREY);
    tft.drawRect(HMI_MENU_W*i, 0, HMI_MENU_W, HMI_MENU_H, TFT_WHITE);

    if (i == 0){
      drawHomeIcon();
    }
    else{
      tft.drawCentreString(hmiMenu[i-1], HMI_MENU_W*i + HMI_MENU_W/2, 12, HMI_FONT_SIZE);
    }
  }
}

//--------------------------------------------------------------------------------
// HMI draw of 5 "non editable" pages + title
//--------------------------------------------------------------------------------

void drawHMImatrix (void){
  tft.fillRect(0, HMI_MENU_H, TFT_PIXELS_X, TFT_PIXELS_Y - HMI_MENU_H, COLOR_HMI_BACK);

  // Draw HMI title  
  String hmiTitle[HMI_MENU_BUT-1] = {"SWITCHES", "BUTTONS", "INPUT ANALOG VALUES", "ANALOG STATUS", "DIGITAL STATUS"};
  tft.drawCentreString(hmiTitle[hmiPageUser], TFT_PIXELS_X/2, HMI_MENU_H + 12, HMI_FONT_SIZE);

  // 8 buttons (size 4x4) non retentive 
  if (hmiPageUser == 0){
    for (uint8_t r = 0; r < 2; r++){
      for (uint8_t c = 0; c < 4; c++){
        drawHMIbutton(c*2, r*2, 1, button[c + r*4]);
        drawHMIbuttonText(c*2, r*2, "M"+ String (c + r*4));
      }
    }
  }
  
  // 8 buttons (size 4x4) retentive or switches
  else if (hmiPageUser == 1){
    
  }
  
  // 8 indicators (size 1x4) 32 x 32 pixels indicator + text
  else if (hmiPageUser == 2){
    
  }
  
  // 4 analog potentiometers
  else if (hmiPageUser == 3){
  
  }
  
  // 8 analog indicators (1 x 4) + text 
  else if (hmiPageUser == 4){
    
  }
}

//--------------------------------------------------------------------------------
// HMI Menu Touch Screen parsing
//--------------------------------------------------------------------------------

void touchHMImenu (uint16_t ts_x, uint16_t ts_y){
  if(ts_y < HMI_MENU_H){
    for (uint16_t i = 0; i < HMI_MENU_BUT; i++){
      if (ts_x > i * HMI_MENU_W && ts_x <= (i + 1) * HMI_MENU_W){
        if (i == 0){
          hmiPage = PAGE_MainMenu;
        }
        else{
          hmiPageUser = i - 1;
          drawHMImatrix();
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------
// HMI Touch Screen parsing of 5 "non editable" pages + menu
//--------------------------------------------------------------------------------

void touchHMImatrix(uint16_t ts_x, uint16_t ts_y, uint16_t value){

  if(ts_y >= HMI_SLOTS_Y && ts_y < 160){
    if(ts_x > 240){
      button[3] = value;
      drawHMIbutton(6, 0, 1, value);
    }
    else if(ts_x > 160){
      button[2] = value;
      drawHMIbutton(4, 0, 1, value);
    }
    else if(ts_x > 80){
      button[1] = value;
      drawHMIbutton(2, 0, 1, value);
    }
    else{
      button[0] = value;
      drawHMIbutton(0, 0, 1, value);
    }
  }
  else if(ts_y >= HMI_SLOTS_Y && ts_y < 240){
    if(ts_x > 240){
      button[7] = value;
      drawHMIbutton(6, 2, 1, value+2);
    }
    else if(ts_x > 160){
      button[6] = value;
      drawHMIbutton(4, 2, 1, value+2);
    }
    else if(ts_x > 80){
      button[5] = value;
      drawHMIbutton(2, 2, 1, value+2);
    }
    else{
      button[4] = value;
      drawHMIbutton(0, 2, 1, value+2);
    }
  }

  M[0] = button[0];
  M[1] = button[1];
  M[2] = button[2];
  M[3] = button[3];
  M[4] = button[4];
  M[5] = button[5];
  M[6] = button[6];
  M[7] = button[7];
}
