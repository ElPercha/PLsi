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