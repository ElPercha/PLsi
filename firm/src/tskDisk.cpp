#include <globals.h>
#include <tskDisk.h>
#include "FS.h"
#include "SD.h"
#include "SPIFFS.h"

//--------------------------------------------------------------------------------
// Disk Task 
// Controls SPIFSS memory and SD Card files
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskDisk(void *pvParameters)
{
  (void) pvParameters;

  loadSettings();
  loadUserProgram();

  while(1){

    Network NetworksTesting[10];

    if (I[4] && false){
      Serial.println  ("TskDisk - Input 4 activated");
      loadSettings();
      delay(2000);
    }
    if (I[5] && false){
        Serial.print("Info SPIFFS Total Bytes: ");
        Serial.println(SPIFFS.totalBytes());
        Serial.print("Info SPIFFS Used Bytes: ");
        Serial.println(SPIFFS.usedBytes());

        Serial.print("Info SD Total Bytes: ");
        Serial.println(uint32_t(SD.totalBytes()/1000));
        Serial.print("Info SD Used Bytes: ");
        Serial.println(uint32_t(SD.usedBytes()/1000));
        Serial.print("Card Size: ");
        Serial.println(uint32_t(SD.cardSize()/1000));
        Serial.print("Card Type: ");
        Serial.println(SD.cardType());
        
      delay(2000);
    }
    if (I[6] && false){
            
      unsigned long StartTime = micros();
      File f = SPIFFS.open("/f.txt", "w");

      if (!SD.begin (SD_CS)){
        Serial.println("Card not present");
//      if (SD.cardType() == CARD_NONE){
      }
      else{
        Serial.println("Card is present. File created");
  
        File fSD = SD.open("/f.txt", "w");
        
        unsigned long CurrentTime = micros();
        Serial.print("Time taken to open file to write: ");
        Serial.println(CurrentTime - StartTime);

        if (!f || !fSD) {
            Serial.println("SD file open failed");
        }
        else{
          NetworksTesting[0]   = onlineNetwork;
          NetworksTesting[1]   = onlineNetwork;
          NetworksTesting[2]   = onlineNetwork;
          NetworksTesting[3]   = onlineNetwork;
          NetworksTesting[4]   = onlineNetwork;
          NetworksTesting[5]   = onlineNetwork;
          NetworksTesting[6]   = onlineNetwork;
          NetworksTesting[7]   = onlineNetwork;
          NetworksTesting[8]   = onlineNetwork;
          NetworksTesting[9]   = onlineNetwork;

          StartTime = micros();
          f.write((uint8_t *)&NetworksTesting, sizeof(NetworksTesting));
          fSD.write((uint8_t *)&NetworksTesting, sizeof(NetworksTesting));
          fSD.seek(1024);
          Serial.print("Position in File: ");
          Serial.println(fSD.position());
          
          
          
          
          
          typedef struct
          {
            uint16_t value1;
            uint16_t value2;
          } testdata;
          
          testdata testdata1;

          testdata1.value1 = 0xFEDC;
          testdata1.value2 = 0xBA98;

          fSD.write((uint8_t *)&testdata1, sizeof(testdata1));

          Serial.print("Value of testdata value 1: ");
          Serial.println(testdata1.value1);
          Serial.print("Value of testdata value 2: ");
          Serial.println(testdata1.value2);
          Serial.print("size of testdata1: ");
          Serial.println(uint16_t(sizeof(testdata1)));


          CurrentTime = micros();
          Serial.print("Time taken to Write the file: ");
          Serial.println(CurrentTime - StartTime);
          
          Serial.print("File Size: ");
          Serial.println(f.size());
          
          StartTime = micros();
          f.close();
          fSD.close();
          CurrentTime = micros();
          Serial.print("Time taken to Close the file: ");
          Serial.println(CurrentTime - StartTime);

          Serial.println(onlineNetwork.Cells[0][0].Code);
          Serial.println(onlineNetwork.Cells[0][0].Data);
          Serial.println(onlineNetwork.Cells[0][0].Type);
          Serial.println(onlineNetwork.Cells[3][3].Code);
          Serial.println(onlineNetwork.Cells[3][3].Data);
          Serial.println(onlineNetwork.Cells[3][3].Type);
          
          SD.end();
        }
      }

      delay(2000);
    }

    
    if (I[7] && false){
      unsigned long StartTime = micros();
      File myFile = SPIFFS.open("/f.txt", "r");
      unsigned long CurrentTime = micros();
      Serial.print("Time taken to Open File for read: ");
      Serial.println(CurrentTime - StartTime);

  

      if (!myFile) {
        Serial.println("file open failed while reading");
      }
      else{
        StartTime = micros();
        myFile.read((uint8_t *)&NetworksTesting, sizeof(NetworksTesting));
        CurrentTime = micros();
        Serial.print("Time taken to read 500 Networks : ");
        Serial.println(CurrentTime - StartTime);

        Serial.print("File size in bytes: ");
        Serial.println(myFile.size());
        
        
        StartTime = micros();
        myFile.close();
        CurrentTime = micros();
        Serial.print("Time taken to Close the file: ");
        Serial.println(CurrentTime - StartTime);
        
        
        Serial.print("Size of all Data: ");
        Serial.println(long(sizeof(NetworksTesting)));  //wtf

        Serial.println("First Network");
        Serial.println(NetworksTesting[0].Cells[0][0].Code);
        Serial.println(NetworksTesting[0].Cells[0][0].Data);
        Serial.println(NetworksTesting[0].Cells[0][0].Type);
        Serial.println(NetworksTesting[0].Cells[3][3].Code);
        Serial.println(NetworksTesting[0].Cells[3][3].Data);
        Serial.println(NetworksTesting[0].Cells[3][3].Type); 

      //   Serial.println("Network 99");
      //   Serial.println(NetworksTesting[99].Cells[0][0].Code);
      //   Serial.println(NetworksTesting[99].Cells[0][0].Data);
      //   Serial.println(NetworksTesting[99].Cells[0][0].Type);
      //   Serial.println(NetworksTesting[99].Cells[3][3].Code);
      //   Serial.println(NetworksTesting[99].Cells[3][3].Data);
      //   Serial.println(NetworksTesting[99].Cells[3][3].Type); 

      //  Serial.println("Network 199");
      //  Serial.println(NetworksTesting[199].Cells[0][0].Code);
      //  Serial.println(NetworksTesting[199].Cells[0][0].Data);
      //  Serial.println(NetworksTesting[199].Cells[0][0].Type);
      //  Serial.println(NetworksTesting[199].Cells[3][3].Code);
      //  Serial.println(NetworksTesting[199].Cells[3][3].Data);
      //  Serial.println(NetworksTesting[199].Cells[3][3].Type); 

      //  Serial.println("Network 299");
      //  Serial.println(NetworksTesting[299].Cells[0][0].Code);
      //  Serial.println(NetworksTesting[299].Cells[0][0].Data);
      //  Serial.println(NetworksTesting[299].Cells[0][0].Type);
      //  Serial.println(NetworksTesting[299].Cells[3][3].Code);
      //  Serial.println(NetworksTesting[299].Cells[3][3].Data);
      //  Serial.println(NetworksTesting[299].Cells[3][3].Type); 

      //  Serial.println("Network 399");
      //  Serial.println(NetworksTesting[399].Cells[0][0].Code);
      //  Serial.println(NetworksTesting[399].Cells[0][0].Data);
      //  Serial.println(NetworksTesting[399].Cells[0][0].Type);
      //  Serial.println(NetworksTesting[399].Cells[3][3].Code);
      //  Serial.println(NetworksTesting[399].Cells[3][3].Data);
      //  Serial.println(NetworksTesting[399].Cells[3][3].Type); 

      //  Serial.println("Last Network");
      //  Serial.println(NetworksTesting[499].Cells[0][0].Code);
      //  Serial.println(NetworksTesting[499].Cells[0][0].Data);
      //  Serial.println(NetworksTesting[499].Cells[0][0].Type);
      //  Serial.println(NetworksTesting[499].Cells[3][3].Code);
      //  Serial.println(NetworksTesting[499].Cells[3][3].Data);
      //  Serial.println(NetworksTesting[499].Cells[3][3].Type); 

      //  Serial.println("Last Network");
      //  Serial.println(NetworksTesting[999].Cells[0][0].Code);
      //  Serial.println(NetworksTesting[999].Cells[0][0].Data);
      //  Serial.println(NetworksTesting[999].Cells[0][0].Type);
      //  Serial.println(NetworksTesting[999].Cells[3][3].Code);
      //  Serial.println(NetworksTesting[999].Cells[3][3].Data);
      //  Serial.println(NetworksTesting[999].Cells[3][3].Type); 
      }
      delay(2000);
    }

    Serial.println  ("TskDisk - running.");
    delay(4000);
  }
}

//--------------------------------------------------------------------------------
// Load user settings at boot.
// If first boot of PLC:
//    Format SPIFSS memory
//    Load default settings
//    Load demo program
//--------------------------------------------------------------------------------

void loadSettings (void) {

// Chequear si el archivo "Settings.PLsi" existe
// si no existe se formatea la memoria y se crea con los defaults
// Tambien se carga demo program y se crea en memoria

// Si en cambio "Settings.PLsi" existe cuando se entra en esta funcion se carga en la estructura "settings" y nada mas

//  SPIFFS.format();
  if (!SPIFFS.begin()){
    Serial.println("TskDisk - Mount SPIFFS failed. Will retry with FormatOnFail = true ...");
    unsigned long StartTime = micros();
    SPIFFS.begin(true);
    unsigned long CurrentTime = micros();
    Serial.println("TskDisk - Disk formatted because regular mount failed.");
    Serial.print  ("TskDisk - Time taken to Format 1Mb: ");
    Serial.println(CurrentTime - StartTime);
    bootSequence = 1;
  }
  else{
    Serial.println("TskDisk - SPIFFS Disk successfully mounted");
    bootSequence = 1;
  }
}

//--------------------------------------------------------------------------------
// Load user program at boot.
// If first boot of PLC:
//    Create an empty program using MAX_NETWORKS quantity
//    load testing program
//    Copy program to RAM
//--------------------------------------------------------------------------------

void loadUserProgram (void) {
  delay(1000);
  bootSequence = 1000;
}


