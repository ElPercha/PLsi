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

  wifiWaitSettings();

  //--------------------------------------------------
  // Connect to WiFi network
  //--------------------------------------------------

  char ssid1[30] = "2203Alden"; // LucasSettings
  char pass1[30] = "HolaHola"; // LucasSettings

  snprintf(settings.wifi.ssid, SSID_LENGTH, ssid1); // LucasSettings
  snprintf(settings.wifi.password, PASS_LENGTH, pass1); // LucasSettings

  // Serial.println(sizeof(settings));
  // Serial.println(settings.wifi.ssid);
  // Serial.println(settings.wifi.password);

  WiFi.begin(settings.wifi.ssid, settings.wifi.password);
  Serial.println("");

  //--------------------------------------------------
  // Wait for connection
  //--------------------------------------------------

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(settings.wifi.ssid);
  Serial.print("Password: ");
  Serial.println(settings.wifi.password);
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
