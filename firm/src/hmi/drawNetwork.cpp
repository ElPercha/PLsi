#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Ladder Logic Network drawing functions
//--------------------------------------------------------------------------------

void drawNetwork (void){

  typedef void (*DrawLadderLogic) (int n, int c, int r, int f);
  DrawLadderLogic drawLadder [] =
  {
    drawNop,    
    drawConn,   
    drawNeg,
    drawNo,
    drawNc,
    drawRe,
    drawFe,
    drawCoil,
    drawCoilL,
    drawCoilU,
    drawTon,
    drawToff,
    drawTp,
    drawCtu,
    drawCtd,
    drawMove,
    drawSub,
    drawAdd,
    drawMul,
    drawDiv,
    drawMod,
    drawShl,
    drawShr,
    drawRol,
    drawRor,
    drawAnd,
    drawOr,
    drawXor,
    drawNot
  };

  // Update Power Bar ststus
  drawPowerBar();
  
  // Draw / Update Ladder instructions  
  for (int c=0; c<NET_COLUMNS; c++){
    for (int r=0; r<NET_ROWS; r++){
      if (onlineNetwork.Cells[r][c].Code > 0) {
        if (onlineNetwork.Cells[r][c].Code >=    FIRST_INVALID_CODE){
          Serial.println("TASK HMI - CORE 0 - INSTRUCTION CODE INVALID: ");
          Serial.print("   - Network (absolute number): ");
          Serial.println(showingNetwork);
          Serial.print("   - Row: ");
          Serial.println(r);
          Serial.print("   - Column: ");
          Serial.println(c);
          Serial.print("   - Code: ");
          Serial.println(onlineNetwork.Cells[r][c].Code);
          onlineNetwork.Cells[r][c].Code = 0;
        }
     
        drawLadder [onlineNetwork.Cells[r][c].Code](r, c, GetFlag(r, c), GetData(r, c));
      } 
    } 
  }
  // Draw / Update Ladder bars
  for (int c=0; c<NET_COLUMNS-1; c++){
    for (int r=0; r<NET_ROWS-1; r++){
      if (onlineNetwork.Bars[c] & FlagsMask[r]){
        if (NetworkFlagsOnline[c] & FlagsMask[r]){
          drawBar (r, c, COLOR_ON);   
        }
        else{
          drawBar (r, c, COLOR_OFF);   
        }
      }
    }
  }
}

int GetData (int r, int c){
  int returnData = 0;
  switch (onlineNetwork.Cells[r][c].Type) {
    case TypeM:
      returnData = int(M[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeQ:
      returnData = int(Q[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeI:
      returnData = int(I[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeCd:
      returnData = int(Cd[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeCr:
      returnData = int(Cr[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeTd:
      returnData = int(Td[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeTr:
      returnData = int(Tr[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeIW:
      returnData = int(IW[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeQW:
      returnData = int(QW[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeC:
      returnData = int(C[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeD:
      returnData = int(D[onlineNetwork.Cells[r][c].Data]);
      break;
    case TypeT:
      returnData = int(Timers[onlineNetwork.Cells[r][c].Data].ACC);
      break;
    case TypeK:
      returnData = int(onlineNetwork.Cells[r][c].Data);
      break;
//    case TypeR:
//      returnData = R[onlineNetwork.Cells[r][c].Data];
//      break;
    default:
      ;
    break;
  }
  return returnData;
}

int GetFlag (int r, int c){
  int returnData;

  if (c == 0){
    if (settings.ladder.PLCstate == RUNNING){returnData = 1;}
    else                    {returnData = 0;}
  }
  else{
    returnData = (NetworkFlagsOnline[c-1] & FlagsMask[r]);
  }
  return returnData;  
}

//--------------------------------------------------------------------------------
// Tags on Bits Instructions
//--------------------------------------------------------------------------------

void drawTagBit (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  
  String tagString = MnemonicsTypes[onlineNetwork.Cells[Row][Column].Type] + String(onlineNetwork.Cells[Row][Column].Data);

  tft.setCursor(((7-tagString.length())*3)+5+Xbase, 4+Ybase);
  tft.setTextColor(Color);
  tft.setTextSize(1);
  tft.print(tagString);
}

//--------------------------------------------------------------------------------
// Tags on Boxes
//--------------------------------------------------------------------------------

void drawBoxTag (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  
  String tagString1 = MnemonicsCodes[onlineNetwork.Cells[Row][Column].Code];

  tft.setTextColor(Color);
  tft.setTextSize(1);
  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 2+Ybase);
  tft.print(tagString1);
}

//--------------------------------------------------------------------------------
// Tags inside 2 cells Boxes
//--------------------------------------------------------------------------------

void drawBox2Tags (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  String tagString2;
  
  //First Row of tags
  String tagString1 = MnemonicsTypes[onlineNetwork.Cells[Row][Column].Type] + String(onlineNetwork.Cells[Row][Column].Data); 
  if(onlineNetwork.Cells[Row][Column].Code >= SHL && onlineNetwork.Cells[Row][Column].Code <= NOT){
    tagString2 =  "0x" + String(uint16_t(GetData(Row, Column)), HEX);    
  }
  else{
    tagString2 = String(GetData(Row, Column));
  }

  tft.setTextColor(Color);
  tft.setTextSize(1);
  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 20+Ybase);
  tft.print(tagString1);
  tft.setTextColor(COLOR_VALUES_ONLINE);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 30+Ybase);
  tft.fillRect(  5+Xbase, 30+Ybase, 43, 8, networkColorBack);
  tft.print(tagString2);

  //Second Row of tags
  tagString1 = MnemonicsTypes[onlineNetwork.Cells[Row+1][Column].Type] + String(onlineNetwork.Cells[Row+1][Column].Data); 
  if(onlineNetwork.Cells[Row][Column].Code >= SHL && onlineNetwork.Cells[Row][Column].Code <= NOT){
    tagString2 =  "0x" + String(uint16_t(GetData(Row+1, Column)), HEX);    
  }
  else{
    tagString2 = String(GetData(Row+1, Column));
  }

  tft.setTextColor(Color);
  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 50+Ybase);
  tft.print(tagString1);
  tft.setTextColor(COLOR_VALUES_ONLINE);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 60+Ybase);
  tft.fillRect(  5+Xbase, 60+Ybase, 43, 8, networkColorBack);
  tft.print(tagString2);
}

//--------------------------------------------------------------------------------
// Tags inside 3 cells Boxes
//--------------------------------------------------------------------------------

void drawBox3Tags (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  String tagString2;
  //First Row of tags
  String tagString1 = MnemonicsTypes[onlineNetwork.Cells[Row][Column].Type] + String(onlineNetwork.Cells[Row][Column].Data); 
  if(onlineNetwork.Cells[Row][Column].Code >= SHL && onlineNetwork.Cells[Row][Column].Code <= NOT){
    tagString2 =  "0x" + String(uint16_t(GetData(Row, Column)), HEX);    
  }
  else{
    tagString2 = String(GetData(Row, Column));
  }

  tft.setTextColor(Color);
  tft.setTextSize(1);
  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 20+Ybase);
  tft.print(tagString1);
  tft.setTextColor(COLOR_VALUES_ONLINE);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 30+Ybase);
  tft.fillRect(  5+Xbase, 30+Ybase, 43, 8, networkColorBack);
  tft.print(tagString2);

  //Second Row of tags
  tagString1 = MnemonicsTypes[onlineNetwork.Cells[Row+1][Column].Type] + String(onlineNetwork.Cells[Row+1][Column].Data); 
  if(onlineNetwork.Cells[Row][Column].Code >= SHL && onlineNetwork.Cells[Row][Column].Code <= NOT){
    tagString2 =  "0x" + String(uint16_t(GetData(Row+1, Column)), HEX);    
  }
  else{
    tagString2 = String(GetData(Row+1, Column));
  }

  tft.setTextColor(Color);
  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 55+Ybase);
  tft.print(tagString1);
  tft.setTextColor(COLOR_VALUES_ONLINE);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 65+Ybase);
  tft.fillRect(  5+Xbase, 65+Ybase, 43, 8, networkColorBack);
  tft.print(tagString2);

  //Third Row of tags
  tagString1 = MnemonicsTypes[onlineNetwork.Cells[Row+2][Column].Type] + String(onlineNetwork.Cells[Row+2][Column].Data); 
  if(onlineNetwork.Cells[Row][Column].Code >= SHL && onlineNetwork.Cells[Row][Column].Code <= NOT){
    tagString2 =  "0x" + String(uint16_t(GetData(Row+2, Column)), HEX);    
  }
  else{
    tagString2 = String(GetData(Row+2, Column));
  }

  tft.setTextColor(Color);
  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 90+Ybase);
  tft.print(tagString1);
  tft.setTextColor(COLOR_VALUES_ONLINE);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 100+Ybase);
  tft.fillRect(  5+Xbase, 100+Ybase, 43, 8, networkColorBack);
  tft.print(tagString2);
}

//--------------------------------------------------------------------------------
// Tags inside Timer Boxes
//--------------------------------------------------------------------------------

void drawTimerTags (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  
  String tagString1, tagString2;
  
  // First Row of tags --> Timer Number
  tft.setTextColor(Color);
  tft.setTextSize(1);

  tagString1 =  "T" + String(onlineNetwork.Cells[Row][Column].Data);

  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 11+Ybase);
  tft.print(tagString1);

  //Second Row of tags --> SET + Scale + Setpoint
  switch (uint16_t(onlineNetwork.Cells[Row+1][Column].Type)) {
    case 1:
      tagString1 = "SET ms";
      break;
    case 10:
      tagString1 = "SET .01";
      break;
    case 100:
      tagString1 = "SET .1";
      break;
    case 1000:
      tagString1 = "SET s";
      break;
    case 60000:
      tagString1 = "SET m";
      break;
    default:
      tagString1 = "ERR";
      Serial.println("Error in Timer configuration");
      break;
  }
  tagString2 = String(onlineNetwork.Cells[Row+1][Column].Data);

  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 27+Ybase);
  tft.print(tagString1);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 37+Ybase);
  tft.print(tagString2);

  // Third Row of tags --> ACC + Accumulator value (ET)
  tagString1 = "ACC";
  tagString2 = String(Timers[onlineNetwork.Cells[Row][Column].Data].ACC);

  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 53+Ybase);
  tft.print(tagString1);
  tft.setTextColor(COLOR_VALUES_ONLINE);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 63+Ybase);
  tft.fillRect(  5+Xbase, 63+Ybase, 43, 8, networkColorBack);
  tft.print(tagString2);
}

//--------------------------------------------------------------------------------
// Tags inside 2 Counter Boxes
//--------------------------------------------------------------------------------

void drawCounterTags (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  
  String tagString1, tagString2;
  
  // First Row of tags --> Timer Number
  tft.setTextColor(Color);
  tft.setTextSize(1);

  tagString1 =  "C" + String(onlineNetwork.Cells[Row][Column].Data);

  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 11+Ybase);
  tft.print(tagString1);

  tagString1 = "SET";
  tagString2 = String(onlineNetwork.Cells[Row+1][Column].Data);

  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 27+Ybase);
  tft.print(tagString1);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 37+Ybase);
  tft.print(tagString2);

  // Third Row of tags --> ACC + Accumulator value (ET)
  tagString1 = "ACC";
  tagString2 = String(C[onlineNetwork.Cells[Row][Column].Data]);

  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 53+Ybase);
  tft.print(tagString1);
  tft.setTextColor(COLOR_VALUES_ONLINE);
  tft.setCursor(((7-tagString2.length())*3)+5+Xbase, 63+Ybase);
  tft.fillRect(  5+Xbase, 63+Ybase, 43, 8, networkColorBack);
  tft.print(tagString2);
}

//--------------------------------------------------------------------------------
// No draw for Nop instructions
//--------------------------------------------------------------------------------

void drawNop (int Row, int Column, int Flag, int Data){;}

//--------------------------------------------------------------------------------
// Draw Contacts
//--------------------------------------------------------------------------------

void drawNo (int Row, int Column, int Flag, int Data){
  drawTagBit(Row, Column, COLOR_TAG);
  
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color;
  
  if (Data){Color = COLOR_ON;}
  else     {Color = COLOR_OFF;} 

  tft.drawFastVLine(21+Xbase, 17+Ybase, 18, Color);
  tft.drawFastVLine(22+Xbase, 17+Ybase, 18, Color);
  tft.drawFastVLine(30+Xbase, 17+Ybase, 18, Color);
  tft.drawFastVLine(31+Xbase, 17+Ybase, 18, Color);
  tft.drawFastHLine( 0+Xbase, 25+Ybase, 21, Color);
  tft.drawFastHLine( 0+Xbase, 26+Ybase, 21, Color);
  tft.drawFastHLine(32+Xbase, 25+Ybase, 21, Color);
  tft.drawFastHLine(32+Xbase, 26+Ybase, 21, Color);
}

void drawNc (int Row, int Column, int Flag, int Data){
  drawTagBit(Row, Column, COLOR_TAG);
  
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color;
  
  if (Data){Color = COLOR_OFF;}
  else     {Color = COLOR_ON;} 

  tft.drawFastVLine(21+Xbase, 17+Ybase, 18, Color);
  tft.drawFastVLine(22+Xbase, 17+Ybase, 18, Color);
  tft.drawFastVLine(30+Xbase, 17+Ybase, 18, Color);
  tft.drawFastVLine(31+Xbase, 17+Ybase, 18, Color);
  tft.drawFastHLine( 0+Xbase, 25+Ybase, 21, Color);
  tft.drawFastHLine( 0+Xbase, 26+Ybase, 21, Color);
  tft.drawFastHLine(32+Xbase, 25+Ybase, 21, Color);
  tft.drawFastHLine(32+Xbase, 26+Ybase, 21, Color);

  tft.drawFastVLine(23+Xbase, 28+Ybase, 3, Color);
  tft.drawFastVLine(24+Xbase, 27+Ybase, 3, Color);
  tft.drawFastVLine(25+Xbase, 26+Ybase, 3, Color);
  tft.drawFastVLine(26+Xbase, 25+Ybase, 3, Color);
  tft.drawFastVLine(27+Xbase, 24+Ybase, 3, Color);
  tft.drawFastVLine(28+Xbase, 23+Ybase, 3, Color);
  tft.drawFastVLine(29+Xbase, 22+Ybase, 3, Color);
}

void drawRe (int Row, int Column, int Flag, int Data){
  drawTagBit(Row, Column, COLOR_TAG);

  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color, Color1, Color2;
  
  if (Flag){Color = COLOR_ON;}
  else     {Color = COLOR_OFF;} 
  if (Data){Color1 = COLOR_ON;}
  else     {Color1 = COLOR_OFF;} 
  Color2 = COLOR_OFF;
  
  tft.drawFastVLine(21+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastVLine(22+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastVLine(30+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastVLine(31+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastHLine( 0+Xbase, 25+Ybase, 21, Color);
  tft.drawFastHLine( 0+Xbase, 26+Ybase, 21, Color);
  tft.drawFastHLine(32+Xbase, 25+Ybase, 21, Color2);
  tft.drawFastHLine(32+Xbase, 26+Ybase, 21, Color2);

  tft.drawFastVLine(26+Xbase, 20+Ybase, 12, Color1);
  tft.drawFastHLine(25+Xbase, 21+Ybase,  3, Color1);
  tft.drawFastHLine(24+Xbase, 22+Ybase,  5, Color1);
}

void drawFe (int Row, int Column, int Flag, int Data){
  drawTagBit(Row, Column, COLOR_TAG);

  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color, Color1, Color2;
  
  if (Flag){Color = COLOR_ON;}
  else     {Color = COLOR_OFF;} 
  if (Data){Color1 = COLOR_ON;}
  else     {Color1 = COLOR_OFF;} 
  Color2 = COLOR_OFF;
  
  tft.drawFastVLine(21+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastVLine(22+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastVLine(30+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastVLine(31+Xbase, 17+Ybase, 18, Color1);
  tft.drawFastHLine( 0+Xbase, 25+Ybase, 21, Color);
  tft.drawFastHLine( 0+Xbase, 26+Ybase, 21, Color);
  tft.drawFastHLine(32+Xbase, 25+Ybase, 21, Color2);
  tft.drawFastHLine(32+Xbase, 26+Ybase, 21, Color2);

  tft.drawFastVLine(26+Xbase, 20+Ybase, 12, Color1);
  tft.drawFastHLine(24+Xbase, 29+Ybase,  5, Color1);
  tft.drawFastHLine(25+Xbase, 30+Ybase,  3, Color1);
}

//--------------------------------------------------------------------------------
// Draw Coils
//--------------------------------------------------------------------------------

void drawCoil (int Row, int Column, int Flag, int Data){
  drawTagBit(Row, Column, COLOR_TAG);

  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color, Color1;
  
  if (Data){Color = COLOR_ON;}
  else     {Color = COLOR_OFF;} 

  if (Flag){Color1 = COLOR_ON;}
  else     {Color1 = COLOR_OFF;} 
  
  tft.drawFastHLine( 0+Xbase, 25+Ybase, 18, Color1);
  tft.drawFastHLine( 0+Xbase, 26+Ybase, 18, Color1);

  tft.drawFastHLine(35+Xbase, 25+Ybase, 18, Color1);
  tft.drawFastHLine(35+Xbase, 26+Ybase, 18, Color1);

  tft.drawFastVLine(18+Xbase, 21+Ybase, 10, Color);
  tft.drawFastVLine(19+Xbase, 20+Ybase, 12, Color);

  tft.drawFastVLine(20+Xbase, 19+Ybase,  3, Color);
  tft.drawFastVLine(21+Xbase, 18+Ybase,  3, Color);
  tft.drawFastVLine(22+Xbase, 17+Ybase,  3, Color);
  tft.drawFastVLine(23+Xbase, 17+Ybase,  2, Color);

  tft.drawFastVLine(20+Xbase, 30+Ybase,  3, Color);
  tft.drawFastVLine(21+Xbase, 31+Ybase,  3, Color);
  tft.drawFastVLine(22+Xbase, 32+Ybase,  3, Color);
  tft.drawFastVLine(23+Xbase, 33+Ybase,  2, Color);
  
  tft.drawFastVLine(33+Xbase, 20+Ybase, 12, Color);
  tft.drawFastVLine(34+Xbase, 21+Ybase, 10, Color);

  tft.drawFastVLine(29+Xbase, 17+Ybase,  2, Color);
  tft.drawFastVLine(30+Xbase, 17+Ybase,  3, Color);
  tft.drawFastVLine(31+Xbase, 18+Ybase,  3, Color);
  tft.drawFastVLine(32+Xbase, 19+Ybase,  3, Color);

  tft.drawFastVLine(29+Xbase, 33+Ybase,  2, Color);
  tft.drawFastVLine(30+Xbase, 32+Ybase,  3, Color);
  tft.drawFastVLine(31+Xbase, 31+Ybase,  3, Color);
  tft.drawFastVLine(32+Xbase, 30+Ybase,  3, Color);
}

void drawCoilU (int Row, int Column, int Flag, int Data){
  drawCoil(Row, Column, Flag, Data); 
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color;
  
  if (Data){Color = COLOR_ON;}
  else     {Color = COLOR_OFF;} 

  tft.drawFastVLine(23+Xbase, 22+Ybase,  8, Color);
  tft.drawFastVLine(24+Xbase, 22+Ybase,  8, Color);

  tft.drawFastVLine(28+Xbase, 22+Ybase,  8, Color);
  tft.drawFastVLine(29+Xbase, 22+Ybase,  8, Color);

  tft.drawFastHLine(25+Xbase, 28+Ybase,  3, Color);
  tft.drawFastHLine(25+Xbase, 29+Ybase,  3, Color);
}

void drawCoilL (int Row, int Column, int Flag, int Data){
  drawCoil(Row, Column, Flag, Data); 
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color;
  
  if (Data){Color = COLOR_ON;}
  else     {Color = COLOR_OFF;} 

  tft.drawFastVLine(24+Xbase, 22+Ybase,  8, Color);
  tft.drawFastVLine(25+Xbase, 22+Ybase,  8, Color);

  tft.drawFastHLine(26+Xbase, 28+Ybase,  4, Color);
  tft.drawFastHLine(26+Xbase, 29+Ybase,  4, Color); 
}

//--------------------------------------------------------------------------------
// Draw Horizontal and Vertical connection bars
//--------------------------------------------------------------------------------

void drawBar (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;

  tft.drawFastVLine(52+Xbase, 25+Ybase, 42, Color);
  tft.drawFastVLine(53+Xbase, 25+Ybase, 42, Color);
}

void drawConn(int Row, int Column, int Flag, int Data){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color;
  
  if (Flag){Color = COLOR_ON;}
  else     {Color = COLOR_OFF;} 
  
  tft.drawFastHLine( 0+Xbase, 25+Ybase, 53, Color);
  tft.drawFastHLine( 0+Xbase, 26+Ybase, 53, Color);
}

void drawNeg(int Row, int Column, int Flag, int Data){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int Color, Color1;
  
  if (Flag){
    Color  = COLOR_ON;
    Color1 = COLOR_OFF;
  }
  else{
    Color  = COLOR_OFF;
    Color1 = COLOR_ON;
  }

  tft.drawFastHLine( 0+Xbase, 25+Ybase, 27, Color);
  tft.drawFastHLine( 0+Xbase, 26+Ybase, 27, Color);

  tft.drawFastHLine(27+Xbase, 25+Ybase, 26, Color1); 
  tft.drawFastHLine(27+Xbase, 26+Ybase, 26, Color1);
  
  tft.drawFastHLine(19+Xbase, 32+Ybase,  2, Color);
  tft.drawFastHLine(19+Xbase, 31+Ybase,  3, Color);
  tft.drawFastHLine(20+Xbase, 30+Ybase,  3, Color);
  tft.drawFastHLine(21+Xbase, 29+Ybase,  3, Color);
  tft.drawFastHLine(22+Xbase, 28+Ybase,  3, Color);
  tft.drawFastHLine(23+Xbase, 27+Ybase,  3, Color);
  tft.drawFastHLine(24+Xbase, 26+Ybase,  3, Color);
  tft.drawFastHLine(25+Xbase, 25+Ybase,  3, Color);
  tft.drawFastHLine(26+Xbase, 24+Ybase,  3, Color);
  tft.drawFastHLine(27+Xbase, 23+Ybase,  3, Color);
  tft.drawFastHLine(28+Xbase, 22+Ybase,  3, Color);
  tft.drawFastHLine(29+Xbase, 21+Ybase,  3, Color);
  tft.drawFastHLine(30+Xbase, 20+Ybase,  3, Color);
  tft.drawFastHLine(31+Xbase, 19+Ybase,  2, Color);
}

//--------------------------------------------------------------------------------
// Draw Timers
//--------------------------------------------------------------------------------

void drawTon(int Row, int Column, int Flag, int Data){
  int BoxColor;
  
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawTimerTags(Row, Column, COLOR_TAG);
  drawBoxOutputPin2 (Row, Column);
}

void drawToff(int Row, int Column, int Flag, int Data){
  int BoxColor;
  
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawTimerTags(Row, Column, COLOR_TAG);
  drawBoxOutputPin2 (Row, Column);
}

void drawTp(int Row, int Column, int Flag, int Data){
  int BoxColor;
  
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawTimerTags(Row, Column, COLOR_TAG);
  drawBoxOutputPin2 (Row, Column);
}

//--------------------------------------------------------------------------------
// Draw Counters
//--------------------------------------------------------------------------------

void drawCtu(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxInputPin2(Row, Column);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawCounterTags(Row, Column, COLOR_TAG);
  drawBoxInputPin2 (Row, Column);
  drawBoxOutputPin2 (Row, Column);
}

void drawCtd(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxInputPin2(Row, Column);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawCounterTags(Row, Column, COLOR_TAG);
  drawBoxInputPin2 (Row, Column);
  drawBoxOutputPin2 (Row, Column);
}

//--------------------------------------------------------------------------------
// Draw Move
//--------------------------------------------------------------------------------

void drawMove(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox2Tags(Row, Column, COLOR_TAG);
}

//--------------------------------------------------------------------------------
// Draw Basic Math Instructions
//--------------------------------------------------------------------------------

void drawSub(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
  drawBoxOutputPin2 (Row, Column);
  drawBoxOutputPin3 (Row, Column);
}

void drawAdd(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
}

void drawMul(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
}

void drawDiv(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
  drawBoxOutputPin3 (Row, Column);
}

void drawMod(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
}

void drawShl(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox2Tags(Row, Column, COLOR_TAG);
}

void drawShr(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox2Tags(Row, Column, COLOR_TAG);
}

void drawRol(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox2Tags(Row, Column, COLOR_TAG);
}

void drawRor(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox2Tags(Row, Column, COLOR_TAG);
}

void drawAnd(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
}

void drawOr(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
}

void drawXor(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox3(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox3Tags(Row, Column, COLOR_TAG);
}

void drawNot(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox2Tags(Row, Column, COLOR_TAG);
}

//--------------------------------------------------------------------------------
// Draw Boxes, Inputs and Output Pins
//--------------------------------------------------------------------------------

void drawBox2 (int Row, int Column, int boxcolor){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int out1;
  
  if(NetworkFlagsOnline[Column] & FlagsMask[Row]){out1  = COLOR_ON;}
  else{out1  = COLOR_OFF;}

  tft.drawFastHLine( 4+Xbase,  39+Ybase, 44, networkColorBack); // Clear intermediate grid horizontal line
 
  tft.drawFastVLine( 3+Xbase, 4+Ybase,  74, boxcolor);
  tft.drawFastVLine(48+Xbase, 4+Ybase,  74, boxcolor);

  tft.drawFastHLine( 4+Xbase,  4+Ybase,  5, boxcolor);
  tft.drawFastHLine(43+Xbase,  4+Ybase,  5, boxcolor);
  tft.drawFastHLine( 4+Xbase, 77+Ybase, 44, boxcolor);
  
  tft.drawFastHLine( 0+Xbase, 25+Ybase,  3, boxcolor);
  tft.drawFastHLine( 0+Xbase, 26+Ybase,  3, boxcolor);

  tft.drawFastHLine( 49+Xbase, 25+Ybase, 5, out1);
  tft.drawFastHLine( 49+Xbase, 26+Ybase, 5, out1);
}

void drawBox3 (int Row, int Column, int boxcolor){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int out1;
  
  if(NetworkFlagsOnline[Column] & FlagsMask[Row]){out1  = COLOR_ON;}
  else{out1  = COLOR_OFF;}

  tft.drawFastHLine( 4+Xbase,  39+Ybase, 44, networkColorBack); // Clear intermediate grid horizontal line
  tft.drawFastHLine( 4+Xbase,  79+Ybase, 44, networkColorBack); // Clear intermediate grid horizontal line
 
  tft.drawFastVLine( 3+Xbase, 4+Ybase, 114, boxcolor);
  tft.drawFastVLine(48+Xbase, 4+Ybase, 114, boxcolor);

  tft.drawFastHLine( 4+Xbase,  4+Ybase,  5, boxcolor);
  tft.drawFastHLine(43+Xbase,  4+Ybase,  5, boxcolor);
  tft.drawFastHLine( 4+Xbase,117+Ybase, 44, boxcolor);
  
  tft.drawFastHLine( 0+Xbase, 25+Ybase,  3, boxcolor);
  tft.drawFastHLine( 0+Xbase, 26+Ybase,  3, boxcolor);

  tft.drawFastHLine( 49+Xbase, 25+Ybase, 5, out1);
  tft.drawFastHLine( 49+Xbase, 26+Ybase, 5, out1);
}

void drawBoxInputPin2 (int Row, int Column){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int in2;  
  
  if (Column == 0){
    if(settings.ladder.PLCstate == RUNNING){in2  = COLOR_ON;}
    else{in2  = COLOR_OFF;}
  }
  else{
    if(NetworkFlagsOnline[Column-1] & FlagsMask[Row+1]){in2  = COLOR_ON;}
    else{in2  = COLOR_OFF;}
  }

  tft.drawFastHLine( 0+Xbase, 65+Ybase,  3, in2);
  tft.drawFastHLine( 0+Xbase, 66+Ybase,  3, in2);
}

void drawBoxInputPin3 (int Row, int Column){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  int in2;
  
  if (Column == 0){
    if(settings.ladder.PLCstate == RUNNING){in2  = COLOR_ON;}
    else{in2  = COLOR_OFF;}
  }
  else{
    if(NetworkFlagsOnline[Column-1] & FlagsMask[Row+2]){in2  = COLOR_ON;}
    else{in2  = COLOR_OFF;}
  }

  tft.drawFastHLine( 0+Xbase, 105+Ybase,  3, in2);
  tft.drawFastHLine( 0+Xbase, 106+Ybase,  3, in2);
}

void drawBoxOutputPin2 (int Row, int Column){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH; 
  int out2;
  
  if(NetworkFlagsOnline[Column] & FlagsMask[Row+1]){out2  = COLOR_ON;}
  else{out2  = COLOR_OFF;}
  
  tft.drawFastHLine( 49+Xbase, 65+Ybase, 5, out2);
  tft.drawFastHLine( 49+Xbase, 66+Ybase, 5, out2);
}

void drawBoxOutputPin3 (int Row, int Column){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH; 
  int out3;

  if(NetworkFlagsOnline[Column] & FlagsMask[Row+2]){out3  = COLOR_ON;}
  else{out3  = COLOR_OFF;}
  
  tft.drawFastHLine( 49+Xbase,105+Ybase, 5, out3);
  tft.drawFastHLine( 49+Xbase,106+Ybase, 5, out3);
}

//--------------------------------------------------------------------------------
// Draw Base Network
//--------------------------------------------------------------------------------

void drawBaseNetwork(){
  tft.fillRect(0, MENU_HEIGTH, BODY_WIDTH, BODY_HEIGTH, networkColorBack);

  //Matrix for contact network
  for (int r=0; r<NET_ROWS+1; r++){
    tft.drawFastHLine(POWER_BAR_WIDTH, r*NET_ROW_HEIGTH+MENU_HEIGTH-1, NET_BODY_WIDTH, networkColorGrid);
  }
  for (int c=0; c<NET_COLUMNS+1; c++){
    tft.drawFastVLine(c*NET_COL_WIDTH+POWER_BAR_WIDTH, MENU_HEIGTH-1, NET_BODY_HEIGTH, networkColorGrid);
  }
}

void drawPowerBar(){
  //Left Power Bar
  int runColor;
  if(editionMode){
    runColor = COLOR_BAR_EDIT;
  }
  else if(settings.ladder.PLCstate == RUNNING){
    runColor = COLOR_BAR_ON;
  }
  else{
    runColor = COLOR_BAR_OFF;
  }
  for (int i=0; i<POWER_BAR_WIDTH; i++){
    tft.drawFastVLine( i, MENU_HEIGTH-1, BODY_HEIGTH+1, runColor);    
  }
}