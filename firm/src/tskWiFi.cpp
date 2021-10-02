/*
Copyright (c) 2019 Prieto Lucas. All rights reserved.
This file is part of the PLsi project.

PLsi is free software and hardware: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
PLsi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <globals.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <ModbusIP.h> //elpercha
#include <tskWiFi.h>
#include <wifi_plsi.h>
#include <disk.h>

// Callback function for client connect. Returns true to allow connection.
// elpercha
// bool cbConn(IPAddress ip) {
//   Serial.print("Se Conecto el cliente: ");
//   Serial.println(ip);
//   return true;
// }
// bool cbDisconn(IPAddress ip) {
//   Serial.println(ip);
//   Serial.println("Se Desconecto el cliente: ");
//   return true;
// }

//--------------------------------------------------------------------------------
// WiFi Task 
// Setup WiFi network service
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskWiFi(void *pvParameters)
{
  (void) pvParameters;

  //----------------------------------------------------
  // Task lock / unlock
  // Delay needed to Wait Program load from Ffat
  //   before to try to connect to Network (?)
  //----------------------------------------------------

  wifiWaitSettings();
  delay(2000);

  //----------------------------------------------------
  // Force first evaluation for communications
  //----------------------------------------------------

  uint16_t WiFiPreviousStatus = !settings.wifi.enabled;
  uint16_t modbusTCPserverPreviousStatus = !settings.comm.modbusTCPserver.enabled; 
  
  //--------------------------------------------------
  // Web server for OTA updates. Two pages:
  //    serverIndex - For *.bin file selection and Update
  //--------------------------------------------------

  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });

  //--------------------------------------------------
  // Web server for OTA updates
  // handling uploading firmware file
  //--------------------------------------------------

  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
  }, []() {
    
    HTTPUpload& upload = server.upload();
    
    if (!configFirmwareEnabled){
      Update.abort();
    }
    else{
      firmwareUpdateSize = Update.size();
      firmwareUpdateProgress = Update.progress();

      if (upload.status == UPLOAD_FILE_START) {
        if(upload.filename == ""){
          firmwareUpdateStatus = "No File Selected";
          firmwareUpdateFilename = "Restarting PLsi...";
          delay(3000);
          ESP.restart();
        }
        else{
          disableCore0WDT();

          // Start with max available size
          if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { 
            firmwareUpdateStatus = "Error: " + String(Update.errorString());
            firmwareUpdateFilename = "Restarting PLsi...";
            delay(3000);
            ESP.restart();
          }
        }
      } 
      else if (upload.status == UPLOAD_FILE_WRITE) {
        // Flashing firmware to ESP
        firmwareUpdateStatus = "Writing PLC Firmware...";
        firmwareUpdateFilename = upload.filename;

        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          firmwareUpdateStatus = "Error: " + String(Update.errorString());
          firmwareUpdateFilename = "Restarting PLsi...";
          delay(3000);
          ESP.restart();
        }
      } 
      else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { // True to set the size to the current progress
          firmwareUpdateStatus = "Update OK - Restarting...";
          settings.general.firmware = FIRMWARE_UPDATED;
          saveSettings();
          delay(3000);
          ESP.restart();
        }
        else {
          Update.printError(Serial);
          firmwareUpdateStatus = Update.errorString();
        }
      }
    }
  });

  //--------------------------------------------------
  // Task Main Loop
  //--------------------------------------------------

  while(1){

    //--------------------------------------------------
    // Connect or Disconnect to WiFi network
    //--------------------------------------------------

    if (settings.wifi.enabled != WiFiPreviousStatus){
      if (settings.wifi.enabled){
        WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE); // required to set hostname properly
        WiFi.setHostname(WIFI_HOSTNAME);
        WiFi.begin(settings.wifi.ssid, settings.wifi.password);
        WiFi.setSleep(false);
      }
      else{
        WiFi.disconnect();
      }
      WiFiPreviousStatus = settings.wifi.enabled;
    }

    //--------------------------------------------------
    // Modbus TCP Server control
    //--------------------------------------------------
    // elpercha

    if ((settings.comm.modbusTCPserver.enabled != modbusTCPserverPreviousStatus) && WiFi.isConnected()){
      if (settings.comm.modbusTCPserver.enabled){

        mb.server();
        // mb.onConnect(cbConn);         // Add callback on connection event
        // mb.onDisconnect(cbDisconn);   // Add callback on connection event
  
        mb.addIsts(0, 0, 10);
        mb.addIreg(0, 0, 10);
        mb.addHreg(0, 0, 100);
        mb.addCoil(0, 0, 100);

        Serial.print("Tsk WiFi - Modbus TCP server Started");
      }
      else{
        //mb. close?
        // mb.connect(ip, 502);

        // mb.readHreg()

        //mb.

        Serial.print("Tsk WiFi - Modbus TCP server Closed");
      }
      modbusTCPserverPreviousStatus = settings.comm.modbusTCPserver.enabled;
    }

    if (WiFi.isConnected() && settings.comm.modbusTCPserver.enabled){
    
      mb.task(); //elpercha debug

      mb.Ists(0, I[0]);
      mb.Ists(1, I[1]);
      mb.Ists(2, I[2]);
      mb.Ists(3, I[3]);
      mb.Ists(4, I[4]);
      mb.Ists(5, I[5]);
      mb.Ists(6, I[6]);
      mb.Ists(7, I[7]);
      mb.Ireg(0, IW[0]);
      mb.Ireg(1, IW[1]);
      mb.Ireg(2, IW[2]);
      mb.Ireg(3, IW[3]);
      mb.Ireg(4, IW[4]);
      mb.Ireg(5, IW[5]);
      mb.Ireg(6, IW[6]);
      mb.Ireg(7, IW[7]);
    } 

    if (I[4]){
      unsigned long StartTime = micros();
      mb.Hreg(10,D[500]);
      mb.Hreg(11,D[501]);
      mb.Hreg(12,D[502]);
      mb.Hreg(13,D[503]);
      mb.Hreg(14,D[504]);
      mb.Hreg(15,D[505]);
      mb.Hreg(16,D[506]);
      mb.Hreg(17,D[507]);
      unsigned long CurrentTime = micros();

      Serial.print("   - Time taken to Perform Local Modbus register WRITE Operation: ");
      Serial.println(CurrentTime - StartTime);
    }

    //--------------------------------------------------
    // Firmware update (OTA)
    //--------------------------------------------------

     // Enable Firmware Update Sequence
     if (configFirmwareSequence == 0 && configFirmwareEnabled == 1 && WiFi.isConnected() && settings.ladder.PLCstate == STOPPED){ 
      configFirmwareSequence = 1;
      server.begin();
      Serial.println("TskWiFi - Firmware Update - Server enabled");
    }
    
    // Enable Web access to user
    if (configFirmwareSequence == 1){ 
      server.handleClient();           
    }

    // Firmware Update Ended by User
    if (configFirmwareEnabled == 0 && configFirmwareMemory == 1){ 
      configFirmwareSequence = 0;
      enableCore0WDT();             // It is disabled during OTA
      Serial.println("TskWiFi - Firmware Update Ended - Watchdog Core 0 Enabled");
      
      // Status for HMI
      firmwareUpdateStatus = "Update not started";
      firmwareUpdateFilename = "No file selected";
      firmwareUpdateSize = 0;
      firmwareUpdateProgress = 0;

      configFirmwareMemory = 0;
    }

    // Firmware Update Enabled - Reset Memory
    if (configFirmwareEnabled){ 
      configFirmwareMemory = 1;
    }

    delay(1);
  }
}

