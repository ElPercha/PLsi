// RTOS Web Server Task Running on Code 0
#include <globals.h>
#include <tskWeb.h>

void TaskWeb(void *pvParameters)
{
  (void) pvParameters;

  // Setup

  Network NetworksTesting[100];
  
  //pwm1.begin();
  //pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency

  // uint16_t Val1;
  // uint16_t Val2;

  SPIFFS.begin();
 
  while(1){
  // Main Loop

//  delay(1000);
//  Serial.println(ActualScanTime);

    // Val1 += 10;
    // if(Val1 > 4095){Val1=0;}   
    // Val2 = 4096 - Val1;

    // pwm1.setPWM(0, Val1, Val2);
    // pwm1.setPWM(15, Val2, Val1);

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
      delay(2000);
    }
    if (I[6]){
      unsigned long StartTime = micros();
      File f = SPIFFS.open("/f.txt", "w");
      unsigned long CurrentTime = micros();
      Serial.print("Time taken to open file to write: ");
      Serial.println(CurrentTime - StartTime);

      if (!f) {
          Serial.println("file open failed");
      }
      else{
        NetworksTesting[0]   = OnlineNetwork;
        NetworksTesting[99]  = OnlineNetwork;
//        NetworksTesting[199] = OnlineNetwork;
//        NetworksTesting[299] = OnlineNetwork;
//        NetworksTesting[399] = OnlineNetwork;
//        NetworksTesting[499] = OnlineNetwork;

        StartTime = micros();
        f.write((uint8_t *)&NetworksTesting, sizeof(NetworksTesting));
        CurrentTime = micros();
        Serial.print("Time taken to Write the file: ");
        Serial.println(CurrentTime - StartTime);
        
        Serial.print("File Size: ");
        Serial.println(f.size());
        
        StartTime = micros();
        f.close();
        CurrentTime = micros();
        Serial.print("Time taken to Close the file: ");
        Serial.println(CurrentTime - StartTime);

        Serial.println(OnlineNetwork.Cells[0][0].Code);
        Serial.println(OnlineNetwork.Cells[0][0].Data);
        Serial.println(OnlineNetwork.Cells[0][0].Type);
        Serial.println(OnlineNetwork.Cells[3][3].Code);
        Serial.println(OnlineNetwork.Cells[3][3].Data);
        Serial.println(OnlineNetwork.Cells[3][3].Type);
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

        Serial.println("Network 99");
        Serial.println(NetworksTesting[99].Cells[0][0].Code);
        Serial.println(NetworksTesting[99].Cells[0][0].Data);
        Serial.println(NetworksTesting[99].Cells[0][0].Type);
        Serial.println(NetworksTesting[99].Cells[3][3].Code);
        Serial.println(NetworksTesting[99].Cells[3][3].Data);
        Serial.println(NetworksTesting[99].Cells[3][3].Type); 

//        Serial.println("Network 199");
//        Serial.println(NetworksTesting[199].Cells[0][0].Code);
//        Serial.println(NetworksTesting[199].Cells[0][0].Data);
//        Serial.println(NetworksTesting[199].Cells[0][0].Type);
//        Serial.println(NetworksTesting[199].Cells[3][3].Code);
//        Serial.println(NetworksTesting[199].Cells[3][3].Data);
//        Serial.println(NetworksTesting[199].Cells[3][3].Type); 
//
//        Serial.println("Network 299");
//        Serial.println(NetworksTesting[299].Cells[0][0].Code);
//        Serial.println(NetworksTesting[299].Cells[0][0].Data);
//        Serial.println(NetworksTesting[299].Cells[0][0].Type);
//        Serial.println(NetworksTesting[299].Cells[3][3].Code);
//        Serial.println(NetworksTesting[299].Cells[3][3].Data);
//        Serial.println(NetworksTesting[299].Cells[3][3].Type); 
//
//        Serial.println("Network 399");
//        Serial.println(NetworksTesting[399].Cells[0][0].Code);
//        Serial.println(NetworksTesting[399].Cells[0][0].Data);
//        Serial.println(NetworksTesting[399].Cells[0][0].Type);
//        Serial.println(NetworksTesting[399].Cells[3][3].Code);
//        Serial.println(NetworksTesting[399].Cells[3][3].Data);
//        Serial.println(NetworksTesting[399].Cells[3][3].Type); 
//
//        Serial.println("Last Network");
//        Serial.println(NetworksTesting[499].Cells[0][0].Code);
//        Serial.println(NetworksTesting[499].Cells[0][0].Data);
//        Serial.println(NetworksTesting[499].Cells[0][0].Type);
//        Serial.println(NetworksTesting[499].Cells[3][3].Code);
//        Serial.println(NetworksTesting[499].Cells[3][3].Data);
//        Serial.println(NetworksTesting[499].Cells[3][3].Type); 
      }
      delay(2000);
    }


    delay(10);
  }
}


  