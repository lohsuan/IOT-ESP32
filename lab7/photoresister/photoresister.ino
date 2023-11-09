/*
這段程式有一點小問題．我們直接使用 “<1000”作為判斷是否開關LED，
問題是，現實使用的情況下，光敏電阻的讀取值會上下浮動，
如果正好在1000附近上下浮動的話，那麼LED燈就會忽明忽滅
*/

// int ledPin = 10;
// int inputPin = 17;

// void setup() {
//   pinMode(ledPin, OUTPUT);
// }

// void loop() {
//   if(analogRead(inputPin) < 1000)
//     digitalWrite(ledPin, LOW);
//   else
//     digitalWrite(ledPin, HIGH);
// }

//////////////////////////////
// 不用使用“硬性”標準，改用“模糊”標準
//////////////////////////////

int ledPin = 10;
int inputPin = 17;
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop() {
  int analogValue = analogRead(inputPin);
  Serial.print(analogValue);

  if (analogRead(inputPin) < 2000) {
    digitalWrite(ledPin, LOW);
  } else if (analogRead(inputPin) > 2100) {
    digitalWrite(ledPin, HIGH);
  }
}

//////////////////////////////
// 使用統計次數，連續發生幾次才改變狀態
//////////////////////////////

// int ledPin = 13;
// int inputPin = 0;
// int tooDark = 0, tooBright = 0;
// void setup() {
//   pinMode(ledPin,OUTPUT);
// }
// void loop() {
//   if(analogRead(inputPin) < 1000){
//     tooBrink++;
//     tooDark = 0;
//   }
//   else {
//     tooBrink = 0;
//     tooDark++;
//   }
//    if(tooBrink >= 5) digitalWrite(ledPin, LOW);
//   else if (tooDark >= 5) digitalWrite(ledPin, HIGH);
// }
