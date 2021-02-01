#ifndef HMI_H
#define HMI_H

#include <Free_Fonts.h>
 
//--------------------------------------------------------------------------------
// Globals variables for HMI 
//--------------------------------------------------------------------------------

extern TFT_eSPI tft; 

extern uint16_t hmiPage;
extern uint16_t hmiPageMemory;
extern uint8_t hmiPageUser;
extern uint8_t hmiPageLoaded;
extern uint16_t hmiEditionIndex;
extern unsigned long timerRefreshHMI;

extern uint16_t indexLadderEditor;

extern uint16_t PLCstateOld; 
extern unsigned long  auxOldScanTime;

extern unsigned long  auxOldScanTime;
extern int networkColorBack;
extern int networkColorGrid;
extern uint16_t dialogCode;
extern uint16_t messageCode;

extern uint16_t ladderEditorRow;
extern uint16_t ladderEditorColumn;

extern uint16_t editingInstructionCode;
extern uint16_t timerSelected;
extern uint16_t instructionFieldSelection;
extern unsigned long timerRefreshMainMenu;
extern unsigned long timerRefreshIOlocal;

//----------------------------------------------------
// Network to show under Online animation
//----------------------------------------------------

extern uint16_t showingNetworkOld;
extern uint16_t editionMode;
extern uint16_t editionModeOld;

//----------------------------------------------------
// Flags for Logic Online animation
//----------------------------------------------------

extern uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];

//----------------------------------------------------
// Defines the width and height of each instruction
//----------------------------------------------------

const uint16_t instructionHeight[FIRST_INVALID_CODE] = {1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,2,2,2,2,3,3,3,2,2,2,2,2,2,2};
const uint16_t instructionWidth[FIRST_INVALID_CODE]  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

//----------------------------------------------------
// Datatypes and Instructions Strings
//----------------------------------------------------

const String MnemonicsTypes[FIRST_INVALID_TYPE] = {"M", "Q", "I", "Cd", "Cr", "Td", "Tr", "IW", "QW", "C", "T", "D", "K", "R"};
const String MnemonicsCodes[FIRST_INVALID_CODE] = {"", "CON", "INV", "NO", "NC", "RE", "FE", "C", "L", "U", 
                                                   "TON", "TOFF", "TP", "CTU", "CTD", "MOVE", "SUB", "ADD", "MUL", "DIV",
                                                   "MOD", "SHL", "SHR", "ROL", "ROR", "AND", "OR", "XOR", "NOT", "EQ", "GT", "GE", "LT", "LE", "NE"};

#define BAR_MNEMONIC      "BAR"
#define BAR_MNEMONIC_LENGTH  3

//----------------------------------------------------
// Timer Base Time definition
//      1 - ms
//     10 - 0.01 sec
//    100	- 0.1 sec
//   1000	- sec
//  60000	- min
//--------------------------------------------------------------------------------

const uint16_t timerBaseTime[5] = {1, 10, 100, 1000, 60000};
const String timerBaseTimeText[5] = {"millisec", "0.01 sec", "0.1 sec", "seconds", "minutes"};

//----------------------------------------------------
// Defines the position of each mnemonic
//  in the 5 x 3 instruction palette
//  We have 2 pages
//----------------------------------------------------

const uint16_t menuInstructions[3][15] = {{NO, NC, RE, FE, BAR_MNEMONIC_CODE, COIL, COILL, COILU, NEG, CONN, TON, TOFF, TP, CTU, CTD},
                                          {SUB, ADD, MUL, DIV, MOVE, AND, OR, XOR, NOT, NOPP, MOD, SHL, SHR, ROL, ROR},
                                          {EQ, GT, GE, LT, LE, NE, NOPP, NOPP, NOPP, NOPP, NOPP, NOPP, NOPP, NOPP, NOPP}};

const String elementsFunctions[4] = {"COPY", "PASTE", "INSERT", "DELETE"};
const String elementsList[3] = {"COLUMN", "ROW", "NETWORK"};

//-------------------------------------------------
// Keyboard characters definition
// 4 pages of 30 char
//
// Printable ASCII:
//       ! " # $ % & ' ( ) * + , - . / 
//     0 1 2 3 4 5 6 7 8 9 : ; < = > ? 
//     @ A B C D E F G H I J K L M N O 
//     P Q R S T U V W X Y Z [ \ ] ^ _ 
//     ` a b c d e f g h i j k l m n o 
//     p q r s t u v w x y z { | } ~
//-------------------------------------------------

const char keyLabel[4][30] = {{'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '.', ' ', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ' ', ' '},
                              {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '.', ' ', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', ' '},
                              {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', ' ', '\\', '|', '/', '-', ':', ',', '.', ' ', ' '},
                              {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '<', '=', '>', '[', ']', '{', '}', '~', ';', '\'', ' ', '?', '_', '+', '`', '\"', ',', '.', ' ', ' '}};

//----------------------------------------------------
// Index of Mnemonic Type. 
// The position in the array is the order in the page
//----------------------------------------------------

const uint16_t menuDataTypes[6] = {TypeD, TypeT, TypeC, TypeIW, TypeK, TypeQW};

//----------------------------------------------------
// Invoke the TFT_eSPI button class and 
// create all the numeric button objects
//----------------------------------------------------

#define NUM_KEY_LEN 16
extern char numberBuffer[NUM_KEY_LEN + 1];

extern uint8_t numberIndex;  
extern TFT_eSPI_Button numericKeys[16];

extern double numericValue;                // Variable to use as return value of numeric keyboard
extern uint16_t numericValueAccepted;      // Variable to use as return value of numeric keyboard

//----------------------------------------------------
// Text Keyboard
//----------------------------------------------------

extern String textValue;                   // Variable to use as return value of text keyboard
extern uint16_t textValueAccepted;         // 1 = Return value of text keyboard was accepted
extern uint16_t keyboardPage;              // Indexes between the 4 pages
extern uint16_t textMaxLength;             // Specifies the max length of the string to be modified

//----------------------------------------------------
// Wifi
//----------------------------------------------------

extern int16_t networksFound;
extern uint16_t networksScanPage;
extern uint16_t networksToShow;

#define VIEW_NET_Y            40 // Height of button for each network found
// For 240 Y display 5 Networks per page 
// For 320 Y display 7 Networks per page
#define NETWORKS_PER_PAGE     uint16_t(TFT_PIXELS_Y / VIEW_NET_Y - 1)

extern uint16_t wifiEditionField;
extern unsigned long timerRefreshWifiStatus;

#define EDITING_WIFI_SSID     0
#define EDITING_WIFI_PASSWORD 1

//--------------------------------------------------------------------------------
// Used Global variables in HMI scope, declared in another task
//--------------------------------------------------------------------------------

extern unsigned long actualScanTime;
extern uint16_t configFirmwareEnabled;

extern unsigned long auxTimerFirmwareBar;

//--------------------------------------------------------------------------------
// HMI Page numbers
//--------------------------------------------------------------------------------

#define PAGE_MainMenu                   0

#define PAGE_MainLadder                10
#define PAGE_LadderEditor              20
#define PAGE_EditInstructions1         21
#define PAGE_EditInstructions2         22
#define PAGE_EditInstructions3         23
#define PAGE_LadderDetails             40

#define PAGE_MainConfig               100
#define PAGE_ConfigNetwork            110
#define PAGE_ConfigWiFi               111
#define PAGE_ScanWiFi                 112

#define PAGE_ConfigPLC                120
#define PAGE_ConfigProgram            121

#define PAGE_ConfigIO                 130
#define PAGE_ConfigIOlocal            131

#define PAGE_ConfigHMI                140

#define PAGE_ConfigSystem             150
#define PAGE_ConfigFirmware           151

#define PAGE_MainHMI                  200

#define PAGE_InputNumber              400
#define PAGE_Keyboard                 410
#define PAGE_DialogOkCancel           420
#define PAGE_DialogMessage            430

#define PAGES_LADDER_EDITOR             6

//--------------------------------------------------------------------------------
// Define Dialog codes. Used to:
//    Define Actions inside Dialog page 
//    Define text to be displayed on Dialog page
//--------------------------------------------------------------------------------

#define DIALOG_RUN_STOP                 1
#define DIALOG_STOP_RUN                 2

//--------------------------------------------------------------------------------
// Define User Messages Codes
//--------------------------------------------------------------------------------

#define MESSAGE_NO_ROWS                     1
#define MESSAGE_NO_COLUMNS                  2
#define MESSAGE_SPACE_USED                  3
#define MESSAGE_CANNOT_COPY_COLUMN          4 
#define MESSAGE_CANNOT_COPY_ROW             5
#define MESSAGE_COLUMN_NOT_EMPTY            6
#define MESSAGE_ROW_NOT_EMPTY               7
#define MESSAGE_NETWORK_NOT_EMPTY           8
#define MESSAGE_CANNOT_DELETE_COLUMN        9
#define MESSAGE_CANNOT_DELETE_ROW          10 
#define MESSAGE_CANNOT_INSERT_COLUMN       11 
#define MESSAGE_CANNOT_INSERT_ROW          12 
#define MESSAGE_CANNOT_INSERT_NETWORK      13 
#define MESSAGE_CANNOT_SPLIT_WIDE_INSTR    14
#define MESSAGE_CANNOT_SPLIT_HIGH_INSTR    15
#define MESSAGE_PLC_MUST_BE_IN_STOP        16
#define MESSAGE_PLC_MUST_BE_IN_STOP1       17
#define MESSAGE_OTA_NOT_POSSIBLE           18
#define MESSAGE_FIRMWARE_UPDATED           19
#define MESSAGE_CHANGE_IO_NOT_POSSIBLE     20

//--------------------------------------------------------------------------------
// TFT Display Dimmensions
//--------------------------------------------------------------------------------

#define TFT_PIXELS_X 320 // width
#define TFT_PIXELS_Y 240 // heigth

//--------------------------------------------------------------------------------
// TFT Display and TouchScreen Rotation
//--------------------------------------------------------------------------------

#define TFT_ROTATION   3
#define TS_ROTATION    1

//--------------------------------------------------------------------------------
// Toch Screen type of command
//--------------------------------------------------------------------------------

#define HMI_IDLE        0
#define HMI_TOUCHED     1
#define HMI_TOUCHING    2
#define HMI_RELEASED    3

//--------------------------------------------------------------------------------
// TFT Display Colors definitions
//--------------------------------------------------------------------------------

#define BLACK    0x0000
#define BLUE     0x001F
#define DARKBLUE 0x0002
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define CYANL    0x05FF
#define AQUA     0x04FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
#define DARKGREY 0x39E7
#define ORANGE   0xFA60
#define LIME     0x07FF
#define PINK     0xF8FF
#define PURPLE   0x78EF
#define PURPLE1  0x60C8
#define PURPLE2  0x2064
#define BROWN    0x2020
#define BROWN1   0x1000
#define YELLOW1  0x3920
#define YELLOW2  0x7DE0
#define BLUE1    0x00E7
#define WHITE1   0xE77C
#define WHITE2   0xC6F8
#define WHITE3   0x8510

//--------------------------------------------------------------------------------
// Main Menu and Body dimmensions [pixels]
//--------------------------------------------------------------------------------

#define MENU_HEIGTH       40
#define MENU_WIDTH        53
#define BODY_WIDTH        TFT_PIXELS_X
#define BODY_HEIGTH       TFT_PIXELS_Y - MENU_HEIGTH

//--------------------------------------------------------------------------------
// Network dimmensions [pixels]
//--------------------------------------------------------------------------------

#define POWER_BAR_WIDTH    2

#define NET_BODY_HEIGTH   BODY_HEIGTH
#define NET_BODY_WIDTH    BODY_WIDTH - POWER_BAR_WIDTH

#define NET_COL_WIDTH     53
#define NET_ROW_HEIGTH    40

//--------------------------------------------------------------------------------
// HMI Screens definitions
//--------------------------------------------------------------------------------

#define HMI_MENU_H       40
#define HMI_TITLE_H      40
#define HMI_MENU_BUT      6
#define HMI_SLOT_W       40
#define HMI_SLOT_H       40

#define HMI_COLUMNS       TFT_PIXELS_X / HMI_SLOT_W
#define HMI_ROWS          (TFT_PIXELS_Y - HMI_MENU_H - HMI_TITLE_H) / HMI_SLOT_H

#define HMI_SLOTS_Y       (HMI_MENU_H + HMI_TITLE_H) // Position where the matrix for components starts

#define HMI_MENU_W        TFT_PIXELS_X / HMI_MENU_BUT
#define HMI_SLOT_2W       HMI_SLOT_W * 2
#define HMI_SLOT_3W       HMI_SLOT_W * 3
#define HMI_SLOT_4W       HMI_SLOT_W * 4
#define HMI_SLOT_2H       HMI_SLOT_W * 2
#define HMI_SLOT_3H       HMI_SLOT_W * 3
#define HMI_FONT_SIZE     2  
#define HMI_FONT_TITLE    4  

//--------------------------------------------------------------------------------
// Ladder Logic Animation Colors
//--------------------------------------------------------------------------------

#define COLOR_TAG                             WHITE
#define COLOR_OFF                             WHITE
#define COLOR_ON                              GREEN
#define COLOR_BACK_NET                        BLACK
#define COLOR_BACK_NET_EDIT                   BROWN1
#define COLOR_NET_GRID                        DARKGREY
#define COLOR_NET_GRID_EDIT                   ORANGE
#define COLOR_BAR_ON                          GREEN
#define COLOR_BAR_OFF                         DARKGREY
#define COLOR_BAR_EDIT                        ORANGE
#define COLOR_VALUES_ONLINE                   CYAN

//--------------------------------------------------------------------------------
// Ladder Editor Colors
//--------------------------------------------------------------------------------

#define COLOR_LADDER_EDITOR_BACKGROUND        TFT_BLACK
#define COLOR_BUTTON_FONT_LADDER_EDITOR       TFT_WHITE
#define COLOR_BUTTON_INSTRUCTION_SELECTED     TFT_DARKGREEN
#define COLOR_BUTTON_INSTRUCTION              TFT_DARKGREY
#define COLOR_BUTTON_BORDER_LADDER_EDITOR     TFT_WHITE
#define COLOR_BUTTON_DELETE_LADDER_EDITOR     TFT_VIOLET
#define COLOR_BUTTON_CANCEL_LADDER_EDITOR     TFT_MAGENTA
#define COLOR_BUTTON_ACCEPT_LADDER_EDITOR     TFT_DARKGREEN
#define COLOR_BUTTON_ARROWS_LADDER_EDITOR     TFT_DARKCYAN
#define COLOR_BAR_LADDER_EDITOR               TFT_WHITE
#define COLOR_BAR_FONT_LADDER_EDITOR          TFT_DARKGREY
#define COLOR_BUTTON_COLUMN                   TFT_BROWN
#define COLOR_BUTTON_ROW                      TFT_PURPLE
#define COLOR_BUTTON_NETWORK                  TFT_OLIVE
#define COLOR_LADDER_INSTRUC_BACKGROUND       TFT_BLACK
#define COLOR_BUTTON_FONT_INSTRUC_EDITOR      TFT_WHITE

#define COLOR_BAR_FONT_INSTRUC_EDITOR         TFT_BLACK
#define COLOR_BAR_FONT1_INSTRUC_EDITOR        TFT_DARKGREY 
#define COLOR_BAR_INSTRUC_EDITOR              WHITE2
#define COLOR_BUTTON_BORDER_INSTRUC_EDITOR    TFT_WHITE
#define COLOR_BUTTON_CANCEL_INSTRUC_EDITOR    TFT_MAGENTA
#define COLOR_BUTTON_BACK_INSTRUC_EDITOR      TFT_DARKGREY
#define COLOR_BUTTON_ACCEPT_INSTRUC_EDITOR    TFT_DARKGREEN
#define COLOR_BUTTON_INSTRUC_BOOLEAN_EDITOR   TFT_DARKCYAN

#define COLOR_TIMER_EDITION                   TFT_DARKCYAN
#define COLOR_TIMER_FIELDS                    WHITE2
#define COLOR_TIMER_EDITION_TEXT              TFT_WHITE
#define COLOR_TIMER_COUNTER_TEXT              TFT_BLACK

#define COLOR_INSTRUCTION_EDITION             TFT_DARKCYAN
#define COLOR_INSTRUCTION_FIELDS              WHITE2
#define COLOR_INSTRUCTION_FIELDS1             GREEN
#define COLOR_INSTRUCTION_EDITION_TEXT        TFT_WHITE
#define COLOR_INSTRUCTION_COUNTER_TEXT        TFT_BLACK

#define COLOR_PALETTE_BUTTON_BORDER           TFT_WHITE
#define COLOR_PALETTE_BUTTON                  TFT_DARKCYAN
#define COLOR_PALETTE_TEXT                    TFT_WHITE
#define COLOR_PALETTE_BAR                     WHITE2
#define COLOR_PALETTE_BAR_TEXT                TFT_BLACK

#define COLOR_KEYBOARD_FONT                   TFT_BLACK
#define COLOR_KEYBOARD_BAR                    TFT_WHITE
#define COLOR_KEYBOARD_KEY                    TFT_WHITE
#define COLOR_KEYBOARD_BACK                   TFT_LIGHTGREY
#define COLOR_KEYBOARD_SPECIAL_KEY            TFT_ORANGE

#define COLOR_CONFIG_MAIN_BACK                TFT_BLACK
#define COLOR_CONFIG_MAIN_BORDER              WHITE2
#define COLOR_CONFIG_MAIN_TEXT                WHITE2

#define COLOR_WIFI_SIGNAL_GOOD                TFT_DARKGREEN
#define COLOR_WIFI_SIGNAL_MED                 ORANGE
#define COLOR_WIFI_SIGNAL_BAD                 TFT_RED
#define COLOR_WIFI_BOX_BORDER                 WHITE2
#define COLOR_WIFI_BOX_TEXT                   WHITE2
#define COLOR_WIFI_SCAN_BACK                  BLUE1
#define COLOR_WIFI_SCAN_BORDER                TFT_WHITE
#define COLOR_WIFI_SCAN_CANCEL                TFT_MAGENTA
#define COLOR_WIFI_SCAN_MORE                  TFT_DARKGREY
#define COLOR_WIFI_SCAN_DO                    TFT_DARKGREEN

#define COLOR_FIRMWARE_ENABLED                TFT_DARKGREEN
#define COLOR_FIRMWARE_ENABLED_FONT           TFT_WHITE
#define COLOR_FIRMWARE_DISABLED               DARKGREY
#define COLOR_FIRMWARE_DISABLED_FONT          TFT_WHITE
#define COLOR_FIRMWARE_CANCEL                 TFT_MAGENTA
#define COLOR_FIRMWARE_CANCEL_FONT            TFT_WHITE
#define COLOR_FIRMWARE_BAR                    WHITE2
#define COLOR_FIRMWARE_BAR_FONT               TFT_BLACK

#define COLOR_HMI_BACK                        TFT_BLACK
#define COLOR_HMI_MENU_BUTTON                 DARKGREY
#define COLOR_HMI_MENU_BORDER                 TFT_WHITE
#define COLOR_HMI_FONT                        TFT_WHITE  
#define COLOR_HMI_BACK_POTENTIOM              TFT_DARKGREEN  
#define COLOR_HMI_BACK_ANA_IND                TFT_VIOLET  
#define COLOR_HMI_FONT_TITLE_COLOR            WHITE2

#define COLOR_HMI_AN_BORDER                   WHITE1
#define COLOR_HMI_AN_INDI_FULL                BLUE
#define COLOR_HMI_AN_INDI_EMPTY               BLACK

#define COLOR_HMI_CONFIG_IO_BACK              BLACK
#define COLOR_HMI_CONFIG_IO_BACK_TITLE        DARKGREY
#define COLOR_HMI_CONFIG_IO_FONT              WHITE
#define COLOR_HMI_CONFIG_IO_BORDER            WHITE

//--------------------------------------------------------------------------------
// Task Functions prototypes
//--------------------------------------------------------------------------------

boolean screenServer(void);                   //  Issue #11 - For Screen Saver PC connection
boolean screenServer(String filename);        //  Issue #11 - For Screen Saver PC connection
boolean serialScreenServer(String filename);  //  Issue #11 - For Screen Saver PC connection
void sendParameters(String filename);         //  Issue #11 - For Screen Saver PC connection

void hmiWaitSettings (void);
void pageMainMenu(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
  void changePLCstate(void);
void pageMainLadder(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageMainHMI(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageMainConfig(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageInputNumber(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageKeyboard(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageLadderEditor(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageEditLadderInstructions1(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageEditLadderInstructions2(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageEditLadderInstructions3(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageLadderDetails(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageDialogOkCancel(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageDialogMessage(uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigNetwork (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigPLC (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigProgram (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigIO (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigIOlocal (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigSystem (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigFirmware (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigWiFi (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigScanWiFi (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);
void pageConfigHMI (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y);


void setDisplay(void);
void touch_calibrate(void);
void touchMainMenu(uint16_t ts_x, uint16_t ts_y);
void touchMainLadder(uint16_t ts_x, uint16_t ts_y);
void touchHMImenu(uint16_t ts_x, uint16_t ts_y);
void touchHMImatrix(uint16_t ts_x, uint16_t ts_y, uint16_t touchType);

void touchMainConfig(uint16_t ts_x, uint16_t ts_y);
void touchInputNumber(uint16_t ts_x, uint16_t ts_y);
void touchInputText(uint16_t ts_x, uint16_t ts_y);
void touchDialogOkCancel(uint16_t ts_x, uint16_t ts_y);
void touchDialogMessage(uint16_t ts_x, uint16_t ts_y);
void touchLadderDetails(uint16_t ts_x, uint16_t ts_y);
void touchLadderEditorNavigation(uint16_t ts_x, uint16_t ts_y);
void touchLadderEditor(uint16_t ts_x, uint16_t ts_y);
  void touchLadderEditorToggleBar(void);
  uint16_t checkValidEdition(uint16_t selectedInstructionCode);
  void deleteElement(void);
  void copyColumn(void);
  void pasteColumn(void);
  void insertColumn(void);
  void deleteColumn(void);
  void copyRow(void);
  void pasteRow(void);
  void insertRow(void);
  void deleteRow(void);
  void copyNetwork(void);
  void pasteNetwork(void);
  void insertNetwork(void);
  void deleteNetwork(void);
  uint16_t columnContainsWideInstruction(uint16_t column);
  uint16_t columnContainsHighInstruction(uint16_t row);
  uint16_t columnIsEmpty(uint16_t column);
  void deleteGivenColumn(uint16_t column);
  uint16_t rowContainsHighInstruction(uint16_t row);
  uint16_t rowIsEmpty(uint16_t row);
  void deleteGivenRow(uint16_t row);
  void elementsEditionAccept(void);
  uint16_t networkIsEmpty(void);
  uint16_t lastNetworkIsEmpty(void);
void touchEditLadderInstructions1 (uint16_t ts_x, uint16_t ts_y);
  void drawLadderEditorInstructionsNavigation();
void touchEditLadderInstructions2 (uint16_t ts_x, uint16_t ts_y);
  void updateTimerBaseTime(void);
  void changeTimerBaseTime(void);
  void updateCounterField(void);
  void updateTimerCounterNumber(void);
  void updateTimerCounterSetPoint(void);
void touchEditLadderInstructions3 (uint16_t ts_x, uint16_t ts_y);
  void updateInstructionEditField1(void);
  void updateInstructionEditField2(void);
  void updateInstructionEditField3(void);
  void drawDataTypesPalette(void);
  void drawBarAddressEdition(void);
  void updateInstruction16Bit(void);
void touchEditLadderInstructionsNavigation(uint16_t ts_x, uint16_t ts_y);
void touchConfigNetwork(uint16_t ts_x, uint16_t ts_y);
void touchConfigWiFiNetwork(uint16_t ts_x, uint16_t ts_y);
void touchConfigPLC(uint16_t ts_x, uint16_t ts_y);
void touchConfigProgram(uint16_t ts_x, uint16_t ts_y);
void touchConfigHMI(uint16_t ts_x, uint16_t ts_y);
void touchConfigIO(uint16_t ts_x, uint16_t ts_y);
void touchConfigIOlocal(uint16_t ts_x, uint16_t ts_y);
void touchConfigSystem(uint16_t ts_x, uint16_t ts_y);
void touchConfigFirmware(uint16_t ts_x, uint16_t ts_y);
void touchConfigScanWiFi(uint16_t ts_x, uint16_t ts_y);


void drawInstructionsEditorBooleanBar(void);
  uint16_t getMaxMemoryAddress(uint16_t type);
  int16_t getMinMemoryAddress(uint16_t type);
  void limitMemoryRange(void);
void drawMainMenu(void);
void drawMainHMI(void);
  void drawHMImenu(void);
  void drawHMImatrix(void);
  void drawHMIbutton(uint16_t posX, uint16_t posY, uint16_t size, uint16_t color);
  void drawHMIbuttonText(uint16_t posX, uint16_t posY, uint16_t type, String text);
  void drawHMIAnalogIndicator(uint16_t posX, uint16_t posY, uint16_t type, double value);
  void drawHMIAnalogIO_Indicator(uint16_t posX, uint16_t posY, uint16_t type, double value);
void drawMainConfig(void);
void drawMainLadder(void);
  void drawLadderMenuBut1(void);
  void drawLadderMenuBut2(void);
  void drawLadderMenuBut3(void);
  void drawLadderMenuBut4(void);
  void drawLadderMenuBut5(void);
  void drawLadderMenuBut6(void);
  void drawHomeIcon(void);
  void drawLeftArrow(void);
  void drawRightArrow(void);
  void printEDIT();  
  void drawBaseNetwork(void);
  void drawPowerBar(void);
  void printNetworkNumber(void);
  void drawNetwork(void);  
  void setLadderGridColor(void); 
void drawLadderOnline(void);
  uint16_t NetworkChanged(void);
  void EditionChanged(void);
  uint16_t PLCstateChanged(void);
  void drawPLCstateSmall (void);
  void drawEditionCancel (void);
  void drawButton6Icon(void);
void drawLadderEditorBase(void);
void drawLadderEditor(void);
  void drawLadderEditorBottomButtons(void);
  void drawLadderEditorNavigationBar(void);
  void drawLadderEditorInstructionsMenu(void);
  void drawLadderEditorElementsMenu(void);
void drawEditLadderInstructions1(void);
void drawEditLadderInstructions2(void);
void drawEditLadderInstructions3(void);
void drawLadderDetails(void);
void drawNumericKeyboard(void);
void drawKeyboard(uint16_t keyboardPage);
  void drawTextBox(void);
  void drawKeyboardSpace(void);
  void changeKeyboardPage(void);
  void clearTextKeyboard(void);
void drawConfigNetwork(void);
void drawConfigWiFiNetwork(void);
  void drawNetworkConfigSSID(void);
  void drawNetworkConfigPass(void);
  void drawWiFiNetworkConfigStatus(void);
  void drawNetworkConfigButtons(void);
  void drawNetworkWifiOnOffButton(void);
void drawConfigPLC(void);
  void drawConfigProgram(void);
void drawConfigHMI(void);
void drawConfigIO(void);
void drawConfigIOlocal(void);
void drawConfigIOlocalUpdate (void);
void drawConfigSystem(void);
  void drawConfigFirmware(void);
  void drawFirmwareEnableButton(void);
  void drawFirmwareStatusBar(void);
void scanWiFiNetworks(void);
  void drawWiFiScanButtons(void);
  void drawDisconnectingWiFi(void);
  void drawScanningWiFi(void);
  void drawWiFiScanFailed(void);
  void drawNetworkInfo(uint16_t netIndex, uint16_t pageIndex);
  void drawNetworksFound(void);
  uint16_t convertDbm(int32_t WiFiPower);
void drawDialogOkCancel(void);
  void drawDialogButtons(void);
void drawDialogMessage(void);
void printPLCstate(void);
void printPLCprogram (void);
uint16_t ScanTimeChanged(void);
void printEDIT(void);
int GetData (int r, int c);
int GetFlag (int r, int c);
void drawTagBit (int Row, int Column, int Color);
void drawBox2 (int Row, int Column, int boxcolor);
void drawBox3 (int Row, int Column, int boxcolor);
void drawBoxTag (int Row, int Column, int Color);
void drawBox2Tags (int Row, int Column, int Color);
void drawBox3Tags (int Row, int Column, int Color);
void drawBoxInputPin2 (int Row, int Column);
void drawBoxInputPin3 (int Row, int Column);
void drawBoxOutputPin2 (int Row, int Column);
void drawBoxOutputPin3 (int Row, int Column);
void drawTimerTags (int Row, int Column, int Color);
void drawCounterTags (int Row, int Column, int Color);
void drawNop (int Row, int Column, int Flag, int Data);
void drawNo (int Row, int Column, int Flag, int Data);
void drawNc (int Row, int Column, int Flag, int Data);
void drawRe (int Row, int Column, int Flag, int Data);
void drawFe (int Row, int Column, int Flag, int Data);
void drawCoil (int Row, int Column, int Flag, int Data);
void drawCoilU (int Row, int Column, int Flag, int Data);
void drawCoilL (int Row, int Column, int Flag, int Data);
void drawBar (int Row, int Column, int Color);
void drawConn(int Row, int Column, int Flag, int Data);
void drawNeg(int Row, int Column, int Flag, int Data);
void drawTon(int Row, int Column, int Flag, int Data);
void drawToff(int Row, int Column, int Flag, int Data);
void drawTp(int Row, int Column, int Flag, int Data);
void drawCtu(int Row, int Column, int Flag, int Data);
void drawCtd(int Row, int Column, int Flag, int Data);
void drawMove(int Row, int Column, int Flag, int Data);
void drawSub(int Row, int Column, int Flag, int Data);
void drawAdd(int Row, int Column, int Flag, int Data);
void drawMul(int Row, int Column, int Flag, int Data);
void drawDiv(int Row, int Column, int Flag, int Data);
void drawMod(int Row, int Column, int Flag, int Data);
void drawShl(int Row, int Column, int Flag, int Data);
void drawShr(int Row, int Column, int Flag, int Data);
void drawRol(int Row, int Column, int Flag, int Data);
void drawRor(int Row, int Column, int Flag, int Data);
void drawAnd(int Row, int Column, int Flag, int Data);
void drawOr(int Row, int Column, int Flag, int Data);
void drawXor(int Row, int Column, int Flag, int Data);
void drawNot(int Row, int Column, int Flag, int Data);
void drawEq(int Row, int Column, int Flag, int Data);
void drawGt(int Row, int Column, int Flag, int Data);
void drawGe(int Row, int Column, int Flag, int Data);
void drawLt(int Row, int Column, int Flag, int Data);
void drawLe(int Row, int Column, int Flag, int Data);
void drawNe(int Row, int Column, int Flag, int Data);
void drawComparison(int Row, int Column, int Flag, int Data);

extern void saveSettings(void);

#endif