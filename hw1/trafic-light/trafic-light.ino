/* -----------------------------------------------------------------
//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// -----------------------------------------------------------------
//  紅綠燈實驗要求：
//  - 依底下的時間設定要求，讓紅綠燈的三種燈依序並且反覆發光
//  - 設定紅燈5秒，綠燈5秒，黃燈2秒，其中黃燈閃爍速率為每0.1秒交替發光與熄滅
// ----------------------------------------------------------------- */

const int redLedPin = 46;
const int greenLedPin = 9;
const int yellowLedPin = 10;
const int SECOND = 1000;
const int YELLOW_BLINK_INTERVAL = 0.1 * SECOND;
int yellowLedState = LOW;  // default is LOW voltage (turn off here)

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
}

void loop() {
  // red light for 5s
  digitalWrite(redLedPin, HIGH);  // turn on (voltage level HIGH)
  delay(5 * SECOND);              // wait 5s
  digitalWrite(redLedPin, LOW);   // turn off (voltage level LOW)

  // green light for 5s
  digitalWrite(greenLedPin, HIGH);
  delay(5 * SECOND);
  digitalWrite(greenLedPin, LOW);

  // yellow blink with interval 0.1s
  for (int i = 0; i < 2 * SECOND; i += YELLOW_BLINK_INTERVAL) {
    if (yellowLedState == HIGH) {  // the last step (1900) go here then exit
      yellowLedState = LOW;        // set to off
    } else {
      yellowLedState = HIGH;
    }
    digitalWrite(yellowLedPin, yellowLedState);
    delay(0.1 * SECOND);
  }
}
