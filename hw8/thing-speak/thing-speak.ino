/* -----------------------------------------------------------------
//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// -----------------------------------------------------------------*/
/*
將 ESP32 接上光敏和溫濕度 sensor
- 光敏 sensor 的資料讀取頻率: 每20秒一次
- 溫濕度 sensor 的資料讀取頻率: 每 40秒一次

為節省存放資料量，如果目前的感測資料沒有更新（和上一筆資料相同），則不要上傳這一次的感測資料
-
不過這樣的設定會有問題，因若長時間沒有更新狀態，容易被你自己的系統誤判為這被有問題
-
如果連續10次沒有上傳資料，則第11次不論資料是否與上一筆相同，則都會上傳最新的感測資料
-------------------------------------------------------------------
加分題：
-
如果我們要使用一個channe記錄兩個以上的ESP32的感測資料，並且能夠分辨是哪塊板子上傳的資料，應該怎麼實現？
-----------------------------------------------------------------*/

#include <HTTPClient.h>
#include <SimpleDHT.h>
#include <WiFi.h>

char ssid[] = "";
char password[] = "";

#define DHT11_PIN 17
#define LIGHT_SENSOR_PIN 10

String Url = "http://api.thingspeak.com/update?api_key=API_KEY";
SimpleDHT11 dht11(DHT11_PIN);

void setup() {
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

long lastSecondChange = -1000000;

byte temperature = 0;
byte temperature_new = 0;
byte humidity = 0;
byte humidity_new = 0;
int light = 0;
int light_new = 0;
int temperature_count = 0;
int humidity_count = 0;
int light_count = 0;

void loop() {
  // Serial.print("使用核心編號：");
  // Serial.println(xPortGetCoreID());

  // reads the DHT11 input every 40s
  unsigned long currentTime = millis();
  if (currentTime - lastSecondChange >= 40 * 1000) {
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature_new, &humidity_new, NULL)) !=
        SimpleDHTErrSuccess) {
      Serial.print("溫度計讀取失敗，錯誤碼=");
      Serial.println(err);
      delay(1000);
      return;
    }
    lastSecondChange = currentTime;
  }

  // reads the LIGHT_SENSOR input on analog pin (0 ~ 4095)
  light_new = analogRead(LIGHT_SENSOR_PIN);
  String updateDataUrl =
      "http://api.thingspeak.com/update?api_key=N0LPL97NBV1HA4T8";

  if ((int)temperature != (int)temperature_new) {
    updateDataUrl = updateDataUrl + "&field1=" + (int)temperature_new;
  } else if (temperature_count == 9) {
    updateDataUrl = updateDataUrl + "&field1=" + (int)temperature_new;
    temperature_count = 0;
  } else {
    temperature_count++;
  }
  if ((int)humidity != (int)humidity_new) {
    updateDataUrl = updateDataUrl + "&field2=" + (int)humidity_new;
  } else if (humidity_count == 9) {
    updateDataUrl = updateDataUrl + "&field2=" + (int)humidity_new;
    humidity_count = 0;
  } else {
    humidity_count++;
  }
  if ((int)light != (int)light_new) {
    updateDataUrl = updateDataUrl + "&field3=" + (int)light_new;
  } else if (light_count == 9) {
    updateDataUrl = updateDataUrl + "&field3=" + (int)light_new;
    light_count = 0;
  } else {
    light_count++;
  }

  Serial.print("updateDataUrl: ");
  Serial.println(updateDataUrl);

  if (updateDataUrl != Url) {  // there is data need to be updated
    // Send data to ThingSpeak
    HTTPClient http;
    http.begin(updateDataUrl);
    int httpCode = http.GET();  // http client get method 取得網頁內容
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("網路傳送失敗");
    }
    http.end();
  } else {  // no data need to update
    Serial.println("無資料需要更新");
  }

  // record data this time
  temperature = temperature_new;
  humidity = humidity_new;
  light = light_new;

  delay(20000);  // 休息 20 秒
}