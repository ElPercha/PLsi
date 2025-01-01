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
#include <tskDisk.h>
#include <disk.h>
#include "FS.h"
#include "SD.h"
#include "FFat.h"

//--------------------------------------------------------------------------------
// Disk Task 
// Controls SPIFSS memory and SD Card files
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskDisk(void *pvParameters)
{
  (void) pvParameters;

  //------------------------------------------------------
  // Regular boot: Mount FFAT Disk
  // First boot: Format FFAT disk
  //------------------------------------------------------
  
  loadDisk();         

  //------------------------------------------------------
  // Regular boot: Load saved settings from FFAT Disk
  // First boot: Load default settings and Save to Disk
  //------------------------------------------------------

  loadSettings();
  
  //------------------------------------------------------
  // Clear auxiliary networks and Unlock tasks
  //------------------------------------------------------

  clearEmptyNetwork();

//----------------------------------------------------
  // Task Main loop 
  //----------------------------------------------------

  while(1){

    //----------------------------------------------------
    // Update Newtork currently in edition mode to disk
    //----------------------------------------------------

    if(updateSelectedProgramDisk){
      FFat.begin(false,"/ffat",1);
      File userProgramFile = FFat.open(FILENAME_USER_PROGRAMS[settings.ladder.UserProgram],"r+");
      userProgramFile.seek(showingNetwork * sizeof(onlineNetwork));
      userProgramFile.write((uint8_t *)&onlineNetwork, sizeof(onlineNetwork));
      userProgramFile.close();
      FFat.end();

      updateSelectedProgramDisk = 0;
    }

    
    
    /*
    //----------------------------------------------------
    // PLC >> SD card programs transfer
    // Development ongoing
    //----------------------------------------------------

    if (D[507] == 1){
      copyProgramFromPLCtoSD(0);
      D[507] = 101;
    }

    if (D[507] == 2){
      copyProgramFromPLCtoSD(1);
      D[507] = 102;
    }
    if (D[507] == 3){
      copyProgramFromPLCtoSD(2);
      D[507] = 103;
    }
    if (D[507] == 4){
      copyProgramFromPLCtoSD(3);
      D[507] = 104;
    }

    //----------------------------------------------------
    // SD >> PLC card programs transfer
    // Development ongoing
    //----------------------------------------------------

    if (D[507] == 11){
      copyProgramFromSDtoPLC(0);
      D[507] = 1011;
    }

    if (D[507] == 12){
      copyProgramFromSDtoPLC(1);
      D[507] = 1012;
    }

    if (D[507] == 13){
      copyProgramFromSDtoPLC(2);
      D[507] = 1013;
    }

    if (D[507] == 14){
      copyProgramFromSDtoPLC(3);
      D[507] = 1014;
    }*/

    delay(5);
 }
}