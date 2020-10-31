#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Input Number Page display (Numeric Keyboard)
//--------------------------------------------------------------------------------

void pageInputText(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawTextBox();
      drawKeyboard(0);
      drawKeyboardSpace();
      
      textValue = "";
      textValueAccepted = 0;
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    if (I[0]){
      drawKeyboard(0);
    }
    if (I[1]){
      drawKeyboard(1);
    }
    if (I[2]){
      drawKeyboard(2);
    }
    if (I[3]){
      drawKeyboard(3);
    }

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchInputText(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Draw Keyboard Text Box
//--------------------------------------------------------------------------------

void drawTextBox (void){
  #define TEXT_BAR_W         TFT_PIXELS_X - 10
  #define TEXT_BAR_H         64
  #define TEXT_BAR_Y         5 
  #define TEXT_BAR_X         5

  tft.fillScreen(COLOR_KEYBOARD_BACK);
  tft.fillRoundRect(TEXT_BAR_X, TEXT_BAR_Y, TEXT_BAR_W, TEXT_BAR_H, 10, COLOR_KEYBOARD_BAR);
  tft.drawRoundRect(TEXT_BAR_X, TEXT_BAR_Y, TEXT_BAR_W, TEXT_BAR_H, 10, COLOR_KEYBOARD_BACK);
}

//--------------------------------------------------------------------------------
// Keyboard Keys
//--------------------------------------------------------------------------------

void drawKeyboard (uint16_t keyboardPage){
  #define KEY_TEXT_Y          TEXT_BAR_H + TEXT_BAR_Y*2
  #define KEY_TEXT_X          0
  #define KEY_TEXT_W          TFT_PIXELS_X / 10
  #define KEY_TEXT_H         40
  #define KEY_TEXT_SPACING    0

  uint16_t i, x, y;

  for (uint8_t row = 0; row < 3; row++) {
    for (uint8_t col = 0; col < 10; col++) {
      i = col + row * 10;
      x = KEY_TEXT_X + KEY_TEXT_W * col;
      y = KEY_TEXT_Y + KEY_TEXT_H * row;
      
      // Draw the boxes
      if (i < 28){
        tft.fillRoundRect(x, y , KEY_TEXT_W, KEY_TEXT_H, 4, COLOR_KEYBOARD_KEY);
        tft.drawRoundRect(x, y , KEY_TEXT_W, KEY_TEXT_H, 4, COLOR_KEYBOARD_BACK);
      }
      else if(i == 28){ // Backspace Key
        tft.fillRoundRect(x, y , KEY_TEXT_W*2, KEY_TEXT_H, 4, COLOR_KEYBOARD_KEY);
        tft.drawRoundRect(x, y , KEY_TEXT_W*2, KEY_TEXT_H, 4, COLOR_KEYBOARD_BACK);
      }

      // Draw the characters and symbols
      tft.setTextSize(2); 
      tft.setTextColor(COLOR_KEYBOARD_FONT); 
      if (i != 20 && i != 28 && i != 29){
        tft.setCursor(x + 11, y + 14);
        tft.print(keyLabel[keyboardPage][i]);
      }
      // Shift symbol in position 20. Row 3 Column 0
      else if (i == 20){
        tft.fillTriangle(7+x+8, 12+y+0, 7+x+0, 12+y+8, 7+x+16, 12+y+8, COLOR_KEYBOARD_SPECIAL_KEY);
        tft.fillRect    (7+x+4, 12+y+8, 9, 8, COLOR_KEYBOARD_SPECIAL_KEY);  
      }
      // Backspace symbol in position 28 and 29. Row 3 Column 8 and 9
      else if (i == 28){
        tft.fillTriangle(15+x+0, 13+y+7, 15+x+7, 13+y+0, 15+x+7, 13+y+14, COLOR_KEYBOARD_SPECIAL_KEY);
        tft.fillRect    (15+x+8, 13+y+0, 25, 15, COLOR_KEYBOARD_SPECIAL_KEY);  
      }
    }
  }
}

//--------------------------------------------------------------------------------
// Keyboard NUM/LETTERS and SPACE bar
//--------------------------------------------------------------------------------

void drawKeyboardSpace (void){
  #define KEY_TEXT_H1        KEY_TEXT_H + 5
  #define KEY_SPACE_Y        KEY_TEXT_Y + KEY_TEXT_H * 3 

  uint16_t x;

  tft.setTextSize(2); 
  tft.setTextColor(COLOR_KEYBOARD_FONT); 

  // Esc 
  x = KEY_TEXT_X;
  tft.fillRoundRect(KEY_TEXT_X, KEY_SPACE_Y, KEY_TEXT_W * 3, KEY_TEXT_H1, 4, COLOR_KEYBOARD_KEY);
  tft.drawRoundRect(KEY_TEXT_X, KEY_SPACE_Y, KEY_TEXT_W * 3, KEY_TEXT_H1, 4, COLOR_KEYBOARD_BACK);
  tft.setCursor(x + 30, KEY_SPACE_Y + 16);
  tft.print("ESC");

  // Space
  x = KEY_TEXT_X + KEY_TEXT_W * 3;
  tft.fillRoundRect(x, KEY_SPACE_Y, KEY_TEXT_W * 4, KEY_TEXT_H1, 4, COLOR_KEYBOARD_KEY);
  tft.drawRoundRect(x, KEY_SPACE_Y, KEY_TEXT_W * 4, KEY_TEXT_H1, 4, COLOR_KEYBOARD_BACK);

  // Enter
  x = KEY_TEXT_X + KEY_TEXT_W * 7;
  tft.fillRoundRect(x, KEY_SPACE_Y, KEY_TEXT_W * 3, KEY_TEXT_H1, 4, COLOR_KEYBOARD_KEY);
  tft.drawRoundRect(x, KEY_SPACE_Y, KEY_TEXT_W * 3, KEY_TEXT_H1, 4, COLOR_KEYBOARD_BACK);
  tft.setCursor(x + 20, KEY_SPACE_Y + 16);
  tft.print("ENTER");
}

//--------------------------------------------------------------------------------
// Keyboard Input Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchInputText(uint16_t ts_x, uint16_t ts_y){

  HMI_Page = HMI_PageMemory;

}