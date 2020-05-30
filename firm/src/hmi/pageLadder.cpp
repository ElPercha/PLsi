#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Ladder Logic Viewer and Editor main Page
//--------------------------------------------------------------------------------

void pageMainLadder (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
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
//--------------------------------------------------------------------------------

void touchMainLadder(uint16_t ts_x, uint16_t ts_y){
// HMI_Touched.Menu = 0        -> No Main Menu selection
// HMI_Touched.Menu = 1 to 6   -> 1 = Left button ... 6 = Right button
// HMI_Touched.Logic.Value = 0 -> No Logic cell selected
// HMI_Touched.Logic.Value = 1 -> Logic cell selected, check Row and Col values 
// HMI_Touched.Logic.Row = 0 to NET_ROWS-1 
// HMI_Touched.Logic.Col = 0 to NET_COLUMNS-1 
  if (ts_y < MENU_HEIGTH){
    HMI_Touched.Menu = abs(ts_x/MENU_WIDTH)+1;    
  }
  else{
    HMI_Touched.Logic.Row   = abs((ts_y-MENU_HEIGTH)/NET_ROW_HEIGTH);    
    HMI_Touched.Logic.Col   = abs((ts_x-POWER_BAR_WIDTH)/NET_COL_WIDTH);    
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
    HMI_Page = PAGE_InputNumber;
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
  if (ShowingNetworkOld != ShowingNetwork){
    ShowingNetworkOld = ShowingNetwork;
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
