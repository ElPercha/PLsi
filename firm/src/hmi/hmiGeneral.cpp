#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <buttons.h>

//--------------------------------------------------------------------------------
// Wait for tskDisk to load the User Settings  
//--------------------------------------------------------------------------------

void hmiWaitSettings (void){
  Serial.println("TaskHMI - Waiting for Unlock");
  while (bootSequence != BOOT_TASK_UNLOCKED){
    delay(10); // forces to update bootSequence global variable
  }
  Serial.println("TaskHMI - Task Unlocked");
}

//--------------------------------------------------------------------------------
// Draw CANCEL BACK ACCEPT Buttons in the bottom of the page
// Used in edition of memory areas of Ladder Instructions Editor
//--------------------------------------------------------------------------------

void drawLadderEditorInstructionsNavigation(){
  #define BORDER10        2
  #define SPACING10       2
  #define BUTTON_H10     45
  #define BUTTON_W10    104
  #define BUTTON_Y10    TFT_PIXELS_Y - SPACING10 - BUTTON_H10 // Y where the button starts

  tft.fillRoundRect(BORDER10, BUTTON_Y10, BUTTON_W10, BUTTON_H10, 8, COLOR_BUTTON_CANCEL_INSTRUC_EDITOR);
  tft.drawRoundRect(BORDER10, BUTTON_Y10, BUTTON_W10, BUTTON_H10, 8, COLOR_BUTTON_BORDER_INSTRUC_EDITOR);

  tft.fillRoundRect(BORDER10+BUTTON_W10+SPACING10, BUTTON_Y10, BUTTON_W10, BUTTON_H10, 8, COLOR_BUTTON_BACK_INSTRUC_EDITOR);
  tft.drawRoundRect(BORDER10+BUTTON_W10+SPACING10, BUTTON_Y10, BUTTON_W10, BUTTON_H10, 8, COLOR_BUTTON_BORDER_INSTRUC_EDITOR);

  tft.fillRoundRect(BORDER10+BUTTON_W10*2+SPACING10*2, BUTTON_Y10, BUTTON_W10, BUTTON_H10, 8, COLOR_BUTTON_ACCEPT_INSTRUC_EDITOR);
  tft.drawRoundRect(BORDER10+BUTTON_W10*2+SPACING10*2, BUTTON_Y10, BUTTON_W10, BUTTON_H10, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);

  tft.setTextSize(2);
  tft.setTextColor(COLOR_BUTTON_FONT_INSTRUC_EDITOR);
  tft.setCursor(20, BUTTON_Y10 + 16);
  tft.print("CANCEL");
  tft.setCursor(140, BUTTON_Y10 + 16);
  tft.print("BACK");
  tft.setCursor(232, BUTTON_Y10 + 16);
  tft.print("ACCEPT");
}

//--------------------------------------------------------------------------------
// Parse 3 navigation buttons for Instructions Memory edition pages
//--------------------------------------------------------------------------------

void touchEditLadderInstructionsNavigation(uint16_t ts_x, uint16_t ts_y){
  if (ts_y > TFT_PIXELS_Y - BUTTON_H10 - SPACING10){
    if (ts_x < BUTTON_W10 - SPACING10){                    // CANCEL
      editingNetwork = onlineNetwork;
      hmiPage = PAGE_MainLadder;
    }
    else if (ts_x < BUTTON_W10*2 - SPACING10*2){            // BACK
      editingNetwork = onlineNetwork;
      hmiPage = PAGE_LadderEditor;
    }
    else {                                                  // ACCEPT
      onlineNetwork = editingNetwork;
      hmiPage = PAGE_MainLadder;
    }
  }
}

//--------------------------------------------------------------------------------
// Draw HMI button
// 
//    posX and posY --> are are the location index for the button, by design the HMI screen is divided in 40 x 40 pixels matrix
//    For example, in a 320 x 240 display, where the top 80 Y pixels are used for the menu and page title
//    and the remaining space is an area of 320 wide in X and 160 height in Y, the matrix will have: 4 rows and 8 columns       
//
//    size = 0 --> 32 x 32 pixels button (uses 1 matrix cell)
//    size = 1 --> 64 x 64 pixels button (uses 4 matrix cells)
//
//    color = 0 --> Red
//    color = 1 --> Green
//    color = 2 --> Blue
//    color = 3 --> Yellow
//--------------------------------------------------------------------------------

void drawHMIbutton(uint16_t posX, uint16_t posY, uint16_t size, uint16_t color){
  tft.setSwapBytes(true);
  if (color >= 4){
    color = 0;
  } 
  if (size >= 2){
    size = 0;
  }
 
  if (size == 0){
    tft.pushImage(4 + posX*HMI_SLOT_W, 4 + posY*HMI_SLOT_H + HMI_SLOTS_Y, 32, 32, buttons32[color]);
  }
  else if (size == 1){
    tft.pushImage(8 + posX*HMI_SLOT_W, 14 + posY*HMI_SLOT_H + HMI_SLOTS_Y, 64, 64, buttons64[color]);
  }
}

//--------------------------------------------------------------------------------
// Draw HMI button text
// type = 0 --> Used for text centered on Y and Left aligned on the specified cell
// type = 1 --> Used on 2 x 2 cells objects, location is top-center 
// type = 2 --> Used for text centered on Y and Centered on the specified cell
// type = 3 --> Used for text Top aligned on Y and Centered on the specified cell
// type = 4 --> Used for text Bottom aligned on Y and Centered on the specified cell
//--------------------------------------------------------------------------------

void drawHMIbuttonText(uint16_t posX, uint16_t posY, uint16_t type, String text){
  tft.setTextColor(COLOR_HMI_FONT);
  tft.setTextFont(1);
  tft.setTextSize(1);

  if (type == 0){
    tft.drawString(text, posX*HMI_SLOT_W + 5, posY*HMI_SLOT_H + HMI_SLOTS_Y + 11, HMI_FONT_SIZE);
  }
  else if (type == 1){
    tft.drawCentreString(text, posX*HMI_SLOT_W + HMI_SLOT_W, posY*HMI_SLOT_H - 2 + HMI_SLOTS_Y, HMI_FONT_SIZE);
  }
  else if (type == 2){
    tft.drawCentreString(text, posX*HMI_SLOT_W + HMI_SLOT_W/2, posY*HMI_SLOT_H + HMI_SLOTS_Y + 13, HMI_FONT_SIZE);
  }
  else if (type == 3){
    tft.drawCentreString(text, posX*HMI_SLOT_W + HMI_SLOT_W/2, posY*HMI_SLOT_H + HMI_SLOTS_Y + 2, HMI_FONT_SIZE);
  }
  else if (type == 4){
    tft.drawCentreString(text, posX*HMI_SLOT_W + HMI_SLOT_W/2, posY*HMI_SLOT_H + HMI_SLOTS_Y + 23, HMI_FONT_SIZE);
  }
}

//--------------------------------------------------------------------------------
// Draw HMI analog Indicator
// type = 0 --> Used for 2 x 2 cells analog potentiometer
// type = 1 --> Used for 2 x 2 cells analog indicator
//--------------------------------------------------------------------------------

void drawHMIAnalogIndicator(uint16_t posX, uint16_t posY, uint16_t type, double value){
  uint32_t color = 0;
  
  tft.setTextColor(COLOR_HMI_FONT);
  tft.setTextFont(1);
  tft.setTextSize(1);
  tft.setFreeFont(FSS9);

  if (type == 0){
    color =  COLOR_HMI_BACK_POTENTIOM;
  }
  if (type == 1){
    color =  COLOR_HMI_BACK_ANA_IND;
  }

  if (type == 0 || type == 1){
    tft.fillRect(posX*HMI_SLOT_W + 2, posY*HMI_SLOT_H + HMI_SLOTS_Y + 20, HMI_SLOT_W*2 - 4, HMI_SLOT_H - 5, color);
    tft.drawCentreString(String(value, 0), posX*HMI_SLOT_W + HMI_SLOT_W, posY*HMI_SLOT_H + HMI_SLOTS_Y + 30, GFXFF);
  }

  tft.setTextFont(1); // Go back to default font
}

//--------------------------------------------------------------------------------
// Draw HMI analog Output Indicator
//    type = not used
//    IO => Value of the IO address
//--------------------------------------------------------------------------------

void drawHMIAnalogIO_Indicator(uint16_t posX, uint16_t posY, uint16_t type, double value){
  tft.setTextColor(COLOR_HMI_FONT);
  tft.setTextFont(1);
  tft.setTextSize(1);

  if (value >= 0 && value <= ANALOG_RESOLUTION){
    uint16_t auxFull = HMI_SLOT_H * value / ANALOG_RESOLUTION;
    uint16_t auxEmpty = HMI_SLOT_H - auxFull;

    tft.fillRect(posX*HMI_SLOT_W, posY*HMI_SLOT_H + HMI_SLOTS_Y, HMI_SLOT_W, auxEmpty, COLOR_HMI_AN_INDI_EMPTY); 
    tft.fillRect(posX*HMI_SLOT_W, posY*HMI_SLOT_H + HMI_SLOTS_Y + auxEmpty, HMI_SLOT_W, auxFull, COLOR_HMI_AN_INDI_FULL);
    tft.drawRect(posX*HMI_SLOT_W, posY*HMI_SLOT_H + HMI_SLOTS_Y, HMI_SLOT_W, HMI_SLOT_H, COLOR_HMI_AN_BORDER);

    tft.drawCentreString(String(value, 0), posX*HMI_SLOT_W + HMI_SLOT_W/2, posY*HMI_SLOT_H + HMI_SLOTS_Y + 18, 1);
  }
  else{
    tft.drawCentreString("ERR", posX*HMI_SLOT_W + HMI_SLOT_W/2, posY*HMI_SLOT_H + HMI_SLOTS_Y + 18, 1);
    Serial.println("TaskHMI - Error in drawHMIAnalogIO_Indicator Parameter value out of range");
  }

  tft.setTextFont(1); // Go back to default font
}

