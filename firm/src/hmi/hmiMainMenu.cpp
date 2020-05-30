#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Main Menu Page
//--------------------------------------------------------------------------------

void pageMainMenu (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y){
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawMainMenu ();
    }

  //-------------------------------
  // update required fields
  //-------------------------------

  if(PLCstateChange() || ScanTimeChange()){
    printPLCstate();
  }

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType){
    touchMainMenu(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// Main Menu Page full draw 
//--------------------------------------------------------------------------------

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
}

//--------------------------------------------------------------------------------
// Update Values on top left corner while in Main Menu  
//--------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------
// Return True if the PLC Staus has changed
//--------------------------------------------------------------------------------

uint16_t PLCstateChange(void) {
  if (PLCstateOld != PLCstate){
    PLCstateOld = PLCstate;
    return 1;
  }
  else {return 0;}
}

//--------------------------------------------------------------------------------
// Return True if the PLC Scan Time has changed
//--------------------------------------------------------------------------------

uint16_t ScanTimeChange(void) {
  unsigned int auxScanTime = actualScanTime/100;
  if (auxOldScanTime != auxScanTime){
    auxOldScanTime = auxScanTime;
    return 1;
  }
  else {return 0;}
}

//--------------------------------------------------------------------------------
// Main Menu Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchMainMenu(uint16_t X, uint16_t Y){
  if      (Y <= 40) {
    PLCstate++;
    if (PLCstate > 2){PLCstate = 0;}
  }
  else if (Y >  40 && Y < 111) {HMI_Page = PAGE_MainLadder;}
  else if (Y <  174)           {HMI_Page = PAGE_MainHMI;}  
  else                         {HMI_Page = PAGE_MainConfig;}
}




