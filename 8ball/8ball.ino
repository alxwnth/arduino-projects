#include <LiquidCrystal.h>

#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 3
#define BTN_RIGHT 4
#define BTN_SELECT 5
#define BTN_NONE 10

const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;
int backlightPower = 150;
int button = 0;

LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);

int detectButton() {
  int keyAnalog = analogRead(A0);
  if (keyAnalog < 100) {
    return BTN_RIGHT;
  } else if (keyAnalog < 200) {
    return BTN_UP;
  } else if (keyAnalog < 400) {
    return BTN_DOWN;
  } else if (keyAnalog < 600) {
    return BTN_LEFT;
  } else if (keyAnalog < 800) {
    return BTN_SELECT;
  } else {
    return BTN_NONE;
  }
}

int rollTheDice() {
  boolean bit1;
  boolean bit2;
  byte dice = B00000000;
  boolean diceResult;
  for (int i = 0; i < 8; i++) {
    bit1 = bitRead((byte)analogRead(1), 0);
    delayMicroseconds(512);
    bit2 = bitRead((byte)analogRead(2), 0);
    if (bit1 != bit2) {
      bitWrite(dice, i, bit1);
    } else {
      i--;
    }
  }
    
  if ((int)dice > 0 && (int)dice <= 90) {
    return 0;
  } else if ((int)dice > 90 && (int)dice <= 180) {
    return 1;
  } else {
    return 2;
  }
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Ask ur question");
  lcd.setCursor(0, 1);
  lcd.print("and press SELECT");
  Serial.begin(9600);
}

void loop() {
  button = detectButton();
  if (button == BTN_SELECT) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("The answer is");
    byte res = rollTheDice();
    if (res == 0) {
      lcd.setCursor(7, 1);
      lcd.print("NO");
    } else if (res == 1) {
      lcd.setCursor(6, 1);
      lcd.print("YES");
    } else {
      lcd.setCursor(6, 1);
      lcd.print("IDK");
    }
  }
}