// DHT11 溫度與溼度感測器應用
#include <SimpleDHT.h>

int pinDHT11 = 9;
SimpleDHT11 dht11(pinDHT11);

void setup() { Serial.begin(9600); }

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  // start working...
  Serial.println("=================================");
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) !=
      SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
    return;
  }
  Serial.print("Humidity = ");
  Serial.print((int)humidity);
  Serial.print("%, ");
  Serial.print("Temperature = ");
  Serial.print((int)temperature);
  Serial.println("C");
  delay(3000);  // 暫停3秒
}
