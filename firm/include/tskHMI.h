#ifndef TSKHMI_H
#define TSKHMI_H

//--------------------------------------------------------------------------------
// Globals variables used in this specific task 
//--------------------------------------------------------------------------------

TFT_eSPI tft = TFT_eSPI(); // TFT Display Instance

uint16_t HMI_Page         = 0; // Main Menu Page 
uint16_t HMI_PagePrevious = 1; // To force Main Manu Load at fist boot

uint16_t PLCstateOld = PLCstate; 

unsigned long  auxOldScanTime = 0;

//--------------------------------------------------------------------------------
// Type definitions for HMI task
//--------------------------------------------------------------------------------




// Touch Screen areas for Ladder edition
typedef struct {
  int Value;
  int Row;
  int Col;
} LogicTouched;

typedef struct {
  int Menu;
  LogicTouched Logic;
} AreaTouched;

AreaTouched HMI_Touched;
uint16_t pressedAux = 0;

int networkColorBack = COLOR_BACK_NET;
int networkColorGrid = DARKGREY;


//Network to show under Online animation
uint16_t ShowingNetwork = 0;
uint16_t ShowingNetworkOld = ShowingNetwork;

uint16_t editionMode = 0;
uint16_t editionModeOld = editionMode;


// Flags for Logic Online animation
uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];


// Datatypes Strings
const String MnemonicsTypes[FIRST_INVALID_TYPE] = {"M", "Q", "I", "Cd", "Cr", "Td", "Tr", "IW", "QW", "C", "T", "D", "K", "R"};
const String MnemonicsCodes[FIRST_INVALID_CODE] = {"", "", "", "", "", "", "", "", "", "", 
                                                   "TON", "TOFF", "TP", "CTU", "CTD", "MOVE", "SUB", "ADD", "MUL", "DIV",
                                                   "MOD", "SHL", "SHR", "ROL", "ROR", "AND", "OR", "XOR", "NOT"};




#endif
