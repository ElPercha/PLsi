#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
//Ladder Details main Page
//--------------------------------------------------------------------------------

void pageEditLadderInstructions1 (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){

  //-------------------------------
  // capture input Value command
  //-------------------------------

  if (numericValueAccepted){
    if (uint16_t(numericValue) <= getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type)){
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data = uint16_t(numericValue);
    }
    numericValueAccepted = 0;
  }

  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if (firstLoad){
      drawEditLadderInstructions1();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchEditLadderInstructionsNavigation(ts_x, ts_y);
    touchEditLadderInstructions1(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Edit Ladder Instructions Page full draw 
//--------------------------------------------------------------------------------

void drawEditLadderInstructions1 (void){
  #define BUTTON_Y11      5
  #define BORDER11        5
  #define BUTTON_H11     50
  #define BUTTON_W11    100
  
  #define BUTTON_Y12      BUTTON_Y11 * 2 + BUTTON_H11
  #define BORDER12        4
  #define BUTTON_H12     45
  #define BUTTON_W12     75

  tft.fillScreen(COLOR_LADDER_INSTRUC_BACKGROUND);

  drawLadderEditorInstructionsNavigation();

  for(uint16_t i = 0; i < 3; i++){
    tft.fillRoundRect(BUTTON_W11*i+BORDER11*(i+1), BUTTON_Y11, BUTTON_W11, BUTTON_H11, 8, COLOR_BUTTON_BORDER_INSTRUC_EDITOR);
    tft.fillRoundRect(BUTTON_W11*i+BORDER11*(i+1)+1, BUTTON_Y11+1, BUTTON_W11-2, BUTTON_H11-2, 8, COLOR_BUTTON_INSTRUC_BOOLEAN_EDITOR);
  }

  for(uint16_t i = 0; i < 4; i++){
    tft.fillRoundRect(BUTTON_W12*i+BORDER12*(i+1), BUTTON_Y12, BUTTON_W12, BUTTON_H12, 8, COLOR_BUTTON_BORDER_INSTRUC_EDITOR);
    tft.fillRoundRect(BUTTON_W12*i+BORDER12*(i+1)+1, BUTTON_Y12+1, BUTTON_W12-2, BUTTON_H12-2, 8, COLOR_BUTTON_INSTRUC_BOOLEAN_EDITOR);
  }

  tft.setTextColor(COLOR_BUTTON_FONT_INSTRUC_EDITOR);
  tft.setTextSize(3);
  tft.setCursor(48, BUTTON_Y11 + 13);
  tft.print("I");
  tft.setCursor(153, BUTTON_Y11 + 13);
  tft.print("M");
  tft.setCursor(258, BUTTON_Y11 + 13);
  tft.print("Q");

  tft.setTextSize(2);
  tft.setCursor(30, BUTTON_Y12 + 16);
  tft.print("Td");
  tft.setCursor(111, BUTTON_Y12 + 16);
  tft.print("Tr");
  tft.setCursor(188, BUTTON_Y12 + 16);
  tft.print("Cd");
  tft.setCursor(267, BUTTON_Y12 + 16);
  tft.print("Cr");

  drawInstructionsEditorBooleanBar();
}

//--------------------------------------------------------------------------------
// Draw and Update Bar for Memory address during Boolean Edition
//--------------------------------------------------------------------------------

void drawInstructionsEditorBooleanBar(void){
  #define BAR_Y           BUTTON_Y12 + BUTTON_Y11 + BUTTON_H12 + 3
  #define BAR_BORDER     40
  #define BAR_H11        73
  #define BAR_W11       240

  tft.fillRoundRect(BAR_BORDER, BAR_Y, BAR_W11, BAR_H11, 8, COLOR_BAR_INSTRUC_EDITOR);
  
  tft.setTextColor(COLOR_BAR_FONT1_INSTRUC_EDITOR);
  tft.setTextSize(2);
  String auxString = MnemonicsTypes[editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type] + "0  to  " + 
                     MnemonicsTypes[editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type] + 
                     String(getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type));
  tft.setCursor(TFT_PIXELS_X/2 - auxString.length() * 6, BAR_Y + 5);
  tft.print(auxString);

  tft.setTextColor(COLOR_BAR_FONT_INSTRUC_EDITOR);
  tft.setTextSize(4);
  auxString = MnemonicsTypes[editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type] +" " + String(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data);
  tft.setCursor(TFT_PIXELS_X/2 - auxString.length() * 12, BAR_Y + 32);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchEditLadderInstructions1(uint16_t ts_x, uint16_t ts_y){
  if (ts_y < BUTTON_Y12){
    if (ts_x < BUTTON_W11 + BORDER11){                    // I
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeI;
    }
    else if (ts_x < BUTTON_W11*2+BORDER11*2){             // M
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeM;
    }
    else {                                                // Q
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeQ;
    }
    limitMemoryRange();
    drawInstructionsEditorBooleanBar();
  }
  else if (ts_y < BAR_Y){
    if (ts_x < BUTTON_W12 + BORDER12){                    // Td
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeTd;
    }
    else if (ts_x < BUTTON_W12*2+BORDER12*2){             // Tr
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeTr;
    }
    else if (ts_x < BUTTON_W12*3+BORDER12*3){             // Cd
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeCd;
    }
    else {                                                // Cr
      editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeCr;
    }
    limitMemoryRange();
    drawInstructionsEditorBooleanBar();
  }
  else if (ts_y < BAR_Y + BAR_H11){
    HMI_PageMemory = HMI_Page;
    HMI_Page = PAGE_InputNumber;  
  }
}
