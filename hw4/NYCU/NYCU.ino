//   系所：資科工碩一 | 學號：312551105  | 姓名：羅羽軒
// 使用 LCD 顯示 “I LOVE NYCU”，其中的 LOVE 改用愛心符號表示
// 同時需要每秒改變一次顯示的黑白對比 

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define I2C_SDA 17
#define I2C_SCL 18

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte iBitmap[8]= {
  B10001,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B10001 }; // I

byte nBitmap[8]= {
  B01110,
  B00110,
  B00110,
  B01010,
  B01010,
  B01010,
  B01100,
  B01110 }; // N

byte yBitmap[8]= {
  B01110,
  B01110,
  B10101,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011}; // Y

byte cBitmap[8]= {
  B00000,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B01111,
  B00000 }; // C

byte uBitmap[8]= {
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B00000 }; // U

byte loveBitmap[8]= {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000 }; // love

byte whiteLoveBitmap[8]= {
  B00000,
  B01010,
  B10101,
  B10101,
  B01010,
  B00100,
  B00000,
  B00000 }; // white love

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();       // initialize the lcd
  lcd.backlight();  // turn on backlight.
  lcd.createChar(0, iBitmap); // 自行造字
  lcd.createChar(1, nBitmap);
  lcd.createChar(2, yBitmap);
  lcd.createChar(3, cBitmap);
  lcd.createChar(4, uBitmap);
  lcd.createChar(5, loveBitmap);
  lcd.createChar(6, whiteLoveBitmap);
}

int contrast = 0;

void loop() {
  lcd.clear();  // Clears the LCD screen
  lcd.setCursor(0, 0);
  contrast = !contrast; // to control black or white flag
   if (contrast) {
    lcd.write(0);
    lcd.print(" ");
    lcd.write(6);
    lcd.print(" ");
    lcd.write(1);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
  }
  else {
    lcd.print("I");
    lcd.print(" ");
    lcd.write(5);
    lcd.print(" ");
    lcd.print("NYCU");
  }

  delay(1000); // 每秒改變一次顯示的黑白對比
}
