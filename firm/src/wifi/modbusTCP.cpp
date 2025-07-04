// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <plsi.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <ModbusIP.h>
#include <disk.h>
#include <wifi_plsi.h>

//--------------------------------------------------------------------------------
// Modbus TCP Callbacks
// Callback function for client connect. Returns true to allow connection.
//--------------------------------------------------------------------------------

// elpercha - on testing functions
bool cbConn(IPAddress ip) {
  Serial.print("client connected with address: ");
  Serial.println(ip);
  return true;
}
// bool cbDisconn(IPAddress ip) {
//   Serial.println(ip);
//   Serial.println("Se Desconecto el cliente: ");
//   return true;
// }

//--------------------------------------------------------------------------------
// Modbus TCP Enable and Configure
//--------------------------------------------------------------------------------

void modbusTCPConfigure (void){
    Serial.println("TaskWiFi - ModbusManager");
    printAvailableMemory();

    modbusTCP.server(); // only when enabled

    printAvailableMemory();

    modbusTCP.client(); // only when enabled

    modbusTCP.onConnect(cbConn);         // Add callback on connection event
    // mb.onDisconnect(cbDisconn);   // Add callback on connection event

    printAvailableMemory();
    modbusTCP.addIsts(0, 0, 200);
    printAvailableMemory();
    modbusTCP.addIreg(0, 0, 50);
    printAvailableMemory();
    modbusTCP.addHreg(0, 0, 200);
    printAvailableMemory();
    modbusTCP.addCoil(0, 0, 200);
    printAvailableMemory();

    Serial.print("Tsk WiFi - Modbus TCP server Started");
}

//--------------------------------------------------------------------------------
// Modbus TCP Disable
//--------------------------------------------------------------------------------

void modbusTCPUnconfigure(void){
  //modbusTCP. close?


  Serial.print("Tsk WiFi - Modbus TCP server Closed");
}

//--------------------------------------------------------------------------------
// Modbus TCP State Machine
//--------------------------------------------------------------------------------

void modbusTCPManager (void){
    modbusTCP.task(); //elpercha debug

    modbusTCP.Ists(0, I[0]);
    modbusTCP.Ists(1, I[1]);
    modbusTCP.Ists(2, I[2]);
    modbusTCP.Ists(3, I[3]);
    modbusTCP.Ists(4, I[4]);
    modbusTCP.Ists(5, I[5]);
    modbusTCP.Ists(6, I[6]);
    modbusTCP.Ists(7, I[7]);
    modbusTCP.Ireg(0, IW[0]);
    modbusTCP.Ireg(1, IW[1]);
    modbusTCP.Ireg(2, IW[2]);
    modbusTCP.Ireg(3, IW[3]);
    modbusTCP.Ireg(4, IW[4]);
    modbusTCP.Ireg(5, IW[5]);
    modbusTCP.Ireg(6, IW[6]);
    modbusTCP.Ireg(7, IW[7]);


    if (I[7] && 0){

      if (modbusTCP.isConnected(remote)) {   // Check if connection to Modbus Slave is established
        // modbusTCP.readHreg(remote, REG, &res);  // Initiate Read Coil from Modbus Slave
        Serial.print("Slave was already Connected ++++++++++++++++");
      } else {
        Serial.print(" Connecting to Slave ....");
        // modbusTCP.connect(remote);           // Try to connect if no connection
        bool slaveConnectionOK = modbusTCP.connect(remote, 502);
        
        if (slaveConnectionOK){
          Serial.print("Slave connected OK ++++++++++++++++");
        }
        else{
          Serial.print(" Slave Not connected -----------------");
        }
      }
     delay(4000);

    }

    if (I[6] && 0){
    // type == COIL;
    // type == ISTS;
    // type == IREG;
    // type == HREG;

      uint16_t value[100];
      // mb.readHreg(remote, 0, value, 8);
      
      
      unsigned long StartTime = micros();

      uint16_t trans = modbusTCP.readIreg(remote, 0, value, 99);

      while(modbusTCP.isTransaction(trans)) {  // Check if transaction is active
        modbusTCP.task();
        delay(10);
      }

      unsigned long CurrentTime = micros();

      Serial.print("   - Time taken to Perform XXX Operation: ");
      Serial.println(CurrentTime - StartTime);

      D[500] = value[0];
      D[501] = value[1];
      D[502] = value[2];
      D[503] = value[3];
      D[504] = value[48];
      D[505] = value[49];
      D[506] = value[98];
      D[507] = value[99];


      Serial.print("    ----- Value 0: ");
      Serial.println(value[0]);
      Serial.print("    ----- Value 1: ");
      Serial.println(value[1]);
      Serial.print("    ----- Value 2: ");
      Serial.println(value[2]);
      Serial.print("    ----- Value 3: ");
      Serial.println(value[3]);
      Serial.print("    ----- Value 4: ");
      Serial.println(value[4]);
      Serial.print("    ----- Value 5: ");
      Serial.println(value[5]);
      Serial.print("    ----- Value 6: ");
      Serial.println(value[6]);
      Serial.print("    ----- Value 7: ");
      Serial.println(value[7]);

      delay(3000);
    }


    // if (I[4]){
    //   unsigned long StartTime = micros();
    //   mb.Hreg(10,D[500]);
    //   mb.Hreg(11,D[501]);
    //   mb.Hreg(12,D[502]);
    //   mb.Hreg(13,D[503]);
    //   mb.Hreg(14,D[504]);
    //   mb.Hreg(15,D[505]);
    //   mb.Hreg(16,D[506]);
    //   mb.Hreg(17,D[507]);
    //   unsigned long CurrentTime = micros();

    //   Serial.print("   - Time taken to Perform Local Modbus register WRITE Operation: ");
    //   Serial.println(CurrentTime - StartTime);
    // }


}
