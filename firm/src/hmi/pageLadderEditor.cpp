#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
//Ladder Editor main Page
//--------------------------------------------------------------------------------

void pageLadderEditor (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawLadderEditor();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchLadderEditor(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Ladder Editor Page full draw 
//--------------------------------------------------------------------------------

void drawLadderEditor (void){

 
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);

  if (indexLadderEditor == 0){
    drawLadderEditorInstructionsMenu();




    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);
    tft.print("Ladder Editor - Index 0");
  }
  if (indexLadderEditor == 1){
    drawLadderEditorInstructionsMenu();




    tft.fillScreen(TFT_GOLD);
    tft.setCursor(10, 10);
    tft.print("Ladder Editor - Index 1");
  }
  if (indexLadderEditor == 2){
    drawLadderEditorElementsMenu();



    tft.fillScreen(TFT_PINK);
    tft.setCursor(10, 10);
    tft.print("Ladder Editor - Index 2");
  }
  if (indexLadderEditor == 3){
    drawLadderEditorElementsMenu();



    tft.fillScreen(TFT_VIOLET);
    tft.setCursor(10, 10);
    tft.print("Ladder Editor - Index 3");
  }
  if (indexLadderEditor == 4){
    drawLadderEditorElementsMenu();




    tft.fillScreen(TFT_GREENYELLOW);
    tft.setCursor(10, 10);
    tft.print("Ladder Editor - Index 4");
  }






  drawLadderEditorBottomButtons();
  drawLadderEditorNavigationBar();










}

//--------------------------------------------------------------------------------
// Ladder Editor Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchLadderEditor(uint16_t ts_x, uint16_t ts_y){
    
  if(ts_y < 120){ // return
    HMI_Page = HMI_PageMemory;
  }
  else if(ts_x > 160){    // Increase Page Index
    indexLadderEditor++;
    if (indexLadderEditor >= PAGES_LADDER_EDITOR){
      indexLadderEditor = 0;
    } 
    drawLadderEditor();
  }
  else{    // Decrease Page Index
    if (indexLadderEditor > 0){
      indexLadderEditor--;
    }
    else{
      indexLadderEditor = PAGES_LADDER_EDITOR - 1;
    }
    drawLadderEditor();
  }

}

//--------------------------------------------------------------------------------
// Draw DELETE CANCEL ACCEPT Buttons in the bottom
//--------------------------------------------------------------------------------

void drawLadderEditorBottomButtons(){
  #define BORDER1        2
  #define SPACING1       2
  #define BUTTON_H1     45
  #define BUTTON_W1    104
  #define BUTTON_Y1     TFT_PIXELS_Y - SPACING1 - BUTTON_H1 // Y where the button starts

  tft.fillRoundRect(BORDER1, BUTTON_Y1, BUTTON_W1, BUTTON_H1, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER1+1, BUTTON_Y1+1, BUTTON_W1-2, BUTTON_H1-2, 7, TFT_VIOLET);

  tft.fillRoundRect(BORDER1+BUTTON_W1+SPACING1, BUTTON_Y1, BUTTON_W1, BUTTON_H1, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER1+BUTTON_W1+SPACING1+1, BUTTON_Y1+1, BUTTON_W1-2, BUTTON_H1-2, 7, TFT_MAGENTA);

  tft.fillRoundRect(BORDER1+BUTTON_W1*2+SPACING1*2, BUTTON_Y1, BUTTON_W1, BUTTON_H1, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER1+BUTTON_W1*2+SPACING1*2+1, BUTTON_Y1+1, BUTTON_W1-2, BUTTON_H1-2, 8, TFT_DARKGREEN);


  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(20, BUTTON_Y1 + 16);
  tft.print("DELETE");
  tft.setCursor(126, BUTTON_Y1 + 16);
  tft.print("CANCEL");
  tft.setCursor(232, BUTTON_Y1 + 16);
  tft.print("ACCEPT");
}

//--------------------------------------------------------------------------------
// Draw Arrows and Info field 
//--------------------------------------------------------------------------------

void drawLadderEditorNavigationBar(void){
  #define BORDER2        2
  #define SPACING2       2
  #define BUTTON_H2     45
  #define BUTTON_W2     76
  #define BAR_H         45
  #define BAR_W        160
  #define BUTTON_Y2     TFT_PIXELS_Y - SPACING2*2 - BUTTON_H2*2 // Y where the button starts

  tft.fillRoundRect(BORDER2, BUTTON_Y2, BUTTON_W2, BUTTON_H2, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER2+1, BUTTON_Y2+1, BUTTON_W2-2, BUTTON_H2-2, 7, TFT_DARKCYAN);

  tft.fillRoundRect(BORDER2+BUTTON_W2+SPACING2, BUTTON_Y2, BAR_W, BAR_H, 8, TFT_WHITE);

  tft.fillRoundRect(BORDER2+BUTTON_W2+SPACING2*2+BAR_W, BUTTON_Y2, BUTTON_W2, BUTTON_H2, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER2+BUTTON_W2+SPACING2*2+BAR_W+1, BUTTON_Y2+1, BUTTON_W2-2, BUTTON_H2-2, 7, TFT_DARKCYAN);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(26, BUTTON_Y2 + 16);
  tft.print("<<");
  tft.setCursor(269, BUTTON_Y2 + 16);
  tft.print(">>");

  tft.setTextColor(TFT_DARKGREY);
  tft.setTextSize(2);
  tft.setCursor(95, BUTTON_Y2 + 7);
  tft.print("NETWORK " + String(showingNetwork));
  tft.setCursor(95, BUTTON_Y2 + 27);
  tft.print("ROW " + String(ladderEditorRow) + " COL " + String(ladderEditorColumn));
}

//--------------------------------------------------------------------------------
// Draw Instructions palette
//--------------------------------------------------------------------------------

void drawLadderEditorInstructionsMenu(void){

  // #define BORDER        2
  // #define SPACING       4
  // #define BUTTON_H     46
  // #define BUTTON_W     60
  // #define BUTTON_Y     TFT_PIXELS_Y - SPACING - BUTTON_H // Y where the button starts

  // tft.fillRoundRect(BORDER, BUTTON_Y, BUTTON_W, BUTTON_H, 8, TFT_WHITE);
  // tft.fillRoundRect(BORDER+2, BUTTON_Y+2, BUTTON_W-4, BUTTON_H-4, 7, TFT_DARKCYAN);

  // tft.fillRoundRect(BORDER+BUTTON_W+SPACING, BUTTON_Y, BUTTON_W, BUTTON_H, 8, TFT_WHITE);
  // tft.fillRoundRect(BORDER+BUTTON_W+SPACING+2, BUTTON_Y+2, BUTTON_W-4, BUTTON_H-4, 7, TFT_DARKCYAN);

  // tft.fillRoundRect(BORDER+BUTTON_W*2+SPACING*2, BUTTON_Y, BUTTON_W, BUTTON_H, 8, TFT_WHITE);
  // tft.fillRoundRect(BORDER+BUTTON_W*2+SPACING*2+2, BUTTON_Y+2, BUTTON_W-4, BUTTON_H-4, 8, TFT_DARKCYAN);


  // tft.setTextColor(TFT_WHITE);
  // tft.setTextSize(2);
  // tft.setCursor(20, BUTTON_Y + 15);
  // tft.print("DELETE");
  // tft.setCursor(126, BUTTON_Y + 15);
  // tft.print("CANCEL");
  // tft.setCursor(232, BUTTON_Y + 15);
  // tft.print("ACCEPT");







}

//--------------------------------------------------------------------------------
// Draw Elements palette
//--------------------------------------------------------------------------------

void drawLadderEditorElementsMenu(void){





}


