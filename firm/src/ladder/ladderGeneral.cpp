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
// Wait for tskDisk to load the User Settings  
//--------------------------------------------------------------------------------

void waitSettings (void){
  Serial.println("Waiting for Settings to be loaded");
  while (bootSequence != 1){}
  Serial.println("Settings loaded correctly");
}

//--------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------

void loadUserProgram (void){
  uint16_t firstRun = 1;
//  Settings.get(0, firstRun);

  if (firstRun == 65535){
    Serial.println ("This is the first Run of your PLC. Default Values are going to be loaded...");
    //clearProgram();
    //clearSettings();
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
//--------------------------------------------------------------------------------
// Set all Settings to Default
// to be called on first Run of PLC or after user request
//--------------------------------------------------------------------------------
void firstRun (void){
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
  }
  Serial.println("RAM PROGRAM CLEARED");
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

