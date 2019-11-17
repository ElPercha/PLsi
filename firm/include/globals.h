#ifndef GlobalsH
#define GlobalsH
extern unsigned short int AGLOBAL; // no value in here!


// Basic Libraries
#include <SPI.h>

// File System
#include "FS.h"
#include "SPIFFS.h"

// I2C
#include <Wire.h>

// PCA9685 Adafruit Servo controller 12 channels
#include <Adafruit_PWMServoDriver.h>

// Web Server
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>


/////////////////////////////////////////////////////

#define FIRMWARE    0

//PLC Running status
#define STOPPED        0 
#define RUNNING        1 
#define PLCERROR       2

// PLC Memory Areas (amount)
#define QTY_M 12000    // Marks
#define QTY_I   200    // Digital Inputs
#define QTY_Q   200    // Digital Outputs
#define QTY_IW   50    // Analog Inputs
#define QTY_QW   50    // Analog Outputs 
#define QTY_C   300    // Counter registers
#define QTY_T   300    // Timer registers in usec
#define QTY_D 10000    // Regular registers
#define QTY_R  2000    // Float registers

// PLC Data Types Codes
// Must match with 'MnemonicsTypes' array
#define TypeM    0
#define TypeQ    1
#define TypeI    2
#define TypeCd   3
#define TypeCr   4
#define TypeTd   5
#define TypeTr   6
#define TypeIW   7
#define TypeQW   8
#define TypeC    9
#define TypeT   10
#define TypeD   11
#define TypeK   12
#define TypeR   13
#define FIRST_INVALID_TYPE   14

// PLC Ladder Instructions codes 
// Must match with array of funtions in TaskLadder
#define NOPP    0
#define CONN    1
#define NEG     2
#define NO      2
#define NC      4
#define RE      5
#define FE      6
#define COIL    7
#define COILL   8
#define COILU   9
#define TON    10
#define TOFF   11
#define TP     12
#define CTU    13
#define CTD    14
#define MOVE   15
#define SUB    16
#define ADD    17
#define MUL    18
#define DIV    19
#define MOD    20
#define SHL    21
#define SHR    22
#define ROL    23
#define ROR    24
#define AND    25
#define OR     26
#define XOR    27
#define NOT    28
#define FIRST_INVALID_CODE 29

// PLC Network Logic Definitions [units]
#define NET_COLUMNS 6     
#define NET_ROWS 5

// Networks distribution in Flash. Block size 4096 bytes
#define NETWORKS_x_BLOCK 20       // 4096/sizeof(Networks)
//#define NETWORKS_BLOCKS 20       // Defined on Flash 
#define NETWORKS_BLOCKS  4       // Defined on Flash 
#define MAX_NETWORKS (NETWORKS_x_BLOCK * NETWORKS_BLOCKS)

// Masks for Bar and Flags analisys
//extern const int FlagsMask[NET_ROWS] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010};
extern const int FlagsMask[NET_ROWS];


// Ladder Logic Network Map in RAM (only one Networks Block)
typedef struct
{
  uint16_t Code;
  int16_t Data;
  int16_t Type;
} Cell;

typedef struct
{
  Cell Cells[NET_ROWS][NET_COLUMNS];
  uint16_t Bars [NET_COLUMNS - 1];
} Network;

extern Network OnlineNetwork;
//Network auxNetworks[NETWORKS_x_BLOCK];
extern Network Networks[NETWORKS_x_BLOCK];


// Bits declarations
extern byte           M[QTY_M];
extern byte           I[QTY_I];
extern byte           Q[QTY_Q];
extern byte           Cr[QTY_C];   // Counter running
extern byte           Cd[QTY_C];   // Counter done
extern byte           Tr[QTY_T];   // Timer running
extern byte           Td[QTY_T];   // Timer done
// Previous Scan Values (history) for FE and RE in all "bits"
extern byte           Mh[QTY_M];
extern byte           Ih[QTY_I];
extern byte           Qh[QTY_Q];
extern byte           Crh[QTY_C];
extern byte           Cdh[QTY_C];
extern byte           Trh[QTY_T];
extern byte           Tdh[QTY_T];
// Registers declaration
extern uint16_t       IW[QTY_IW];
extern uint16_t       QW[QTY_QW];
extern uint16_t       C[QTY_C];
extern int16_t        D[QTY_D];
extern float          R[QTY_R];
//unsigned long  T[QTY_T]; // 32bits same as unsigned int

// Timers struct
typedef struct {
  unsigned long TimeStamp; // 32bits same as unsigned int
  uint16_t            ACC;
} Timer;

extern Timer Timers[QTY_T];

// Global variables
extern int StepDebug; //LUCAS

// Main PLC status 1=Running 0=Stopped >1 Error Codes
extern uint16_t PLCstate; 

// Flags for Logic processing 
extern int NetworkFlags[NET_COLUMNS - 1];

#endif
