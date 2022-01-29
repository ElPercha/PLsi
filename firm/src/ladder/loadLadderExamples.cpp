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

//-----------------------------------------------------------------------
// Demo program has the minimum code to  perform the I/O validation
//  Network 0
//    HMI Switch M500 --> Activate Digital Output Q0
//    HMI Switch M501 --> Activate Digital Output Q1
//    HMI Switch M502 --> Activate Digital Output Q2
//  Network 1
//    HMI Switch M503 --> Activate Digital Output Q3
//    HMI Switch M504 --> Activate Digital Output Q4
//    HMI Switch M505 --> Activate Digital Output Q5
//  Network 2
//    HMI Value (POT) D500 --> Moved to Analog Output QW4 
//    HMI Value (POT) D501 --> Moved to Analog Output QW5 
//-----------------------------------------------------------------------

void loadDemoUserPogram(Network Networks[]){

  //--------------------------------------------------
  // NETWORK 0
  //--------------------------------------------------

  Networks[0].Cells[0][0].Code = 3;
  Networks[0].Cells[0][0].Data = 500;
  Networks[0].Cells[0][0].Type = 0;

  Networks[0].Cells[0][1].Code = 7;  
  Networks[0].Cells[0][1].Data = 0;  
  Networks[0].Cells[0][1].Type = 1;  

  Networks[0].Cells[1][0].Code = 3;  
  Networks[0].Cells[1][0].Data = 501;
  Networks[0].Cells[1][0].Type = 0;

  Networks[0].Cells[1][1].Code = 7;
  Networks[0].Cells[1][1].Data = 1;
  Networks[0].Cells[1][1].Type = 1;

  Networks[0].Cells[2][0].Code = 3;
  Networks[0].Cells[2][0].Data = 502;
  Networks[0].Cells[2][0].Type = 0;  

  Networks[0].Cells[2][1].Code = 7;  
  Networks[0].Cells[2][1].Data = 2;  
  Networks[0].Cells[2][1].Type = 1;  

  //--------------------------------------------------
  // NETWORK 1
  //--------------------------------------------------

  Networks[1].Cells[0][0].Code = 3;
  Networks[1].Cells[0][0].Data = 503;
  Networks[1].Cells[0][0].Type = 0;

  Networks[1].Cells[0][1].Code = 7;  
  Networks[1].Cells[0][1].Data = 3;  
  Networks[1].Cells[0][1].Type = 1;  

  Networks[1].Cells[1][0].Code = 3;  
  Networks[1].Cells[1][0].Data = 504;
  Networks[1].Cells[1][0].Type = 0;

  Networks[1].Cells[1][1].Code = 7;
  Networks[1].Cells[1][1].Data = 4;
  Networks[1].Cells[1][1].Type = 1;

  Networks[1].Cells[2][0].Code = 3;
  Networks[1].Cells[2][0].Data = 505;
  Networks[1].Cells[2][0].Type = 0;  

  Networks[1].Cells[2][1].Code = 7;  
  Networks[1].Cells[2][1].Data = 5;  
  Networks[1].Cells[2][1].Type = 1;  

  //--------------------------------------------------
  // NETWORK 2
  //--------------------------------------------------

  Networks[2].Cells[0][0].Code = 15;
  Networks[2].Cells[0][0].Data = 500;
  Networks[2].Cells[0][0].Type = 11;
  Networks[2].Cells[1][0].Code = 4111;
  Networks[2].Cells[1][0].Data = 4;
  Networks[2].Cells[1][0].Type = 8;

  Networks[2].Cells[2][0].Code = 15;
  Networks[2].Cells[2][0].Data = 501;
  Networks[2].Cells[2][0].Type = 11;
  Networks[2].Cells[3][0].Code = 4111;
  Networks[2].Cells[3][0].Data = 5;
  Networks[2].Cells[3][0].Type = 8;

  Serial.println("TaskLadder - Demo program loaded...");
}

