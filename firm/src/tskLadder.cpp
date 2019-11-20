// RTOS Ladder processing Task Running on Code 1
//#include <Arduino.h>
#include <globals.h>
#include <tskLadder.h>
//#include <ladder.h>
#include <plsi.h>

void TaskLadder(void *pvParameters)
{
  (void) pvParameters;
  
  Network Networks[TOTAL_NETWORKS];

  configureIO();
  clearMemory();
  //loadUserProgram();

  clearProgram(Networks);
  DebugCreateNetworks(Networks);

  while(1){
    scanTime();
    
    readInputsLocal();
    readInputsRemote();

    for (int n=0; n<TOTAL_NETWORKS; n++){
      execNetwork = Networks[n];
      execScanPLC(); 
      if (n == ShowingNetwork){
        onlineNetwork = Networks[n];
        for (int ff=0; ff<NET_COLUMNS-1; ff++){NetworkFlagsOnline[ff]= NetworkFlags[ff];}
      }
    }

    savePreviousValues();

    writeOutputsLocal();
    writeOutputsRemote();
  }
}

// --------------------------------------------------------------------------------
// Local IO -----------------------------------------------------------------------
// --------------------------------------------------------------------------------
void readInputsLocal(void){
  I[0] = !digitalRead(INPUT_00); 
  I[1] = !digitalRead(INPUT_01); 
  I[2] = !digitalRead(INPUT_02); 
  I[3] = !digitalRead(INPUT_03); 
  I[4] = !digitalRead(INPUT_04); 
  I[5] = !digitalRead(INPUT_05); 
  I[6] = !digitalRead(INPUT_06); 
  I[7] = !digitalRead(INPUT_07); 
//  IW[0]= analogRead(AN_INPUT_00);
//  IW[AN_INPUT_BAT]= uint16_t(float(analogRead(AN_INPUT_BAT_PIN))*330.0/4095.0*2.29); //2.25 because R divisor in circuit / 330 is 3.3V *100 (nominal max voltage of the ADC) / 4095 max of 12bits ADC
//  IW[AN_INPUT_BAT-1]= uint16_t(analogRead(AN_INPUT_BAT_PIN));
}
void writeOutputsLocal(void){
  digitalWrite(OUTPUT_00, Q[0]);
  digitalWrite(OUTPUT_01, Q[1]);
  digitalWrite(OUTPUT_02, Q[2]);
  digitalWrite(OUTPUT_03, Q[3]);
  digitalWrite(OUTPUT_04, Q[4]);
  digitalWrite(OUTPUT_05, Q[5]);
  //dacWrite(AN_OUTPUT_01, QW[0]);
}

// --------------------------------------------------------------------------------
// Remote IO ----------------------------------------------------------------------
// --------------------------------------------------------------------------------
void readInputsRemote(void){

}

void writeOutputsRemote(void){

}

// --------------------------------------------------------------------------------
// IO physical assignment ---------------------------------------------------------
// --------------------------------------------------------------------------------
void configureIO(void){
  pinMode( INPUT_00,  INPUT);
  pinMode( INPUT_01,  INPUT);
  pinMode( INPUT_02,  INPUT);
  pinMode( INPUT_03,  INPUT);
  pinMode( INPUT_04,  INPUT);
  pinMode( INPUT_05,  INPUT);
  pinMode( INPUT_06,  INPUT);
  pinMode( INPUT_07,  INPUT);
  
  pinMode(OUTPUT_00, OUTPUT);
  pinMode(OUTPUT_01, OUTPUT);
  pinMode(OUTPUT_02, OUTPUT);
  pinMode(OUTPUT_03, OUTPUT);
  pinMode(OUTPUT_04, OUTPUT);
  pinMode(OUTPUT_05, OUTPUT);
}

//--------------------------------------------------------------------------------
// Calculate Scan Time in us 
//--------------------------------------------------------------------------------
void scanTime(void){
  unsigned long    ScanTimeMicros = micros();
  ActualScanTime = ScanTimeMicros - StartTime;
  StartTime      = ScanTimeMicros;  
}

void loadUserProgram (void){
  uint16_t firstRun = 1;
//  Settings.get(0, firstRun);

  if (firstRun == 65535){
    Serial.println ("This is the first Run of your PLC. Default Values are going to be loaded...");
    //clearProgram();
    clearSettings();
    //DebugCreateNetworks(); // LUCAS DEBUG LOGIC. TO BE DELETED
  }  
  else{
    Serial.println ("This is not the first Run of your PLC. Your user program will be loaded...");
  }


    //uint16_t foo;
  Serial.print("Setting Value 0 at booting: "); // Debug Lucas
  //Serial.println(Settings.get(0, foo)); // Debug Lucas

  Serial.print("Flash Networks Value 0 at booting: "); // Debug Lucas
  //Serial.println(FlashNetworks[0].get(0, foo)); // Debug Lucas


}

// Set all Settings to Default
void clearSettings (void){
  //uint16_t clearSettings = 123;
  //for (int i = 0; i < 204; i++){clearSettings[i] = 0;}
  //Settings.put(0, clearSettings);
  //Settings.commit();
  //Settings.end();
  Serial.println("First Run Setting cleared.");
}

// Deletes all Networks (all values to 0)    
void clearProgram (Network Networks[]){
  // Creates a empty block of Networks that fits in Flash block size
  for (int n=0; n<TOTAL_NETWORKS; n++){
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
    // Copy the empty block to every Flash Block
    // FlashNetworks[b].put(0, Networks);
    // FlashNetworks[b].commit();
    // FlashNetworks[b].end();
    Serial.print("User Program Action - Network: ");
    Serial.print(n);
    Serial.println(" cleared.");
  }
}

// Deletes PLC Memory Areas
void clearMemory (void){
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

// Saves current network unedr edition to Flash
void saveNetworkFlash(uint16_t NetworkNumber){
  Serial.print  ("Network ");
  Serial.print  (NetworkNumber);
  Serial.println(" saved to Flash");
}


//// Loads one Networks Block from Networks (RAM to RAM)
//void LoadNetworkAuxBlock (int Index){
//  for (int i=0; i<NETWORKS_x_BLOCK; i++){
//    Networks[i+(Index*NETWORKS_x_BLOCK)] = Networks[i];
//  }
//}
//
//// NO SE USARIA!!!
//// Loads Networks Block from a Networks Block (RAM to RAM)
//void LoadNetworks (int Index){
//  for (int i=0; i<NETWORKS_x_BLOCK; i++){
//    Networks[i+(Index*NETWORKS_x_BLOCK)] = Networks[i];
//  }
//}



void DebugCreateNetworks(Network Networks[]){
  Networks[0].Cells[0][0].Code = 4;
  Networks[0].Cells[0][0].Data = 77;
  Networks[0].Cells[0][0].Type = 0;

  Networks[1].Cells[0][0].Code = 4;
  Networks[1].Cells[0][0].Data = 100;
  Networks[1].Cells[0][0].Type = 0;

  Networks[1].Cells[2][0].Code = 3;
  Networks[1].Cells[2][0].Data = 101;
  Networks[1].Cells[2][0].Type = 0;
          
  Networks[1].Cells[0][3].Code = 7;
  Networks[1].Cells[0][3].Data = 101;
  Networks[1].Cells[0][3].Type = 0;

  Networks[1].Cells[3][4].Code = 7;
  Networks[1].Cells[3][4].Data = 100;
  Networks[1].Cells[3][4].Type = 0;

  Networks[1].Cells[0][1].Code = 10;
  Networks[1].Cells[0][1].Data = 11;
  Networks[1].Cells[0][1].Type = 10;
  //Networks[1].Cells[1][1].Code = 0;
  Networks[1].Cells[1][1].Data = 6500;
  Networks[1].Cells[1][1].Type = 1;

  Networks[1].Cells[2][1].Code = 10;   //TON
  Networks[1].Cells[2][1].Data = 57;   //Timer number
  Networks[1].Cells[2][1].Type = 10;   //TypeTimer always 10
  //Networks[1].Cells[3][1].Code = 0;  //
  Networks[1].Cells[3][1].Data = 80;   //Setpoint
  Networks[1].Cells[3][1].Type = 1000; //Scale


  Networks[1].Cells[3][3].Code = 10;
  Networks[1].Cells[3][3].Data = 299;
  Networks[1].Cells[3][3].Type = 10;
  //Networks[1].Cells[4][3].Code = 0;
  Networks[1].Cells[4][3].Data = 777;
  Networks[1].Cells[4][3].Type = 10;


      
  Networks[1].Cells[0][2].Code = 1;
  Networks[1].Cells[1][2].Code = 1;
  Networks[1].Cells[2][2].Code = 1;

  Networks[1].Bars[2] = 4;


  Networks[2].Cells[0][0].Code = 3;
  Networks[2].Cells[0][0].Data = 3;
  Networks[2].Cells[0][0].Type = 2;

  Networks[2].Cells[0][1].Code = 11;
  Networks[2].Cells[0][1].Data = 15;
  Networks[2].Cells[0][1].Type = 10;
  //Networks[2].Cells[1][1].Code = 0;
  Networks[2].Cells[1][1].Data = 800;
  Networks[2].Cells[1][1].Type = 1;

  Networks[2].Cells[0][2].Code = 1;
  Networks[2].Cells[1][2].Code = 1;

  Networks[3].Cells[0][0].Code = 3;
  Networks[3].Cells[0][0].Data = 1;
  Networks[3].Cells[0][0].Type = 2;

  Networks[3].Cells[0][1].Code = 12;
  Networks[3].Cells[0][1].Data = 16;
  Networks[3].Cells[0][1].Type = 10;
  //Networks[3].Cells[1][1].Code = 0;
  Networks[3].Cells[1][1].Data = 90;
  Networks[3].Cells[1][1].Type = 10;

  Networks[3].Cells[0][2].Code = 1;
  Networks[3].Cells[1][2].Code = 1;


  Networks[4].Cells[0][0].Code = 3;
  Networks[4].Cells[0][0].Data = 0;
  Networks[4].Cells[0][0].Type = 2;

  Networks[4].Cells[1][0].Code = 3;
  Networks[4].Cells[1][0].Data = 1;
  Networks[4].Cells[1][0].Type = 2;

  Networks[4].Cells[2][0].Code = 3;
  Networks[4].Cells[2][0].Data = 2;
  Networks[4].Cells[2][0].Type = 2;

  Networks[4].Cells[3][0].Code = 3;
  Networks[4].Cells[3][0].Data = 3;
  Networks[4].Cells[3][0].Type = 2;

  Networks[4].Cells[4][0].Code = 3;
  Networks[4].Cells[4][0].Data = 4;
  Networks[4].Cells[4][0].Type = 2;

  Networks[4].Cells[0][1].Code = 7;
  Networks[4].Cells[0][1].Data = 0;
  Networks[4].Cells[0][1].Type = 1;

  Networks[4].Cells[1][1].Code = 7;
  Networks[4].Cells[1][1].Data = 1;
  Networks[4].Cells[1][1].Type = 1;

  Networks[4].Cells[2][1].Code = 7;
  Networks[4].Cells[2][1].Data = 2;
  Networks[4].Cells[2][1].Type = 1;

  Networks[4].Cells[3][1].Code = 7;
  Networks[4].Cells[3][1].Data = 3;
  Networks[4].Cells[3][1].Type = 1;

  Networks[4].Cells[4][1].Code = 7;
  Networks[4].Cells[4][1].Data = 4;
  Networks[4].Cells[4][1].Type = 1;

  Networks[4].Cells[4][2].Code = 7;
  Networks[4].Cells[4][2].Data = 5;
  Networks[4].Cells[4][2].Type = 1;

  Networks[4].Cells[1][2].Code = 3;
  Networks[4].Cells[1][2].Data = 5;
  Networks[4].Cells[1][2].Type = 2;

  Networks[4].Cells[2][2].Code = 3;
  Networks[4].Cells[2][2].Data = 6;
  Networks[4].Cells[2][2].Type = 2;

  Networks[4].Cells[3][2].Code = 3;
  Networks[4].Cells[3][2].Data = 7;
  Networks[4].Cells[3][2].Type = 2;

  Networks[5].Cells[0][0].Code = 3;
  Networks[5].Cells[0][0].Data = 1;
  Networks[5].Cells[0][0].Type = 2;

  Networks[5].Cells[0][1].Code = 15;
  Networks[5].Cells[0][1].Data = -32100;
  Networks[5].Cells[0][1].Type = 12;

  Networks[5].Cells[1][1].Code = 0;
  Networks[5].Cells[1][1].Data = 0;
  Networks[5].Cells[1][1].Type = 8;

  Networks[5].Cells[3][0].Code = 3;
  Networks[5].Cells[3][0].Data = 0;
  Networks[5].Cells[3][0].Type = 2;

  Networks[5].Cells[3][1].Code = 15;
  Networks[5].Cells[3][1].Data = 0;
  Networks[5].Cells[3][1].Type = 7;

  Networks[5].Cells[4][1].Code = 0;
  Networks[5].Cells[4][1].Data = 0;
  Networks[5].Cells[4][1].Type = 8;

  Networks[6].Cells[0][0].Code = 4;
  Networks[6].Cells[0][0].Data = 130;
  Networks[6].Cells[0][0].Type = 5;

  Networks[6].Cells[0][1].Code = 10;
  Networks[6].Cells[0][1].Data = 130;
  Networks[6].Cells[0][1].Type = 10;

  Networks[6].Cells[1][1].Code = 0;
  Networks[6].Cells[1][1].Data = 256;
  Networks[6].Cells[1][1].Type = 10;

  Networks[6].Cells[0][2].Code = 15;
  Networks[6].Cells[0][2].Data = 130;
  Networks[6].Cells[0][2].Type = 10;

  Networks[6].Cells[1][2].Code = 0;
  Networks[6].Cells[1][2].Data = 0;
  Networks[6].Cells[1][2].Type = 8;

  Networks[6].Bars[1] = 1;

  Networks[7].Cells[0][0].Code = 15;
  Networks[7].Cells[0][0].Data = 49;
  Networks[7].Cells[0][0].Type = 7;

  Networks[7].Cells[1][0].Code = 0;
  Networks[7].Cells[1][0].Data = 100;
  Networks[7].Cells[1][0].Type = 11;

  Networks[7].Cells[0][1].Code = 15;
  Networks[7].Cells[0][1].Data = 48;
  Networks[7].Cells[0][1].Type = 7;

  Networks[7].Cells[1][1].Code = 0;
  Networks[7].Cells[1][1].Data = 101;
  Networks[7].Cells[1][1].Type = 11;

  Networks[8].Cells[1][1].Code = 16;
  Networks[8].Cells[1][1].Data = 23;
  Networks[8].Cells[1][1].Type = 11;

  Networks[8].Cells[1][2].Code = 17;
  Networks[8].Cells[1][2].Data = 23;
  Networks[8].Cells[1][2].Type = 11;
  
  Networks[9].Cells[0][1].Code = 13;
  Networks[9].Cells[0][1].Data = 92;
  Networks[9].Cells[0][1].Type =  9;
  Networks[9].Cells[1][1].Code =  0;
  Networks[9].Cells[1][1].Data = 30;
  Networks[9].Cells[1][1].Type =  0;
 
  Networks[9].Cells[2][1].Code = 14;
  Networks[9].Cells[2][1].Data = 93;
  Networks[9].Cells[2][1].Type =  9;
  Networks[9].Cells[3][1].Code =  0;
  Networks[9].Cells[3][1].Data = 30;
  Networks[9].Cells[3][1].Type =  0;

  Networks[9].Cells[0][0].Code = 3;
  Networks[9].Cells[0][0].Data = 0;
  Networks[9].Cells[0][0].Type = 2;

  Networks[9].Cells[1][0].Code = 3;
  Networks[9].Cells[1][0].Data = 1;
  Networks[9].Cells[1][0].Type = 2;

  Networks[9].Cells[2][0].Code = 3;
  Networks[9].Cells[2][0].Data = 2;
  Networks[9].Cells[2][0].Type = 2;

  Networks[9].Cells[3][0].Code = 3;
  Networks[9].Cells[3][0].Data = 3;
  Networks[9].Cells[3][0].Type = 2;

  Networks[9].Cells[4][0].Code = 3;
  Networks[9].Cells[4][0].Data = 92;
  Networks[9].Cells[4][0].Type = 3;

  Networks[9].Cells[4][1].Code = 3;
  Networks[9].Cells[4][1].Data = 93;
  Networks[9].Cells[4][1].Type = 3;

  Networks[0].Cells[2][0].Code = 14;
  Networks[0].Cells[2][0].Data = 94;
  Networks[0].Cells[2][0].Type =  9;
  Networks[0].Cells[3][0].Code =  0;
  Networks[0].Cells[3][0].Data = 10;
  Networks[0].Cells[3][0].Type =  0;

  Networks[10].Cells[0][0].Code = 16;
  Networks[10].Cells[0][0].Data = 130;
  Networks[10].Cells[0][0].Type =  10;
  Networks[10].Cells[1][0].Code =  0;
  Networks[10].Cells[1][0].Data = 93;
  Networks[10].Cells[1][0].Type =  9;
  Networks[10].Cells[2][0].Code =  0;
  Networks[10].Cells[2][0].Data =200;
  Networks[10].Cells[2][0].Type = 11;

  Networks[10].Cells[0][1].Code = 17;
  Networks[10].Cells[0][1].Data = 130;
  Networks[10].Cells[0][1].Type =  10;
  Networks[10].Cells[1][1].Code =  0;
  Networks[10].Cells[1][1].Data = 93;
  Networks[10].Cells[1][1].Type =  9;
  Networks[10].Cells[2][1].Code =  0;
  Networks[10].Cells[2][1].Data =201;
  Networks[10].Cells[2][1].Type = 11;

  Networks[10].Cells[0][2].Code = 18;
  Networks[10].Cells[0][2].Data = 92;
  Networks[10].Cells[0][2].Type =  9;
  Networks[10].Cells[1][2].Code =  0;
  Networks[10].Cells[1][2].Data = 93;
  Networks[10].Cells[1][2].Type =  9;
  Networks[10].Cells[2][2].Code =  0;
  Networks[10].Cells[2][2].Data =202;
  Networks[10].Cells[2][2].Type = 11;
  
  Networks[10].Cells[0][3].Code = 19;
  Networks[10].Cells[0][3].Data = 92;
  Networks[10].Cells[0][3].Type =  9;
  Networks[10].Cells[1][3].Code =  0;
  Networks[10].Cells[1][3].Data = 93;
  Networks[10].Cells[1][3].Type =  9;
  Networks[10].Cells[2][3].Code =  0;
  Networks[10].Cells[2][3].Data =203;
  Networks[10].Cells[2][3].Type = 11;

  Networks[10].Cells[0][4].Code = 20;
  Networks[10].Cells[0][4].Data = 92;
  Networks[10].Cells[0][4].Type =  9;
  Networks[10].Cells[1][4].Code =  0;
  Networks[10].Cells[1][4].Data = 93;
  Networks[10].Cells[1][4].Type =  9;
  Networks[10].Cells[2][4].Code =  0;
  Networks[10].Cells[2][4].Data =204;
  Networks[10].Cells[2][4].Type = 11;

  //Networks[10].Bars[0] = 3;

  Networks[11].Cells[0][0].Code = 25;
  Networks[11].Cells[0][0].Data = 92;
  Networks[11].Cells[0][0].Type =  9;
  Networks[11].Cells[1][0].Code =  0;
  Networks[11].Cells[1][0].Data = 93;
  Networks[11].Cells[1][0].Type =  9;
  Networks[11].Cells[2][0].Code =  0;
  Networks[11].Cells[2][0].Data =205;
  Networks[11].Cells[2][0].Type = 11;

  Networks[11].Cells[0][1].Code = 26;
  Networks[11].Cells[0][1].Data = 92;
  Networks[11].Cells[0][1].Type =  9;
  Networks[11].Cells[1][1].Code =  0;
  Networks[11].Cells[1][1].Data = 93;
  Networks[11].Cells[1][1].Type =  9;
  Networks[11].Cells[2][1].Code =  0;
  Networks[11].Cells[2][1].Data =206;
  Networks[11].Cells[2][1].Type = 11;
  
  Networks[11].Cells[0][2].Code = 27;
  Networks[11].Cells[0][2].Data = 92;
  Networks[11].Cells[0][2].Type =  9;
  Networks[11].Cells[1][2].Code =  0;
  Networks[11].Cells[1][2].Data = 93;
  Networks[11].Cells[1][2].Type =  9;
  Networks[11].Cells[2][2].Code =  0;
  Networks[11].Cells[2][2].Data =207;
  Networks[11].Cells[2][2].Type = 11;

  Networks[11].Cells[0][3].Code = 28;
  Networks[11].Cells[0][3].Data = 92;
  Networks[11].Cells[0][3].Type =  9;
  Networks[11].Cells[1][3].Code =  0;
  Networks[11].Cells[1][3].Data =208;
  Networks[11].Cells[1][3].Type = 11;

  
  Networks[11].Cells[3][0].Code = 21;
  Networks[11].Cells[3][0].Data = 92;
  Networks[11].Cells[3][0].Type =  9;
  Networks[11].Cells[4][0].Code =  0;
  Networks[11].Cells[4][0].Data = 300;
  Networks[11].Cells[4][0].Type =  11;
  
  Networks[11].Cells[3][1].Code = 22;
  Networks[11].Cells[3][1].Data = 92;
  Networks[11].Cells[3][1].Type =  9;
  Networks[11].Cells[4][1].Code =  0;
  Networks[11].Cells[4][1].Data = 301;
  Networks[11].Cells[4][1].Type =  11;

  Networks[11].Cells[3][2].Code = 23;
  Networks[11].Cells[3][2].Data = 92;
  Networks[11].Cells[3][2].Type =  9;
  Networks[11].Cells[4][2].Code =  0;
  Networks[11].Cells[4][2].Data = 302;
  Networks[11].Cells[4][2].Type =  11;

  Networks[11].Cells[3][3].Code = 24;
  Networks[11].Cells[3][3].Data = 92;
  Networks[11].Cells[3][3].Type =  9;
  Networks[11].Cells[4][3].Code =  0;
  Networks[11].Cells[4][3].Data = 303;
  Networks[11].Cells[4][3].Type =  11;

  // FlashNetworks[0].put(0, Networks);
  // FlashNetworks[0].commit();
  // FlashNetworks[0].end();
  Serial.println("Testing program loaded...");
}





    
    
