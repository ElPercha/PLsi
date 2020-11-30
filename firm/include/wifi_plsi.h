#ifndef WIFI_PLSI_H
#define WIFI_PLSI_H

//--------------------------------------------------------------------------------
// Globals variables for WiFi task
//--------------------------------------------------------------------------------

extern uint8_t configFirmwareEnabled;
extern uint8_t configFirmwareSequence;
extern uint8_t configFirmwareMemory;

//--------------------------------------------------------------------------------
// Wifi task main functions
//--------------------------------------------------------------------------------

void wifiWaitSettings(void);

#endif
