#include <globals.h>

//--------------------------------------------------------------------------------
// Main PLC status 
//  0  = Stopped 
//  1  = Running 
// >1  = Error Codes
//--------------------------------------------------------------------------------

uint16_t PLCstate = 1; 

//--------------------------------------------------------------------------------
// Type definition for Networks and global declarations
//--------------------------------------------------------------------------------

Network diskNetwork;
Network execNetwork;
Network onlineNetwork;

//--------------------------------------------------------------------------------
// PLC Memory types definitions 
// Byte is used for Bits for increased performance of Scan time
//--------------------------------------------------------------------------------

// Bits declarations
byte           M     [QTY_M];   // Regular flags
byte           I     [QTY_I];   // Digital Inputs
byte           Q     [QTY_Q];   // Digital Outputs
byte           Cr    [QTY_C];   // Counter running
byte           Cd    [QTY_C];   // Counter done
byte           Tr    [QTY_T];   // Timer running
byte           Td    [QTY_T];   // Timer done

// Bits Previous Scan Values (history) for FE and RE instructions
byte           Mh    [QTY_M];
byte           Ih    [QTY_I];
byte           Qh    [QTY_Q];
byte           Crh   [QTY_C];
byte           Cdh   [QTY_C];
byte           Trh   [QTY_T];
byte           Tdh   [QTY_T];

// Registers declaration
uint16_t       IW    [QTY_IW];  // Analog Inputs  (word)
uint16_t       QW    [QTY_QW];  // Analog Outputs (word)
uint16_t       C     [QTY_C];   // Counter registers (16 bits)
int16_t        D     [QTY_D];   // Regular registers (signed 16 bits)
float          R     [QTY_R];   // Floaing point registers
Timer          Timers[QTY_T];   // Timers

//--------------------------------------------------------------------------------
// User settings structure global declaration
//--------------------------------------------------------------------------------

userSettings settings;

//--------------------------------------------------------------------------------
// Manage the boot secuence between tasks.
// Booting state = 0
// User config loaded = 1
//--------------------------------------------------------------------------------

uint16_t bootSequence = BOOT_INIT;

//--------------------------------------------------------------------------------
// Force User prorgam loading on boot
//--------------------------------------------------------------------------------

uint16_t loadSelectedProgram = 1;

//--------------------------------------------------------------------------------
// Mask for "Bars vs Flags" analisys
//--------------------------------------------------------------------------------

const int FlagsMask[NET_ROWS] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010};



