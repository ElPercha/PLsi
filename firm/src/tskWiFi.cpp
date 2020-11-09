#include <globals.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include <wifi_plsi.h>
#include <tskWiFi.h>

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
  // Force first evaluation of WiFi Action to execute (connect or disconnect)
  //----------------------------------------------------

  uint16_t WiFiPreviousStatus = !settings.wifi.enabled;
  
  //--------------------------------------------------
  // Web server for OTA updates
  // return index page which is stored in serverIndex 
  //--------------------------------------------------

  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
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
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      disableCore0WDT();
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
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
        WiFi.begin(settings.wifi.ssid, settings.wifi.password);
      }
      else{
        WiFi.disconnect();
      }
      WiFiPreviousStatus = settings.wifi.enabled;
    }

    //--------------------------------------------------
    // Web server for OTA updates
    // loop call
    // Enable WDT (it is disabled during OTA)
    //--------------------------------------------------

    if (I[3]){ // Manually enable the firmware update page
      server.begin();        // lucas these 3 functions must be coordinated. this begin needs WIFI OK
      server.handleClient(); // This has to be enabled when user selects firmware update
      enableCore0WDT();      // This has to be reenabled when OTA finish or User unselect Firmware update
    }
 
    delay(1);
  }
}
