#ifndef TSKLADDER_H
#define TSKLADDER_H

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
// PLC program management functions
//--------------------------------------------------------------------------------
void clearProgram(Network Networks[]);
void clearSettings(void);
void DebugCreateNetworks(Network Networks[]);

//--------------------------------------------------------------------------------
// Globals variables for Ladder "scope"
//--------------------------------------------------------------------------------
unsigned long ActualScanTime = 0;
unsigned long StartTime = 0;

int NetworkFlags[NET_COLUMNS - 1];

#endif
