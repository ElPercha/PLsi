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
#include <ladder.h>

//--------------------------------------------------------------------------------
// Calculate Scan Time in us 
//--------------------------------------------------------------------------------

void scanTime(void){
  unsigned long    scanTimeMicros = micros();
  actualScanTime = scanTimeMicros - startTime;
  startTime      = scanTimeMicros;  
}

//--------------------------------------------------------------------------------
// Copy values to history for RE and FE instructions 
//--------------------------------------------------------------------------------

void savePreviousValues(void){
  for (int i=0; i<QTY_M; i++){
    Mh[i] = M[i]; 
  }
  for (int i=0; i<QTY_I; i++){
    Ih[i] = I[i]; 
  }
  for (int i=0; i<QTY_Q; i++){
    Qh[i] = Q[i]; 
  }
  for (int i=0; i<QTY_C; i++){
    Crh[i] = Cr[i]; 
    Cdh[i] = Cd[i]; 
  }
  for (int i=0; i<QTY_T; i++){
    Tdh[i] = Td[i]; 
    Trh[i] = Tr[i]; 
  }
}


//--------------------------------------------------------------------------------
// Deletes PLC Memory Areas
//--------------------------------------------------------------------------------

void clearMemory(void){
  for (int i=0; i<QTY_M; i++){
    Mh[i] = 0;
    M[i] = 0; 
  }
  for (int i=0; i<QTY_I; i++){
    Ih[i] = 0;
    I[i] = 0; 
  }
  for (int i=0; i<QTY_Q; i++){
    Qh[i] = 0;
    Q[i] = 0; 
  }
  for (int i=0; i<QTY_C; i++){
    Cdh[i] = 0;
    Cd[i] = 0; 
    Crh[i] = 0;
    Cr[i] = 0; 
  }
  for (int i=0; i<QTY_T; i++){
    Tdh[i] = 0;
    Td[i] = 0; 
    Trh[i] = 0;
    Tr[i] = 0; 
  }
}

//--------------------------------------------------------------------------------
// Wait for tskDisk to load the User Settings  
//--------------------------------------------------------------------------------

void ladderWaitSettings(void){
  Serial.println("TaskLadder - Waiting for Unlock");
  while (bootSequence != BOOT_TASK_UNLOCKED){
    delay(10); // forces to update bootSequence global variable
  }
  Serial.println("TaskLadder - Task Unlocked");
}

//--------------------------------------------------------------------------------
// Deletes all Networks (all values to 0)    
//--------------------------------------------------------------------------------

void clearProgram (Network Networks[]){
  for (int n = 0; n < settings.ladder.NetworksQuantity; n++){
    Networks[n].Bars[0] = 0;
    Networks[n].Bars[1] = 0;
    Networks[n].Bars[2] = 0;  
    Networks[n].Bars[3] = 0;  
    Networks[n].Bars[4] = 0;  
    for (int c=0 ; c<NET_COLUMNS; c++){
      for (int r=0 ; r<NET_ROWS; r++){
        Networks[n].Cells[r][c].Code = 0;
        Networks[n].Cells[r][c].Data = 0;
        Networks[n].Cells[r][c].Type = 0;
      }
    }
  }
  Serial.println("TaskLadder - PROGRAM RAM CLEARED");
}
