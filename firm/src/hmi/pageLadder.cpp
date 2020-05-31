#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Ladder Logic Viewer and Editor main Page
//--------------------------------------------------------------------------------

void pageMainLadder (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  
  //-------------------------------
  // capture input Value command
  //-------------------------------

    if(numericValueAccepted && numericValue >= 0 && numericValue < TOTAL_NETWORKS){
      showingNetwork = uint16_t(numericValue);
      numericValueAccepted = 0;
    }

  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawMainLadder();
    }
    
  //-------------------------------
  // update required fields
  //-------------------------------

    drawLadderOnline();

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchMainLadder(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Main Ladder Logic viewer full draw 
//--------------------------------------------------------------------------------

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
}

//--------------------------------------------------------------------------------
// Ladder Logic Network 
// Online Update
//--------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------
// Main Configuration Page
// Touch Screen parsing
//
//     ladderTouched.Menu = 0        -> No Main Menu selection
//     ladderTouched.Menu = 1 to 6   -> 1 = Left button ... 6 = Right button
//     ladderTouched.Logic.Value = 0 -> No Logic cell selected
//     ladderTouched.Logic.Value = 1 -> Logic cell selected, check Row and Col values 
//     ladderTouched.Logic.Row = 0 to NET_ROWS-1 
//     ladderTouched.Logic.Col = 0 to NET_COLUMNS-1 
//
//--------------------------------------------------------------------------------

void touchMainLadder(uint16_t ts_x, uint16_t ts_y){
typedef struct {
  int Value;
  int Row;
  int Col;
} LogicTouched;

typedef struct {
  int Menu;
  LogicTouched Logic;
} AreaTouched;

AreaTouched ladderTouched;
  ladderTouched.Menu = 0;
  ladderTouched.Logic.Value = 0;
  ladderTouched.Logic.Row = 0;
  ladderTouched.Logic.Col = 0;

  if (ts_y < MENU_HEIGTH){
    ladderTouched.Menu = abs(ts_x/MENU_WIDTH)+1;    
  }
  else{
    ladderTouched.Logic.Row   = abs((ts_y-MENU_HEIGTH)/NET_ROW_HEIGTH);    
    ladderTouched.Logic.Col   = abs((ts_x-POWER_BAR_WIDTH)/NET_COL_WIDTH);    
    ladderTouched.Logic.Value = 1;
  }

  //-------------------------------------------
  // Execute Menu Function from 1 to 6
  //-------------------------------------------

  if(ladderTouched.Menu == 1){ // HOME
    ladderTouched.Menu = 0;
    editionMode = 0;
    HMI_Page = PAGE_MainMenu;
  }
  if(ladderTouched.Menu == 2){ // LEFT ARROW
    ladderTouched.Menu = 0;
    editionMode = 0;
    if (showingNetwork == 0){showingNetwork=TOTAL_NETWORKS-1;}
    else{showingNetwork--;}
  }
  if(ladderTouched.Menu == 3){ // GO TO
    ladderTouched.Menu = 0;
    editionMode = 0;
    HMI_PageMemory = HMI_Page;
    HMI_Page = PAGE_InputNumber;
  }
  if(ladderTouched.Menu == 4){ // RIGHT ARROW
    ladderTouched.Menu = 0;
    editionMode = 0;
    showingNetwork++;
    if (showingNetwork >= TOTAL_NETWORKS-1){showingNetwork=0;}
  }
  if(ladderTouched.Menu == 5){ // EDIT / SAVE
    ladderTouched.Menu = 0;
    if (editionMode == 0){
      editionMode = 1;
    }
    else{
      editionMode = 0;
      //saveNetworkFlash(showingNetwork); CONVERSION
    }
  }
  if(ladderTouched.Menu == 6){ // CHANGE PLC STATE
    ladderTouched.Menu = 0;
    if      (PLCstate == PLCERROR) {PLCstate = STOPPED;}
    else if (PLCstate == RUNNING)  {PLCstate = STOPPED;}
    else if (PLCstate == STOPPED)  {PLCstate = RUNNING;}
  }
  
  //-------------------------------------------
  // Execute Logic Cell Edition or Highlight
  //-------------------------------------------
  
  if (ladderTouched.Logic.Value){
    ladderTouched.Logic.Value = 0;
    //ladderTouched.Logic.Row;
    //ladderTouched.Logic.Col;

    Serial.print ("Touched Row Cell: ");
    Serial.println (ladderTouched.Logic.Row);
    Serial.print ("Touched Col Cell: ");
    Serial.println (ladderTouched.Logic.Col);
  }
}

//--------------------------------------------------------------------------------
// Ladder viewer / editor
// Top Menu bar auxiliary functions
//--------------------------------------------------------------------------------

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

void drawLadderMenuBut1(void){
  tft.fillRect(  1, 1, 54, 37, DARKGREY);
}

void drawLadderMenuBut2(void){
  tft.fillRect( 56, 1, 52, 37, DARKGREY);
}

void drawLadderMenuBut3(void){
  tft.fillRect(109, 1, 52, 37, DARKGREY);
}

void drawLadderMenuBut4(void){
  tft.fillRect(162, 1, 52, 37, DARKGREY);
}

void drawLadderMenuBut5(void){
  tft.fillRect(215, 1, 52, 37, DARKGREY);
}

void drawLadderMenuBut6(void){
  tft.fillRect(268, 1, 51, 37, DARKGREY);
}

uint16_t NetworkChanged(void) {
  if (showingNetworkOld != showingNetwork){
    showingNetworkOld = showingNetwork;
    return 1;
  }
  else {return 0;}
}

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
  if      (showingNetwork <  10){tft.setCursor(109+20, 17);}
  else if (showingNetwork < 100){tft.setCursor(109+14, 17);}
  else                          {tft.setCursor(109+ 9, 17);}
  tft.print(showingNetwork);
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
