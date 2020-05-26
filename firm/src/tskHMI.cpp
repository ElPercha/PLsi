#include <globals.h>
#include <plsi.h>

// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_ILI9341.h>


#include <TFT_eSPI.h> // LUCAS

#include <XPT2046_Touchscreen.h>
#include <tskHMI.h>

void TaskHMI(void *pvParameters)
{
  (void) pvParameters;
  
  // Touch Screen initializations
  ts.begin();
  ts.setRotation(TS_ROTATION);

  // TFT Display initializations
  tft.begin();
  tft.setRotation(TFT_ROTATION);
  
  // HMI Touch Screen Global Variables init
  HMI_Touched.Menu = 0;
  HMI_Touched.Logic.Value = 0;
  HMI_Touched.Logic.Row = 0;
  HMI_Touched.Logic.Col = 0;

  while(1){
    // Check for command from Touch Screen
    if (ts.touched() && !AuxTouched){
      AuxTouched = 1;
      parseTouchScreen();
    }
    if (!ts.touched()){
      AuxTouched = 0;
    }
  // Draw pages selector
    if (true){
      switch (HMI_Page) {
      case PAGE_MainMenu: 
        drawMainMenu();
        break;
      case PAGE_MenuWait:
        drawMenuWait();
        break;
      case PAGE_MainLadder:
        drawMainLadder();
        break;
      case PAGE_LadderOnline:
        drawLadderOnline();
        break;
      case PAGE_MainHMI:
        drawMainHMI();
        break;
      case PAGE_HMImenu:
        drawHMImenu();
        break;
      case PAGE_MainConfig:
        drawMainConfig();
        break;
      case PAGE_ConfigWait:
        drawConfigWait();
        break;
      case PAGE_SelectNumber:
        drawSelectNumber();
        break;
      case PAGE_InputNumber:
        drawInputNumber();
        break;
      default:
        ;
      break;
      }
    }
    delay(5); 
  }
}

/******************************************************/
/*** MAIN MENU ****************************************/
/******************************************************/
void drawMainMenu (void){
  tft.fillScreen(BLACK);
   
  tft.fillRect     (  0,   0, 320, 34,    DARKGREY); // Header
  tft.fillRoundRect( 20,  48, 280, 55, 6, WHITE);    // Button 1
  tft.fillRoundRect( 20, 111, 280, 55, 6, CYAN);     // Button 2
  tft.fillRoundRect( 20, 174, 280, 55, 6, AQUA);     // Button 3

  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("PLsi v" + String(FIRMWARE));

  printPLCstate();

  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.setCursor(90, 61);
  tft.print("LADDER");
  
  tft.setCursor(130, 124);
  tft.print("HMI");

  tft.setTextSize(3);
  tft.setCursor(43, 191);
  tft.print("CONFIGURATION");

  HMI_Page = PAGE_MenuWait;
}

void drawMenuWait (void){
//Update Values RUN, STOP, etc  
  if(PLCstateChange() || ScanTimeChange()){printPLCstate();}
}
/******************************************************/
/*** LADDER *******************************************/
/******************************************************/
void drawMainLadder (void){
  tft.fillScreen(WHITE);
  
  // 6 Buttons shapes on Header
  drawLadderMenuBut1();
  drawLadderMenuBut2();
  drawLadderMenuBut3();
  drawLadderMenuBut4();
  drawLadderMenuBut5();
  drawLadderMenuBut6();

  drawHomeIcon();         // Home Icon on button 1 (left)
  drawLeftArrow();        // On Menu position 2 
  printNetworkNumber();   // Network Number on Button 3
  drawRightArrow();       // On Menu position 4   
  printEDIT();            // Edit/Save in position 5 
  printPLCstateSmall();   // Text PLC state on button 6 (right)
  
  drawBaseNetwork();
  drawNetwork();   
  
  HMI_Page = PAGE_LadderOnline;
}

void drawLadderOnline (void){
  if(NetworkChanged()){
    drawBaseNetwork();
    printNetworkNumber();
  }
  //unsigned long StartTimeHMI = millis();
  drawNetwork();   
  //Serial.println(millis()-StartTimeHMI);

  EditionChanged();
  if(PLCstateChange()){printPLCstateSmall();}
}

void drawSelectNumber (void){
  HMI_Page = PAGE_InputNumber;
}

void drawInputNumber (){


}

/******************************************************/
/*** LADDER EDITOR ************************************/
/******************************************************/




/******************************************************/
/*** HMI **********************************************/
/******************************************************/
void drawMainHMI (void){
  tft.fillScreen(YELLOW);
   
  tft.setTextColor(BLACK);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("HMI Not available");

  HMI_Page = PAGE_HMImenu;
}

void drawHMImenu (void){
}

/******************************************************/
/*** CONFIG *******************************************/
/******************************************************/
void drawMainConfig (void){
  tft.fillScreen(MAGENTA);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 10);
  tft.setTextSize(2);
  tft.print("CONFIG Not available");

  HMI_Page = PAGE_ConfigWait;
}

void drawConfigWait (void){
}

/******************************************************/
/*** AUX FUNCTIONS ************************************/
/******************************************************/
void printPLCstate(void){
  tft.setTextSize(2);
  tft.fillRect     (  100,   0, 320, 34,    DARKGREY);
  if (PLCstate == RUNNING){
    tft.setTextColor(GREEN);
    String auxString = "RUNNING " + String(float(actualScanTime)/1000.0, 1) + " ms";
    tft.setCursor(315 - auxString.length() * 12, 10);
    tft.print(auxString);
  }
  else if (PLCstate == STOPPED){
    tft.setCursor(220, 10);
    tft.setTextColor(YELLOW);
    tft.print("STOPPED");
  }
  else if (PLCstate == PLCERROR){
    tft.setCursor(240, 10);
    tft.setTextColor(RED);
    tft.print("ERROR");
  }
}

void printPLCstateSmall(void){
  tft.setTextSize(2);
  tft.setCursor(276, 13);
  drawLadderMenuBut6();
  if (PLCstate == RUNNING){
    tft.setTextColor(GREEN);
    tft.print("RUN");
  }
  else if (PLCstate == STOPPED){
    tft.setCursor(271, 13);
    tft.setTextColor(YELLOW);
    tft.print("STOP");
  }
  else if (PLCstate == PLCERROR){
    tft.setTextColor(RED);
    tft.print("ERR");
  }
}

uint16_t PLCstateChange(void) {
  if (PLCstateOld != PLCstate){
    PLCstateOld = PLCstate;
    return 1;
  }
  else {return 0;}
}
uint16_t ScanTimeChange(void) {
  unsigned int auxScanTime = actualScanTime/100;
  if (auxOldScanTime != auxScanTime){
    auxOldScanTime = auxScanTime;
    return 1;
  }
  else {return 0;}
}

uint16_t NetworkChanged(void) {
  if (ShowingNetworkOld != ShowingNetwork){
    ShowingNetworkOld = ShowingNetwork;
    return 1;
  }
  else {return 0;}
}

void drawLadderMenuBut1(void){tft.fillRect(  1, 1, 54, 37, DARKGREY);}
void drawLadderMenuBut2(void){tft.fillRect( 56, 1, 52, 37, DARKGREY);}
void drawLadderMenuBut3(void){tft.fillRect(109, 1, 52, 37, DARKGREY);}
void drawLadderMenuBut4(void){tft.fillRect(162, 1, 52, 37, DARKGREY);}
void drawLadderMenuBut5(void){tft.fillRect(215, 1, 52, 37, DARKGREY);}
void drawLadderMenuBut6(void){tft.fillRect(268, 1, 51, 37, DARKGREY);}

void drawHomeIcon(void){
  tft.fillTriangle( 1+15, 1+17, 1+39, 1+17, 1+27,  1+5, WHITE);   // Roof 
  tft.drawTriangle( 1+15, 1+17, 1+39, 1+17, 1+27,  1+5, BLACK);   // Roof
  tft.fillRect    ( 1+19, 1+17,   17,   14,             WHITE);   // Home
  tft.drawRect    ( 1+19, 1+17,   17,   14,             BLACK);   // Wall
  tft.fillRect    ( 1+25, 1+23,    5,    7,             BLACK);   // Door
}

void drawLeftArrow(void){
  tft.fillTriangle( 56+13, 1+19, 56+20, 1+12, 56+20, 1+26, WHITE);   
  tft.fillRect    ( 56+21, 1+16,    18,    7,              WHITE);   
}
  
void drawRightArrow(void){
  tft.fillTriangle( 162+40, 1+19, 162+33, 1+12, 162+33, 1+26, WHITE);
  tft.fillRect    ( 162+15, 1+16,     18,    7,               WHITE);   
}
  
void printNetworkNumber(void){
  drawLadderMenuBut3();
  tft.setTextColor(WHITE);

  tft.setTextSize(1);
  tft.setCursor(109+6, 5);
  tft.print("Network");
    
  tft.setTextSize(2);
  if      (ShowingNetwork <  10){tft.setCursor(109+20, 17);}
  else if (ShowingNetwork < 100){tft.setCursor(109+14, 17);}
  else                          {tft.setCursor(109+ 9, 17);}
  tft.print(ShowingNetwork);
}  
  
void EditionChanged(void){
  if (editionModeOld != editionMode){
    if (editionMode == 0){
      printEDIT();
      networkColorBack = COLOR_BACK_NET;
      networkColorGrid = COLOR_NET_GRID;
    }
    else                 {
      printSAVE();
      networkColorBack = COLOR_BACK_NET_EDIT;
      networkColorGrid = COLOR_NET_GRID_EDIT;
    }    
    drawBaseNetwork();
    editionModeOld = editionMode;
  }
}  
void printEDIT(void){
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(215+3, 13);
  drawLadderMenuBut5();
  tft.print("EDIT");
}
void printSAVE(void){
  tft.setTextSize(2);
  tft.setTextColor(ORANGE);
  tft.setCursor(215+3, 13);
  drawLadderMenuBut5();
  tft.print("SAVE");
}































/******************************************************/
/*** NETWORK ******************************************/
/******************************************************/
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
  if(PLCstate == RUNNING){runColor = COLOR_BAR_ON;}
  else                   {runColor = COLOR_BAR_OFF;}
  for (int i=0; i<POWER_BAR_WIDTH; i++){
    tft.drawFastVLine( i, MENU_HEIGTH-1, BODY_HEIGTH+1, runColor);    
  }
}

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
  
  //uint16_t Data;
  //uint16_t Flag;
  
  // Draw / Update Ladder instructions  
  for (int c=0; c<NET_COLUMNS; c++){
    for (int r=0; r<NET_ROWS; r++){
      if (onlineNetwork.Cells[r][c].Code > 0) {
        //Data  = GetData(r, c);
        //Flag  = GetFlag(r, c);

        if (onlineNetwork.Cells[r][c].Code >=    FIRST_INVALID_CODE){
          Serial.println("TASK HMI - CORE 0 - INSTRUCTION CODE INVALID: ");
          Serial.print("   - Network (absolute number): ");
          Serial.println(ShowingNetwork);
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
    if (PLCstate == RUNNING){returnData = 1;}
    else                    {returnData = 0;}
  }
  else{
    returnData = (NetworkFlagsOnline[c-1] & FlagsMask[r]);
  }
  return returnData;  
}

/******************************************************/
/*** TAGS ON BITS *************************************/
/******************************************************/
void drawTagBit (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  
  String tagString = MnemonicsTypes[onlineNetwork.Cells[Row][Column].Type] + String(onlineNetwork.Cells[Row][Column].Data);

  tft.setCursor(((7-tagString.length())*3)+5+Xbase, 4+Ybase);
  tft.setTextColor(Color);
  tft.setTextSize(1);
  tft.print(tagString);
}

/******************************************************/
/*** TAGS ON BOXES ************************************/
/******************************************************/
void drawBoxTag (int Row, int Column, int Color){
  int Xbase = Column * NET_COL_WIDTH + POWER_BAR_WIDTH; 
  int Ybase = Row * NET_ROW_HEIGTH + MENU_HEIGTH;
  
  String tagString1 = MnemonicsCodes[onlineNetwork.Cells[Row][Column].Code];

  tft.setTextColor(Color);
  tft.setTextSize(1);
  tft.setCursor(((7-tagString1.length())*3)+5+Xbase, 2+Ybase);
  tft.print(tagString1);
}

/******************************************************/
/*** TAGS INSIDE BOX 2 CELLS **************************/
/******************************************************/
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

/******************************************************/
/*** TAGS INSIDE BOX 3 CELLS **************************/
/******************************************************/
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

/******************************************************/
/*** TAGS ON TIMERS ***********************************/
/******************************************************/
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
/******************************************************/
/*** TAGS ON COUNTERS *********************************/
/******************************************************/
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

/******************************************************/
/*** NOP **********************************************/
/******************************************************/
void drawNop (int Row, int Column, int Flag, int Data){;}

/******************************************************/
/*** CONTACTS *****************************************/
/******************************************************/
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

/******************************************************/
/*** COILS ********************************************/
/******************************************************/

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

/******************************************************/
/*** HORIZONTAL AND VERTICAL BARS *********************/
/******************************************************/
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

/******************************************************/
/*** TIMERS  ******************************************/
/******************************************************/
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

/******************************************************/
/*** COUNTERS *****************************************/
/******************************************************/
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

/******************************************************/
/*** GENERAL ******************************************/
/******************************************************/
void drawMove(int Row, int Column, int Flag, int Data){
  int BoxColor;
  if (Flag){BoxColor  = COLOR_ON;}
  else{BoxColor  = COLOR_OFF;}

  drawBox2(Row, Column, BoxColor);
  drawBoxTag(Row, Column, COLOR_TAG);
  drawBox2Tags(Row, Column, COLOR_TAG);
}
/******************************************************/
/*** MATH BASIC ***************************************/
/******************************************************/

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

/******************************************************/
/*** BOXES for 1, 2 and 3 cells ***********************/
/******************************************************/

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
    if(PLCstate == RUNNING){in2  = COLOR_ON;}
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
    if(PLCstate == RUNNING){in2  = COLOR_ON;}
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




























/******************************************************/
/*** TOUCH SCREEN MAIN SELECTOR ***********************/
/******************************************************/
void parseTouchScreen(void){
  TS_Point p = ts.getPoint();
  float TS_PixelX = abs((float(p.x) - TS_LEFT_X)/(TS_RIGHT_X - TS_LEFT_X)* TFT_PIXELS_X);
  float TS_PixelY = abs((1 - (float(p.y) - TS_BOTTOM_Y)/(TS_TOP_Y - TS_BOTTOM_Y))* TFT_PIXELS_Y);

  switch (HMI_Page) {
    case PAGE_MenuWait: //PAGE_MainMenu or 
      touchMainMenu(TS_PixelX, TS_PixelY); 
      break;
    case PAGE_LadderOnline: //PAGE_MainLadder or 
      touchMainLadder(TS_PixelX, TS_PixelY);
      break;
    case PAGE_HMImenu:
      touchHMImenu(TS_PixelX, TS_PixelY);
      break;
    case PAGE_ConfigWait:
      touchConfigWait(TS_PixelX, TS_PixelY);
      break;
    case PAGE_InputNumber:
      touchInputNumber(TS_PixelX, TS_PixelY);
      break;

    default:
      ;
    break;
  }
}

/******************************************************/
/*** MAIN MENU COMMANDS *******************************/
/******************************************************/
void touchMainMenu(float X, float Y){
  if      (Y <= 40) {
    PLCstate++;
    if (PLCstate > 2){PLCstate = 0;}
  }
  else if (Y >  40 && Y < 111) {HMI_Page = PAGE_MainLadder;}
  else if (Y <  174)           {HMI_Page = PAGE_MainHMI;}  
  else                         {HMI_Page = PAGE_MainConfig;}
}

/******************************************************/
/*** MAIN LADDER COMMANDS *****************************/
/******************************************************/
void touchMainLadder(float X, float Y){
// HMI_Touched.Menu = 0        -> No Main Menu selection
// HMI_Touched.Menu = 1 to 6   -> 1 = Left button ... 6 = Right button
// HMI_Touched.Logic.Value = 0 -> No Logic cell selected
// HMI_Touched.Logic.Value = 1 -> Logic cell selected, check Row and Col values 
// HMI_Touched.Logic.Row = 0 to NET_ROWS-1 
// HMI_Touched.Logic.Col = 0 to NET_COLUMNS-1 
  if (Y < MENU_HEIGTH){
    HMI_Touched.Menu = abs(X/MENU_WIDTH)+1;    
  }
  else{
    HMI_Touched.Logic.Row   = abs((Y-MENU_HEIGTH)/NET_ROW_HEIGTH);    
    HMI_Touched.Logic.Col   = abs((X-POWER_BAR_WIDTH)/NET_COL_WIDTH);    
    HMI_Touched.Logic.Value = 1;
  }

//Execute Menu Function from 1 to 6
  if(HMI_Touched.Menu == 1){
    HMI_Touched.Menu = 0;
    editionMode = 0;
    HMI_Page = PAGE_MainMenu;
  }
  if(HMI_Touched.Menu == 2){
    HMI_Touched.Menu = 0;
    editionMode = 0;
    if (ShowingNetwork == 0){ShowingNetwork=TOTAL_NETWORKS-1;}
    else{ShowingNetwork--;}
  }
  if(HMI_Touched.Menu == 3){
    HMI_Touched.Menu = 0;
    editionMode = 0;

    HMI_PagePrevious = HMI_Page;
    HMI_Page = PAGE_SelectNumber;
  }
  if(HMI_Touched.Menu == 4){
    HMI_Touched.Menu = 0;
    editionMode = 0;
    ShowingNetwork++;
    if (ShowingNetwork >= TOTAL_NETWORKS-1){ShowingNetwork=0;}
  }
  if(HMI_Touched.Menu == 5){
    HMI_Touched.Menu = 0;
    if (editionMode == 0){
      editionMode = 1;
    }
    else{
      editionMode = 0;
      //saveNetworkFlash(ShowingNetwork); CONVERSION
    }
  }
  if(HMI_Touched.Menu == 6){
    HMI_Touched.Menu = 0;
    if      (PLCstate == PLCERROR) {PLCstate = STOPPED;}
    else if (PLCstate == RUNNING)  {PLCstate = STOPPED;}
    else if (PLCstate == STOPPED)  {PLCstate = RUNNING;}
  }

// Execute Logic Cell Edition or Highlight
  if (HMI_Touched.Logic.Value){
    HMI_Touched.Logic.Value = 0;
    //HMI_Touched.Logic.Row;
    //HMI_Touched.Logic.Col;


    Serial.print ("Touched Row Cell: ");
    Serial.println (HMI_Touched.Logic.Row);
    Serial.print ("Touched Col Cell: ");
    Serial.println (HMI_Touched.Logic.Col);
  }
}
/******************************************************/
/*** INPUT NUMERIC VALUE ******************************/
/******************************************************/
void touchInputNumber(float X, float Y){
  //HMI_Page = 0;

  //agarrar donde toco y actuar sobre el numero a crear
}

/******************************************************/
/*** MAIN HMI MENU ************************************/
/******************************************************/
void touchHMImenu(float X, float Y){
  HMI_Page = 0;
}

/******************************************************/
/*** MAIN CONFIG MENU *********************************/
/******************************************************/

void touchConfigWait(float X, float Y){
  HMI_Page = 0;
}


// /* Reading input device (simulated encoder here) */
// bool read_touchscreen(lv_indev_drv_t * indev, lv_indev_data_t * data)
// {
//   /* Read the touchpad */
//   float TS_PixelX = 0; 
//   float TS_PixelY = 0; 

//   if (ts.touched()) {
//     data->state = LV_INDEV_STATE_PR;
//     TS_Point p = ts.getPoint();
//     TS_PixelX = abs((float(p.x) - TS_LEFT_X)/(TS_RIGHT_X - TS_LEFT_X)* TFT_PIXELS_X);
//     TS_PixelY = abs((1 - (float(p.y) - TS_BOTTOM_Y)/(TS_TOP_Y - TS_BOTTOM_Y))* TFT_PIXELS_Y);
//   } 
//   else {
//     data->state = LV_INDEV_STATE_REL;
//   }
//   data->point.x = TS_PixelX;
//   data->point.y = TS_PixelY;
//   return false;   /*false: no more data to read because we are no buffering*/
// }

