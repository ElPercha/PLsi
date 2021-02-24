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
