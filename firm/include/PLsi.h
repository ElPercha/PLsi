#ifndef PLSI_H
#define PLSI_H

//--------------------------------------------------------------------------------
// Main congigurations for PLsi CPU 
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Firmware version 
//--------------------------------------------------------------------------------

#define FIRMWARE         0

//--------------------------------------------------------------------------------
// Baud Rate fo Serial console. Mainly for debbuging
//--------------------------------------------------------------------------------

#define BAUD_RATE   115200

//--------------------------------------------------------------------------------
// Total Networks. Max quantity tested OK = 500
//--------------------------------------------------------------------------------

#define TOTAL_NETWORKS 500

//--------------------------------------------------------------------------------
// PLC Memory Areas quantites (amount)
//--------------------------------------------------------------------------------

#define QTY_M      12000    // Marks. Regular flags
#define QTY_I        200    // Digital Inputs
#define QTY_Q        200    // Digital Outputs
#define QTY_IW        50    // Analog Inputs
#define QTY_QW        50    // Analog Outputs 
#define QTY_C        300    // Counter registers (16 bits)
#define QTY_T        300    // Timers
#define QTY_D      10000    // Regular registers (16 bit signed)
#define QTY_R       2000    // Float or Real registers

//--------------------------------------------------------------------------------
// PLC Physical I/O assignment. GPIO number on ESP WROVER datasheet
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

#endif
