
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <Wire.h>

#include "time.h"

// set your wifi’s ssid and password const char* ssid = "YOUR_SSID";
const char* ssid = "";
const char* password = "";

// the address of the  NTP Server
const char* ntpServer = "time.stdtime.gov.tw";
long gmtOffset_sec = 0;      // Adjust the offset for your timezone
const int daylightOffset_sec = 0;  // Change the Daylight offset (in seconds)
int hourOffset = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define I2C_SDA 17
#define I2C_SCL 18
#define SWITCH_MODE_BUTTON 12

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void connectToWifi() {
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  time_t rawtime;
  time(&rawtime);
  localtime_r(&rawtime, &timeinfo);
  int hour = timeinfo.tm_hour;
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void printLocalTimeToLCD() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  time_t rawtime;
  time(&rawtime);
  localtime_r(&rawtime, &timeinfo);
  int hour = timeinfo.tm_hour;
  lcd.setCursor(0, 0);
  lcd.print(hour + hourOffset);
  lcd.print(&timeinfo, ":%M:%S");
  lcd.print(" GMT+");
  lcd.print(hourOffset);
}

void setup() {
  Serial.begin(115200);
  // connect to LCD
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.noBacklight();

  // connect to WiFi
  connectToWifi();
  configTime(gmtOffset_sec, daylightOffset_sec,
             ntpServer);  // init and get the time
  printLocalTimeToLCD();

  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

int duration;
int distance;
unsigned long lastSecondChange = 0;

void loop() {
  int switchModeButtonState = digitalRead(SWITCH_MODE_BUTTON);

  if (switchModeButtonState == HIGH) {
    hourOffset += 1;
    hourOffset = hourOffset % 24;
    delay(500);  // 防止按鈕彈跳
  }

  printLocalTimeToLCD();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);  // 發射超音波
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);  // 超音波發射到接收的時間
  distance = duration * 0.034 / 2;     // 計算距離 (cm)
  delay(50);  // delay 50ms => 避免和第二個波重疊

  if (distance < 10) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }

  unsigned long currentTime = millis();
  if (currentTime - lastSecondChange >= 15 * 1000) {
    connectToWifi();
    gmtOffset_sec = hourOffset * 60 * 60;
    configTime(gmtOffset_sec, daylightOffset_sec,
               ntpServer);  // init and get the time
    printLocalTimeToLCD();

    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    lastSecondChange = currentTime;
  }
}

