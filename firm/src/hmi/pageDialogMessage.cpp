#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Page for generic Message to user. No user decision requested
//--------------------------------------------------------------------------------

void pageDialogMessage (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawDialogMessage();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchDialogMessage(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Page full draw 
//--------------------------------------------------------------------------------

void drawDialogMessage (void){
  #define DIALOG_BORDER2    16
  #define DIALOG_BORDER3    20

  tft.fillRoundRect(DIALOG_BORDER2, DIALOG_BORDER2, TFT_PIXELS_X - (DIALOG_BORDER2*2), TFT_PIXELS_Y - (DIALOG_BORDER2*2), 18, TFT_NAVY);
  tft.fillRoundRect(DIALOG_BORDER3, DIALOG_BORDER3, TFT_PIXELS_X - (DIALOG_BORDER3*2), TFT_PIXELS_Y - (DIALOG_BORDER3*2), 13, WHITE2);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);

  if (messageCode == MESSAGE_NO_ROWS){
    tft.setCursor(30, 45);
    tft.print("THERE ARE NOT");
    tft.setCursor(30, 65);
    tft.print("ENOUGH ROWS TO");
    tft.setCursor(30, 85);
    tft.print("FIT THIS INSTRUCTION");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_NO_COLUMNS){
    tft.setCursor(30, 45);
    tft.print("THERE ARE NOT");
    tft.setCursor(30, 65);
    tft.print("ENOUGH COLUMNS TO");
    tft.setCursor(30, 85);
    tft.print("FIT THIS INSTRUCTION");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_SPACE_USED){
    tft.setCursor(30, 45);
    tft.print("THE SPACE IS USED");
    tft.setCursor(30, 65);
    tft.print("DELETE INSTRUCTIONS");
    tft.setCursor(30, 85);
    tft.print(" FIRST");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
}

//--------------------------------------------------------------------------------
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchDialogMessage(uint16_t ts_x, uint16_t ts_y){
  HMI_Page = HMI_PageMemory;
}
