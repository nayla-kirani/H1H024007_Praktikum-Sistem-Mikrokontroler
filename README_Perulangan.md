## Percobaan 2A: Perulangan

---

#### 1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan! 

* LED 1 → Pin 2 Arduino
* LED 2 → Pin 3 Arduino
* LED 3 → Pin 4 Arduino
* LED 4 → Pin 5 Arduino
* LED 5 → Pin 6 Arduino
* Setiap LED diseri dengan resistor 220Ω
* Kaki negatif LED → GND

Rangkaian ini memungkinkan setiap LED dikontrol secara individu melalui pin digital Arduino.

---

#### 2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan! 

Menggunakan perulangan:

```cpp
for (int ledPin = 2; ledPin < 8; ledPin++)
```

Penjelasan:

Dimulai dari pin kecil ke besar (2 → 7), lalu LED menyala satu per satu dan memberikan efek berjalan ke kanan

---

#### 3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri! 

Menggunakan perulangan:

```cpp
for (int ledPin = 7; ledPin >= 2; ledPin--)
```

Penjelasan:

Dimulai dari pin besar ke kecil (7 → 2), lalu LED menyala berurutan dan memberikan efek berjalan ke kiri

---

#### 4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

```cpp
int timer = 500; // delay

void setup() {
  for (int pin = 2; pin <= 7; pin++) {
    pinMode(pin, OUTPUT); // Set semua pin sebagai output
  }
}

void loop() {
  // LED kiri nyala
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);

  // LED kanan nyala
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  delay(timer);

  // semua LED mati
  for (int pin = 2; pin <= 7; pin++) {
    digitalWrite(pin, LOW);
  }

  // LED kanan nyala
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  // LED kiri mati
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  delay(timer);

  // Reset semua LED
  for (int pin = 2; pin <= 7; pin++) {
    digitalWrite(pin, LOW);
  }
}
```

---

### Penjelasan Program

* LED dibagi menjadi dua bagian:

  Kiri → pin 2, 3, 4
  Kanan → pin 5, 6, 7
* Program menyalakan kiri → mati → kanan → mati
* Menghasilkan efek **bergantian kiri dan kanan**

---
