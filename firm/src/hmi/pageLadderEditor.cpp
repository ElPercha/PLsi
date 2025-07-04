// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

#include "FS.h"
#include "SD.h"
#include "FFat.h"

//--------------------------------------------------------------------------------
// Ladder Editor main Page
//--------------------------------------------------------------------------------

void pageLadderEditor (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if (firstLoad){
      // Adjust to the first Column and Row of instruction. User can select any of the instructions cells
      ladderEditorRow = ladderEditorRow - ((editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code >> 12) & 0x0007);
      ladderEditorColumn = ladderEditorColumn - (editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code >> 15);

      editingInstructionCode = editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code;

      drawLadderEditorBase();
      drawLadderEditor();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    //Nothing to update

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchLadderEditorNavigation(ts_x, ts_y); 
    touchLadderEditor(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Ladder Editor Page full draw 
//--------------------------------------------------------------------------------

void drawLadderEditorBase (void){
  tft.fillScreen(COLOR_LADDER_EDITOR_BACKGROUND);
  drawLadderEditorBottomButtons();
  drawLadderEditorNavigationBar();
}

void drawLadderEditor (void){
  tft.fillRect(0,0,320,145,COLOR_LADDER_EDITOR_BACKGROUND);

  if (indexLadderEditor == 0){
    drawLadderEditorInstructionsMenu();
  }
  if (indexLadderEditor == 1){
    drawLadderEditorInstructionsMenu();
  }
  if (indexLadderEditor == 2){
    drawLadderEditorInstructionsMenu();
  }
  if (indexLadderEditor == 3){
    drawLadderEditorElementsMenu();
  }
  if (indexLadderEditor == 4){
    drawLadderEditorElementsMenu();
  }
  if (indexLadderEditor == 5){
    drawLadderEditorElementsMenu();
  }
}

//--------------------------------------------------------------------------------
// Draw DELETE CANCEL ACCEPT Buttons in the bottom of the page
//--------------------------------------------------------------------------------

void drawLadderEditorBottomButtons(){
  #define BORDER1        2
  #define SPACING1       2
  #define BUTTON_H1     45
  #define BUTTON_W1    104
  #define BUTTON_Y1    TFT_PIXELS_Y - SPACING1 - BUTTON_H1 // Y where the button starts

  tft.fillRoundRect(BORDER1, BUTTON_Y1, BUTTON_W1, BUTTON_H1, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);
  tft.fillRoundRect(BORDER1+1, BUTTON_Y1+1, BUTTON_W1-2, BUTTON_H1-2, 7, COLOR_BUTTON_DELETE_LADDER_EDITOR);

  tft.fillRoundRect(BORDER1+BUTTON_W1+SPACING1, BUTTON_Y1, BUTTON_W1, BUTTON_H1, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);
  tft.fillRoundRect(BORDER1+BUTTON_W1+SPACING1+1, BUTTON_Y1+1, BUTTON_W1-2, BUTTON_H1-2, 7, COLOR_BUTTON_CANCEL_LADDER_EDITOR);

  tft.fillRoundRect(BORDER1+BUTTON_W1*2+SPACING1*2, BUTTON_Y1, BUTTON_W1, BUTTON_H1, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);
  tft.fillRoundRect(BORDER1+BUTTON_W1*2+SPACING1*2+1, BUTTON_Y1+1, BUTTON_W1-2, BUTTON_H1-2, 8, COLOR_BUTTON_ACCEPT_LADDER_EDITOR);

  tft.setTextSize(2);
  tft.setTextColor(COLOR_BUTTON_FONT_LADDER_EDITOR);
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

  tft.fillRoundRect(BORDER2, BUTTON_Y2, BUTTON_W2, BUTTON_H2, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);
  tft.fillRoundRect(BORDER2+1, BUTTON_Y2+1, BUTTON_W2-2, BUTTON_H2-2, 7, COLOR_BUTTON_ARROWS_LADDER_EDITOR);

  tft.fillRoundRect(BORDER2+BUTTON_W2+SPACING2, BUTTON_Y2, BAR_W, BAR_H, 8, COLOR_BAR_LADDER_EDITOR);

  tft.fillRoundRect(BORDER2+BUTTON_W2+SPACING2*2+BAR_W, BUTTON_Y2, BUTTON_W2, BUTTON_H2, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);
  tft.fillRoundRect(BORDER2+BUTTON_W2+SPACING2*2+BAR_W+1, BUTTON_Y2+1, BUTTON_W2-2, BUTTON_H2-2, 7, COLOR_BUTTON_ARROWS_LADDER_EDITOR);

  tft.setTextColor(COLOR_BUTTON_FONT_LADDER_EDITOR);
  tft.setTextSize(2);
  tft.setCursor(26, BUTTON_Y2 + 16);
  tft.print("<<");
  tft.setCursor(269, BUTTON_Y2 + 16);
  tft.print(">>");

  tft.setTextColor(COLOR_BAR_FONT_LADDER_EDITOR);
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

  uint16_t auxX, index, auxColor;

  tft.setTextColor(COLOR_BUTTON_FONT_LADDER_EDITOR);
  tft.setTextSize(2);
  
  for (uint16_t row = 0; row < 3; row++){
    for (uint16_t col = 0; col < 5; col++){
      index = row*5+col;
      
      // Draw Button
      tft.fillRoundRect(BORDER3+BUTTON_W3*col+SPACING3*col, BUTTON_Y3+BUTTON_H3*row+SPACING3*row, BUTTON_W3, BUTTON_H3, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);
      if (editingInstructionCode == menuInstructions[indexLadderEditor][index]){
        auxColor = COLOR_BUTTON_INSTRUCTION_SELECTED;
      }
      else {
        auxColor = COLOR_BUTTON_INSTRUCTION;
      }

      if (menuInstructions[indexLadderEditor][index] == BAR_MNEMONIC_CODE){
        if (editingNetwork.Bars[ladderEditorColumn] & FlagsMask[ladderEditorRow]){
          auxColor = COLOR_BUTTON_INSTRUCTION_SELECTED;
        }
        else {
          auxColor = COLOR_BUTTON_INSTRUCTION;
        }
      }

      tft.fillRoundRect(BORDER3+BUTTON_W3*col+SPACING3*col+1, BUTTON_Y3+BUTTON_H3*row+SPACING3*row+1, BUTTON_W3-2, BUTTON_H3-2, 7, auxColor);

      // Insert Text
      auxX = BORDER3+BUTTON_W3*col+SPACING3*col+BUTTON_W3/2; // Center of button

      if (menuInstructions[indexLadderEditor][index] == BAR_MNEMONIC_CODE){
        auxX = auxX - BAR_MNEMONIC_LENGTH * 6 + 1;
        tft.setCursor(auxX, BUTTON_Y3+BUTTON_H3*row+SPACING3*row + 16);
        tft.print(BAR_MNEMONIC);
      }
      else { 
        auxX = auxX - MnemonicsCodes[menuInstructions[indexLadderEditor][index]].length()*6 + 1;  // Text length offset. Font size 2 is 10 pixel width and 2 px spacing (6 = (10+2)/2)
        tft.setCursor(auxX, BUTTON_Y3+BUTTON_H3*row+SPACING3*row + 16);
        tft.print(MnemonicsCodes[menuInstructions[indexLadderEditor][index]]);
      }
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
  #define BUTTON_W4    156
  #define BUTTON_Y4    BORDER4V

  uint16_t auxX, auxXcenter, index, auxColor=0;
  
  tft.setTextColor(COLOR_BUTTON_FONT_LADDER_EDITOR);
  tft.setTextSize(2);
  
  if (indexLadderEditor == 3){
    auxColor = COLOR_BUTTON_COLUMN;
  }
  else if (indexLadderEditor == 4){
    auxColor = COLOR_BUTTON_ROW;
  }
  else if (indexLadderEditor == 5){
    auxColor = COLOR_BUTTON_NETWORK;
  }

  for (uint16_t row = 0; row < 2; row++){
    for (uint16_t col = 0; col < 2; col++){
      index = row*2+col;

      tft.fillRoundRect(BORDER4H+BUTTON_W4*col+SPACING4*col, BUTTON_Y4+BUTTON_H4*row+SPACING4*row, BUTTON_W4, BUTTON_H4, 8, COLOR_BUTTON_BORDER_LADDER_EDITOR);
      tft.fillRoundRect(BORDER4H+BUTTON_W4*col+SPACING4*col+2, BUTTON_Y4+BUTTON_H4*row+SPACING4*row+2, BUTTON_W4-4, BUTTON_H4-4, 7, auxColor);

      auxXcenter = BORDER4H+BUTTON_W4*col+SPACING4*col+BUTTON_W4/2; // Center of button
      auxX = auxXcenter - elementsFunctions[index].length()*6 + 1;  // Text length offset. Font size 2 is 10 pixel width and 2 px spacing (6 = (10+2)/2)
      tft.setCursor(auxX, BUTTON_Y4+BUTTON_H4*row+SPACING4*row + 15);
      tft.print(elementsFunctions[index]);

      auxX = auxXcenter - elementsList[indexLadderEditor-3].length()*6 + 1; // Text length offset. Font size 2 is 10 pixel width and 2 px spacing (6 = (10+2)/2)
      tft.setCursor(auxX, BUTTON_Y4+BUTTON_H4*row+SPACING4*row + 37);
      tft.print(elementsList[indexLadderEditor-3]);
    }
  }
}

//--------------------------------------------------------------------------------
// Ladder Editor Page
// Touch Screen parsing for navigation buttons
//--------------------------------------------------------------------------------

void touchLadderEditorNavigation(uint16_t ts_x, uint16_t ts_y){
    
  if (ts_y > TFT_PIXELS_Y - BUTTON_H1 - SPACING1){
    if (ts_x < BUTTON_W1 - SPACING1){                     // DELETE
      deleteElement();
      onlineNetwork = editingNetwork;
    }
    else if (ts_x < BUTTON_W1*2 - SPACING1*2){            // CANCEL
      editingNetwork = onlineNetwork;
    }
    else {                                                // ACCEPT
      onlineNetwork = editingNetwork;
    }
    hmiPage = PAGE_MainLadder;
  }
  else if (ts_y > TFT_PIXELS_Y - BUTTON_H1 - SPACING1 - BUTTON_H2 - SPACING2){
    if (ts_x < BUTTON_W2 + SPACING2){                     // LEFT ARROW
      if (indexLadderEditor > 0){
        indexLadderEditor--;
      }
      else {
        indexLadderEditor = PAGES_LADDER_EDITOR - 1;
      }
      drawLadderEditor();
    }
    else if (ts_x > TFT_PIXELS_X - BUTTON_W2 - SPACING2){ // RIGHT ARROW
      indexLadderEditor++;
      if (indexLadderEditor >= PAGES_LADDER_EDITOR){
        indexLadderEditor = 0;
      } 
      drawLadderEditor();
    }
  }
}

//--------------------------------------------------------------------------------
// Ladder Editor Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchLadderEditor(uint16_t ts_x, uint16_t ts_y){
    
  uint16_t index;
  uint16_t halfXpalette = BORDER4H + BUTTON_W4 + SPACING4/2;
  uint16_t halfYpalette = BORDER4V + BUTTON_H4 + SPACING4/2;

  if (ts_y < TFT_PIXELS_Y - BUTTON_H1 - SPACING1 - BUTTON_H2 - SPACING2){ // Touch is in the palette area
    if (indexLadderEditor < 3){                                           // Page 0 and 1 only
      for (uint16_t row = 0; row < 3; row++){                             // Instruction matrix 3 x 5
        for (uint16_t col = 0; col < 5; col++){
          index = row*5+col;
          if(ts_x < BORDER3 + BUTTON_W3 + BUTTON_W3*col + SPACING3*col && ts_y < BORDER3 + BUTTON_H3 + BUTTON_H3*row + SPACING3*row){
            if (menuInstructions[indexLadderEditor][index] == BAR_MNEMONIC_CODE){
              touchLadderEditorToggleBar();
              drawLadderEditorInstructionsMenu();
            }
            else{
              if (checkValidEdition(menuInstructions[indexLadderEditor][index])){ // Validate size and position
                editingInstructionCode = menuInstructions[indexLadderEditor][index];
                if (editingInstructionCode == 0){      // Nop
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode;
                  drawLadderEditorInstructionsMenu();
                }
                else if (editingInstructionCode == 1){ // Connection (Horizontal Bar)
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode;
                  drawLadderEditorInstructionsMenu();
                }
                else if (editingInstructionCode == 2){ // Inversion (Horizontal Bar)
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode;
                  drawLadderEditorInstructionsMenu();
                }
                else if (editingInstructionCode < 10){ // Boolean instructions
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode;
                  hmiPage = PAGE_EditInstructions1;
                }
                else if (editingInstructionCode < 15){ // Timers and Counters
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode;
                  editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Code = editingInstructionCode | 0x1000;
                  instructionFieldSelection = 1;
                  hmiPage = PAGE_EditInstructions2;
                }
                else if (editingInstructionCode < 29){ // 16 Bit Math instructions
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode;
                  editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Code = editingInstructionCode | 0x1000;
                  if (instructionHeight[editingInstructionCode] == 3){
                    editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Code = editingInstructionCode | 0x2000;
                  }
                  instructionFieldSelection = 1;
                  hmiPage = PAGE_EditInstructions3;
                }
                else if (editingInstructionCode < 35){ // 16 Bit Comparisons
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode;
                  editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Code = editingInstructionCode | 0x1000;
                  instructionFieldSelection = 1;
                  hmiPage = PAGE_EditInstructions3;
                }
              }
            }
            return;
          }
        }
      }
    }
    else if (indexLadderEditor == 3){                                     // COLUMN menu 
      if (ts_x < halfXpalette && ts_y < halfYpalette){
        copyColumn();
       }
      else if (ts_x > halfXpalette && ts_y < halfYpalette){
        pasteColumn();
     }
      else if (ts_x < halfXpalette && ts_y > halfYpalette){
        insertColumn();
      }
      else if (ts_x > halfXpalette && ts_y > halfYpalette){
        deleteColumn();
      }
    }
    else if (indexLadderEditor == 4){                                     // ROW menu
      if (ts_x < halfXpalette && ts_y < halfYpalette){
        copyRow();
      }
      else if (ts_x > halfXpalette && ts_y < halfYpalette){
        pasteRow();
      }
      else if (ts_x < halfXpalette && ts_y > halfYpalette){
        insertRow();
      }
      else if (ts_x > halfXpalette && ts_y > halfYpalette){
        deleteRow();
      }
    }
    else if (indexLadderEditor == 5){                                     // NETWORK menu
      if (ts_x < halfXpalette && ts_y < halfYpalette){
        copyNetwork();
      }
      else if (ts_x > halfXpalette && ts_y < halfYpalette){
        pasteNetwork();
      }
      else if (ts_x < halfXpalette && ts_y > halfYpalette){
        insertNetwork();
      }
      else if (ts_x > halfXpalette && ts_y > halfYpalette){
        deleteNetwork();
      }
    }
  }
}

//--------------------------------------------------------------------------------
// Toggle Bar status, exclude last column and last row              
//--------------------------------------------------------------------------------

void touchLadderEditorToggleBar(void){
  if (ladderEditorColumn < NET_COLUMNS && ladderEditorRow < NET_ROWS){
    if (editingNetwork.Bars[ladderEditorColumn] & FlagsMask[ladderEditorRow]){
      uint16_t FlagMaskInverted = 65535;
      FlagMaskInverted = FlagMaskInverted ^ FlagsMask[ladderEditorRow];
      editingNetwork.Bars[ladderEditorColumn] = editingNetwork.Bars[ladderEditorColumn] & FlagMaskInverted; 
    }
    else {
      editingNetwork.Bars[ladderEditorColumn] = editingNetwork.Bars[ladderEditorColumn] | FlagsMask[ladderEditorRow]; 
    }
  }              
}

//--------------------------------------------------------------------------------
// Validates the edition in terms of size and position
//   New instruction should have the same size format 
//    or
//   New Instruction must have enough space in the network 
//--------------------------------------------------------------------------------

uint16_t checkValidEdition(uint16_t selectedInstructionCode){
  
  if (instructionWidth[editingInstructionCode] == instructionWidth[selectedInstructionCode] && instructionHeight[editingInstructionCode] == instructionHeight[selectedInstructionCode]){
    return 1;
  }
  else {
    uint16_t row, column;

    for (uint16_t width=0; width < instructionWidth[selectedInstructionCode]; width++){
      for (uint16_t height=0; height < instructionHeight[selectedInstructionCode]; height++){

        row = ladderEditorRow + height;
        column = ladderEditorColumn + width;

        if (row >= NET_ROWS){
          messageCode = MESSAGE_NO_ROWS;
          hmiPageMemory = hmiPage;
          hmiPage = PAGE_DialogMessage;
          return 0;
        }
        if (column >= NET_COLUMNS){
          messageCode = MESSAGE_NO_COLUMNS;
          hmiPageMemory = hmiPage;
          hmiPage = PAGE_DialogMessage;
          return 0;
        }
        if (onlineNetwork.Cells[row][column].Code != 0){
          messageCode = MESSAGE_SPACE_USED;
          hmiPageMemory = hmiPage;
          hmiPage = PAGE_DialogMessage;
          return 0;
        }       
      }
    }
    return 1;
  }
}

//--------------------------------------------------------------------------------
// Delete selected instruction
// Instructions bigger than one cell are defined on subsequent cells using Index code as follows:
//
//  Byte 1	| Byte 1	 |			Byte 0    |
//  Index		| Instruction Code 12 bits  |
//								
//  0	0	0	0		Instruction is simple height cell or it is the first cell of a multiple cells instruction			
//  x	0	0	1		Second cell for a multiple cell height instruction			
//  x	0	1	0		Third cell for a multiple cell height instruction			
//  x	0	1	1		Fourth cell for a multiple cell height instruction			
//  x	1	0	0		Fifth cell for a multiple cell height instruction			
//  1	x	x	x		Second column for a multiple columns instruction			
//
//--------------------------------------------------------------------------------

void deleteElement(void){

  uint16_t instructionCode = editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code;

  if (instructionCode == 0){
    // No instruction to delete
  }
  else if (instructionWidth[instructionCode] == 1 && instructionHeight[instructionCode] == 1){
    editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = 0;
    editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data = 0;
    editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = 0;
  }
  else {
    for (uint16_t width=0; width < instructionWidth[instructionCode]; width++){
      for (uint16_t height=0; height < instructionHeight[instructionCode]; height++){
        editingNetwork.Cells[ladderEditorRow + height][ladderEditorColumn + width].Code = 0;
        editingNetwork.Cells[ladderEditorRow + height][ladderEditorColumn + width].Data = 0;
        editingNetwork.Cells[ladderEditorRow + height][ladderEditorColumn + width].Type = 0;
      }
    }
  }
}

//--------------------------------------------------------------------------------
// Elements edition: Copy Column 
//--------------------------------------------------------------------------------

void copyColumn(void){
  if (columnContainsWideInstruction(ladderEditorColumn)){
    messageCode = MESSAGE_CANNOT_COPY_COLUMN;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  for (uint16_t row = 0; row < NET_ROWS; row++){
    copyMemoryColumn.column[row] = editingNetwork.Cells[row][ladderEditorColumn];
  }
  copyMemoryColumn.bar = editingNetwork.Bars[ladderEditorColumn];
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Paste Column 
//--------------------------------------------------------------------------------

void pasteColumn(void){
  if (!columnIsEmpty(ladderEditorColumn)){
    messageCode = MESSAGE_COLUMN_NOT_EMPTY;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  for (uint16_t row = 0; row < NET_ROWS; row++){
    editingNetwork.Cells[row][ladderEditorColumn] = copyMemoryColumn.column[row];
  }
  editingNetwork.Bars[ladderEditorColumn] = copyMemoryColumn.bar;
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Insert Column 
//--------------------------------------------------------------------------------

void insertColumn(void){
  if (!columnIsEmpty(NET_COLUMNS-1)){
    messageCode = MESSAGE_CANNOT_INSERT_COLUMN;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  for (uint16_t row = 0; row < NET_ROWS; row++){
    if ((editingNetwork.Cells[row][ladderEditorColumn].Code >> 15) == 1){
      messageCode = MESSAGE_CANNOT_SPLIT_WIDE_INSTR;
      hmiPageMemory = hmiPage;
      hmiPage = PAGE_DialogMessage;
      return;
    }
  }
  for (int16_t column = NET_COLUMNS-1; column > ladderEditorColumn; column--) {
    for (uint16_t row = 0; row < NET_ROWS; row++){
      editingNetwork.Cells[row][column] = editingNetwork.Cells[row][column-1];
    }
    editingNetwork.Bars[column] = editingNetwork.Bars[column-1];
  }
  deleteGivenColumn(ladderEditorColumn);
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Delete Column 
//    If instruction is double width, it cannot be splitted -> User Message
//    If column is not empty: delete it
//    If column is empty: Shift Newtwork content to left and delete last column
//--------------------------------------------------------------------------------

void deleteColumn(void){
  if (columnContainsWideInstruction(ladderEditorColumn)){
    messageCode = MESSAGE_CANNOT_DELETE_COLUMN;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  else if (!columnIsEmpty(ladderEditorColumn)){
    deleteGivenColumn(ladderEditorColumn);
  }
  else { 
    for (int16_t column = ladderEditorColumn; column < NET_COLUMNS-1; column++) {
      for (uint16_t row = 0; row < NET_ROWS; row++){
        editingNetwork.Cells[row][column] = editingNetwork.Cells[row][column+1];
      }
    }
    for (int16_t column = ladderEditorColumn; column < NET_COLUMNS-2; column++) { //dont bring Bars from column 5, they doesn't exist
      editingNetwork.Bars[column] = editingNetwork.Bars[column+1];
    }  
    editingNetwork.Bars[NET_COLUMNS-2] = 0; // This is because it supposed to copy Bars from Column 5 with 0 value but it doesn't happen
    deleteGivenColumn(NET_COLUMNS-1);
  }
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Copy Row
//--------------------------------------------------------------------------------

void copyRow(void){
  if (rowContainsHighInstruction(ladderEditorRow)){
    messageCode = MESSAGE_CANNOT_COPY_ROW;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  for (uint16_t col = 0; col < NET_COLUMNS; col++){
    copyMemoryRow.row[col] = editingNetwork.Cells[ladderEditorRow][col];
  }
  for (uint16_t col = 0; col < NET_COLUMNS-1; col++){
    if (editingNetwork.Bars[col] & FlagsMask[ladderEditorRow]){
      copyMemoryRow.bar |= FlagsMask[col]; 
    }
    else {
      copyMemoryRow.bar &= FlagsMaskAnd[col]; 
    }
  }
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Paste Row 
//--------------------------------------------------------------------------------

void pasteRow(void){
  if (!rowIsEmpty(ladderEditorRow)){
    messageCode = MESSAGE_ROW_NOT_EMPTY;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  for (uint16_t col = 0; col < NET_COLUMNS; col++){
    editingNetwork.Cells[ladderEditorRow][col] = copyMemoryRow.row[col];
  }
  for (uint16_t col = 0; col < NET_COLUMNS-1; col++){
    if (copyMemoryRow.bar & FlagsMask[col]){
      editingNetwork.Bars[col] |= FlagsMask[ladderEditorRow]; 
    }
    else {
      editingNetwork.Bars[col] &= FlagsMaskAnd[ladderEditorRow]; 
    }
  }
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Insert Row
//--------------------------------------------------------------------------------

void insertRow(void){
  if (!rowIsEmpty(NET_ROWS-1)){
    messageCode = MESSAGE_CANNOT_INSERT_ROW;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  for (uint16_t col = 0; col < NET_ROWS; col++){
    if(((editingNetwork.Cells[ladderEditorRow][col].Code >> 12) & 0x0007) >= 1){ //0x0007 to remove higher bit that represent the width and not the height
      messageCode = MESSAGE_CANNOT_SPLIT_HIGH_INSTR;
      hmiPageMemory = hmiPage;
      hmiPage = PAGE_DialogMessage;
      return;
    }
  }
  for (int16_t row = NET_ROWS-1; row > ladderEditorRow; row--) {
    for (uint16_t col = 0; col < NET_COLUMNS; col++){
      editingNetwork.Cells[row][col] = editingNetwork.Cells[row-1][col];
    }
  }
  for (int16_t row = NET_ROWS-2; row > ladderEditorRow; row--) {
    for (uint16_t col = 0; col < NET_COLUMNS-1; col++){
      if (editingNetwork.Bars[col] & FlagsMask[row]){
        editingNetwork.Bars[col] |= FlagsMask[row+1]; 
      }
      else{
        editingNetwork.Bars[col] &= FlagsMaskAnd[row+1]; 
      }
    }
  }  
  deleteGivenRow(ladderEditorRow);
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Delete Row
//--------------------------------------------------------------------------------

void deleteRow(void){
  if (rowContainsHighInstruction(ladderEditorRow)){
    messageCode = MESSAGE_CANNOT_DELETE_ROW;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  else if (!rowIsEmpty(ladderEditorRow)){
    deleteGivenRow(ladderEditorRow);
  }
  else { // Row is empty, shift network up from selected row
    for (int16_t row = ladderEditorRow; row < NET_ROWS-1; row++) {
      for (uint16_t col = 0; col < NET_COLUMNS; col++){
        editingNetwork.Cells[row][col] = editingNetwork.Cells[row+1][col];
      }
      for (uint16_t col = 0; col < NET_COLUMNS-1; col++){
        if (row == NET_ROWS-2){
          editingNetwork.Bars[col] &= FlagsMaskAnd[row]; 
        }
        else if (editingNetwork.Bars[col] & FlagsMask[row+1]){
          editingNetwork.Bars[col] |= FlagsMask[row]; 
        }
        else {
          editingNetwork.Bars[col] &= FlagsMaskAnd[row]; 
        }
      }
    }
    deleteGivenRow(NET_ROWS-1);
  }
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Copy Network
//--------------------------------------------------------------------------------

void copyNetwork(void){
  copyMemoryNetwork = editingNetwork;
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Paste Network
//--------------------------------------------------------------------------------

void pasteNetwork(void){
  if (!networkIsEmpty()){
    messageCode = MESSAGE_NETWORK_NOT_EMPTY;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  editingNetwork = copyMemoryNetwork;
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Insert Network
// It has to be requested to tskLadder because it is not available on local RAM
// And it has to be saved on SPIFSS memory
//--------------------------------------------------------------------------------

void insertNetwork(void){
  if (!lastNetworkIsEmpty()){
    messageCode = MESSAGE_CANNOT_INSERT_NETWORK;
    hmiPageMemory = hmiPage;
    hmiPage = PAGE_DialogMessage;
    return;
  }
  moveNetworksInsert = showingNetwork + 1;

  while(moveNetworksInsert != 0){
    delay(10);
  }
  editingNetwork = emptyNetwork;
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Elements edition: Delete Network
// It has to be requested to tskLadder because it is not available on local RAM
// And it has to be saved on SPIFSS memory
//--------------------------------------------------------------------------------

void deleteNetwork(void){
  if (!networkIsEmpty()){
    editingNetwork = emptyNetwork;
  }
  else{
    moveNetworksDelete = showingNetwork + 1;

    while(moveNetworksDelete != 0){
      delay(10);
    }
  }
  elementsEditionAccept();
}

//--------------------------------------------------------------------------------
// Return True if Column does not have an instruction wider than 1 Cell 
// Column can be deleted or copy
//--------------------------------------------------------------------------------

uint16_t columnContainsWideInstruction(uint16_t column){
  for (uint16_t row = 0; row < NET_ROWS; row++){
    if(instructionWidth[editingNetwork.Cells[row][column].Code & CELL_CODE_MASK] > 1){
      return 1;
    };
  }
  return 0;
}

//--------------------------------------------------------------------------------
// Return True if Column is empty
// Used to validate INSERT and PASTE column
//--------------------------------------------------------------------------------

uint16_t columnIsEmpty(uint16_t column){
  for (uint16_t row = 0; row < NET_ROWS; row++){
    if(editingNetwork.Cells[row][column].Code != 0){
      return 0;
    };
  }
  return 1;
}

//--------------------------------------------------------------------------------
// Delete column with no control
// Must be previously checked for double column instructions
//--------------------------------------------------------------------------------

void deleteGivenColumn(uint16_t column){
  for (uint16_t row = 0; row < NET_ROWS; row++){
    editingNetwork.Cells[row][column].Code = 0;
    editingNetwork.Cells[row][column].Data = 0;
    editingNetwork.Cells[row][column].Type = 0;
  }
  editingNetwork.Bars[column] = 0;
}

//--------------------------------------------------------------------------------
// Return True if Row does not have an instruction higher than 1 Cell 
// Row can be deleted or copy
//--------------------------------------------------------------------------------

uint16_t rowContainsHighInstruction(uint16_t row){
  for (uint16_t col = 0; col < NET_COLUMNS; col++){
    if(instructionHeight[editingNetwork.Cells[row][col].Code & CELL_CODE_MASK] > 1){
      return 1;
    };
  }
  return 0;
}

//--------------------------------------------------------------------------------
// Return True if Row is empty
// Used to validate INSERT and PASTE column
//--------------------------------------------------------------------------------

uint16_t rowIsEmpty(uint16_t row){
  for (uint16_t col = 0; col < NET_COLUMNS; col++){
    if(editingNetwork.Cells[row][col].Code != 0){
      return 0;
    };
  }
  return 1;
}

//--------------------------------------------------------------------------------
// Delete Row with no control
// Must be previously checked for double+ height instructions
//--------------------------------------------------------------------------------

void deleteGivenRow(uint16_t row){
  for (uint16_t col = 0; col < NET_COLUMNS; col++){
    editingNetwork.Cells[row][col].Code = 0;
    editingNetwork.Cells[row][col].Data = 0;
    editingNetwork.Cells[row][col].Type = 0;
  }
  for (uint16_t col = 0; col < NET_COLUMNS-1; col++){
    editingNetwork.Bars[col] &= FlagsMaskAnd[row]; 
  }
}

//--------------------------------------------------------------------------------
// Elements edition - Go back and accept change
//--------------------------------------------------------------------------------

void elementsEditionAccept(void){
  onlineNetwork = editingNetwork;
  hmiPage = PAGE_MainLadder;
}

//--------------------------------------------------------------------------------
// Elements edition - Evaluate Network, Return 1 if Network is empty
//--------------------------------------------------------------------------------

uint16_t networkIsEmpty(void){
  for (uint16_t row = 0; row < NET_ROWS; row++){
    for (uint16_t col = 0; col < NET_COLUMNS; col++){
      if (editingNetwork.Cells[row][col].Code != 0){
        return 0;
      };
    }
  }
  for (uint16_t col = 0; col < NET_COLUMNS-1; col++){
    if (editingNetwork.Bars[col] != 0){
      return 0;
    }
  }
  return 1;
}

//--------------------------------------------------------------------------------
// Evaluates Last network
//--------------------------------------------------------------------------------

uint16_t lastNetworkIsEmpty(void){

  Network auxNetwork;

  FFat.begin(false,"/ffat",1);
  File userProgramFile = FFat.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"r");
  userProgramFile.seek((settings.ladder.NetworksQuantity - 1) * sizeof(auxNetwork));
  userProgramFile.read((uint8_t *)&auxNetwork, sizeof(auxNetwork));
  userProgramFile.close();
  FFat.end();

  for (uint16_t row = 0; row < NET_ROWS; row++){
    for (uint16_t col = 0; col < NET_COLUMNS; col++){
      if (auxNetwork.Cells[row][col].Code != 0){
        return 0;
      };
    }
  }
  for (uint16_t col = 0; col < NET_COLUMNS-1; col++){
    if (auxNetwork.Bars[col] != 0){
      return 0;
    }
  }
  return 1;
}

