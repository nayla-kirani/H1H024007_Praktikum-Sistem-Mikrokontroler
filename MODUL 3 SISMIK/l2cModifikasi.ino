#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);

  lcd_1.begin(16, 2);
  lcd_1.setBacklight(1);
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
  Serial.print(volt, 2);
  Serial.print(" V | Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // ===== LCD BARIS 1 (disederhanakan biar muat) =====
  lcd_1.setCursor(0, 0);
  lcd_1.print(nilai);

  lcd_1.print(" ");
  lcd_1.print(volt, 1);  // biar ga kepanjangan

  lcd_1.print(" ");      // spasi

  lcd_1.print(persen);
  lcd_1.print("% ");

  // ===== LCD BARIS 2 =====
  lcd_1.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < bar) {
      lcd_1.print((char)255);
    } else {
      lcd_1.print(" ");
    }
  }

  delay(200);
}