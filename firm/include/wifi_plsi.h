/*
Copyright (c) 2019 Prieto Lucas. All rights reserved.
This file is part of the PLsi project.

PLsi is free software and hardware: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
PLsi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
