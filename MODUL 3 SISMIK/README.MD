B 3.6.3 Pertanyaan Praktikum

### 1. Proses Input Keyboard → LED

Proses kerja sistem:

1. User mengetik data pada keyboard melalui **Serial Monitor**
2. Data dikirim ke Arduino melalui komunikasi **UART (Serial)**
3. Arduino membaca data menggunakan `Serial.read()`
4. Data dicek:

   * `'1'` → LED menyala
   * `'0'` → LED mati
5. Arduino mengontrol LED dengan:

   ```cpp
   digitalWrite(LED_PIN, HIGH/LOW);
   ```
6. LED berubah sesuai input



### 2. Fungsi `Serial.available()`

Digunakan untuk memastikan data tersedia sebelum dibaca:

```cpp
if (Serial.available() > 0)
```

#### Jika tidak digunakan:

* Arduino tetap membaca meskipun tidak ada data
* Bisa menyebabkan:

  * Data tidak valid
  * Error logika
  * Program tidak stabil



### 3. Program LED Blink (Input '2')

##  Kode Program

```cpp
const int ledPin = 13;
char data;
bool blinkMode = false;
unsigned long prevTime = 0;
const int interval = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {
    data = Serial.read();

    if (data == '1') {
      digitalWrite(ledPin, HIGH);
      blinkMode = false;
    }
    else if (data == '0') {
      digitalWrite(ledPin, LOW);
      blinkMode = false;
    }
    else if (data == '2') {
      blinkMode = true;
    }
  }

  if (blinkMode) {
    unsigned long currentTime = millis();

    if (currentTime - prevTime >= interval) {
      prevTime = currentTime;
      digitalWrite(ledPin, !digitalRead(ledPin));
    }
  }
}


##  Penjelasan Program

### Variabel

* `ledPin` → pin LED
* `data` → menyimpan input serial
* `blinkMode` → status mode kedip
* `prevTime` → waktu sebelumnya
* `interval` → jeda kedip

### Setup

* `pinMode()` → set LED sebagai output
* `Serial.begin()` → mulai komunikasi serial

### Loop

* `Serial.available()` → cek data masuk
* `Serial.read()` → baca data

### Kondisi

* `'1'` → LED ON
* `'0'` → LED OFF
* `'2'` → aktifkan blink

### Blink

Menggunakan `millis()` agar tidak menghambat program (non-blocking)

---

### 4. Perbandingan `delay()` vs `millis()`

#### `delay()`

**Kelebihan:**

* Mudah digunakan

**Kekurangan:**

* Menghentikan program sementara
* Tidak bisa membaca input lain

#### `millis()`

**Kelebihan:**

* Non-blocking
* Bisa multitasking

**Kesimpulan:**
Gunakan `millis()` untuk sistem interaktif

---

##  3.6.4 Pertanyaan Praktikum

### 1. Cara Kerja I2C (Arduino ↔ LCD)

* Menggunakan 2 jalur:

  * SDA (data)
  * SCL (clock)

#### Alur:

1. Arduino sebagai master
2. LCD sebagai slave
3. Arduino mengirim alamat (contoh: `0x27`)
4. LCD merespon jika alamat cocok
5. Data ditampilkan di LCD

---

### 2. Potensiometer

#### Susunan normal:

* Kiri → GND
* Tengah → Output (ke Arduino)
* Kanan → VCC

#### Jika kiri & kanan tertukar:

* Tidak merusak komponen
* Arah putaran terbalik

---

### 3. Program UART + I2C

##  Kode Program

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int potPin = A0;
int adcValue = 0;
float voltage = 0;
int percent = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  adcValue = analogRead(potPin);

  voltage = adcValue * (5.0 / 1023.0);
  percent = map(adcValue, 0, 1023, 0, 100);

  Serial.print("ADC: ");
  Serial.println(adcValue);

  Serial.print("Volt: ");
  Serial.println(voltage);

  Serial.print("Persen: ");
  Serial.print(percent);
  Serial.println("%");

  lcd.setCursor(0, 0);
  lcd.print("ADC:");
  lcd.print(adcValue);

  lcd.setCursor(0, 1);
  lcd.print(percent);
  lcd.print("% ");

  int bar = map(percent, 0, 100, 0, 16);
  for (int i = 0; i < bar; i++) {
    lcd.print("|");
  }

  delay(500);
}
```

---

##  Penjelasan Program

### Library

* `Wire` → komunikasi I2C
* `LiquidCrystal_I2C` → kontrol LCD

### Variabel

* `adcValue` → nilai analog
* `voltage` → nilai tegangan
* `percent` → persen

### Output

#### Serial Monitor:

* ADC
* Volt
* Persen

#### LCD:

* Baris 1 → ADC
* Baris 2 → Persen + bar indikator

---

### 4. Tabel Hasil

| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 5%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |

---

##  3.7 Pertanyaan Praktikum

### 1. UART vs I2C

#### UART

**Kelebihan:**

* Sederhana
* Tidak butuh alamat

**Kekurangan:**

* Hanya komunikasi 2 perangkat

#### I2C

**Kelebihan:**

* Bisa banyak perangkat
* Hemat pin

**Kekurangan:**

* Perlu alamat
* Lebih kompleks

---

### 2. Alamat I2C

Contoh:

* `0x27`
* `0x20`

#### Fungsi:

Sebagai identitas perangkat

#### Jika salah:

* LCD tidak merespon

---

### 3. Sistem UART + I2C

#### Alur:

1. Input dari Serial Monitor (UART)
2. Arduino memproses data
3. Output ke:

   * Serial Monitor
   * LCD (I2C)

#### Pengelolaan:

* UART → `Serial`
* I2C → `Wire`
* Semua dijalankan dalam `loop()`

