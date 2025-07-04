// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#ifndef WIFI_PLSI_H
#define WIFI_PLSI_H

//--------------------------------------------------------------------------------
// Globals variables for WiFi task
//--------------------------------------------------------------------------------

extern uint16_t configFirmwareEnabled;
extern uint16_t configFirmwareSequence;
extern uint16_t configFirmwareMemory;

extern uint32_t previousFreeMemory;

//--------------------------------------------------------------------------------
// Web Server Object 
//--------------------------------------------------------------------------------

extern WebServer server; 

//--------------------------------------------------------------------------------
// Modbus TCP 
//--------------------------------------------------------------------------------

extern ModbusIP modbusTCP;
extern IPAddress remote;  // Address of Modbus Slave device

//--------------------------------------------------------------------------------
// Wifi task main functions
//--------------------------------------------------------------------------------

void wifiWaitSettings(void);
void printAvailableMemory(void);

void modbusTCPConfigure (void);
void modbusTCPUnconfigure (void);
void modbusTCPManager (void);

#endif
