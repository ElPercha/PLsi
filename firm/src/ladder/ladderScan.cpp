#include <globals.h>
#include <ladder/ladderScan.h>

//--------------------------------------------------------------------------------
// Ladder Logic Scanning 
//--------------------------------------------------------------------------------
void execScanPLC(void){
  typedef void (*LadderLogic) (int n, int c, int r, int f);
  LadderLogic execLadder [] =
  {
    execNop,    
    execConn,   
    execNeg,
    execNO,
    execNC,
    execRE,
    execFE,
    execCoil,
    execCoilL,
    execCoilU,
    execTON,
    execTOFF,
    execTP,
    execCTU,
    execCTD,
    execMOVE,
    execSUB,
    execADD,
    execMUL,
    execDIV,
    execMOD,
    execSHL,
    execSHR,
    execROL,
    execROR,
    execAND,
    execOR,
    execXOR,
    execNOT
  };
  
  for (int b=0; b<NETWORKS_BLOCKS; b++){
    //FlashNetworks[b].get(0, Networks);
    for (int n=0; n<NETWORKS_x_BLOCK; n++){
      // Resets Dynamic Flags before to start 
      for (int f=0; f<NET_COLUMNS-1; f++){NetworkFlags[f] = 0;}
      
      // Call Ladder Instructions 
      for (int c=0; c<NET_COLUMNS; c++){
        for (int r=0; r<NET_ROWS; r++){
          if (Networks[n].Cells[r][c].Code >=  FIRST_INVALID_CODE){
            Serial.println("TASK LADDER - CORE 1 - INSTRUCTION CODE INVALID: ");
            Serial.print("   - Block: ");
            Serial.println(b);
            Serial.print("   - Network: ");
            Serial.println(n);
            Serial.print("   - Code: ");
            Serial.println(Networks[n].Cells[r][c].Code);
            Serial.print("   - Data: ");
            Serial.println(Networks[n].Cells[r][c].Data);
            Serial.print("   - Type: ");
            Serial.println(Networks[n].Cells[r][c].Type);
            Networks[n].Cells[r][c].Code = 0;
          }  
          if (Networks[n].Cells[r][c].Code != 0) {
            if (c == 0) {
              if(PLCstate == RUNNING){execLadder[Networks[n].Cells[r][c].Code](n,c,r,1);}
              else                   {execLadder[Networks[n].Cells[r][c].Code](n,c,r,0);}
            } 
            else{
              execLadder[Networks[n].Cells[r][c].Code](n,c,r,(NetworkFlags[c-1] & FlagsMask[r]));
            }
          }  
        } 
        //Update dynamic Flags vs Bars (not for column 5)
        if((c < 5) && (NetworkFlags[c] != 0 )){execBars(n, c);}
      }
      // Copy Network Info for Online Visualization
      if ((b * NETWORKS_x_BLOCK) + n == ShowingNetwork){
        OnlineNetwork = Networks[n];
        for (int ff=0; ff<NET_COLUMNS-1; ff++){NetworkFlagsOnline[ff]= NetworkFlags[ff];}
      }
    }
  }
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
// BARS Management
//--------------------------------------------------------------------------------

void execBars (int n, int c){
  for (int i=0; i<NET_ROWS-1; i++){
    NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & Networks[n].Bars[c]) << 1);
    NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & (Networks[n].Bars[c] << 1)) >> 1);
  }
}