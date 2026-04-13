
# Percobaan 1B – Kontrol Counter dengan Push Button

---

## 1. Gambarkan rangkaian schematic yang digunakan pada percobaan!

Rangkaian terdiri dari:
- Arduino Uno
- Seven Segment
- Resistor 220Ω
- 1 Push Button 
- Breadboard & kabel jumper  

### Konfigurasi Pin Seven Segment

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

### Push Button
- Button → Pin 2
- Koneksi ke GND (menggunakan INPUT_PULLUP)

<img width="650" height="450" alt="image" src="https://github.com/user-attachments/assets/3ff106bd-759c-4014-bee5-bfc91dc4a48a" />

<img width="650" height="450" alt="image" src="https://github.com/user-attachments/assets/f4d83e7a-bfb9-419b-9bc2-e513235b5820" />

Link Tinkercad ada di sini: https://www.tinkercad.com/things/8mdW2rfbE50-kontrol-counter-dengan-push-button?sharecode=0qpuVYCPW20DIaiI8WWTz_olSK_Su673AGhC3Rc_Hpg

---

## 2. Mengapa menggunakan INPUT_PULLUP?

Mode `INPUT_PULLUP` digunakan karena:
- Arduino memiliki resistor internal (pull-up)
- Pin akan bernilai:
  - HIGH → saat tidak ditekan
  - LOW → saat ditekan

Keuntungannya: Tidak perlu resistor eksternal, rangkaian lebih sederhana, mengurangi noise (lebih stabil), menghindari kondisi floating (nilai tidak jelas)

---

## 3. Jika LED segmen tidak menyala

Jika salah satu LED pada seven segment tidak menyala, hal tersebut bisa disebabkan oleh beberapa faktor dari sisi hardware maupun software. Dari sisi hardware, kemungkinan terjadi kesalahan pada:
- pemasangan kabel jumper, seperti kabel yang longgar atau salah posisi pada pin Arduino maupun seven segment.
- resistor yang tidak terpasang dengan benar atau dalam kondisi rusak juga dapat menyebabkan arus tidak mengalir dengan baik. 
- Kerusakan pada LED segmen itu sendiri juga bisa menjadi penyebab, terutama jika salah satu segmen memang sudah tidak berfungsi.

Sementara itu, dari sisi software, kesalahan dapat terjadi pada pemetaan pin yang tidak sesuai dengan rangkaian, sehingga sinyal tidak dikirim ke segmen yang benar. Pola array yang digunakan untuk menampilkan angka juga bisa salah, sehingga ada segmen yang tidak pernah diberi logika HIGH. Selain itu, kesalahan dalam logika program, seperti penggunaan HIGH dan LOW yang terbalik (terutama jika jenis seven segment berbeda), juga dapat menyebabkan LED tidak menyala sebagaimana mestinya.

---

## 4. Modifikasi Program (2 Push Button)

### Fungsi:
Tombol 1 → Increment (+)

Tombol 2 → Decrement (-)

---

## 🔧 Source Code

```cpp
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

// Push button
const int btnUp = 2;
const int btnDown = 3;

// Variabel counter
int num = 0;

byte digitPattern[10][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}  // 9
};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(btnUp) == LOW) {
    num++;
    if (num > 9) num = 0; // reset ke 0
    delay(200); // debounce
  }

  if (digitalRead(btnDown) == LOW) {
    num--;
    if (num < 0) num = 9; // kembali ke 9
    delay(200); // debounce
  }

  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], digitPattern[num][i]);
  }
}
