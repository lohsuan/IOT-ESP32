//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// 通過LCD顯示目前環境的溫度與目前的時間，並且需要顯示溫度的單位
// Button 設計(兩個按鍵)：
// - 一個按鍵表示設定狀態，
//   按下第一次表示設定小時，按下第二次表示設定分鐘，按下第三次表示結束設定
// - 第二個按鍵用來增加時間的設定值

#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>
#include <Wire.h>

// 設定 DHT11
#define DHT11_PIN 9
SimpleDHT11 dht11(DHT11_PIN);

// 設定 LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define I2C_SDA 17
#define I2C_SCL 18

// 設定 兩個按鈕
#define SWITCH_MODE_BUTTON 12
#define ADD_TIME_BUTTON 13

int settingMode = 0;  // 0 表示顯示時間，1 表示設定小時，2 表示設定分鐘

int hours = 0;
int minutes = 0;
int seconds = 0;
unsigned long lastSecondChange = 0;

byte temperature = 0;
byte humidity = 0;

// function prototype
String formatTime(int timeValue);
void showTime();
void showTemperature();

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();

  pinMode(SWITCH_MODE_BUTTON, INPUT);
  pinMode(ADD_TIME_BUTTON, INPUT);
}

void loop() {
  // 讀取按鈕狀態
  int switchModeButtonState = digitalRead(SWITCH_MODE_BUTTON);
  int addTimeButtonState = digitalRead(ADD_TIME_BUTTON);

  unsigned long currentMillis = millis();

  // 切換模式 0: 顯示時間 1: 設定小時 2: 設定分
  if (switchModeButtonState == HIGH) {
    settingMode = (settingMode + 1) % 3;
    Serial.print("switchModeButtonState: ");
    Serial.println(settingMode);
    delay(500);  // 防止按鈕彈跳
  }

  if (settingMode == 0) {  // 顯示時間
    unsigned long currentTime = millis();
    if (currentTime - lastSecondChange >= 1000) {  // 自動增加秒數
      seconds += 1;
      if (seconds == 60) {
        seconds %= 60;
        minutes = (minutes + 1);
        if (minutes > 59) {
          minutes %= 60;
          hours = (hours + 1) % 24;
        }
      }
      lastSecondChange = currentTime;
    }
  } else if (settingMode == 1) {  // 設定小時
    if (addTimeButtonState == HIGH) {
      Serial.print("hours: ");
      Serial.println(hours);
      hours = (hours + 1) % 24;
      delay(500);
    }
  } else if (settingMode == 2) {  // 設定分鐘
    if (addTimeButtonState == HIGH) {
      minutes = (minutes + 1) % 60;
      delay(500);
    }
  }
  showTime();
  showTemperature();
}

// 顯示時間
void showTime() {
  // format: Time: HH：MM：SS
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(formatTime(hours));
  lcd.print(":");
  lcd.print(formatTime(minutes));
  lcd.print(":");
  lcd.print(formatTime(seconds));
}

// 顯示溫度
void showTemperature() {
  dht11.read(DHT11_PIN, &temperature, &humidity, NULL);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print((int)temperature);
  lcd.write(B11011111);
  lcd.print("C");
}

// 確保時間數字為兩位數
String formatTime(int timeValue) {
  if (timeValue < 10) {
    return "0" + String(timeValue);
  } else {
    return String(timeValue);
  }
}