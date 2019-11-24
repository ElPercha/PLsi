// RTOS Web Server Task Running on Code 0
#include <globals.h>
#include <tskDisk.h>
#include "FS.h"
#include "SD.h"
#include "SPIFFS.h"


void TaskDisk(void *pvParameters)
{
  (void) pvParameters;

  Network NetworksTesting[10];

  SPIFFS.begin();


  while(1){


    if (I[4]){
      unsigned long StartTime = micros();
      SPIFFS.format();
      unsigned long CurrentTime = micros();
      Serial.print  ("Time taken to Format 1Mb: ");
      Serial.println(CurrentTime - StartTime);
      delay(2000);
    }
    if (I[5]){
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
    if (I[6]){
            
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

    
    if (I[7]){
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


    delay(10);
  }
}


  