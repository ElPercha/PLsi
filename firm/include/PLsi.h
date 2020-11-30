#ifndef PLSI_H
#define PLSI_H

//--------------------------------------------------------------------------------
// Main congigurations for PLsi CPU 
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Firmware version 
//--------------------------------------------------------------------------------

#define FIRMWARE         "Version 0.0.1"

//--------------------------------------------------------------------------------
// Baud Rate fo Serial console. Mainly for debbuging
//--------------------------------------------------------------------------------

#define BAUD_RATE   115200
//#define BAUD_RATE   921600 //  Issue #11 - For Screen Saver PC connection

//--------------------------------------------------------------------------------
// Total Networks. Max quantity tested OK = 500
//--------------------------------------------------------------------------------

#define TOTAL_NETWORKS 400

//--------------------------------------------------------------------------------
// Slot where the Demo Program will be loaded after first boot
//--------------------------------------------------------------------------------

#define DEMO_PROGRAM_SLOT 0

//--------------------------------------------------------------------------------
// PLC Memory Areas quantites (amount)
//--------------------------------------------------------------------------------

#define QTY_M       2000    // Marks. Regular flags
#define QTY_I        200    // Digital Inputs
#define QTY_Q        200    // Digital Outputs
#define QTY_IW        50    // Analog Inputs
#define QTY_QW        50    // Analog Outputs 
#define QTY_C        200    // Counter registers (16 bits)
#define QTY_T        300    // Timers
#define QTY_D      10000    // Regular registers (16 bit signed)
#define QTY_R       2000    // Float or Real registers

//--------------------------------------------------------------------------------
// PLC Physical I/O assignment. GPIO number on ESP 32 datasheet
//--------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------
// SD Card ChipSelect PIN 
//--------------------------------------------------------------------------------

#define SD_CS          5

//--------------------------------------------------------------------------------
// Default file names and paths
//--------------------------------------------------------------------------------

#define FILENAME_SETTINGS    "/settings.bin"
#define MAX_PROGRAMS   4
const String FILENAME_USER_PROGRAMS[MAX_PROGRAMS] = {"/PROGRAM_1.plsi",
                                                     "/PROGRAM_2.plsi",
                                                     "/PROGRAM_3.plsi",
                                                     "/PROGRAM_4.plsi"};

//--------------------------------------------------------------------------------
// TS Calibration default constants.
// 2.8" SPI display 
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
