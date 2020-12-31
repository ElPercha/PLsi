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
  // capture input Value command
  //-------------------------------

  if (numericValueAccepted){
    D[settings.hmi.potentiometersIndex + hmiEditionIndex] = int16_t(numericValue);
    numericValueAccepted = 0;
  }

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

  if (millis() - timerRefreshHMI > 500){

    // Update Switches
    if (hmiPageUser == 0){
      for (uint8_t r = 0; r < 2; r++){
        for (uint8_t c = 0; c < 4; c++){
          drawHMIbutton(c*2, r*2, 1, M[settings.hmi.switchesIndex + c + r*4]);
        }
      }
    }

    // Update buttons
    if (hmiPageUser == 1){
      for (uint8_t r = 0; r < 2; r++){
        for (uint8_t c = 0; c < 4; c++){
          drawHMIbutton(c*2, r*2, 1, M[settings.hmi.buttonsIndex + c + r*4] + 2);
        }
      }
    }

    // Update analog potentiometers 
    if (hmiPageUser == 2){
      for (uint8_t r = 0; r < 2; r++){
        for (uint8_t c = 0; c < 4; c++){
          drawHMIAnalogIndicator(c*2, r*2, 0, double(D[settings.hmi.potentiometersIndex + c + r*4]));
        }
      }
    }

    // Update analog indicators 
    if (hmiPageUser == 3){
      for (uint8_t r = 0; r < 2; r++){
        for (uint8_t c = 0; c < 4; c++){
          drawHMIAnalogIndicator(c*2, r*2, 1, double(D[settings.hmi.analogIndicatorsIndex + c + r*4]));
        }
      }
    }

    // Update digital indicators (Leds)
    if (hmiPageUser == 4){
      for (uint8_t r = 0; r < 4; r++){
        for (uint8_t c = 0; c < 2; c++){
          drawHMIbutton(c*4, r, 0, M[settings.hmi.digitalIndicatorsIndex + c + r*2]);
        }
      }
    }
    timerRefreshHMI = millis();
  }


  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_IDLE){
    hmiPageLoaded = 1; // To avoid any action when user keep pressing the touch and release once the page is loaded
  }
  if (ts_y <= HMI_MENU_H && touchType == HMI_TOUCHED){
    touchHMImenu(ts_x, ts_y);
  } 
  if (ts_y >= HMI_SLOTS_Y && hmiPageLoaded && touchType){
    touchHMImatrix(ts_x, ts_y, touchType); 
  }
}

//--------------------------------------------------------------------------------
// HMI top menu
//--------------------------------------------------------------------------------

void drawHMImenu(void){
  String hmiMenu[HMI_MENU_BUT-1] = {"SWI", "BUT", "POT", "STAT", "LEDS"};

  tft.setTextColor(COLOR_HMI_FONT);
  tft.setTextFont(1);
  tft.setTextSize(1);

  for (uint16_t i = 0; i < HMI_MENU_BUT; i++){
    tft.fillRect(HMI_MENU_W*i, 0, HMI_MENU_W, HMI_MENU_H, COLOR_HMI_MENU_BUTTON);
    tft.drawRect(HMI_MENU_W*i, 0, HMI_MENU_W, HMI_MENU_H, COLOR_HMI_MENU_BORDER);

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
  tft.setTextColor(COLOR_HMI_FONT_TITLE_COLOR);
  tft.setTextFont(1);
  tft.setTextSize(1);
  String hmiTitle[HMI_MENU_BUT-1] = {"SWITCHES", "BUTTONS", "INPUT VALUES", "ANALOG STATUS", "DIGITAL STATUS"};
  tft.drawCentreString(hmiTitle[hmiPageUser], TFT_PIXELS_X/2, HMI_MENU_H + 8, HMI_FONT_TITLE);

  // 8 switches (size 2x2) retentive 
  if (hmiPageUser == 0){
    for (uint8_t r = 0; r < 2; r++){
      for (uint8_t c = 0; c < 4; c++){
        drawHMIbutton(c*2, r*2, 1, M[settings.hmi.switchesIndex + c + r*4]);
        drawHMIbuttonText(c*2, r*2, 1, "M" + String (settings.hmi.switchesIndex + c + r*4));
      }
    }
  }
  
  // 8 buttons (size 2x2) non retentive
  else if (hmiPageUser == 1){
    for (uint8_t r = 0; r < 2; r++){
      for (uint8_t c = 0; c < 4; c++){
        drawHMIbutton(c*2, r*2, 1, M[settings.hmi.buttonsIndex + c + r*4] + 2);
        drawHMIbuttonText(c*2, r*2, 1, "M"+ String (settings.hmi.buttonsIndex + c + r*4));
      }
    }
  }
  
  // 4 analog potentiometers
  else if (hmiPageUser == 2){
    for (uint8_t r = 0; r < 2; r++){
      for (uint8_t c = 0; c < 4; c++){
        drawHMIbuttonText(c*2, r*2, 1, "D"+ String (settings.hmi.potentiometersIndex + c + r*4));
        drawHMIAnalogIndicator(c*2, r*2, 0, double(D[settings.hmi.potentiometersIndex + c + r*4]));
      }
    }
  }
  
  // 8 analog indicators (2 x 2) + text 
  else if (hmiPageUser == 3){
    for (uint8_t r = 0; r < 2; r++){
      for (uint8_t c = 0; c < 4; c++){
        drawHMIbuttonText(c*2, r*2, 1, "D"+ String (settings.hmi.analogIndicatorsIndex + c + r*4));
        drawHMIAnalogIndicator(c*2, r*2, 1, double(D[settings.hmi.analogIndicatorsIndex + c + r*4]));
      }
    }
  }
  
  // 8 indicators (size 1x4) 32 x 32 pixels indicator + text
  else if (hmiPageUser == 4){
    for (uint8_t r = 0; r < 4; r++){
      for (uint8_t c = 0; c < 2; c++){
        drawHMIbutton(c*4, r, 0, M[settings.hmi.digitalIndicatorsIndex + c + r*2]);
        drawHMIbuttonText(c*4 + 1, r, 0, "M"+ String (settings.hmi.digitalIndicatorsIndex + c + r*2));
      }
    }
  }
}

//--------------------------------------------------------------------------------
// HMI Menu Touch Screen parsing
//--------------------------------------------------------------------------------

void touchHMImenu (uint16_t ts_x, uint16_t ts_y){
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

//--------------------------------------------------------------------------------
// HMI Touch Screen parsing of 5 "non editable" pages + menu
//--------------------------------------------------------------------------------

void touchHMImatrix (uint16_t ts_x, uint16_t ts_y, uint16_t touchType){
  uint16_t column = 0, row = 0, index = 0;

  // Defime column, row and index of the touch event
  if (ts_y < 160){
    if(ts_x > 240){
      column = 6;
      row = 0;
      index = 3;
    }
    else if(ts_x > 160){
      column = 4;
      row = 0;
      index = 2;
    }
    else if(ts_x > 80){
      column = 2;
      row = 0;
      index = 1;
    }
    else{
      column = 0;
      row = 0;
      index = 0;
    }
  }
  else if (ts_y < 240){
    if(ts_x > 240){
      column = 6;
      row = 2;
      index = 7;
    }
    else if(ts_x > 160){
      column = 4;
      row = 2;
      index = 6;
    }
    else if(ts_x > 80){
      column = 2;
      row = 2;
      index = 5;
    }
    else{
      column = 0;
      row = 2;
      index = 4;
    }
  }

  // Page 0 - Switches
  // Uses only the Touched event
  if (hmiPageUser == 0 && touchType == HMI_TOUCHED){
    M[settings.hmi.switchesIndex + index] = !M[settings.hmi.switchesIndex + index];
    drawHMIbutton(column, row, 1, M[settings.hmi.switchesIndex + index]);
  }
  
  // Page 1 - Buttons
  // Uses Touched and Released events
  else if (hmiPageUser == 1){
    if (touchType == HMI_TOUCHED){
      M[settings.hmi.buttonsIndex + index] = 1;
      drawHMIbutton(column, row, 1, 3);
    }
    if (touchType == HMI_RELEASED){
      M[settings.hmi.buttonsIndex + index] = 0;
      drawHMIbutton(column, row, 1, 2);
    }
  }
  
  // Page 2 - Potentiometer - Input Values
  // Uses Touched event
  else if (hmiPageUser == 2){
    if (touchType == HMI_TOUCHED){
      hmiEditionIndex = index;
      hmiPageMemory = hmiPage;  
      hmiPage = PAGE_InputNumber;
    }
  }
  
  // Page 3 - Status of analog values 
  // Don't use touch functions, just visualization
  else if (hmiPageUser == 3){
    // nop
  }

  // Page 4 - Status of Digital values (Leds)
  // Don't use touch functions, just visualization
  else if (hmiPageUser == 4){
    // nop
  }
}
