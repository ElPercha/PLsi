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

  tft.fillScreen(TFT_BLACK);

  drawLadderEditorBottomButtons();
  drawLadderEditorNavigationBar();

  if (indexLadderEditor == 0){
    drawLadderEditorInstructionsMenu();
  }
  if (indexLadderEditor == 1){
    drawLadderEditorInstructionsMenu();
  }
  if (indexLadderEditor == 2){
    drawLadderEditorElementsMenu();
  }
  if (indexLadderEditor == 3){
    drawLadderEditorElementsMenu();
  }
  if (indexLadderEditor == 4){
    drawLadderEditorElementsMenu();
  }

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

  #define BORDER3        2
  #define SPACING3       4
  #define BUTTON_H3     44
  #define BUTTON_W3     60
  #define BUTTON_Y3     BORDER3

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  for (uint16_t row = 0; row < 3; row++){
    for (uint16_t col = 0; col < 5; col++){
      tft.fillRoundRect(BORDER3+BUTTON_W3*col+SPACING3*col, BUTTON_Y3+BUTTON_H3*row+SPACING3*row, BUTTON_W3, BUTTON_H3, 8, TFT_WHITE);
      tft.fillRoundRect(BORDER3+BUTTON_W3*col+SPACING3*col+1, BUTTON_Y3+BUTTON_H3*row+SPACING3*row+1, BUTTON_W3-2, BUTTON_H3-2, 7, TFT_DARKGREY);
      tft.setCursor(BORDER3+BUTTON_W3*col+SPACING3*col+25, BUTTON_Y3+BUTTON_H3*row+SPACING3*row + 15);
      tft.print(String((row+1)*(col+1)));
    }
  }
}

//--------------------------------------------------------------------------------
// Draw Elements palette
//--------------------------------------------------------------------------------

void drawLadderEditorElementsMenu(void){
  #define BORDER4V       4
  #define BORDER4H       2
  #define SPACING4       4
  #define BUTTON_H4     67
  #define BUTTON_W4     156
  #define BUTTON_Y4     BORDER4V

  tft.fillRoundRect(BORDER4H, BUTTON_Y4, BUTTON_W4, BUTTON_H4, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER4H+2, BUTTON_Y4+2, BUTTON_W4-4, BUTTON_H4-4, 7, TFT_DARKGREY);

  tft.fillRoundRect(BORDER4H+BUTTON_W4+SPACING4, BUTTON_Y4, BUTTON_W4, BUTTON_H4, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER4H+BUTTON_W4+SPACING4+2, BUTTON_Y4+2, BUTTON_W4-4, BUTTON_H4-4, 7, TFT_DARKGREY);

  tft.fillRoundRect(BORDER4H, BUTTON_Y4+BUTTON_H4+SPACING4, BUTTON_W4, BUTTON_H4, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER4H+2, BUTTON_Y4+BUTTON_H4+SPACING4+2, BUTTON_W4-4, BUTTON_H4-4, 7, TFT_DARKGREY);

  tft.fillRoundRect(BORDER4H+BUTTON_W4+SPACING4, BUTTON_Y4+BUTTON_H4+SPACING4, BUTTON_W4, BUTTON_H4, 8, TFT_WHITE);
  tft.fillRoundRect(BORDER4H+BUTTON_W4+SPACING4+2,  BUTTON_Y4+BUTTON_H4+SPACING4+2, BUTTON_W4-4, BUTTON_H4-4, 7, TFT_DARKGREY);

}


