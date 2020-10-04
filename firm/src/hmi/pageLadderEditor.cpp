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
      editingInstructionCode = editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code & CELL_CODE_MASK;
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

  if (touchType){
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
// Draw DELETE CANCEL ACCEPT Buttons in the bottom
//--------------------------------------------------------------------------------

void drawLadderEditorBottomButtons(){
  #define BORDER1        2
  #define SPACING1       2
  #define BUTTON_H1     45
  #define BUTTON_W1    104
  #define BUTTON_Y1     TFT_PIXELS_Y - SPACING1 - BUTTON_H1 // Y where the button starts

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
      if(editingInstructionCode == menuInstructions[indexLadderEditor][index]){
        auxColor = COLOR_BUTTON_INSTRUCTION_SELECTED;
      }
      else{
        auxColor = COLOR_BUTTON_INSTRUCTION;
      }

      if(menuInstructions[indexLadderEditor][index] == BAR_MNEMONIC_CODE){
        if(editingNetwork.Bars[ladderEditorColumn] & FlagsMask[ladderEditorRow]){
          auxColor = COLOR_BUTTON_INSTRUCTION_SELECTED;
        }
        else{
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
      else{
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
  
  if (indexLadderEditor == 2){
    auxColor = COLOR_BUTTON_COLUMN;
  }
  else if(indexLadderEditor == 3){
    auxColor = COLOR_BUTTON_ROW;
  }
  else if(indexLadderEditor == 4){
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

      auxX = auxXcenter - elementsList[indexLadderEditor-2].length()*6 + 1; // Text length offset. Font size 2 is 10 pixel width and 2 px spacing (6 = (10+2)/2)
      tft.setCursor(auxX, BUTTON_Y4+BUTTON_H4*row+SPACING4*row + 37);
      tft.print(elementsList[indexLadderEditor-2]);
    }
  }
}

//--------------------------------------------------------------------------------
// Ladder Editor Page
// Touch Screen parsing for navigation buttons
//--------------------------------------------------------------------------------

void touchLadderEditorNavigation(uint16_t ts_x, uint16_t ts_y){
    
  if(ts_y > TFT_PIXELS_Y - BUTTON_H1 - SPACING1){
    if(ts_x < BUTTON_W1 - SPACING1){                     // DELETE
      deleteElement();
      onlineNetwork = editingNetwork;
    }
    else if(ts_x < BUTTON_W1*2 - SPACING1*2){            // CANCEL
      editingNetwork = onlineNetwork;
    }
    else{                                                // ACCEPT
      onlineNetwork = editingNetwork;
    }
    HMI_Page = PAGE_MainLadder;
  }
  else if(ts_y > TFT_PIXELS_Y - BUTTON_H1 - SPACING1 - BUTTON_H2 - SPACING2){
    if(ts_x < BUTTON_W2 + SPACING2){                     // LEFT ARROW
      if (indexLadderEditor > 0){
        indexLadderEditor--;
      }
      else{
        indexLadderEditor = PAGES_LADDER_EDITOR - 1;
      }
      drawLadderEditor();
    }
    else if(ts_x > TFT_PIXELS_X - BUTTON_W2 - SPACING2){ // RIGHT ARROW
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

  if(ts_y < TFT_PIXELS_Y - BUTTON_H1 - SPACING1 - BUTTON_H2 - SPACING2){ // Touch is in the palette area
    if(indexLadderEditor < 2){                                           // Page 0 and 1 only
      for (uint16_t row = 0; row < 3; row++){                            // Instruction matrix 3 x 5
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
                  HMI_Page = PAGE_EditInstructions1;
                }
                else if (editingInstructionCode < 15){ // Timers and Counters
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode; //LUCAS
                  
                  
                  HMI_Page = PAGE_EditInstructions2;
                }
                else if (editingInstructionCode < 29){ // 16 Bit Math instructions
                  editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = editingInstructionCode; //LUCAS


                  HMI_Page = PAGE_EditInstructions3;
                }
              }
            }
            return;
          }
        }
      }
    }
    else{
      //parsing elements    //lucas
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
    else{
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
  
  if(instructionWidth[editingInstructionCode] == instructionWidth[selectedInstructionCode] && instructionHeight[editingInstructionCode] == instructionHeight[selectedInstructionCode]){
    return 1;
  }
  else{
    uint16_t row, column;

    for(uint16_t width=0; width < instructionWidth[selectedInstructionCode]; width++){
      for(uint16_t height=0; height < instructionHeight[selectedInstructionCode]; height++){

        row = ladderEditorRow + height;
        column = ladderEditorColumn + width;

        if(row >= NET_ROWS){
          messageCode = MESSAGE_NO_ROWS;
          HMI_PageMemory = HMI_Page;
          HMI_Page = PAGE_DialogMessage;
          return 0;
        }
        if(column >= NET_COLUMNS){
          messageCode = MESSAGE_NO_COLUMNS;
          HMI_PageMemory = HMI_Page;
          HMI_Page = PAGE_DialogMessage;
          return 0;
        }
        if(onlineNetwork.Cells[row][column].Code != 0){
          messageCode = MESSAGE_SPACE_USED;
          HMI_PageMemory = HMI_Page;
          HMI_Page = PAGE_DialogMessage;
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

  if( instructionCode == 0){
    // No instruction to delete
  }
  else if(instructionWidth[instructionCode] == 1 && instructionHeight[instructionCode] == 1){
    editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code = 0;
    editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data = 0;
    editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = 0;
  }
  else{
    uint16_t firstRowInstruction = ladderEditorRow - (instructionCode >> 12);
    uint16_t firstColumnInstruction = ladderEditorColumn - (instructionCode >> 15);
  
    for(uint16_t width=0; width < instructionWidth[instructionCode]; width++){
      for(uint16_t height=0; height < instructionHeight[instructionCode]; height++){
        editingNetwork.Cells[firstRowInstruction + height][firstColumnInstruction + width].Code = 0;
        editingNetwork.Cells[firstRowInstruction + height][firstColumnInstruction + width].Data = 0;
        editingNetwork.Cells[firstRowInstruction + height][firstColumnInstruction + width].Type = 0;
      }
    }
  }
}