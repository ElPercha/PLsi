#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
//Ladder Details main Page
//--------------------------------------------------------------------------------

void pageEditLadderInstructions3 (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  
  //-------------------------------
  // capture input Value command
  //-------------------------------

  if (numericValueAccepted){
    // Validate that the Memory address is in a valid range for the given Type
    if (uint16_t(numericValue) <= getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow + instructionFieldSelection - 1][ladderEditorColumn].Type)){
      editingNetwork.Cells[ladderEditorRow + instructionFieldSelection - 1][ladderEditorColumn].Data = uint16_t(numericValue);
    } 
    numericValueAccepted = 0;
  }

  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      // Control and Default fields to a Valid Type if required
      if (editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type < TypeIW || editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type > TypeK){
        editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type = TypeD; //Default to D
      }
      if (instructionHeight[editingInstructionCode] == 2){
        if (editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type < TypeIW || editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type >= TypeK){
          editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type = TypeD; //Default to D - Cannot write a K (constant)
        }
      }
      if (instructionHeight[editingInstructionCode] == 3){
        if (editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type < TypeIW || editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type > TypeK){
          editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type = TypeD; //Default to D - Cannot write a K (constant)
        }
        if (editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Type < TypeIW || editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Type >= TypeK){
          editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Type = TypeD; //Default to D - Cannot write a K (constant)
        }
      }
      // Control and Default fields to a Valid Memory Range if required
      if (editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data > getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type)){
        editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data = getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type);
      } 
      if (editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Data > getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type)){
        editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Data = getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type);
      } 
      if (instructionHeight[editingInstructionCode] == 3){
        if (editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Data > getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Type)){
          editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Data = getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Type);
        } 
      }
      
      // Draw Page
      drawEditLadderInstructions3();
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
    touchEditLadderInstructions3(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Edit Ladder Instructions Page full draw 
//--------------------------------------------------------------------------------

void drawEditLadderInstructions3 (void){
  #define INSTRUCTION_BORDER       2
  #define INSTRUCTION_H3         177
  #define INSTRUCTION_H2         127
  #define INSTRUCTION_W          120 
 
  #define INSTRUCTION_BORDER1      5
  #define INSTRUCTION_TEXT        11
  #define INSTRUCTION_BUTTON_Y    30
  #define INSTRUCTION_BUTTON_H    45
  #define INSTRUCTION_BUTTON_W   114
  #define INSTRUCTION_BUTTON_X    INSTRUCTION_BORDER + INSTRUCTION_W/2 - INSTRUCTION_BUTTON_W/2

  //clear the screen and draw the buttons at bottom of page
  tft.fillScreen(COLOR_LADDER_INSTRUC_BACKGROUND);
  drawLadderEditorInstructionsNavigation();

  // Print base rectangle "Instruction box"
  if (instructionHeight[editingInstructionCode] == 2){
    tft.fillRoundRect(INSTRUCTION_BORDER, INSTRUCTION_BORDER, INSTRUCTION_W, INSTRUCTION_H2, 8, COLOR_INSTRUCTION_EDITION);
  }
  else if (instructionHeight[editingInstructionCode] == 3){
    tft.fillRoundRect(INSTRUCTION_BORDER, INSTRUCTION_BORDER, INSTRUCTION_W, INSTRUCTION_H3, 8, COLOR_INSTRUCTION_EDITION);
  }
  
  // Print Header - Instruction Mnemonic
  tft.setTextColor(COLOR_TIMER_EDITION_TEXT);
  tft.setTextSize(2);
  String auxString = MnemonicsCodes[editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Code];
  tft.setCursor(INSTRUCTION_W/2 + INSTRUCTION_BORDER - auxString.length()*6, INSTRUCTION_TEXT);
  tft.print(auxString);

  // Draw first Field
  updateInstructionEditField1();
  
  // Draw second Field
  updateInstructionEditField2();

  // Draw third Field
  if (instructionHeight[editingInstructionCode] == 3){
    updateInstructionEditField3();
  }

  // Draw Palette of Data Types Top Right
  drawDataTypesPalette();

  // Draw Bar for address edition
  drawBarAddressEdition();
}

//--------------------------------------------------------------------------------
// Update First Field during Instruction edition
//--------------------------------------------------------------------------------

void updateInstructionEditField1(void){
  uint32_t auxColor = 0;

  if(instructionFieldSelection == 1){
    auxColor = COLOR_INSTRUCTION_FIELDS1;
  }
  else{
    auxColor = COLOR_INSTRUCTION_FIELDS;
  }
  tft.fillRoundRect(INSTRUCTION_BUTTON_X, INSTRUCTION_BUTTON_Y, INSTRUCTION_BUTTON_W, INSTRUCTION_BUTTON_H, 8, auxColor);

  tft.setTextSize(3);
  tft.setTextColor(COLOR_INSTRUCTION_COUNTER_TEXT);
  String auxString = MnemonicsTypes[editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type] + String(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data);
  tft.setCursor(INSTRUCTION_BORDER + INSTRUCTION_W/2 - auxString.length() * 9, INSTRUCTION_BUTTON_Y + 13);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Update Second Field during Instruction edition
//--------------------------------------------------------------------------------

void updateInstructionEditField2(void){
  uint32_t auxColor = 0;

  if(instructionFieldSelection == 2){
    auxColor = COLOR_INSTRUCTION_FIELDS1;
  }
  else{
    auxColor = COLOR_INSTRUCTION_FIELDS;
  }
  tft.fillRoundRect(INSTRUCTION_BUTTON_X, INSTRUCTION_BUTTON_Y + INSTRUCTION_BORDER1 + INSTRUCTION_BUTTON_H , INSTRUCTION_BUTTON_W, INSTRUCTION_BUTTON_H, 8, auxColor);

  tft.setTextSize(3);
  tft.setTextColor(COLOR_INSTRUCTION_COUNTER_TEXT);
  String auxString = MnemonicsTypes[editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type] + String(editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Data);
  tft.setCursor(INSTRUCTION_BORDER + INSTRUCTION_W/2 - auxString.length() * 9, INSTRUCTION_BUTTON_Y + INSTRUCTION_BORDER1 + INSTRUCTION_BUTTON_H + 13);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Update Third Field during Instruction edition
//--------------------------------------------------------------------------------

void updateInstructionEditField3(void){
  uint32_t auxColor = 0;

  if(instructionFieldSelection == 3){
    auxColor = COLOR_INSTRUCTION_FIELDS1;
  }
  else{
    auxColor = COLOR_INSTRUCTION_FIELDS;
  }
  tft.fillRoundRect(INSTRUCTION_BUTTON_X, INSTRUCTION_BUTTON_Y + INSTRUCTION_BORDER1*2 + INSTRUCTION_BUTTON_H*2, INSTRUCTION_BUTTON_W, INSTRUCTION_BUTTON_H, 8, auxColor);

  tft.setTextSize(3);
  tft.setTextColor(COLOR_INSTRUCTION_COUNTER_TEXT);
  String auxString = MnemonicsTypes[editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Type] + String(editingNetwork.Cells[ladderEditorRow+2][ladderEditorColumn].Data);
  tft.setCursor(INSTRUCTION_BORDER + INSTRUCTION_W/2 - auxString.length() * 9, INSTRUCTION_BUTTON_Y + INSTRUCTION_BORDER1*2 + INSTRUCTION_BUTTON_H*2 + 13);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Draw Palette of Data Types Top Right
//--------------------------------------------------------------------------------

void drawDataTypesPalette(void){
  #define DATA_TYPE_PAL_X        INSTRUCTION_BORDER + INSTRUCTION_W + 10
  #define DATA_TYPE_PAL_Y        INSTRUCTION_BORDER                
  #define DATA_TYPE_BORDER         2
  #define DATA_TYPE_BUTTON_H      55
  #define DATA_TYPE_BUTTON_W      60

  uint16_t auxX, auxY, index;
  String auxString;

  for (uint16_t row = 0; row < 2; row++){
    for (uint16_t col = 0; col < 3; col++){
      index = row * 3 + col;
      auxX = DATA_TYPE_PAL_X + DATA_TYPE_BORDER*col + DATA_TYPE_BUTTON_W*col;
      auxY = DATA_TYPE_PAL_Y + DATA_TYPE_BORDER*row + DATA_TYPE_BUTTON_H*row;

      // Draw Button
      tft.fillRoundRect(auxX, auxY , DATA_TYPE_BUTTON_W, DATA_TYPE_BUTTON_H, 8, COLOR_PALETTE_BUTTON_BORDER);
      tft.fillRoundRect(auxX + 1, auxY + 1, DATA_TYPE_BUTTON_W - 2, DATA_TYPE_BUTTON_H - 2, 8, COLOR_PALETTE_BUTTON);

      // Insert Text
      auxX = auxX + DATA_TYPE_BUTTON_W/2;
      auxY = auxY + 21;
      tft.setTextSize(2);
      tft.setTextColor(COLOR_PALETTE_TEXT);
      auxString = MnemonicsTypes[menuDataTypes[index]];
      tft.setCursor(auxX - auxString.length() * 6, auxY);
      tft.print(auxString);
    }
  }
}

//--------------------------------------------------------------------------------
// Draw Detailed Bar for Field edition
//--------------------------------------------------------------------------------

void drawBarAddressEdition(void){
  #define DATA_TYPE_BAR_X          DATA_TYPE_PAL_X
  #define DATA_TYPE_BAR_Y          DATA_TYPE_PAL_Y + DATA_TYPE_BORDER*2 + DATA_TYPE_BUTTON_H*2 + 10
  #define DATA_TYPE_BAR_W          184
  #define DATA_TYPE_BAR_H          53

  // Draw bar
  tft.fillRoundRect(DATA_TYPE_BAR_X, DATA_TYPE_BAR_Y , DATA_TYPE_BAR_W, DATA_TYPE_BAR_H, 8, COLOR_PALETTE_BAR);

  // Insert Text
  tft.setTextSize(4);
  tft.setTextColor(COLOR_PALETTE_BAR_TEXT);
  String auxString = MnemonicsTypes[editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Type] + 
                             String(editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Data);
  tft.setCursor(DATA_TYPE_BAR_X + DATA_TYPE_BAR_W/2 - auxString.length() * 12, DATA_TYPE_BAR_Y + 12);
  tft.print(auxString);
}

//--------------------------------------------------------------------------------
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchEditLadderInstructions3(uint16_t ts_x, uint16_t ts_y){

  #define TOUCH_INSTRUCTION_W      INSTRUCTION_BORDER + INSTRUCTION_W 
  #define TOUCH_INSTRUCTION_H1     INSTRUCTION_BUTTON_Y + INSTRUCTION_BUTTON_H
  #define TOUCH_INSTRUCTION_H2     INSTRUCTION_BUTTON_Y + INSTRUCTION_BUTTON_H*2 + INSTRUCTION_BORDER1
  #define TOUCH_INSTRUCTION_H3     INSTRUCTION_BUTTON_Y + INSTRUCTION_BUTTON_H*3 + INSTRUCTION_BORDER1*2
  #define TOUCH_PALETTE_W          DATA_TYPE_BORDER + DATA_TYPE_BUTTON_W
  #define TOUCH_PALETTE_H          DATA_TYPE_BORDER + DATA_TYPE_BUTTON_H
  #define TOUCH_BAR_Y_HIGH         TOUCH_PALETTE_H*2
  #define TOUCH_BAR_Y_LOW          TOUCH_BAR_Y_HIGH + DATA_TYPE_BAR_H

  // Parse touch of instructions fields 1 to 3
  if(ts_x < TOUCH_INSTRUCTION_W && ts_y < TOUCH_INSTRUCTION_H3){
    if(ts_y < TOUCH_INSTRUCTION_H1){
      instructionFieldSelection = 1;
    }
    else if(ts_y < TOUCH_INSTRUCTION_H2){
      instructionFieldSelection = 2;
    }
    else if(instructionHeight[editingInstructionCode] == 3){
      instructionFieldSelection = 3;
    }
    updateInstruction16Bit();
  }

  if (ts_x > DATA_TYPE_PAL_X && ts_y < TOUCH_PALETTE_H*2){
    if(ts_y < TOUCH_PALETTE_H){
      if(ts_x < DATA_TYPE_PAL_X + TOUCH_PALETTE_W){
        editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Type = menuDataTypes[0];
      }
      else if(ts_x < DATA_TYPE_PAL_X + TOUCH_PALETTE_W*2){
        editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Type = menuDataTypes[1];
      }
      else if(ts_x < DATA_TYPE_PAL_X + TOUCH_PALETTE_W*3){
        editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Type = menuDataTypes[2];
      }
    }
    else if(ts_y < TOUCH_PALETTE_H*2){
      if(ts_x < DATA_TYPE_PAL_X + TOUCH_PALETTE_W){
        if(instructionFieldSelection != instructionHeight[editingInstructionCode]){  // Don't allow IW Type in output of instruction
          editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Type = menuDataTypes[3];
        }
      }
      else if(ts_x < DATA_TYPE_PAL_X + TOUCH_PALETTE_W*2){
        if(instructionFieldSelection != instructionHeight[editingInstructionCode]){  // Don't allow K Type in output of instruction
          editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Type = menuDataTypes[4];
        }
      }
      else if(ts_x < DATA_TYPE_PAL_X + TOUCH_PALETTE_W*3){
        editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Type = menuDataTypes[5];
      }
    }
    if (editingNetwork.Cells[ladderEditorRow+instructionFieldSelection-1][ladderEditorColumn].Data > getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow + instructionFieldSelection - 1][ladderEditorColumn].Type)){
      editingNetwork.Cells[ladderEditorRow + instructionFieldSelection - 1][ladderEditorColumn].Data = getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow + instructionFieldSelection - 1][ladderEditorColumn].Type);
    } 
    updateInstruction16Bit();
  }

  // Parse touch of Memory address modification --> call Keyboard
  if(ts_x > DATA_TYPE_PAL_X && ts_y > TOUCH_BAR_Y_HIGH && ts_y < TOUCH_BAR_Y_LOW){
    HMI_PageMemory = HMI_Page;
    HMI_Page = PAGE_InputNumber;
  }
}

//--------------------------------------------------------------------------------
// Draw and Update required screen for 16 bit instructions editing
//--------------------------------------------------------------------------------

void updateInstruction16Bit(void){
  drawBarAddressEdition();
  updateInstructionEditField1();
  updateInstructionEditField2();
  if(instructionHeight[editingInstructionCode] == 3){
    updateInstructionEditField3();
  }
}