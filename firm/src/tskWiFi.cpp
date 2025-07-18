// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <plsi.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <ModbusIP.h>
#include <disk.h>
#include <tskWiFi.h>
#include <wifi_plsi.h>

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
    // Modbus TCP Server & client management
    //--------------------------------------------------

    if ((settings.comm.modbusTCPserver.enabled != modbusTCPserverPreviousStatus) && WiFi.isConnected()){
      if (settings.comm.modbusTCPserver.enabled){
        modbusTCPConfigure();
      }
      else{
        modbusTCPUnconfigure();
      }
      modbusTCPserverPreviousStatus = settings.comm.modbusTCPserver.enabled;
    }

    if (WiFi.isConnected() && settings.comm.modbusTCPserver.enabled){
      modbusTCPManager();
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

