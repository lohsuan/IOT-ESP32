/* -----------------------------------------------------------------
//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// -----------------------------------------------------------------
//  加分題：
//  - 實驗作業的 LED 接線中的 GND 可以換成 5V 嗎？ Ans: 可以。
//  - 如果可以，電路和程式又應該如何修改？
//   Ans：
//   電路更動：
//      1. 將 "LED 接地端" 改接到 "電源 5V"
//      2. 此時高低電位相反 -> 電流和原本方向相反 -> LED 正負極要反過來接，
//         讓電流維持從 LED 正極 流向 LED 負級
//   程式更動：
//      原本的程式因接地，電流是從 "pin端(高電位)" 流向 "LED接地端(低電位)"
//      現在 LED 接到 5V (高電位) -> pin 腳屬於低電位 -> 電流相反
//      -> pin 腳是低電位時電流通過，LED 發亮
//      -> 所以需把程式中的 HIGH, LOW 對調
// ----------------------------------------------------------------- */

const int redLedPin = 46;
const int greenLedPin = 9;
const int yellowLedPin = 10;
const int SECOND = 1000;
const int YELLOW_BLINK_INTERVAL = 0.1 * SECOND;
int yellowLedState = HIGH;  // default is HIGH voltage (turn off here)

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  // set all LED to off
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(yellowLedPin, HIGH);
}

void loop() {
  // red light for 5s
  digitalWrite(redLedPin, LOW);  // turn on (voltage level LOW)
  delay(5 * SECOND);
  digitalWrite(redLedPin, HIGH);  // turn off (voltage level HIGH)

  // green light for 5s
  digitalWrite(greenLedPin, LOW);
  delay(5 * SECOND);
  digitalWrite(greenLedPin, HIGH);

  // yellow blink with interval 0.1s
  for (int i = 0; i < 2 * SECOND; i += YELLOW_BLINK_INTERVAL) {
    if (yellowLedState == HIGH) {
      yellowLedState = LOW;
    } else {
      yellowLedState = HIGH;  // the last step (1900) go here then exit
    }
    digitalWrite(yellowLedPin, yellowLedState);
    delay(0.1 * SECOND);
  }
}
