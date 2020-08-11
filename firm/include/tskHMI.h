#ifndef TSKHMI_H
#define TSKHMI_H

//--------------------------------------------------------------------------------
// Globals variables used in this specific task 
//--------------------------------------------------------------------------------

TFT_eSPI tft = TFT_eSPI(); // TFT Display Instance

uint16_t HMI_Page         = 0; // Main Menu Page 
uint16_t HMI_PageMemory   = 0; // Main Menu Page 

uint16_t PLCstateOld = PLCstate; 
uint16_t userProgramOld = 0;

unsigned long  auxOldScanTime = 0;
int networkColorBack = COLOR_BACK_NET;
int networkColorGrid = DARKGREY;

//----------------------------------------------------
// Network to show under Online animation
//----------------------------------------------------

uint16_t showingNetwork = 0;
uint16_t showingNetworkOld = showingNetwork;

uint16_t editionMode = 0;
uint16_t editionModeOld = editionMode;

//----------------------------------------------------
// Flags for Logic Online animation
//----------------------------------------------------

uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];

//----------------------------------------------------
// Datatypes Strings
//----------------------------------------------------

const String MnemonicsTypes[FIRST_INVALID_TYPE] = {"M", "Q", "I", "Cd", "Cr", "Td", "Tr", "IW", "QW", "C", "T", "D", "K", "R"};
const String MnemonicsCodes[FIRST_INVALID_CODE] = {"", "", "", "", "", "", "", "", "", "", 
                                                   "TON", "TOFF", "TP", "CTU", "CTD", "MOVE", "SUB", "ADD", "MUL", "DIV",
                                                   "MOD", "SHL", "SHR", "ROL", "ROR", "AND", "OR", "XOR", "NOT"};

//----------------------------------------------------
// Invoke the TFT_eSPI button class and 
// create all the numeric button objects
//----------------------------------------------------

#define NUM_KEY_LEN 16
char numberBuffer[NUM_KEY_LEN + 1] = "";
uint8_t numberIndex = 0;  

TFT_eSPI_Button numericKeys[16];

double numericValue = 0;            // Variable to use as return value of numeric keyboard
uint16_t numericValueAccepted = 0;  // Variable to use as return value of numeric keyboard

#endif
