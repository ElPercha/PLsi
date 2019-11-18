// Onboard Analog input measuring battery voltage in Lolin D32 PRO is GPIO35
#define AN_INPUT_BAT 49
#define AN_INPUT_BAT_PIN 35

// PLC Physical I/O. GPIO number on ESP WROVER datasheet
#define INPUT_00      34  
#define INPUT_01      35 
#define INPUT_02      32
#define INPUT_03      13
#define INPUT_04      04  
#define INPUT_05      00 
#define INPUT_06      39
#define INPUT_07      36
#define AN_INPUT_00   39
#define AN_INPUT_01   36

#define OUTPUT_00     17
#define OUTPUT_01     16
#define OUTPUT_02     02
#define OUTPUT_03     15
#define OUTPUT_04     26
#define OUTPUT_05     25
#define AN_OUTPUT_00  26
#define AN_OUTPUT_01  25

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




