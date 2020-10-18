#include <globals.h>

//--------------------------------------------------------------------------------
// Type definition for Networks and global declarations
//--------------------------------------------------------------------------------

Network execNetwork;            // Network in excecution 
Network onlineNetwork;          // Network for Online animation and program visualization
Network editingNetwork;         // Intermediate Network for editing 
Network copyMemoryNetwork;      // Used To Copy and Paste Networks
Network emptyNetwork;           // Empty Network
memoryColumn copyMemoryColumn;  // Struct to copy and paste columns
memoryRow copyMemoryRow;        // Struct to copy and paste rows

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
// Sync between taskLadder and others
//--------------------------------------------------------------------------------

uint16_t loadSelectedProgram = 1; // Force to load user program on boot
uint16_t updateSelectedProgramRAM = 0;
uint16_t updateSelectedProgramDisk = 0;
uint16_t moveNetworksInsert = 0;
uint16_t moveNetworksDelete = 0;

uint16_t showingNetwork = 0;      // Network to show under Online animation

//--------------------------------------------------------------------------------
// Mask for "Bars vs Flags" analisys
//--------------------------------------------------------------------------------

const uint16_t FlagsMask[NET_ROWS] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010};
const uint16_t FlagsMaskAnd[NET_ROWS] = {0xFFFE, 0xFFFD, 0xFFFB, 0x0007, 0xFFEF};



