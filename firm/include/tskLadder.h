
unsigned long ActualScanTime = 0;
unsigned long StartTime = 0;


//////////////////////////////////////////////////////////

extern uint16_t ShowingNetwork;
extern uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];

void configureIO(void);
void clearMemory(void);
void loadUserProgram(void);

void readInputsLocal(void);
void readInputsRemote(void);

void scanTime(void);
void execScanPLC(void);
void savePreviousValues(void);

void writeOutputsLocal(void);
void writeOutputsRemote(void);

//////////////////////////////////////////////////////////



void clearProgram(Network Networks[]);
void clearSettings(void);

void DebugCreateNetworks(Network Networks[]);




