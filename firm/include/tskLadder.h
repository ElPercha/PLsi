#ifndef TSKLADDER_H
#define TSKLADDER_H

//--------------------------------------------------------------------------------
// PLC Scan main functions
//--------------------------------------------------------------------------------
void configureIO(void);
void clearMemory(void);
void loadUserProgram(void);

void readInputsLocal(void);
void readInputsRemote(void);

void scanTime(void);
void execScanPLC(uint16_t NetworkNumber);
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
// Used variables Globals for Ladder "scope"
//--------------------------------------------------------------------------------
unsigned long ActualScanTime = 0;
unsigned long StartTime = 0;

int NetworkFlags[NET_COLUMNS - 1];

extern uint16_t ShowingNetwork;
extern uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];

#endif
