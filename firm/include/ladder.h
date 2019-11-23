#ifndef LADDER_H
#define LADDER_H

//--------------------------------------------------------------------------------
// Globals variables for Ladder "scope"
//--------------------------------------------------------------------------------

extern uint16_t NetworkFlags[NET_COLUMNS - 1];
extern unsigned long ActualScanTime;
extern unsigned long StartTime;

//--------------------------------------------------------------------------------
// Used Global variables in ladder scope declared in another task
//--------------------------------------------------------------------------------

extern uint16_t NetworkFlagsOnline [NET_COLUMNS - 1];
extern uint16_t ShowingNetwork;

//--------------------------------------------------------------------------------
// PLC Scan main functions
//--------------------------------------------------------------------------------

void configureLocal_IO(void);
void clearMemory(void);
void loadUserProgram(void);

void readInputsLocal(void);
void readInputsRemote(void);

void scanTime(void);
void execScanPLC(Network Networks[]);
void savePreviousValues(void);

void writeOutputsLocal(void);
void writeOutputsRemote(void);

//--------------------------------------------------------------------------------
// Ladder logic instructions prototypes
//--------------------------------------------------------------------------------

void execNop (int c, int r, int f);
void execConn (int c, int r, int f);
void execNeg (int c, int r, int f);
void execNO (int c, int r, int f);
void execNC (int c, int r, int f);
void execRE (int c, int r, int f);
void execFE (int c, int r, int f);
void execCoil (int c, int r, int f);
void execCoilL (int c, int r, int f);
void execCoilU (int c, int r, int f);
void execTON (int c, int r, int f);
void execTOFF (int c, int r, int f);
void execTP (int c, int r, int f);
void execCTU (int c, int r, int f);
void execCTD (int c, int r, int f);
void execMOVE (int c, int r, int f);
void execSUB (int c, int r, int f);
void execADD (int c, int r, int f);
void execMUL (int c, int r, int f);
void execDIV (int c, int r, int f);
void execMOD (int c, int r, int f);
void execSHL (int c, int r, int f);
void execSHR (int c, int r, int f);
void execROL (int c, int r, int f);
void execROR (int c, int r, int f);
void execAND (int c, int r, int f);
void execOR (int c, int r, int f);
void execXOR (int c, int r, int f);
void execNOT (int c, int r, int f);

//--------------------------------------------------------------------------------
// Aux functions for ladder logic instructions data management
//--------------------------------------------------------------------------------

int GetDataValue (int r, int c);
int GetPreviousValue (int r, int c);
void SetDataValue(int r, int c, int Value);

//--------------------------------------------------------------------------------
// PLC program management functions
//--------------------------------------------------------------------------------

void clearProgram(Network Networks[]);
void clearSettings(void);
void DebugCreateNetworks(Network Networks[]);

#endif