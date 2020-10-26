#ifndef TSKHMI_H
#define TSKHMI_H

//--------------------------------------------------------------------------------
// Globals variables used in this specific task 
//--------------------------------------------------------------------------------

TFT_eSPI tft = TFT_eSPI(); // TFT Display Instance

uint16_t HMI_Page         = 0; // Main Menu Page 
uint16_t HMI_PageMemory   = 0; // Main Menu Page 
uint16_t HMI_PagePrevious = 1; // To force Main Manu Load at fist boot

uint16_t indexLadderEditor = 0; // Subpage of Ladder Editor

uint16_t PLCstateOld = 0; 
uint16_t userProgramOld = 0;

unsigned long  auxOldScanTime = 0;

int networkColorBack;
int networkColorGrid;

uint16_t dialogCode;
uint16_t messageCode;

uint16_t ladderEditorRow = 0;
uint16_t ladderEditorColumn = 0;

uint16_t editingInstructionCode = 0;
uint16_t timerSelected = 0;
uint16_t instructionFieldSelection = 0;

//----------------------------------------------------
// Network to show under Online animation
//----------------------------------------------------

uint16_t showingNetworkOld = showingNetwork;
uint16_t editionMode = 0;
uint16_t editionModeOld = editionMode;

//----------------------------------------------------
// Flags for Logic Online animation
//----------------------------------------------------

uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];

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
