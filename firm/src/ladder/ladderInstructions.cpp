#include <globals.h>
#include <ladder/ladderInstructions.h>

//--------------------------------------------------------------------------------
// PLC instructions  
//--------------------------------------------------------------------------------

void execNop (int n, int c, int r, int f){
  ;
}

void execConn (int n, int c, int r, int f){
  if (f){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execNeg (int n, int c, int r, int f){
  if (!f){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execNO (int n, int c, int r, int f){
  if ((f) && (GetDataValue(r, c, n))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execNC (int n, int c, int r, int f){
  if ((f) && !(GetDataValue(r, c, n))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execRE (int n, int c, int r, int f){
  if ((f) && (GetDataValue(r, c, n)) && !(GetPreviousValue(r, c, n))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execFE (int n, int c, int r, int f){
  if ((f) && !(GetDataValue(r, c, n)) && (GetPreviousValue(r, c, n))){
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execCoil (int n, int c, int r, int f){
  if (f){
    SetDataValue(r, c, n, 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
  else  {SetDataValue(r, c, n, 0);}
}

void execCoilL (int n, int c, int r, int f){
  if (f){
    SetDataValue(r, c, n, 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }  
}

void execCoilU (int n, int c, int r, int f){
  if (f){
    SetDataValue(r, c, n, 0);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];      
  }
}

void execTON (int n, int c, int r, int f){
  // Timer is not active --> Reset
  if(!f){
    Timers[Networks[n].Cells[r][c].Data].ACC = 0;
    Tr[Networks[n].Cells[r][c].Data] = 0;
    Td[Networks[n].Cells[r][c].Data] = 0;
  }
  // Timer is activated in this Scan, set timer Running flag and snapshot the TimeStamp
  if(f && !Td[Networks[n].Cells[r][c].Data] && !Tr[Networks[n].Cells[r][c].Data]){
    Tr[Networks[n].Cells[r][c].Data] = 1;
    Timers[Networks[n].Cells[r][c].Data].TimeStamp = millis();    
  }
  // Timer is running, update ACC value
  if (Tr[Networks[n].Cells[r][c].Data]){
    Timers[Networks[n].Cells[r][c].Data].ACC = uint16_t((millis() - Timers[Networks[n].Cells[r][c].Data].TimeStamp)/Networks[n].Cells[r+1][c].Type);    
  }
  // Timer Done --> Activate Timer Done flag and set ACC value to his setpoint
  if (Tr[Networks[n].Cells[r][c].Data] &&
     ((millis() - Timers[Networks[n].Cells[r][c].Data].TimeStamp) >= (Networks[n].Cells[r+1][c].Data * Networks[n].Cells[r+1][c].Type))){  
    Tr[Networks[n].Cells[r][c].Data] = 0;
    Td[Networks[n].Cells[r][c].Data] = 1;
    Timers[Networks[n].Cells[r][c].Data].ACC = Networks[n].Cells[r+1][c].Data;
  }
  // Copy Timer Flags to Dynamic flags on Network
  if(Td[Networks[n].Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Tr[Networks[n].Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execTOFF (int n, int c, int r, int f){
  // Timer is activated
  if(f && !Td[Networks[n].Cells[r][c].Data] && !Tr[Networks[n].Cells[r][c].Data]){
    Td[Networks[n].Cells[r][c].Data] = 1;
  }
  // Timer reactivated while Running --> Reset
  if(f && Tr[Networks[n].Cells[r][c].Data]){
    Tr[Networks[n].Cells[r][c].Data] = 0;
  }
  // Timer is activated in this Scan, set timer Running flag and snapshot the TimeStamp
  if(!f && Td[Networks[n].Cells[r][c].Data] && !Tr[Networks[n].Cells[r][c].Data]){
    Tr[Networks[n].Cells[r][c].Data] = 1;
    Timers[Networks[n].Cells[r][c].Data].TimeStamp = millis();    
  }
  // Timer is running, update ACC value
  if (Tr[Networks[n].Cells[r][c].Data]){
    Timers[Networks[n].Cells[r][c].Data].ACC = uint16_t((millis() - Timers[Networks[n].Cells[r][c].Data].TimeStamp)/Networks[n].Cells[r+1][c].Type);    
  }
  // Timer Done --> Activate Timer Done flag and set ACC value to his setpoint
  if (Tr[Networks[n].Cells[r][c].Data] &&
     ((millis() - Timers[Networks[n].Cells[r][c].Data].TimeStamp) >= (Networks[n].Cells[r+1][c].Data * Networks[n].Cells[r+1][c].Type))){  
    Tr[Networks[n].Cells[r][c].Data] = 0;
    Td[Networks[n].Cells[r][c].Data] = 0;
    Timers[Networks[n].Cells[r][c].Data].ACC = Networks[n].Cells[r+1][c].Data;
  }
  // Copy Timer Flags to Dynamic flags on Network
  if(Td[Networks[n].Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Tr[Networks[n].Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execTP (int n, int c, int r, int f){
  // Timer is activated in this Scan, set timer Running flag and snapshot the TimeStamp
  if(f && !Td[Networks[n].Cells[r][c].Data] && !Tr[Networks[n].Cells[r][c].Data]){
    Td[Networks[n].Cells[r][c].Data] = 1;
    Tr[Networks[n].Cells[r][c].Data] = 1;
    Timers[Networks[n].Cells[r][c].Data].TimeStamp = millis();    
  }
  // Reset Timer Running when Input goes False to avoid continously running the timer if input stays True
  if(!f && !Td[Networks[n].Cells[r][c].Data] && Tr[Networks[n].Cells[r][c].Data]){
    Tr[Networks[n].Cells[r][c].Data] = 0;
  }
  // Timer is running, update ACC value
  if (Td[Networks[n].Cells[r][c].Data]){
    Timers[Networks[n].Cells[r][c].Data].ACC = uint16_t((millis() - Timers[Networks[n].Cells[r][c].Data].TimeStamp)/Networks[n].Cells[r+1][c].Type);    
  }
  // Timer Done --> Activate Timer Done flag and set ACC value to his setpoint
  if (Td[Networks[n].Cells[r][c].Data] &&
     ((millis() - Timers[Networks[n].Cells[r][c].Data].TimeStamp) >= (Networks[n].Cells[r+1][c].Data * Networks[n].Cells[r+1][c].Type))){  
    Td[Networks[n].Cells[r][c].Data] = 0;
    Timers[Networks[n].Cells[r][c].Data].ACC = Networks[n].Cells[r+1][c].Data;
  }
  // Copy Timer Flags to Dynamic flags on Network
  if(Td[Networks[n].Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Tr[Networks[n].Cells[r][c].Data]){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execCTU (int n, int c, int r, int f){
 // Reset Counter
  if (c == 0){
    if(PLCstate == RUNNING){
      C[Networks[n].Cells[r][c].Data] = 0;    
      Cd[Networks[n].Cells[r][c].Data] = 0;
      Cr[Networks[n].Cells[r][c].Data] = 0;
    }
  }
  else{
    if (NetworkFlags[c-1] & FlagsMask[r+1]){
      C[Networks[n].Cells[r][c].Data] = 0;    
      Cd[Networks[n].Cells[r][c].Data] = 0;
      Cr[Networks[n].Cells[r][c].Data] = 0;
    }    
  }
 // Counter is activated in this Scan, change count
  if(f && !Cr[Networks[n].Cells[r][c].Data] && !Cd[Networks[n].Cells[r][c].Data]){
    Cr[Networks[n].Cells[r][c].Data] = 1;
    C[Networks[n].Cells[r][c].Data]++;    
  }
  // Reset Counter edge detection
  if(!f){
    Cr[Networks[n].Cells[r][c].Data] = 0;
  }
 // Counter Done 
  if (C[Networks[n].Cells[r][c].Data] >= Networks[n].Cells[r+1][c].Data){
    Cd[Networks[n].Cells[r][c].Data] = 1;
  }
 // Copy Counter Flags to Dynamic flags on Network
  if(Cd[Networks[n].Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Cr[Networks[n].Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execCTD (int n, int c, int r, int f){
 // Reset Counter
  if (c == 0){
    if(PLCstate == RUNNING){
      C[Networks[n].Cells[r][c].Data] = Networks[n].Cells[r+1][c].Data;    
      Cd[Networks[n].Cells[r][c].Data] = 0;
      Cr[Networks[n].Cells[r][c].Data] = 0;
    }
  }
  else{
    if (NetworkFlags[c-1] & FlagsMask[r+1]){
      C[Networks[n].Cells[r][c].Data] = Networks[n].Cells[r+1][c].Data;    
      Cd[Networks[n].Cells[r][c].Data] = 0;
      Cr[Networks[n].Cells[r][c].Data] = 0;
    }    
  }
 // Counter is activated in this Scan, change count
  if(f && !Cr[Networks[n].Cells[r][c].Data] && !Cd[Networks[n].Cells[r][c].Data]){
    Cr[Networks[n].Cells[r][c].Data] = 1;
    C[Networks[n].Cells[r][c].Data]--;    
  }
  // Reset Counter edge detection
  if(!f){
    Cr[Networks[n].Cells[r][c].Data] = 0;
  }
 // Counter Done 
  if (C[Networks[n].Cells[r][c].Data] == 0){
    Cd[Networks[n].Cells[r][c].Data] = 1;
  }
 // Copy Counter Flags to Dynamic flags on Network
  if(Cd[Networks[n].Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];}
  if(Cr[Networks[n].Cells[r][c].Data] && f){NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];}
}

void execMOVE (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, n, GetDataValue (r, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execSUB (int n, int c, int r, int f){
  if(f){
    int16_t auxValue1 = GetDataValue(r, c, n);
    int16_t auxValue2 = GetDataValue(r+1, c, n);

    if(auxValue1 > auxValue2){
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
    }  
    else if (auxValue1 == auxValue2){
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+1];
    }
    else{
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+2];
    }
    SetDataValue(r+2, c, n, auxValue1 - auxValue2);
  }
}

void execADD (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, n, GetDataValue (r, c, n) + GetDataValue(r+1, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execMUL (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, n, GetDataValue(r, c, n) * GetDataValue(r+1, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execDIV (int n, int c, int r, int f){
  if(f){
    if(GetDataValue (r+1, c, n) == 0){
      SetDataValue(r+2, c, n, 0);
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r+2];
    }  
    else{  
      SetDataValue(r+2, c, n, GetDataValue (r, c, n) / GetDataValue (r+1, c, n));
      NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
    }  
  }
}

void execMOD (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, n, GetDataValue(r, c, n) % GetDataValue(r+1, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execSHL (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, n, GetDataValue (r, c, n) << 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execSHR (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, n, GetDataValue (r, c, n) >> 1);
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execROL (int n, int c, int r, int f){
  if(f){
    uint16_t auxCarryBit, auxValue;
    
    auxValue = GetDataValue (r, c, n);
    auxCarryBit = auxValue & 0x8000;
    auxValue = auxValue << 1;
    if (auxCarryBit){auxValue = auxValue | 0x0001;}
    SetDataValue(r+1, c, n, auxValue);
    
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execROR (int n, int c, int r, int f){
  if(f){
    uint16_t auxCarryBit, auxValue;
    
    auxValue = GetDataValue (r, c, n);
    auxCarryBit = auxValue & 0x0001;
    auxValue = auxValue >> 1;
    if (auxCarryBit){auxValue = auxValue | 0x8000;}
    SetDataValue(r+1, c, n, auxValue);
    
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execAND (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, n, GetDataValue(r, c, n) & GetDataValue(r+1, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execOR (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, n, GetDataValue(r, c, n) | GetDataValue(r+1, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execXOR (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+2, c, n, GetDataValue(r, c, n) ^ GetDataValue(r+1, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

void execNOT (int n, int c, int r, int f){
  if(f){
    SetDataValue(r+1, c, n, ~GetDataValue(r, c, n));
    NetworkFlags[c] = NetworkFlags[c] | FlagsMask[r];
  }  
}

//--------------------------------------------------------------------------------
// GET and SET Memory Values
//--------------------------------------------------------------------------------

int GetPreviousValue (int r, int c, int NetworkNumber){
  int returnData = 0;
  switch (Networks[NetworkNumber].Cells[r][c].Type) {
    case TypeM:
      returnData = int(Mh[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeQ:
      returnData = int(Qh[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeI:
      returnData = int(Ih[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeCd:
      returnData = int(Cdh[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeCr:
      returnData = int(Crh[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeTd:
      returnData = int(Tdh[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeTr:
      returnData = int(Trh[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    default:
      ;
    break;
  }
  return returnData;
}
int GetDataValue (int r, int c, int NetworkNumber){
  int returnData = 0;
  switch (Networks[NetworkNumber].Cells[r][c].Type) {
    case TypeM:
      returnData = int(M[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeQ:
      returnData = int(Q[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeI:
      returnData = int(I[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeCd:
      returnData = int(Cd[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeCr:
      returnData = int(Cr[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeTd:
      returnData = int(Td[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeTr:
      returnData = int(Tr[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeIW:
      returnData = int(IW[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeQW:
      returnData = int(QW[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeC:
      returnData = int(C[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeD:
      returnData = int(D[Networks[NetworkNumber].Cells[r][c].Data]);
      break;
    case TypeT:
      returnData = int(Timers[Networks[NetworkNumber].Cells[r][c].Data].ACC);
      break;
    case TypeK:
      returnData = int(Networks[NetworkNumber].Cells[r][c].Data);
      break;
//    case TypeR:
//      returnData = R[Networks[NetworkNumber].Cells[r][c].Data];
//      break;
    default:
      ;
      break;
  }
  return returnData;
}

void SetDataValue(int r, int c, int NetworkNumber, int Value){
  switch (Networks[NetworkNumber].Cells[r][c].Type) {
    case TypeM:
      M[Networks[NetworkNumber].Cells[r][c].Data] = byte(Value);
      break;
    case TypeQ:
      Q[Networks[NetworkNumber].Cells[r][c].Data] = byte(Value);
      break;
    case TypeI:
      I[Networks[NetworkNumber].Cells[r][c].Data] = byte(Value);
      break;
    case TypeCd:
      Cd[Networks[NetworkNumber].Cells[r][c].Data] = byte(Value);
      break;
    case TypeCr:
      Cr[Networks[NetworkNumber].Cells[r][c].Data] = byte(Value);
      break;
    case TypeTd:
      Td[Networks[NetworkNumber].Cells[r][c].Data] = byte(Value);
      break;
    case TypeTr:
      Tr[Networks[NetworkNumber].Cells[r][c].Data] = byte(Value);
      break;
    case TypeIW:
      IW[Networks[NetworkNumber].Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeQW:
      QW[Networks[NetworkNumber].Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeC:
      C[Networks[NetworkNumber].Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeD:
      D[Networks[NetworkNumber].Cells[r][c].Data] = uint16_t(Value);
      break;
    case TypeT:
      Timers[Networks[NetworkNumber].Cells[r][c].Data].ACC = uint16_t(Value);
      break;
//    case TypeR:
//      R[Networks[NetworkNumber].Cells[r][c].Data] = Value;
//      break;
    default:
      Serial.println("SetDataValue ERROR in SwitchCase index");
      break;
  }
}

