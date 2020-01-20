#include <globals.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WebServer.h>

void TaskWiFi(void *pvParameters)
{
  (void) pvParameters;

  while(1){
    Serial.println("TskWiFi running");
    delay(5000);
  }
}
