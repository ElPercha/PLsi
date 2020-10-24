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
  else if (messageCode == MESSAGE_CANNOT_COPY_COLUMN){
    tft.setCursor(30, 45);
    tft.print("CANNOT COPY COLUMN");
    tft.setCursor(30, 65);
    tft.print("CONTAINING DOUBLE");
    tft.setCursor(30, 85);
    tft.print("COLUMN INSTRUCTIONS");
    tft.setCursor(30, 105);
    tft.print("COPY NETWORK INSTEAD");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_COPY_ROW){
    tft.setCursor(30, 45);
    tft.print("CANNOT COPY ROW");
    tft.setCursor(30, 65);
    tft.print("CONTAINING INSTRUCTION");
    tft.setCursor(30, 85);
    tft.print("HIGHER THAN 1 CELL");
    tft.setCursor(30, 105);
    tft.print("COPY NETWORK INSTEAD");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_COLUMN_NOT_EMPTY){
    tft.setCursor(30, 45);
    tft.print("CANNOT PASTE");
    tft.setCursor(30, 65);
    tft.print("COLUMN IS NOT EMPTY");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_ROW_NOT_EMPTY){
    tft.setCursor(30, 45);
    tft.print("CANNOT PASTE");
    tft.setCursor(30, 65);
    tft.print("ROW IS NOT EMPTY");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_NETWORK_NOT_EMPTY){
    tft.setCursor(30, 45);
    tft.print("CANNOT PASTE");
    tft.setCursor(30, 65);
    tft.print("NETWORK IS NOT EMPTY");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_DELETE_COLUMN){
    tft.setCursor(30, 45);
    tft.print("CANNOT DELETE COLUMN");
    tft.setCursor(30, 65);
    tft.print("CONTAINING DOUBLE");
    tft.setCursor(30, 85);
    tft.print("COLUMN INSTRUCTIONS");
    tft.setCursor(30, 105);
    tft.print("DELETE NETWORK INSTEAD");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_DELETE_ROW){
    tft.setCursor(30, 45);
    tft.print("CANNOT DELETE ROW");
    tft.setCursor(30, 65);
    tft.print("CONTAINING INSTRUCTION");
    tft.setCursor(30, 85);
    tft.print("HIGHER THAN 1 CELL");
    tft.setCursor(30, 105);
    tft.print("DELETE NETWORK INSTEAD");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_INSERT_COLUMN){
    tft.setCursor(30, 45);
    tft.print("CANNOT INSERT COLUMN");
    tft.setCursor(30, 65);
    tft.print("LAST COLUMN");
    tft.setCursor(30, 85);
    tft.print("IS NOT EMPTY");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_INSERT_ROW){
    tft.setCursor(30, 45);
    tft.print("CANNOT INSERT ROW");
    tft.setCursor(30, 65);
    tft.print("LAST ROW");
    tft.setCursor(30, 85);
    tft.print("IS NOT EMPTY");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_INSERT_NETWORK){
    tft.setCursor(30, 45);
    tft.print("CANNOT INSERT NETWORK");
    tft.setCursor(30, 65);
    tft.print("LAST NETWORK");
    tft.setCursor(30, 85);
    tft.print("IS NOT EMPTY");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_SPLIT_WIDE_INSTR){
    tft.setCursor(30, 45);
    tft.print("CANNOT INSERT COLUMN");
    tft.setCursor(30, 65);
    tft.print("CANNOT SPLIT INSTRUCTION");
    tft.setCursor(30, 85);
    tft.print("SELECT THE RIGHT COLUMN");
    tft.setCursor(30, 170);
    tft.print("TOUCH TO CONTINUE...");
  }
  else if (messageCode == MESSAGE_CANNOT_SPLIT_HIGH_INSTR){
    tft.setCursor(30, 45);
    tft.print("CANNOT INSERT ROW");
    tft.setCursor(30, 65);
    tft.print("SPLIT INSTRUCTION");
    tft.setCursor(30, 85);
    tft.print("NOT POSSIBLE");
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
