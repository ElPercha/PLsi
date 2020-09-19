#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Page for generic YES / NO dialog 
//--------------------------------------------------------------------------------

void pageDialogOkCancel (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawDialogOkCancel();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchDialogOkCancel(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Page full draw 
//--------------------------------------------------------------------------------

void drawDialogOkCancel (void){
  #define DIALOG_BORDER     7
  #define DIALOG_BORDER1    10

  if (dialogCode == DIALOG_RUN_STOP){
    tft.fillScreen(TFT_BLACK);
    tft.fillRoundRect(DIALOG_BORDER, DIALOG_BORDER, TFT_PIXELS_X - (DIALOG_BORDER*2), TFT_PIXELS_Y - (DIALOG_BORDER*2), 6, TFT_WHITE);
    tft.fillRoundRect(DIALOG_BORDER1, DIALOG_BORDER1, TFT_PIXELS_X - (DIALOG_BORDER1*2), TFT_PIXELS_Y - (DIALOG_BORDER1*2), 4, TFT_RED);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(60, 60);
    tft.print("Do you want to");
    tft.setCursor(60, 90);
    tft.print("STOP your PLsi?");
  }
  else if (dialogCode == DIALOG_STOP_RUN){
    tft.fillScreen(TFT_BLACK);
    tft.fillRoundRect(DIALOG_BORDER, DIALOG_BORDER, TFT_PIXELS_X - (DIALOG_BORDER*2), TFT_PIXELS_Y - (DIALOG_BORDER*2), 6, TFT_WHITE);
    tft.fillRoundRect(DIALOG_BORDER1, DIALOG_BORDER1, TFT_PIXELS_X - (DIALOG_BORDER1*2), TFT_PIXELS_Y - (DIALOG_BORDER1*2), 4, TFT_DARKGREEN);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(60, 60);
    tft.print("Do you want to");
    tft.setCursor(60, 90);
    tft.print("RUN your PLsi?");
  }

  drawDialogButtons();
}

//--------------------------------------------------------------------------------
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchDialogOkCancel(uint16_t ts_x, uint16_t ts_y){
  if (ts_y > 160 && ts_x < 160){
    if (dialogCode == DIALOG_RUN_STOP){
      settings.ladder.PLCstate = STOPPED;
      saveSettings();
    }
    else if (dialogCode == DIALOG_STOP_RUN){
      settings.ladder.PLCstate = RUNNING;
      saveSettings();
    }
    HMI_Page = HMI_PageMemory;
  }
  if (ts_y > 160 && ts_x > 160){
      HMI_Page = HMI_PageMemory;
  }
}

//--------------------------------------------------------------------------------
// Drawing of Dialog buttons YES / NO 
//--------------------------------------------------------------------------------

void drawDialogButtons(){
  #define SPACING      20 // Spacing between buttons
  #define BUTTON_H     60 // Button Height
  #define BUTTON_W     (TFT_PIXELS_X - (SPACING * 3))/2 // Button Width
  #define BUTTON_Y     TFT_PIXELS_Y - SPACING - BUTTON_H // Y where the button starts

  tft.fillRoundRect(SPACING, BUTTON_Y, BUTTON_W, BUTTON_H, 8, TFT_BLACK);
  tft.fillRoundRect(SPACING+2, BUTTON_Y+2, BUTTON_W-4, BUTTON_H-4, 7, TFT_SILVER);

  tft.fillRoundRect(SPACING*2+BUTTON_W, BUTTON_Y, BUTTON_W, BUTTON_H, 8, TFT_BLACK);
  tft.fillRoundRect(SPACING*2+BUTTON_W+2, BUTTON_Y+2, BUTTON_W-4, BUTTON_H-4, 7, TFT_SILVER);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(59, BUTTON_Y + 19);
  tft.print("YES");
  tft.setCursor(220, BUTTON_Y + 19);
  tft.print("NO");
}
