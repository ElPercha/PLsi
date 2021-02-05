#ifndef PLSI_H
#define PLSI_H

//--------------------------------------------------------------------------------
// Main congigurations for PLsi CPU 
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Firmware version
// History:
//  - Version 0.00.01 - First stable version
//  - Version 0.00.02 - Comparison instructions added (16bit)
//  - Version 0.00.03 - Analog I/O support
//--------------------------------------------------------------------------------

#define FIRMWARE  "Version 0.00.03"

//--------------------------------------------------------------------------------
// Total Networks. 
//     Max quantity tested = 500 (for 6 x 5 matrix)
//     Max stable quantity = 400 (for 6 x 5 matrix)
//--------------------------------------------------------------------------------

#define TOTAL_NETWORKS         400

//--------------------------------------------------------------------------------
// Slot where the Demo Program will be loaded after first boot
//--------------------------------------------------------------------------------

#define DEMO_PROGRAM_SLOT        0

//--------------------------------------------------------------------------------
// PLC Memory Areas quantites (amount)
//--------------------------------------------------------------------------------

#define QTY_M                 2000  // Marks. Regular flags
#define QTY_I                  200  // Digital Inputs
#define QTY_Q                  200  // Digital Outputs
#define QTY_IW                  50  // Analog Inputs
#define QTY_QW                  50  // Analog Outputs 
#define QTY_C                  200  // Counter registers (16 bits)
#define QTY_T                  300  // Timers
#define QTY_D                10000  // Regular registers (16 bit signed)
#define QTY_R                 2000  // Float or Real registers

//--------------------------------------------------------------------------------
// PLC IO Quantities and configurations
//    PLsi v0 has
//         8 inputs
//         6 outputs
//--------------------------------------------------------------------------------

#define IO_LOCAL_IN_QTY          8
#define IO_LOCAL_OUT_QTY         6
#define IO_LOCAL_IN_ANALOG_QTY   2
#define IO_LOCAL_OUT_ANALOG_QTY  2

#define ANALOG_IN_RESOLUTION  1024
#define ANALOG_OUT_RESOLUTION  256
#define ANALOG_IN_BITS          10 
#define ANALOG_CLOCK_DIVIDER     1
#define ANALOG_IN_ZERO_OFFSET   35  // Offset near 0 volts in ESP32
#define ANALOG_IN_CALIBRATION  850  // Raw value + ZERO_OFFSET when reading 5V/3 = 1.66V on ESP32 pin
#define ANALOG_FILTER_SAMPLES   20  // Samples number for moving average Analog inputs filter

const uint8_t configInputCanBeAnalog[IO_LOCAL_IN_QTY] = {0, 0, 0, 0, 0, 0, 1, 1};
const uint8_t configOutputCanBeAnalog[IO_LOCAL_OUT_QTY] = {0, 0, 0, 0, 1, 1};

//--------------------------------------------------------------------------------
// PLC Physical I/O assignment. GPIO number on ESP 32 datasheet
//--------------------------------------------------------------------------------

#define INPUT_00                34  
#define INPUT_01                35 
#define INPUT_02                32
#define INPUT_03                13
#define INPUT_04                04  
#define INPUT_05                00 
#define INPUT_06                39
#define INPUT_07                36
#define AN_INPUT_00             39
#define AN_INPUT_01             36

#define OUTPUT_00               17
#define OUTPUT_01               16
#define OUTPUT_02               02
#define OUTPUT_03               15
#define OUTPUT_04               26
#define OUTPUT_05               25
#define AN_OUTPUT_00            26
#define AN_OUTPUT_01            25

//--------------------------------------------------------------------------------
// TFT Display and TS (TouchScreen) Pinout in board socket at LOLIN D32 PRO
//--------------------------------------------------------------------------------

#define TFT_CS                  14  
#define TFT_DC                  27  
#define TFT_RST                 33 
#define TS_CS                   12 

//--------------------------------------------------------------------------------
// SD Card ChipSelect PIN 
//--------------------------------------------------------------------------------

#define SD_CS                    5

//--------------------------------------------------------------------------------
// Baud Rate fo Serial console. Mainly for debbuging
//--------------------------------------------------------------------------------

#define BAUD_RATE          115200
// #define BAUD_RATE   921600 //  Issue #11 - For Screen Saver PC connection

//--------------------------------------------------------------------------------
// Default file names and paths
//--------------------------------------------------------------------------------

#define FILENAME_SETTINGS    "/settings.bin"
#define MAX_PROGRAMS         4
const String FILENAME_USER_PROGRAMS[MAX_PROGRAMS] = {"/PROGRAM_1.plsi",
                                                     "/PROGRAM_2.plsi",
                                                     "/PROGRAM_3.plsi",
                                                     "/PROGRAM_4.plsi"};

//--------------------------------------------------------------------------------
// TS Calibration default constants.
// 320x240 2.8" SPI display 
//--------------------------------------------------------------------------------

#define TS_LEFT_X      394
#define TS_RIGHT_X    3469 
#define TS_TOP_Y       323
#define TS_BOTTOM_Y   3441

//--------------------------------------------------------------------------------
// Default WiFi credentials
//--------------------------------------------------------------------------------

#define WIFI_SSID     "Your_SSID"
#define WIFI_PASS     "Your_Password"
#define WIFI_HOSTNAME "PLsi"

#endif
