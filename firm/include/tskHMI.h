#ifndef TSKHMI_H
#define TSKHMI_H

//--------------------------------------------------------------------------------
// Globals variables used in this specific task 
//--------------------------------------------------------------------------------

TFT_eSPI tft = TFT_eSPI();     // TFT Display Instance

uint16_t hmiPage          = 0; // GUI general Page number
uint16_t hmiPageMemory    = 0; // Used to go back to previous page
uint8_t hmiPageFirstLoad  = 1; // 1 to force Main Menu Load at fist boot. Used to detect the first "frame" of the current page.
uint8_t hmiPageUser       = 0; // HMI page number
uint8_t hmiPageLoaded     = 0;
uint8_t button[8] = {0,0,0,0,0,0,0,0};

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
unsigned long timerRefreshMainMenu = 0;

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
uint16_t numericValueAccepted = 0;  // 1 = Return value of numeric keyboard was accepted

//----------------------------------------------------
// Text Keyboard
//----------------------------------------------------

String textValue = "";                    // Variable to use as return value of text keyboard
uint16_t textValueAccepted = 0;           // 1 = Return value of text keyboard was accepted
uint16_t keyboardPage = 0;                // Indexes between the 4 pages
uint16_t textMaxLength;                   // Specifies the max length of the string to be modified

//----------------------------------------------------
// Wifi Editing
//----------------------------------------------------

int16_t networksFound = 0;
uint16_t networksScanPage = 0;
uint16_t networksToShow = 0;

uint16_t wifiEditionField = 0;
unsigned long timerRefreshWifiStatus = 0;

//----------------------------------------------------
// Firmware Update
//----------------------------------------------------

unsigned long auxTimerFirmwareBar = 0;

#endif
