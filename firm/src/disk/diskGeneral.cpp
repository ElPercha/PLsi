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

#include <globals.h>
#include <plsi.h>
#include <disk.h>
 
//--------------------------------------------------------------------------------
// Initialize empty Network (all values to 0)
//--------------------------------------------------------------------------------

void clearEmptyNetwork (void){
  if(bootSequence == BOOT_SETTINGS_LOADED){
    for (int c=0 ; c<NET_COLUMNS; c++){
      for (int r=0 ; r<NET_ROWS; r++){
        emptyNetwork.Cells[r][c].Code = 0;
        emptyNetwork.Cells[r][c].Data = 0;
        emptyNetwork.Cells[r][c].Type = 0;
      }
    }
    for (int c = 0 ; c < NET_COLUMNS-1; c++){
      emptyNetwork.Bars[c] = 0;
    }
    copyMemoryNetwork = emptyNetwork;
    onlineNetwork = emptyNetwork;
    editingNetwork = emptyNetwork;

    Serial.println("TaskDisk - emptyNetwork and auxiliary Networks Initialized");
    bootSequence = BOOT_TASK_UNLOCKED;
  }
}

