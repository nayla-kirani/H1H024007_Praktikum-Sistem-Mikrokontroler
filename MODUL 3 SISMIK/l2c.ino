// C++ code
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

const int pinPot = A0;

void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.setBacklight(1);
}

void loop()
{
  int nilai = analogRead(pinPot);

  // Mapping ke bar (0–16)
  int panjangBar = map(nilai, 0, 1023, 0, 16);

  // Baris 1: nilai ADC
  lcd_1.setCursor(0, 0);
  lcd_1.print("ADC: ");
  lcd_1.print(nilai);
  lcd_1.print("    "); // clear sisa

  // Baris 2: bar
  lcd_1.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd_1.print((char)255);
    } else {
      lcd_1.print(" ");
    }
  }

  delay(200);
}