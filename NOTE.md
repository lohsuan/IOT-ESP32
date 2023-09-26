# NOTE

## Lab 1 note

### delay  的缺點

- 在 delay() 期間，不能讀取感測器、不能做數學運算、不能處理 pin 腳信號，也就是說它會讓大部分的動作都停擺。
- 在  delay()  期間，CPU 還是可以做某些事情，例如：序列埠的 RX pin 腳進來的資料會被紀錄下來。

### Blink without Delay

https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay

| Turns on and off a light emitting diode (LED) connected to a digital pin, without using the `delay()` function.
| This means that other code can run at the same time without being interrupted by the LED code.

The code below uses the `millis()` function, a command that returns the number of milliseconds since the board started running its current sketch, to blink an LED.

```cpp
const int ledPin = LED_BUILTIN;
int ledState = LOW;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 1000;  // interval at which to blink (milliseconds)

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
  }
}

```
