#ifndef TSKLADDER_H
#define TSKLADDER_H

//--------------------------------------------------------------------------------
// Globals variables used in this specific task 
//--------------------------------------------------------------------------------

uint16_t NetworkFlags[NET_COLUMNS - 1];
unsigned long actualScanTime = 0;
unsigned long startTime = 0;
uint16_t analogInFilter[IO_LOCAL_IN_ANALOG_QTY][ANALOG_FILTER_SAMPLES]= {{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
uint16_t analogInFilterPointer[IO_LOCAL_IN_ANALOG_QTY]= {0,0};

#endif
