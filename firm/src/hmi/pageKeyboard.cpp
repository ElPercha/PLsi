#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Keyboard Page - Input Text
//--------------------------------------------------------------------------------

void pageKeyboard(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      clearTextKeyboard();  

      tft.fillScreen(COLOR_KEYBOARD_BACK);
      drawTextBox();
      drawKeyboard(0);
      drawKeyboardSpace();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    // nothing to update

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

  tft.fillRoundRect(TEXT_BAR_X, TEXT_BAR_Y, TEXT_BAR_W, TEXT_BAR_H, 10, COLOR_KEYBOARD_BAR);
  tft.drawRoundRect(TEXT_BAR_X, TEXT_BAR_Y, TEXT_BAR_W, TEXT_BAR_H, 10, COLOR_KEYBOARD_BACK);

  tft.setTextSize(2); 
  tft.setTextColor(COLOR_KEYBOARD_FONT); 

  if(textValue.length() <= 24){
    tft.drawString(textValue, TEXT_BAR_X + 10, TEXT_BAR_Y + 25);
  }
  else if (textValue.length() <= 48){
    tft.drawString(textValue.substring(0, 24), TEXT_BAR_X + 10, TEXT_BAR_Y + 15);
    tft.drawString(textValue.substring(24, textValue.length()), TEXT_BAR_X + 10, TEXT_BAR_Y + 35);
  }  
  else{
    tft.drawString(textValue.substring( 0, 24), TEXT_BAR_X + 10, TEXT_BAR_Y + 7);
    tft.drawString(textValue.substring(24, 48), TEXT_BAR_X + 10, TEXT_BAR_Y + 27);
    tft.drawString(textValue.substring(48, textValue.length()), TEXT_BAR_X + 10, TEXT_BAR_Y + 47);
  }  
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
  uint16_t i, x, y, x1, y1;

  // Touching the top bar also changes the Page, to simplify usage
  if (ts_y < KEY_TEXT_Y){
    changeKeyboardPage();
  }
  // Parsing of Printable keys, shift and Backspace
  else if (ts_y < KEY_SPACE_Y){
    for (uint8_t row = 0; row < 3; row++) {
      for (uint8_t col = 0; col < 10; col++) {
        i = col + row * 10;
        x = KEY_TEXT_X + KEY_TEXT_W * col;
        y = KEY_TEXT_Y + KEY_TEXT_H * row;
        x1 = KEY_TEXT_X + KEY_TEXT_W * col + KEY_TEXT_W;
        y1 = KEY_TEXT_Y + KEY_TEXT_H * row + KEY_TEXT_H;

        if (ts_x > x && ts_x < x1 && ts_y > y && ts_y < y1){
          if (i != 20 && i != 28 && i != 29){ // Printable ASCII characters
            if (textValue.length() < textMaxLength) {
              textValue = textValue + keyLabel[keyboardPage][i];
            }
          }
          else if(i == 20){                  // Shift key - Same position in all pages
            changeKeyboardPage();
          }
          else if(i == 28 || i == 29){       // Backspace key - Same position in all pages
            if (textValue.length() > 0) {
              textValue = textValue.substring(0, textValue.length()-1);
            }
          }
        }
      }
    }
    drawTextBox();      // Draw the string in top box
  }
  // Bottom buttons
  else{
    if (ts_x < KEY_TEXT_W * 3){            // ESC
      clearTextKeyboard();  
      HMI_Page = HMI_PageMemory;
    }    
    else if (ts_x < KEY_TEXT_W * 7){       // SPACE 
      if (textValue.length() < textMaxLength) {
        textValue = textValue + ' ';
      }
    }    
    else{                                  // ENTER 
      textValueAccepted = 1;
      HMI_Page = HMI_PageMemory;
    }    
  }
}

//--------------------------------------------------------------------------------
// Change Keyboard Page 
//--------------------------------------------------------------------------------

void changeKeyboardPage(void){
  keyboardPage ++;
  if (keyboardPage > 3){
    keyboardPage = 0;
  }
  drawKeyboard(keyboardPage);
}

//--------------------------------------------------------------------------------
// Initialize required variables 
//--------------------------------------------------------------------------------

void clearTextKeyboard(void){
  keyboardPage = 0;          // KeyboardPage
  textValueAccepted = 0;     // Output validation variable
}  