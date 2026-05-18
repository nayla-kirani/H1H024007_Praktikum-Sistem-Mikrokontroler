#include <Arduino.h> 
 
// Ini variabel volatile agar dapat diubah dalam ISR 
volatile bool ledState = false; 
 
// ISR: dijalankan saat tombol ditekan (FALLING edge) 
void tombolInterrupt() { 
  ledState = !ledState;   // Toggle status LED 
} 
 
void setup() { 
  // Bagian ini konfigurasi pin 13 sebagai output (LED) 
  pinMode(13, OUTPUT); 
 
  // kalau ini konfigurasi pin 2 sebagai input dengan pull-up internal 
  pinMode(2, INPUT_PULLUP); 
 
  // ISR pada pin 2, dipicu FALLING (tombol ditekan) 
  attachInterrupt( 
    digitalPinToInterrupt(2), 
    tombolInterrupt, 
    FALLING 
  ); 
} 
 
void loop() { 
  digitalWrite(13, ledState); 
}
