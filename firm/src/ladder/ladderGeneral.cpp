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
  Serial.println("TskLadder - Waiting for Settings to be loaded");
  while (bootSequence != 1){
    delay(10); // forces to update bootSequence variable
  }
  Serial.println("TskLadder - Settings loaded correctly");
}

//--------------------------------------------------------------------------------
// Load user program to local Networks[] array 
// Using the global variable diskNetwork and bootSequence sync variable
//--------------------------------------------------------------------------------

void waitUserProgram (void){
  Serial.println("TskLadder - Start loading user program");
  while (bootSequence != 1000){
    delay(10); 
  }
  Serial.println("TskLadder - Finished loading user program");
}

//--------------------------------------------------------------------------------
// Deletes all Networks (all values to 0)    
//--------------------------------------------------------------------------------

void clearProgram (Network Networks[]){
  // Creates a empty block of Networks that fits in Flash block size
  for (int n = 0; n < TOTAL_NETWORKS; n++){
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
  Serial.println("Tsk General - RAM PROGRAM CLEARED");
}

//--------------------------------------------------------------------------------
// Deletes PLC Memory Areas
//--------------------------------------------------------------------------------

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
