#include <globals.h>
#include <ladder.h>

//--------------------------------------------------------------------------------
// Ladder Logic execution (PLC SCAN)
//--------------------------------------------------------------------------------

void execScanPLC(Network Networks[]){
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
  
  for (int n=0; n<TOTAL_NETWORKS; n++){
    execNetwork = Networks[n];

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
      //Update dynamic Flags vs Bars (not for last column)
      if((c < NET_COLUMNS - 1) && (NetworkFlags[c] != 0 )){
        for (int i=0; i<NET_ROWS-1; i++){
          NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & execNetwork.Bars[c]) << 1);
          NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & (execNetwork.Bars[c] << 1)) >> 1);
        }
      }
    }
    if (n == showingNetwork){
      onlineNetwork = Networks[n];
      for (int ff=0; ff<NET_COLUMNS-1; ff++){NetworkFlagsOnline[ff]= NetworkFlags[ff];}
    }
  }
}
