// 通過 PWM 方法實現呼吸燈

const int ledPin = 21;

void setup() {
  ledcSetup(0, 1000, 8);  // 指定channel 0的頻率為1000Hz, resolution為8 (0-255)
  ledcAttachPin(ledPin, 0);  // 指定ledPin使用channel 0
}

void loop() {
  for (int a = 10; a <= 255; a++) {
    ledcWrite(0, a);  // 設定channel 0的佔空比
    delay(10);        // 當前亮度級別維持的時間，單位毫秒
  }
  for (int a = 255; a >= 10; a--) {
    ledcWrite(0, a);
    delay(10);  // 當前亮度的維持的時間，單位毫秒
  }
  delay(500);  // 完成一個迴圈后等待的時間，單位毫秒
}
