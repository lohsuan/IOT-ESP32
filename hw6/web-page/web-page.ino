/* -----------------------------------------------------------------
//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// -----------------------------------------------------------------*/

#include <SimpleDHT.h>
#include <WiFi.h>

int pinDHT11 = 45;
SimpleDHT11 dht11(pinDHT11);

const char* ssid = "ESP32-Access-Point-yuhsuan";  // REPLACE_WITH_YOUR_SSID
const char* password = "123456789";               // REPLACE_WITH_YOUR_PASSWORD

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output45State = "off";

// Static IP address
IPAddress local_IP(192, 168, 4, 11);
IPAddress gateway(192, 168, 50, 1);
IPAddress subnet(255, 255, 255, 0);
// IPAddress primaryDNS(8, 8, 8, 8); //optional
// PAddress secondaryDNS(8, 8, 4, 4); //optional

void setup() {
  Serial.begin(115200);

  // set ESP32 as AP mode
  WiFi.mode(WIFI_AP);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAPConfig(local_IP, local_IP, subnet);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

unsigned long lastSecondChange = 0;

byte temperature = 0;
byte humidity = 0;

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSecondChange >= 3 * 1000) {
    int err = SimpleDHTErrSuccess;
    Serial.println("=================================");
    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) !=
        SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err=");
      Serial.println(err);
      delay(1000);
      return;
    }
    lastSecondChange = currentTime;
  }

  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {                     // If a new client connects,
    Serial.println("New Client.");  // print a message out in the serial port
    String currentLine =
        "";  // make a String to hold incoming data from the client
    while (client.connected()) {  // loop while the client's connected
      if (client.available()) {   // if there's bytes to read from the client,
        char c = client.read();   // read a byte, then
        Serial.write(c);          // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a
          // row. that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200
            // OK) and a content-type so the client knows what's coming, then a
            // blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /45/on") >= 0) {
              Serial.println("GPIO 45 on");
              output45State = "on";
              //   digitalWrite(output45, HIGH);
            } else if (header.indexOf("GET /45/off") >= 0) {
              Serial.println("GPIO 45 off");
              output45State = "off";
              //   digitalWrite(output45, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println(
                "<head><meta name=\"viewport\" content=\"width=device-width, "
                "initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println(
                "<style>html { font-family: Helvetica; display: inline-block; "
                "margin: 0px auto; text-align: center;}");
            client.println(
                ".button { background-color: #4CAF50; border: none; color: "
                "white; padding: 16px 40px;");
            client.println(
                "text-decoration: none; font-size: 30px; margin: 2px; cursor: "
                "pointer;}");
            client.println(
                ".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            if (output45State == "off") {
              client.println(String("<p>Temperature: ") + (int)temperature +
                             String(" C</p>"));
              client.println(
                  "<p><a href=\"/45/on\"><button "
                  "class=\"button\">switch</button></a></p>");

            } else {
              client.println(String("<p>Temperature: ") +
                             ((int)temperature * 9 / 5 + 32) +
                             String(" F</p>"));
              client.println(
                  "<p><a href=\"/45/off\"><button "
                  "class=\"button\">switch</button></a></p>");
            }

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage
                                 // return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}