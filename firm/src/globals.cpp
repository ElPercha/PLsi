#include <globals.h>


//--------------------------------------------------------------------------------
// Globals to share Networks between Tasks 
//--------------------------------------------------------------------------------

// Bits declarations
byte           M[QTY_M];
byte           I[QTY_I];
byte           Q[QTY_Q];
byte           Cr[QTY_C];   // Counter running
byte           Cd[QTY_C];   // Counter done
byte           Tr[QTY_T];   // Timer running
byte           Td[QTY_T];   // Timer done
// Previous Scan Values (history) for FE and RE in all "bits"
byte           Mh[QTY_M];
byte           Ih[QTY_I];
byte           Qh[QTY_Q];
byte           Crh[QTY_C];
byte           Cdh[QTY_C];
byte           Trh[QTY_T];
byte           Tdh[QTY_T];
// Registers declaration
uint16_t       IW[QTY_IW];
uint16_t       QW[QTY_QW];
uint16_t       C[QTY_C];
int16_t        D[QTY_D];
float          R[QTY_R];


Timer Timers[QTY_T];

int StepDebug = 0; //LUCAS

// Main PLC status 1=Running 0=Stopped >1 Error Codes
uint16_t PLCstate    = 1; 

Network diskNetwork;
Network execNetwork;
Network onlineNetwork;


//--------------------------------------------------------------------------------
// Masks and Flags for Bar and Flags analisys
//--------------------------------------------------------------------------------
const int FlagsMask[NET_ROWS] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010};
//int NetworkFlags[NET_COLUMNS - 1];

