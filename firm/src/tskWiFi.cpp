#include <globals.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>

//--------------------------------------------------------------------------------
// WiFi Task 
// Setup WiFi network service
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskWiFi(void *pvParameters)
{
  (void) pvParameters;

  while(1){
    Serial.println("TskWiFi running");
    delay(5000);
  }
}
