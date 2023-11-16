
#include <HTTPClient.h>
#include <SimpleDHT.h>
#include <WiFi.h>

char ssid[] = "";
char password[] = "";
String url = "http://api.thingspeak.com/update?api_key=API_KEY";
int pinDHT11 = 17;

SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  Serial.print("使用核心編號：");
  Serial.println(xPortGetCoreID());
  // 嘗試讀取溫濕度內容
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) !=
      SimpleDHTErrSuccess) {
    Serial.print("溫度計讀取失敗，錯誤碼=");
    Serial.println(err);
    delay(1000);
    return;
  }
  // 讀取成功，將溫濕度顯示在序列視窗
  Serial.print("溫度計讀取成功: ");
  Serial.print((int)temperature);
  Serial.print(" *C, ");
  Serial.print((int)humidity);
  Serial.println(" H");
  // 開始傳送到thingspeak
  Serial.println("啟動網頁連線");
  HTTPClient http;
  // 將溫度及濕度以http get參數方式補入網址後方
  String url1 =
      url + "&field1=" + (int)temperature + "&field2=" + (int)humidity;
  // http client取得網頁內容
  http.begin(url1);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();  // 讀取網頁內容到 payload
    Serial.print("網頁內容=");          // 顯示網頁內容
    Serial.println(payload);
  } else {
    Serial.println("網路傳送失敗");
  }
  http.end();
  delay(20000);  // 休息20秒```
}