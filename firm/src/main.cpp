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
#include <main.h>

//--------------------------------------------------------------------------------
// Standard setup
//--------------------------------------------------------------------------------

void setup() {

  //--------------------------------------------------------------------------------
  // Serial Console initialization
  //--------------------------------------------------------------------------------

  Serial.begin(BAUD_RATE); 

  //--------------------------------------------------------------------------------
  // RTOS tasks configuration and setup
  //--------------------------------------------------------------------------------
  
  xTaskCreatePinnedToCore(
    TaskHMI
    ,  "HMI display"
    ,  4096   // Stack size up to 113000
    ,  NULL
    ,  2      // Priority 3=highest 0=lowest
    ,  NULL 
    ,  0);    // Processor Core 

  xTaskCreatePinnedToCore(
    TaskDisk
    ,  "Disk management"
    ,  4096
    ,  NULL
    ,  0
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore(
    TaskWiFi
    ,  "WiFi communications"
    ,  4096 
    ,  NULL
    ,  1
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore( 
    TaskLadder
    ,  "Ladder Logic"
    ,  80000  // Networks structure size is 76000 leaving 4K free
    ,  NULL
    ,  3
    ,  NULL 
    ,  1);    // Ladders Logic runs on Core 1
}

//--------------------------------------------------------------------------------
// Standard loop not used
//--------------------------------------------------------------------------------

void loop() {
    delay(1000);
}
