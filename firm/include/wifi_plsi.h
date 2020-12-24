#ifndef WIFI_PLSI_H
#define WIFI_PLSI_H

//--------------------------------------------------------------------------------
// Globals variables for WiFi task
//--------------------------------------------------------------------------------

extern uint16_t configFirmwareEnabled;
extern uint16_t configFirmwareSequence;
extern uint16_t configFirmwareMemory;

//--------------------------------------------------------------------------------
// Wifi task main functions
//--------------------------------------------------------------------------------

void wifiWaitSettings(void);

#endif
