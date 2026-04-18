#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);

  float volt = nilai * (5.0 / 1023.0);
  int persen = map(nilai, 0, 1023, 0, 100);
  int bar = map(nilai, 0, 1023, 0, 16);

  // ===== SERIAL =====
  Serial.print("ADC: ");
  Serial.print(nilai);
  Serial.print(" | Volt: ");
  Serial.print(volt);
  Serial.print(" V | Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // ===== LCD BARIS 1 =====
  lcd.setCursor(0, 0);
  lcd.print("ADC:");
  lcd.print(nilai);
  lcd.print(" ");
  lcd.print("V:");
  lcd.print(volt);
  lcd.print(" ");
  lcd.print(persen);
  lcd.print("%");

  // ===== LCD BARIS 2 =====
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < bar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(500);
}