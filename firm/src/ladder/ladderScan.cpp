#include <globals.h>
#include <ladder.h>

//--------------------------------------------------------------------------------
// Ladder Logic execution main function
//--------------------------------------------------------------------------------

void execScanPLC(uint16_t n){
  typedef void (*LadderLogic) (int c, int r, int f);
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
  
  // Resets Dynamic Flags before to start 
  for (int f=0; f<NET_COLUMNS-1; f++){NetworkFlags[f] = 0;}
  
  // Call Ladder Instructions 
  for (int c=0; c<NET_COLUMNS; c++){
    for (int r=0; r<NET_ROWS; r++){
      if (execNetwork.Cells[r][c].Code >=  FIRST_INVALID_CODE){
        Serial.println("TASK LADDER - CORE 1 - INSTRUCTION CODE INVALID: ");
        Serial.print("   - Network: ");
        Serial.println(n);
        Serial.print("   - Code: ");
        Serial.println(execNetwork.Cells[r][c].Code);
        Serial.print("   - Data: ");
        Serial.println(execNetwork.Cells[r][c].Data);
        Serial.print("   - Type: ");
        Serial.println(execNetwork.Cells[r][c].Type);
        execNetwork.Cells[r][c].Code = 0;
      }  
      if (execNetwork.Cells[r][c].Code != 0) {
        if (c == 0) {
          if(PLCstate == RUNNING){execLadder[execNetwork.Cells[r][c].Code](c,r,1);}
          else                   {execLadder[execNetwork.Cells[r][c].Code](c,r,0);}
        } 
        else{
          execLadder[execNetwork.Cells[r][c].Code](c,r,(NetworkFlags[c-1] & FlagsMask[r]));
        }
      }  
    } 
    //Update dynamic Flags vs Bars (not for column 5)
    if((c < 5) && (NetworkFlags[c] != 0 )){
      execBars (c);
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

void execBars (int c){
  for (int i=0; i<NET_ROWS-1; i++){
    NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & execNetwork.Bars[c]) << 1);
    NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & (execNetwork.Bars[c] << 1)) >> 1);
  }
}