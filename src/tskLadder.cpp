// RTOS Ladder processing Task Running on Code 1
//#include <Arduino.h>
#include <globals.h>
#include "EEPROM.h"
#include <tskLadder.h>

void TaskLadder(void *pvParameters)
{
  (void) pvParameters;



  Serial.println("Flash Memory initialization: Starts");

  //Settings Flash Block Init
  if (!Settings.begin(0x1000)) {
    Serial.println("Failed to initialise Settings");
    delay(1000);
    ESP.restart();
  }  
  else{
    Serial.println("Settings Flash Sector Initialised.");
  } 

  //20 Networks blocks of 0x1000 bytes are inizializated on Flash
  for(int b=0; b<NETWORKS_BLOCKS; b++){
    if (!FlashNetworks[b].begin(sizeof(Networks))) {
      Serial.print("Failed to initialise Networks Flash Sector: ");
      Serial.println(b);
      delay(1000);
      ESP.restart();
    }
    else{
      Serial.print("Networks Flash Sector Initialised: ");
      Serial.println(b);
    } 
  }
  
  Serial.println("Flash Memory initialization: Done");



  configureIO();
  clearMemory();
  firstRunSettings();

  uint16_t foo;
  Serial.print("Setting Value 0 at booting: "); // Debug Lucas
  Serial.println(Settings.get(0, foo)); // Debug Lucas

  Serial.print("Flash Networks Value 0 at booting: "); // Debug Lucas
  Serial.println(FlashNetworks[0].get(0, foo)); // Debug Lucas

  delay(2000); // Debug Lucas
  
  while(1){
    scanTime();
    
    readInputsLocal();
    readInputsRemote();

    execScanPLC();
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
// Ladder Logic Scanning ----------------------------------------------------------
// --------------------------------------------------------------------------------
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
    FlashNetworks[b].get(0, Networks);
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

// --------------------------------------------------------------------------------
// Copy values to history for RE and FE instructions ------------------------------
// --------------------------------------------------------------------------------
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

// --------------------------------------------------------------------------------
// Calculate Scan Time in us ------------------------------------------------------
// --------------------------------------------------------------------------------
void scanTime(void){
  unsigned long    ScanTimeMicros = micros();
  ActualScanTime = ScanTimeMicros - StartTime;
  StartTime      = ScanTimeMicros;  
}

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

/******************************************************/
/*** BARS Management **********************************/
/******************************************************/
void execBars (int n, int c){
  for (int i=0; i<NET_ROWS-1; i++){
    NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & Networks[n].Bars[c]) << 1);
    NetworkFlags[c] = NetworkFlags[c] | ((NetworkFlags[c] & (Networks[n].Bars[c] << 1)) >> 1);
  }
}

/******************************************************/
/*** GET and SET Memory Values ************************/
/******************************************************/

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



void firstRunSettings (void){
  uint16_t firstRun = 1;
  Settings.get(0, firstRun);

  if (firstRun == 65535){
    Serial.println ("This is the first Run of your PLC. Default Values are going to be loaded...");
    clearProgram();
    clearSettings();
    DebugCreateNetworks(); // LUCAS DEBUG LOGIC. TO BE DELETED
  }  
  else{
    Serial.println ("This is not the first Run of your PLC. Your user program will be loaded...");
  }
}

// Set all Settings to Default
void clearSettings (void){
  uint16_t clearSettings = 123;
  //for (int i = 0; i < 204; i++){clearSettings[i] = 0;}
  Settings.put(0, clearSettings);
  Settings.commit();
  //Settings.end();
  Serial.println("First Run Setting cleared.");
}

// Deletes all Networks (all values to 0)    
void clearProgram (void){
  // Creates a empty block of Networks that fits in Flash block size
  for (int b=0; b<NETWORKS_BLOCKS; b++){
    for (int i=0; i<NETWORKS_x_BLOCK; i++){
      Networks[i].Bars[0] = 0;
      Networks[i].Bars[1] = 0;
      Networks[i].Bars[2] = 0;  
      Networks[i].Bars[3] = 0;  
      Networks[i].Bars[4] = 0;  
      for (int c=0 ; c<NET_COLUMNS; c++){
        for (int r=0 ; r<NET_ROWS; r++){
          Networks[i].Cells[r][c].Code = 0;
          Networks[i].Cells[r][c].Data = 0;
          Networks[i].Cells[r][c].Type = 0;
        }
      }
    }
    // Copy the empty block to every Flash Block
    FlashNetworks[b].put(0, Networks);
    FlashNetworks[b].commit();
    //FlashNetworks[b].end();
    Serial.print("User Program block ");
    Serial.print(b);
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



void DebugCreateNetworks(void){
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

  FlashNetworks[0].put(0, Networks);
  FlashNetworks[0].commit();
  //FlashNetworks[0].end();
  Serial.println("Testing program loaded...");
}





    
    
