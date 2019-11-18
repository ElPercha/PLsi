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

void configureIO(void);
void clearMemory(void);
void firstRunSettings(void);


extern uint16_t ShowingNetwork;
extern uint16_t NetworkFlagsOnline[NET_COLUMNS - 1];

unsigned long ActualScanTime = 0;
unsigned long StartTime = 0;


// Instantiate Flash memory objects
// Library supports blocks of 0x1000 bytes (4096 bytes)
// "spiffs" must be declared on Flash partition, it is a default definition on Arduino "Default" Partition Scheme.

EEPROMClass  Settings("nvs", 0x9000);
EEPROMClass  FlashNetworks[] = {EEPROMClass("nvs", 0x9100),
                                EEPROMClass("nvs", 0x9200),
                                EEPROMClass("nvs", 0x9300),
                                EEPROMClass("nvs", 0x9400) };

void scanTime(void);
void readInputsLocal(void);
void readInputsRemote(void);
void execScanPLC(void);
void savePreviousValues(void);
void writeOutputsLocal(void);
void writeOutputsRemote(void);

void clearProgram(void);
void clearSettings(void);
void DebugCreateNetworks(void);




