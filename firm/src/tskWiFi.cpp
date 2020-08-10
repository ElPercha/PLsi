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
  //----------------------------------------------------

  wifiWaitSettings();

  //--------------------------------------------------
  // Connect to WiFi network
  //--------------------------------------------------

  WiFi.begin(settings.wifi.ssid, settings.wifi.password);

  //--------------------------------------------------
  // Wait for connection
  //--------------------------------------------------

  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.println("TaskWiFi - Network not connected - Retrying in 3 seconds...");
    Serial.print("TaskWiFi - Trying to connect to: ");
    Serial.println(settings.wifi.ssid);
    Serial.print("TaskWiFi - Trying with Password: ");
    Serial.println(settings.wifi.password);
  }
  Serial.print("Connected to ");
  Serial.println(settings.wifi.ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

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
  // Starts Web server
  //--------------------------------------------------
  
  server.begin();

  //--------------------------------------------------
  // Task Main Loop
  //--------------------------------------------------

  while(1){

    //--------------------------------------------------
    // Web server for OTA updates
    // loop call
    // Enable WDT (it is disabled during OTA)
    //--------------------------------------------------

    if (I[0]){ // Manually enable the firmware update page
      server.handleClient();
      enableCore0WDT();
    }
    delay(1);
  }
}
