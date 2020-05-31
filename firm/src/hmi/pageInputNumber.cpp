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
      numericValue = 0;
      numericValueAccepted = 0;
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

  if (!touchType){
    for (uint8_t b = 0; b < 16; b++) {
      if (numericKeys[b].isPressed()){
        numericKeys[b].press(false);
        numericKeys[b].drawButton(false);     // draw normal
      }
    }
  }

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
  
  //-------------------------------------------------
  // Keypad start position, key sizes and spacing
  //-------------------------------------------------

  #define KEY_X         40 // Centre of key
  #define KEY_Y         90
  #define KEY_W         77 // Width and height
  #define KEY_H         40
  #define KEY_SPACING_X  2 // X and Y gap
  #define KEY_SPACING_Y  2
  #define KEY_TEXTSIZE   2 // Font size multiplier

  //-------------------------------------------------
  // Numeric display box size and location
  //-------------------------------------------------

  #define DISP_X         6
  #define DISP_Y         8
  #define DISP_W       304
  #define DISP_H        54
  #define DISP_TSIZE     3
  
  //-------------------------------------------------
  // Key Labels and Colors
  //-------------------------------------------------

  char keyLabel[16][5] = {"1", "2", "3", "ESC", "4", "5", "6", "DEL", "7", "8", "9", "<<", ".", "0", "-", "OK"};
  uint16_t keyColor[16] = {TFT_DARKGREY, TFT_DARKGREY, TFT_DARKGREY, TFT_MAGENTA, 
                           TFT_DARKGREY, TFT_DARKGREY, TFT_DARKGREY, TFT_VIOLET,
                           TFT_DARKGREY, TFT_DARKGREY, TFT_DARKGREY, TFT_DARKCYAN,
                           TFT_DARKGREY, TFT_DARKGREY, TFT_DARKGREY, TFT_DARKGREEN};

  //-------------------------------------------------
  // Draw number display area and frame
  //-------------------------------------------------

  tft.fillScreen(TFT_BLACK);
  tft.fillRoundRect(DISP_X, DISP_Y, DISP_W, DISP_H, 4, TFT_DARKGREY);
  tft.drawRoundRect(DISP_X, DISP_Y, DISP_W, DISP_H, 4, TFT_WHITE);

  //-------------------------------------------------
  // Draw the keys
  //-------------------------------------------------

  for (uint8_t row = 0; row < 4; row++) {
    for (uint8_t col = 0; col < 4; col++) {
      uint8_t b = col + row * 4;

      numericKeys[b].initButton(&tft, KEY_X + col * (KEY_W + KEY_SPACING_X),
                        KEY_Y + row * (KEY_H + KEY_SPACING_Y), // x, y, w, h, outline, fill, text
                        KEY_W, KEY_H, TFT_WHITE, keyColor[b], TFT_WHITE,
                        keyLabel[b], KEY_TEXTSIZE);
      numericKeys[b].setLabelDatum(2,5);
      numericKeys[b].drawButton();
    }
  }
}

//--------------------------------------------------------------------------------
// Keyboard Numeric Input Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchInputNumber(uint16_t ts_x, uint16_t ts_y){
  
  //---------------------------------------------------------------------
  // Check if any key coordinate boxes contain the touch coordinates
  //---------------------------------------------------------------------

  for (uint8_t b = 0; b < 16; b++) {
    if (numericKeys[b].contains(ts_x, ts_y)) {
      numericKeys[b].press(true);  // tell the button it is pressed
    }
  }

  //---------------------------------------------------------------------
  // Check if any key has changed state
  //---------------------------------------------------------------------

  for (uint8_t b = 0; b < 16; b++) {

    if (numericKeys[b].justPressed()) {
      numericKeys[b].drawButton(true);  // draw invert

      //---------------------------------------------------------------------
      // if a numberpad button, append the relevant # to the numberBuffer
      //---------------------------------------------------------------------

      if (b == 0) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '1';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 1) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '2';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 2) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '3';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 4) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '4';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 5) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '5';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 6) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '6';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 8) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '7';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 9) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '8';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 10) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '9';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 12) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '.';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 13) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '0';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }
      if (b == 14) {
        if (numberIndex < NUM_KEY_LEN) {
          numberBuffer[numberIndex] = '-';
          numberIndex++;
          numberBuffer[numberIndex] = 0; // zero terminate
        }
      }

      //---------------------------------------------------------------------
      // ESC button, delete buffer and go back to previous page
      //---------------------------------------------------------------------

      if (b == 3) {
        numberIndex = 0;               // Reset index to 0
        numberBuffer[numberIndex] = 0; // Place null in buffer
        HMI_Page = HMI_PageMemory;
      }

      //---------------------------------------------------------------------
      // DEL button, delete buffer
      //---------------------------------------------------------------------

      if (b == 7) {
        numberIndex = 0;               // Reset index to 0
        numberBuffer[numberIndex] = 0; // Place null in buffer
      }
      
      //---------------------------------------------------------------------
      // Backspace Button, delete last Char
      //---------------------------------------------------------------------

      if (b == 11) {
        numberBuffer[numberIndex] = 0;
        if (numberIndex > 0) {
          numberIndex--;
          numberBuffer[numberIndex] = 0;
        }
      }

      //---------------------------------------------------------------------
      // OK Button, save numeric value, reset buffer and go to previous page
      //---------------------------------------------------------------------

      if (b == 15) {
        numericValue = atof(numberBuffer);
        numericValueAccepted = 1;
        Serial.println(numericValue, 10);

        numberIndex = 0;               // Reset index to 0
        numberBuffer[numberIndex] = 0; // Place null in buffer

        HMI_Page = HMI_PageMemory;
      }

      //---------------------------------------------------------------------
      // Draw the string in top box
      //---------------------------------------------------------------------

      tft.setTextSize(3); 
      tft.setTextColor(TFT_WHITE); 
      tft.fillRoundRect(DISP_X, DISP_Y, DISP_W, DISP_H, 4, TFT_DARKGREY);
      tft.drawRoundRect(DISP_X, DISP_Y, DISP_W, DISP_H, 4, TFT_WHITE);
      tft.drawString(numberBuffer, DISP_X + 10, DISP_Y + 17);
    }   
  }
}