// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

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

