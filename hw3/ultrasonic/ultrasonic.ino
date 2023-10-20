//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// (1)超過20 公分時，不亮燈。
// (2)10 ~ 20 公分時，低速閃爍LED 。 
// (3)低於10 公分時，高速閃爍LED 。

const int trigPin = 2;
const int echoPin = 11;
const int redLedPin = 46;

const int SECOND = 1000;
const int HIGH_BLINK_INTERVAL = 0.1 * SECOND;
const int LOW_BLINK_INTERVAL = 1 * SECOND;
int redLedState = LOW;

int Duration;
int Distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
}

void ledBlinkWithIntervalAndContinueTime(int interval, int continueTime) {
  for (int i = 0; i < continueTime; i += interval) {
    if (redLedState == HIGH) {
      redLedState = LOW;
    } else {
      redLedState = HIGH;
    }
    digitalWrite(redLedPin, redLedState);
    delay(interval);
  }
}

void printDistanceInfo() {
  if (Distance < 10) {
    Serial.print("Distance < 10: ");
  } else if (Distance < 20) {
    Serial.print("Distance between 10 ~ 20: ");
  } else {
    Serial.print("Distance > 20: ");
  }
  Serial.println(Distance);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // 發射超音波
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Duration = pulseIn(echoPin, HIGH);  // 超音波發射到接收的時間
  Distance = Duration * 0.034 / 2;    // 計算距離 (cm)
  delay(50);  // delay 50ms => 避免和第二個波重疊
  printDistanceInfo();

  if (Distance < 10) {
    // blink with interval 0.1s for 3 seconds
    ledBlinkWithIntervalAndContinueTime(HIGH_BLINK_INTERVAL, 3);
  } else if (Distance < 20) {
    // blink with interval 1s for 3 seconds
    ledBlinkWithIntervalAndContinueTime(LOW_BLINK_INTERVAL, 3);
  } else {
    // turn off led
    if (redLedState != LOW) {
      redLedState = LOW;
      digitalWrite(redLedPin, redLedState);
    }
  }
}
