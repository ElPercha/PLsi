// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#ifndef DISK_H
#define DISK_H

//--------------------------------------------------------------------------------
// Globals variables for Disk 
//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
// Task functions prototypes
//--------------------------------------------------------------------------------

void loadDisk(void);

void clearEmptyNetwork(void);

//--------------------------------------------------------------------------------
// User Settings management functions
//--------------------------------------------------------------------------------

void loadSettings(void);
void loadDefaultSettings(void);
void saveSettings(void);

//--------------------------------------------------------------------------------
// User programs transfer from PLC <> SD
//--------------------------------------------------------------------------------

void copyProgramFromPLCtoSD(uint16_t programNumber);
void copyProgramFromSDtoPLC(uint16_t programNumber);

#endif