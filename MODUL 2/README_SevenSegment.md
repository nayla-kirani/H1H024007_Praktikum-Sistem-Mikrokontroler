
# Percobaan 2A – Seven Segment 

---

## 1. Rangkaian Schematic

Rangkaian menggunakan:
- Arduino Uno
- Seven Segment 1 digit
- Resistor 220Ω
- Breadboard & kabel jumper  

**Konfigurasi pin:**

| Segmen | Pin Arduino |
|--------|------------|
| a | 7 |
| b | 6 |
| c | 5 |
| d | 11 |
| e | 10 |
| f | 8 |
| g | 9 |
| dp | 4 |

Setiap pin Arduino dihubungkan ke segmen melalui resistor.

<img width="650" height="450" alt="image" src="https://github.com/user-attachments/assets/402967ba-cf23-41e5-af82-bb296f1ef44e" />

<img width="650" height="450" alt="image" src="https://github.com/user-attachments/assets/df541bea-5f47-4859-8e71-65022b94d7cb" />

Link Tinkercad ada di sini: https://www.tinkercad.com/things/2q25b1muDNm-7-segment?sharecode=g8NBX6xbc9Rpr08CtsQk5heRI3KUAsX-ZUdGYA7hOpo

---

## 2. Apa yang terjadi jika nilai `num lebih dari 15`?

Jika nilai `num` lebih dari 15:
Program akan mengakses indeks array yang tidak tersedia, yang menyebabkan:
  - Tampilan tidak sesuai / acak
  - Segment bisa menyala tidak beraturan
  - Potensi error (out of bounds)

**Kesimpulannya:**  
Nilai `num` harus berada pada rentang **0 – 15**.

---

## 3. Jenis Seven Segment

Program ini menggunakan **Common Cathode**.

**Karena:**
- Logika `HIGH (1)` → LED menyala
- Logika `LOW (0)` → LED mati
- Kaki common terhubung ke GND

---

## 4. Program Modifikasi (F → 0)

### 🔧 Source Code

```cpp
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {1,1,1,0,1,1,1,0}, // A
  {0,0,1,1,1,1,1,0}, // b
  {1,0,0,1,1,1,0,0}, // C
  {0,1,1,1,1,0,1,0}, // d
  {1,0,0,1,1,1,1,0}, // E
  {1,0,0,0,1,1,1,0}  // F
};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {

  for (int num = 15; num >= 0; num--) {

    for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], digitPattern[num][i]);
    }

    delay(1000); // Delay 1 detik
  }
}
