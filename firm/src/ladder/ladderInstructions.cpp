#include <globals.h>
#include <ladder.h>

//--------------------------------------------------------------------------------
// Ladder logic instructions  
//--------------------------------------------------------------------------------

void execNop (int c, int r, int f){
  ;
}

void execConn (int c, int r, int f){
  if (f){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execNeg (int c, int r, int f){
  if (!f){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execNO (int c, int r, int f){
  if ((f) && (GetDataValue(r, c))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execNC (int c, int r, int f){
  if ((f) && !(GetDataValue(r, c))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execRE (int c, int r, int f){
  if ((f) && (GetDataValue(r, c)) && !(GetPreviousValue(r, c))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execFE (int c, int r, int f){
  if ((f) && !(GetDataValue(r, c)) && (GetPreviousValue(r, c))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execCoil (int c, int r, int f){
  if (f){
    SetDataValue(r, c, 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
  else  {SetDataValue(r, c, 0);}
}

void execCoilL (int c, int r, int f){
  if (f){
    SetDataValue(r, c, 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }  
}

void execCoilU (int c, int r, int f){
  if (f){
    SetDataValue(r, c, 0);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execTON (int c, int r, int f){
  // Timer is not active --> Reset
  if(!f){
    Timers[execNetwork.Cells[r][c].Data].ACC = 0;
    Tr[execNetwork.Cells[r][c].Data] = 0;
    Td[execNetwork.Cells[r][c].Data] = 0;
  }
  // Timer is activated in this Scan, set timer Running flag and snapshot the TimeStamp
  if(f && !Td[execNetwork.Cells[r][c].Data] && !Tr[execNetwork.Cells[r][c].Data]){
    Tr[execNetwork.Cells[r][c].Data] = 1;
    Timers[execNetwork.Cells[r][c].Data].TimeStamp = millis();    
  }
  // Timer is running, update ACC value
  if (Tr[execNetwork.Cells[r][c].Data]){
    Timers[execNetwork.Cells[r][c].Data].ACC = uint16_t((millis() - Timers[execNetwork.Cells[r][c].Data].TimeStamp)/execNetwork.Cells[r+1][c].Type);    
  }
  // Timer Done --> Activate Timer Done flag and set ACC value to his setpoint
  if (Tr[execNetwork.Cells[r][c].Data] &&
     ((millis() - Timers[execNetwork.Cells[r][c].Data].TimeStamp) >= (execNetwork.Cells[r+1][c].Data * execNetwork.Cells[r+1][c].Type))){  
    Tr[execNetwork.Cells[r][c].Data] = 0;
    Td[execNetwork.Cells[r][c].Data] = 1;
    Timers[execNetwork.Cells[r][c].Data].ACC = execNetwork.Cells[r+1][c].Data;
  }
  // Copy Timer Flags to Dynamic flags on Network
  if(Td[execNetwork.Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Tr[execNetwork.Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execTOFF (int c, int r, int f){
  // Timer is activated
  if(f && !Td[execNetwork.Cells[r][c].Data] && !Tr[execNetwork.Cells[r][c].Data]){
    Td[execNetwork.Cells[r][c].Data] = 1;
  }
  // Timer reactivated while Running --> Reset
  if(f && Tr[execNetwork.Cells[r][c].Data]){
    Tr[execNetwork.Cells[r][c].Data] = 0;
  }
  // Timer is activated in this Scan, set timer Running flag and snapshot the TimeStamp
  if(!f && Td[execNetwork.Cells[r][c].Data] && !Tr[execNetwork.Cells[r][c].Data]){
    Tr[execNetwork.Cells[r][c].Data] = 1;
    Timers[execNetwork.Cells[r][c].Data].TimeStamp = millis();    
  }
  // Timer is running, update ACC value
  if (Tr[execNetwork.Cells[r][c].Data]){
    Timers[execNetwork.Cells[r][c].Data].ACC = uint16_t((millis() - Timers[execNetwork.Cells[r][c].Data].TimeStamp)/execNetwork.Cells[r+1][c].Type);    
  }
  // Timer Done --> Activate Timer Done flag and set ACC value to his setpoint
  if (Tr[execNetwork.Cells[r][c].Data] &&
     ((millis() - Timers[execNetwork.Cells[r][c].Data].TimeStamp) >= (execNetwork.Cells[r+1][c].Data * execNetwork.Cells[r+1][c].Type))){  
    Tr[execNetwork.Cells[r][c].Data] = 0;
    Td[execNetwork.Cells[r][c].Data] = 0;
    Timers[execNetwork.Cells[r][c].Data].ACC = execNetwork.Cells[r+1][c].Data;
  }
  // Copy Timer Flags to Dynamic flags on Network
  if(Td[execNetwork.Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Tr[execNetwork.Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execTP (int c, int r, int f){
  // Timer is activated in this Scan, set timer Running flag and snapshot the TimeStamp
  if(f && !Td[execNetwork.Cells[r][c].Data] && !Tr[execNetwork.Cells[r][c].Data]){
    Td[execNetwork.Cells[r][c].Data] = 1;
    Tr[execNetwork.Cells[r][c].Data] = 1;
    Timers[execNetwork.Cells[r][c].Data].TimeStamp = millis();    
  }
  // Reset Timer Running when Input goes False to avoid continously running the timer if input stays True
  if(!f && !Td[execNetwork.Cells[r][c].Data] && Tr[execNetwork.Cells[r][c].Data]){
    Tr[execNetwork.Cells[r][c].Data] = 0;
  }
  // Timer is running, update ACC value
  if (Td[execNetwork.Cells[r][c].Data]){
    Timers[execNetwork.Cells[r][c].Data].ACC = uint16_t((millis() - Timers[execNetwork.Cells[r][c].Data].TimeStamp)/execNetwork.Cells[r+1][c].Type);    
  }
  // Timer Done --> Activate Timer Done flag and set ACC value to his setpoint
  if (Td[execNetwork.Cells[r][c].Data] &&
     ((millis() - Timers[execNetwork.Cells[r][c].Data].TimeStamp) >= (execNetwork.Cells[r+1][c].Data * execNetwork.Cells[r+1][c].Type))){  
    Td[execNetwork.Cells[r][c].Data] = 0;
    Timers[execNetwork.Cells[r][c].Data].ACC = execNetwork.Cells[r+1][c].Data;
  }
  // Copy Timer Flags to Dynamic flags on Network
  if(Td[execNetwork.Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Tr[execNetwork.Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execCTU (int c, int r, int f){
 // Reset Counter
  if (c == 0){
    if(settings.ladder.PLCstate == RUNNING){
      C[execNetwork.Cells[r][c].Data] = 0;    
      Cd[execNetwork.Cells[r][c].Data] = 0;
      Cr[execNetwork.Cells[r][c].Data] = 0;
    }
  }
  else{
    if (NetworkFlags[c-1] & FlagsMask[r+1]){
      C[execNetwork.Cells[r][c].Data] = 0;    
      Cd[execNetwork.Cells[r][c].Data] = 0;
      Cr[execNetwork.Cells[r][c].Data] = 0;
    }    
  }
 // Counter is activated in this Scan, change count
  if(f && !Cr[execNetwork.Cells[r][c].Data] && !Cd[execNetwork.Cells[r][c].Data]){
    Cr[execNetwork.Cells[r][c].Data] = 1;
    C[execNetwork.Cells[r][c].Data]++;    
  }
  // Reset Counter edge detection
  if(!f){
    Cr[execNetwork.Cells[r][c].Data] = 0;
  }
 // Counter Done 
  if (C[execNetwork.Cells[r][c].Data] >= execNetwork.Cells[r+1][c].Data){
    Cd[execNetwork.Cells[r][c].Data] = 1;
  }
 // Copy Counter Flags to Dynamic flags on Network
  if(Cd[execNetwork.Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Cr[execNetwork.Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execCTD (int c, int r, int f){
 // Reset Counter
  if (c == 0){
    if(settings.ladder.PLCstate == RUNNING){
      C[execNetwork.Cells[r][c].Data] = execNetwork.Cells[r+1][c].Data;    
      Cd[execNetwork.Cells[r][c].Data] = 0;
      Cr[execNetwork.Cells[r][c].Data] = 0;
    }
  }
  else{
    if (NetworkFlags[c-1] & FlagsMask[r+1]){
      C[execNetwork.Cells[r][c].Data] = execNetwork.Cells[r+1][c].Data;    
      Cd[execNetwork.Cells[r][c].Data] = 0;
      Cr[execNetwork.Cells[r][c].Data] = 0;
    }    
  }
 // Counter is activated in this Scan, change count
  if(f && !Cr[execNetwork.Cells[r][c].Data] && !Cd[execNetwork.Cells[r][c].Data]){
    Cr[execNetwork.Cells[r][c].Data] = 1;
    C[execNetwork.Cells[r][c].Data]--;    
  }
  // Reset Counter edge detection
  if(!f){
    Cr[execNetwork.Cells[r][c].Data] = 0;
  }
 // Counter Done 
  if (C[execNetwork.Cells[r][c].Data] == 0){
    Cd[execNetwork.Cells[r][c].Data] = 1;
  }
 // Copy Counter Flags to Dynamic flags on Network
  if(Cd[execNetwork.Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Cr[execNetwork.Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execMOVE (int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, GetDataValue (r, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execSUB (int c, int r, int f){
  if(f){
    int16_t auxValue1 = GetDataValue(r, c);
    int16_t auxValue2 = GetDataValue(r+1, c);

    if(auxValue1 > auxValue2){
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
    }  
    else if (auxValue1 == auxValue2){
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];
    }
    else{
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+2];
    }
    SetDataValue(r+2, c, auxValue1 - auxValue2);
  }
}

void execADD (int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, GetDataValue (r, c) + GetDataValue(r+1, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execMUL (int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, GetDataValue(r, c) * GetDataValue(r+1, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execDIV (int c, int r, int f){
  if(f){
    if(GetDataValue (r+1, c) == 0){
      SetDataValue(r+2, c, 0);
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+2];
    }  
    else{  
      SetDataValue(r+2, c, GetDataValue (r, c) / GetDataValue (r+1, c));
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
    }  
  }
}

void execMOD (int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, GetDataValue(r, c) % GetDataValue(r+1, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execSHL (int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, GetDataValue (r, c) << 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execSHR (int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, GetDataValue (r, c) >> 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execROL (int c, int r, int f){
  if(f){
    uint16_t auxCarryBit, auxValue;
    
    auxValue = GetDataValue (r, c);
    auxCarryBit = auxValue & 0x8000;
    auxValue = auxValue << 1;
    if (auxCarryBit){auxValue = auxValue | 0x0001;}
    SetDataValue(r+1, c, auxValue);
    
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execROR (int c, int r, int f){
  if(f){
    uint16_t auxCarryBit, auxValue;
    
    auxValue = GetDataValue (r, c);
    auxCarryBit = auxValue & 0x0001;
    auxValue = auxValue >> 1;
    if (auxCarryBit){auxValue = auxValue | 0x8000;}
    SetDataValue(r+1, c, auxValue);
    
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execAND (int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, GetDataValue(r, c) & GetDataValue(r+1, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execOR (int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, GetDataValue(r, c) | GetDataValue(r+1, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execXOR (int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, GetDataValue(r, c) ^ GetDataValue(r+1, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execNOT (int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, ~GetDataValue(r, c));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

//--------------------------------------------------------------------------------
// GET and SET Memory Values
//--------------------------------------------------------------------------------

int GetPreviousValue (int r, int c){
  int returnData = 0;
  switch (execNetwork.Cells[r][c].Type) {
    case TypeM:
      returnData = int(Mh[execNetwork.Cells[r][c].Data]);
      break;
    case TypeQ:
      returnData = int(Qh[execNetwork.Cells[r][c].Data]);
      break;
    case TypeI:
      returnData = int(Ih[execNetwork.Cells[r][c].Data]);
      break;
    case TypeCd:
      returnData = int(Cdh[execNetwork.Cells[r][c].Data]);
      break;
    case TypeCr:
      returnData = int(Crh[execNetwork.Cells[r][c].Data]);
      break;
    case TypeTd:
      returnData = int(Tdh[execNetwork.Cells[r][c].Data]);
      break;
    case TypeTr:
      returnData = int(Trh[execNetwork.Cells[r][c].Data]);
      break;
    default:
      Serial.println("GetPreviousValue ERROR in SwitchCase index");
      break;
  }
  return returnData;
}
int GetDataValue (int r, int c) { //lucas change to uint16_t ?
  int returnData = 0;
  switch (execNetwork.Cells[r][c].Type) {
    case TypeM:
      returnData = int(M[execNetwork.Cells[r][c].Data]);
      break;
    case TypeQ:
      returnData = int(Q[execNetwork.Cells[r][c].Data]);
      break;
    case TypeI:
      returnData = int(I[execNetwork.Cells[r][c].Data]);
      break;
    case TypeCd:
      returnData = int(Cd[execNetwork.Cells[r][c].Data]);
      break;
    case TypeCr:
      returnData = int(Cr[execNetwork.Cells[r][c].Data]);
      break;
    case TypeTd:
      returnData = int(Td[execNetwork.Cells[r][c].Data]);
      break;
    case TypeTr:
      returnData = int(Tr[execNetwork.Cells[r][c].Data]);
      break;
    case TypeIW:
      returnData = int(IW[execNetwork.Cells[r][c].Data]);
      break;
    case TypeQW:
      returnData = int(QW[execNetwork.Cells[r][c].Data]);
      break;
    case TypeC:
      returnData = int(C[execNetwork.Cells[r][c].Data]);
      break;
    case TypeD:
      returnData = int(D[execNetwork.Cells[r][c].Data]);
      break;
    case TypeT:
      returnData = int(Timers[execNetwork.Cells[r][c].Data].ACC);
      break;
    case TypeK:
      returnData = int(execNetwork.Cells[r][c].Data);
      break;
//    case TypeR:
//      returnData = R[execNetwork.Cells[r][c].Data];
//      break;
    default:
      Serial.println("GetDataValue ERROR in SwitchCase index");
      break;
  }
  return returnData;
}

void SetDataValue(int r, int c, int Value){ //lucas change to uint16_t ?
  switch (execNetwork.Cells[r][c].Type) {
    case TypeM:
      M[execNetwork.Cells[r][c].Data] = byte(Value);
      break;
    case TypeQ:
      Q[execNetwork.Cells[r][c].Data] = byte(Value);
      break;
    case TypeI:
      I[execNetwork.Cells[r][c].Data] = byte(Value);
      break;
    case TypeCd:
      Cd[execNetwork.Cells[r][c].Data] = byte(Value);
      break;
    case TypeCr:
      Cr[execNetwork.Cells[r][c].Data] = byte(Value);
      break;
    case TypeTd:
      Td[execNetwork.Cells[r][c].Data] = byte(Value);
      break;
    case TypeTr:
      Tr[execNetwork.Cells[r][c].Data] = byte(Value);
      break;
    case TypeIW:
      IW[execNetwork.Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeQW:
      QW[execNetwork.Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeC:
      C[execNetwork.Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeD:
      D[execNetwork.Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeT:
      Timers[execNetwork.Cells[r][c].Data].ACC = uint16_t(Value);
      break;
//    case TypeR:
//      R[execNetwork.Cells[r][c].Data] = Value;
//      break;
    default:
      Serial.println("SetDataValue ERROR in SwitchCase index");
      break;
  }
}

