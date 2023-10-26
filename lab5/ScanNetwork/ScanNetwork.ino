#include "WiFi.h" 

void setup() { 
  Serial.begin(115200); // Set WiFi to station mode and disconnect from an AP if it was previously connected 
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect();   // Turn off your wifi connection
  delay(100); 
  Serial.println("Setup done"); 
} 


void loop() { 
  Serial.println("scan start"); 
  int n = WiFi.scanNetworks(); // return the number of networks found 
  Serial.println("scan done"); 
  if (n == 0) { Serial.println("no networks found"); } 
  else { 
    Serial.print(n); 
    Serial.println(" networks found"); 
    for (int i = 0; i < n; ++i) { // Print SSID and RSSI
      Serial.print(i + 1); 
      Serial.print(": "); 
      Serial.print(WiFi.SSID(i)); 
      Serial.print(" ("); 
      Serial.print(WiFi.RSSI(i)); 
      Serial.print("), "); 
      if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN) Serial.println("*");
      else Serial.println(WiFi.encryptionType(i)); 
      delay(10); 
    } 
  } 
  Serial.println(""); // Wait a bit before scanning again delay(5000); 
}
