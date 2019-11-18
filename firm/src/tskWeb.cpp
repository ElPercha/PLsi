// RTOS Web Server Task Running on Code 0
#include <globals.h>
#include <tskWeb.h>


void TaskWeb(void *pvParameters)
{
  (void) pvParameters;

  // Setup
  //Network NetworksTesting[100];



 // SPIFFS.begin();
 
  while(1){


    // if (I[4]){
    //   unsigned long StartTime = micros();
    //   SPIFFS.format();
    //   unsigned long CurrentTime = micros();
    //   Serial.print  ("Time taken to Format 1Mb: ");
    //   Serial.println(CurrentTime - StartTime);
    //   delay(2000);
    // }
    // if (I[5]){
    //     Serial.print("Info SPIFFS Total Bytes: ");
    //     Serial.println(SPIFFS.totalBytes());
    //     Serial.print("Info SPIFFS Used Bytes: ");
    //     Serial.println(SPIFFS.usedBytes());
    //   delay(2000);
    // }
    // if (I[6]){
    //   unsigned long StartTime = micros();
    //   File f = SPIFFS.open("/f.txt", "w");
    //   unsigned long CurrentTime = micros();
    //   Serial.print("Time taken to open file to write: ");
    //   Serial.println(CurrentTime - StartTime);

    //   if (!f) {
    //       Serial.println("file open failed");
    //   }
    //   else{
    //     NetworksTesting[0]   = onlineNetwork;
    //     NetworksTesting[99]  = onlineNetwork;
    //     // NetworksTesting[199] = onlineNetwork;
    //     // NetworksTesting[299] = onlineNetwork;
    //     // NetworksTesting[399] = onlineNetwork;
    //     // NetworksTesting[499] = onlineNetwork;

    //     StartTime = micros();
    //     f.write((uint8_t *)&NetworksTesting, sizeof(NetworksTesting));
    //     CurrentTime = micros();
    //     Serial.print("Time taken to Write the file: ");
    //     Serial.println(CurrentTime - StartTime);
        
    //     Serial.print("File Size: ");
    //     Serial.println(f.size());
        
    //     StartTime = micros();
    //     f.close();
    //     CurrentTime = micros();
    //     Serial.print("Time taken to Close the file: ");
    //     Serial.println(CurrentTime - StartTime);

    //     Serial.println(onlineNetwork.Cells[0][0].Code);
    //     Serial.println(onlineNetwork.Cells[0][0].Data);
    //     Serial.println(onlineNetwork.Cells[0][0].Type);
    //     Serial.println(onlineNetwork.Cells[3][3].Code);
    //     Serial.println(onlineNetwork.Cells[3][3].Data);
    //     Serial.println(onlineNetwork.Cells[3][3].Type);
    //   }
    //   delay(2000);
    // }

    
    // if (I[7]){
    //   unsigned long StartTime = micros();
    //   File myFile = SPIFFS.open("/f.txt", "r");
    //   unsigned long CurrentTime = micros();
    //   Serial.print("Time taken to Open File for read: ");
    //   Serial.println(CurrentTime - StartTime);

    //   if (!myFile) {
    //     Serial.println("file open failed while reading");
    //   }
    //   else{
    //     StartTime = micros();
    //     myFile.read((uint8_t *)&NetworksTesting, sizeof(NetworksTesting));
    //     CurrentTime = micros();
    //     Serial.print("Time taken to read 500 Networks : ");
    //     Serial.println(CurrentTime - StartTime);

    //     Serial.print("File size in bytes: ");
    //     Serial.println(myFile.size());
        
        
    //     StartTime = micros();
    //     myFile.close();
    //     CurrentTime = micros();
    //     Serial.print("Time taken to Close the file: ");
    //     Serial.println(CurrentTime - StartTime);
        
        
    //     Serial.print("Size of all Data: ");
    //     Serial.println(long(sizeof(NetworksTesting)));  //wtf

    //     Serial.println("First Network");
    //     Serial.println(NetworksTesting[0].Cells[0][0].Code);
    //     Serial.println(NetworksTesting[0].Cells[0][0].Data);
    //     Serial.println(NetworksTesting[0].Cells[0][0].Type);
    //     Serial.println(NetworksTesting[0].Cells[3][3].Code);
    //     Serial.println(NetworksTesting[0].Cells[3][3].Data);
    //     Serial.println(NetworksTesting[0].Cells[3][3].Type); 

    //     Serial.println("Network 99");
    //     Serial.println(NetworksTesting[99].Cells[0][0].Code);
    //     Serial.println(NetworksTesting[99].Cells[0][0].Data);
    //     Serial.println(NetworksTesting[99].Cells[0][0].Type);
    //     Serial.println(NetworksTesting[99].Cells[3][3].Code);
    //     Serial.println(NetworksTesting[99].Cells[3][3].Data);
    //     Serial.println(NetworksTesting[99].Cells[3][3].Type); 

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
    //   }
    //   delay(2000);
    // }


    delay(10);
  }
}


  