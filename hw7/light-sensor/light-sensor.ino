/* -----------------------------------------------------------------
//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// -----------------------------------------------------------------
// 智慧夜燈：外面越暗、LED 越亮；外面越亮、LED 越暗
// Hint: analogWrite()
// Ref: https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
// -----------------------------------------------------------------*/

#define LIGHT_SENSOR_PIN 17
#define LED_PIN 10

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.println(analogValue);  // the raw analog reading

  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  analogWrite(LED_PIN, (4095 - analogValue) / 16);

  delay(300);
}
