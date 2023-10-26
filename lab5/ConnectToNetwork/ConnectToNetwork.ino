#include <WiFi.h>
char ssid[] = ""; //SSID of your network
char pass[] = ""; //password of your WPA Network

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // if you are connected, print out info about the connection:
  Serial.println();
  Serial.print("ip = "); //print the local IP address
  Serial.println(WiFi.localIP());
  Serial.print("WiFi RSSI:");
  Serial.println(WiFi.RSSI());
}

void loop () {
}
