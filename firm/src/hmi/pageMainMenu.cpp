#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Main Menu Page
//--------------------------------------------------------------------------------

void pageMainMenu (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // draw full Page on first load
  //-------------------------------
    
    if(firstLoad){
      drawMainMenu ();
      printPLCprogram();
      printPLCstate ();
    }

  //-------------------------------
  // update required fields
  //-------------------------------

  if (PLCstateChanged() || (millis() - timerRefreshMainMenu > 2000)){
    printPLCstate();
    timerRefreshMainMenu = millis();
  }

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){

    touchMainMenu(ts_x, ts_y);
  } 
}

//--------------------------------------------------------------------------------
// Main Menu Page full draw 
//--------------------------------------------------------------------------------

void drawMainMenu (void){
  tft.fillScreen(BLACK);
   
  tft.fillRect     (  0,   0, 320, 34,    DARKGREY); // Header
  tft.fillRoundRect( 20,  48, 280, 55, 11, WHITE);    // Button 1
  tft.fillRoundRect( 20, 111, 280, 55, 11, CYAN);     // Button 2
  tft.fillRoundRect( 20, 174, 280, 55, 11 , AQUA);     // Button 3

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 10);

  String str = FILENAME_USER_PROGRAMS[settings.ladder.UserProgram];
  str = str.substring(1, str.length());
  tft.print(str);

  printPLCstate ();
  
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
// Update Values PLC State and Scan time on top bar of Main Menu  
//--------------------------------------------------------------------------------

void printPLCstate (void){
  tft.fillRect (170, 0, 320-170, 34,    DARKGREY); 
  tft.setTextSize(2);

  if (settings.ladder.PLCstate == RUNNING){
    tft.setTextColor(GREEN);
    String auxString = "RUN " + String(float(actualScanTime)/1000.0, 1) + " ms";
    tft.setCursor(315 - auxString.length() * 12, 10);
    tft.print(auxString);
  }
  else if (settings.ladder.PLCstate == STOPPED){
    tft.setCursor(240, 10);
    tft.setTextColor(YELLOW);
    tft.print("STOP");
  }
  else if (settings.ladder.PLCstate >= PLCERROR){
    tft.setCursor(240, 10);
    tft.setTextColor(RED);
    tft.print("ERROR");
  }
}

//--------------------------------------------------------------------------------
// Update Values PLC State and Scan time on top bar of Main Menu  
//--------------------------------------------------------------------------------

void printPLCprogram (void){
  tft.fillRect (  0,   0, 320, 34,    DARKGREY); 

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 10);

  String str = FILENAME_USER_PROGRAMS[settings.ladder.UserProgram];
  str = str.substring(1, str.length());
  tft.print(str);
}

//--------------------------------------------------------------------------------
// Return True if the PLC Staus has changed
//--------------------------------------------------------------------------------

uint16_t PLCstateChanged(void) {
  if (PLCstateOld != settings.ladder.PLCstate ){
    PLCstateOld = settings.ladder.PLCstate ;
    return 1;
  }
  else {
    return 0;
  }
}

//--------------------------------------------------------------------------------
// Return True if the PLC Scan Time has changed
//--------------------------------------------------------------------------------

uint16_t ScanTimeChanged(void) {
  unsigned int auxScanTime = actualScanTime/100;
  if (auxOldScanTime != auxScanTime){
    auxOldScanTime = auxScanTime;
    return 1;
  }
  else {
    return 0;
  }
}

//--------------------------------------------------------------------------------
// Main Menu Page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchMainMenu(uint16_t X, uint16_t Y){
  if      (Y <= 40 && X > 200) {changePLCstate();}
  else if (Y >  40 && Y < 111) {hmiPage = PAGE_MainLadder;}
  else if (Y > 111 && Y < 174) {hmiPage = PAGE_MainHMI   ;}  
  else if (Y > 174           ) {hmiPage = PAGE_MainConfig;}
}

//--------------------------------------------------------------------------------
// Change PLC State 
// Ask for user decision usIng a Dialog OK / CANCEL screen
//--------------------------------------------------------------------------------

void changePLCstate(void){  
  if (settings.ladder.PLCstate >= PLCERROR) {
    settings.ladder.PLCstate = STOPPED;
    saveSettings();
  }
  else if (settings.ladder.PLCstate == RUNNING){
    hmiPageMemory = hmiPage;
    dialogCode = DIALOG_RUN_STOP;
    hmiPage = PAGE_DialogOkCancel;
  }
  else if (settings.ladder.PLCstate == STOPPED){
    hmiPageMemory = hmiPage;
    dialogCode = DIALOG_STOP_RUN;
    hmiPage = PAGE_DialogOkCancel;
  }
}



