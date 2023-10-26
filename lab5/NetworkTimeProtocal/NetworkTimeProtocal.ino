#include <WiFi.h>
#include "time.h"

// set your wifi’s ssid and password const char* ssid = "YOUR_SSID";
const char* ssid = "hsuan";
const char* password = "yuhsuanya";

// the address of the  NTP Server 
const char* ntpServer = "time.stdtime.gov.tw";
const long gmtOffset_sec = 8*60*60; // Adjust the offset for your timezone 
const int daylightOffset_sec = 0; // Change the Daylight offset (in seconds)

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup() {
  Serial.begin(115200);
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}
void loop() {
  delay(1000);
  printLocalTime();
}
