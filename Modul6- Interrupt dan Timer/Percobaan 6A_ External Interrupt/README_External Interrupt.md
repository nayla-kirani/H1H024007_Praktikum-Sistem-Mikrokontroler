# Modul 6 - Percobaan 6A: External Interrupt

## Tujuan Percobaan
Percobaan ini bertujuan untuk memahami penggunaan **external interrupt** pada Arduino Uno untuk mengendalikan LED menggunakan push button tanpa metode polling secara terus-menerus.
<img width="1600" height="900" alt="WhatsApp Image 2026-05-12 at 09 55 55" src="https://github.com/user-attachments/assets/dc3cdcf9-0f57-4b34-8808-244485010e18" />
<img width="559" height="542" alt="Screenshot 2026-05-17 190840" src="https://github.com/user-attachments/assets/d0a2f344-0560-431f-ac66-8c8755daac76" />

---

# 1. Jelaskan proses bagaimana tombol dapat mengubah kondisi LED menggunakan interrupt!

Pada program ini, tombol terhubung ke pin 2 Arduino yang digunakan sebagai pin interrupt. Ketika tombol ditekan atau dilepas, Arduino akan mendeteksi perubahan sinyal pada pin tersebut sesuai mode interrupt yang digunakan.

Saat interrupt terjadi:
1. Program utama (`loop`) dihentikan sementara.
2. Arduino menjalankan fungsi ISR (*Interrupt Service Routine*) yaitu `tombolInterrupt()`.
3. Di dalam ISR, variabel `ledState` diubah menggunakan:
   ```cpp
   ledState = !ledState;
   ```
4. Setelah ISR selesai, program utama dilanjutkan kembali.
5. Nilai `ledState` kemudian digunakan untuk menyalakan atau mematikan LED melalui:
   ```cpp
   digitalWrite(13, ledState);
   ```

Dengan interrupt, Arduino tidak perlu terus-menerus mengecek tombol menggunakan polling sehingga sistem menjadi lebih cepat dan efisien.

---

# 2. Apa fungsi attachInterrupt() pada program tersebut?

Fungsi `attachInterrupt()` digunakan untuk menghubungkan pin interrupt dengan fungsi ISR yang akan dijalankan ketika kondisi tertentu terjadi.

Format umum:
```cpp
attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
```

Pada program:
```cpp
attachInterrupt(
  digitalPinToInterrupt(2),
  tombolInterrupt,
  RISING
);
```

Penjelasan:
- `digitalPinToInterrupt(2)`  
  Menentukan pin interrupt yaitu pin 2.

- `tombolInterrupt`  
  Fungsi ISR yang akan dijalankan saat interrupt terjadi.

- `RISING`  
  Mode interrupt yang digunakan.

---

# 3. Mengapa pada ISR tidak disarankan menggunakan delay() dan Serial.print()?

Karena selama ISR berjalan, proses utama Arduino akan berhenti sementara.

## a. delay()
`delay()` bersifat blocking sehingga dapat membuat sistem berhenti terlalu lama di dalam ISR dan mengganggu proses interrupt lainnya.

## b. Serial.print()
`Serial.print()` membutuhkan proses komunikasi serial yang relatif lambat dan menggunakan interrupt internal. Jika dipanggil di dalam ISR dapat menyebabkan:
- program menjadi lambat,
- data serial rusak,
- bahkan program freeze atau crash.

Karena itu ISR harus dibuat: singkat, cepat, sederhana.

---

# 4. Apa fungsi keyword volatile pada variabel ledState?

Keyword `volatile` digunakan agar compiler selalu membaca nilai terbaru dari variabel tersebut dari memori.

Pada program:
```cpp
volatile bool ledState = false;
```

Hal ini diperlukan karena variabel `ledState` dapat berubah:
- di program utama (`loop`)
- maupun di ISR (`tombolInterrupt()`)

Tanpa `volatile`, compiler dapat melakukan optimasi yang menyebabkan perubahan nilai dari ISR tidak terdeteksi dengan benar.

---

# 5. Modifikasi Program Menggunakan Mode Interrupt Lain

## A. Mode RISING

### Source Code
```cpp
#include <Arduino.h>

volatile bool ledState = false;

// ISR
void tombolInterrupt() {
  ledState = !ledState;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    RISING
  );
}

void loop() {
  digitalWrite(13, ledState);
}
```

### Penjelasan Program
`RISING` akan memicu interrupt ketika sinyal berubah dari LOW ke HIGH. Pada push button dengan `INPUT_PULLUP`, kondisi ini biasanya terjadi saat tombol dilepas.

### Perilaku LED
LED berubah kondisi ketika tombol dilepas. Respon LED terjadi sesudah tombol tidak ditekan lagi.

---

# B. Mode CHANGE

### Source Code
```cpp
#include <Arduino.h>

volatile bool ledState = false;

void tombolInterrupt() {
  ledState = !ledState;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    CHANGE
  );
}

void loop() {
  digitalWrite(13, ledState);
}
```

### Penjelasan Program
`CHANGE` akan memicu interrupt setiap terjadi perubahan sinyal:
  - LOW ke HIGH
  - maupun HIGH ke LOW

### Perilaku LED
LED dapat berubah dua kali: saat tombol ditekan, dan saat tombol dilepas. Akibatnya LED dapat terlihat berkedip lebih cepat atau kembali ke kondisi awal.

---

# C. Mode LOW

### Source Code
```cpp
#include <Arduino.h>

volatile bool ledState = false;

void tombolInterrupt() {
  ledState = !ledState;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    LOW
  );
}

void loop() {
  digitalWrite(13, ledState);
}
```

### Penjelasan Program
`LOW` akan terus memicu interrupt selama pin berada pada kondisi LOW.

### Perilaku LED
- Saat tombol ditekan dan ditahan, interrupt akan dipanggil terus-menerus.
- LED dapat berkedip sangat cepat atau berubah kondisi secara tidak stabil karena ISR dijalankan berulang kali.

---

# Perbedaan Mode Interrupt

| Mode | Kondisi Trigger | Perilaku LED |
|---|---|---|
| FALLING | HIGH ke LOW | LED berubah saat tombol ditekan |
| RISING | LOW ke HIGH | LED berubah saat tombol dilepas |
| CHANGE | Semua perubahan sinyal | LED berubah saat ditekan dan dilepas |
| LOW | Saat pin LOW terus-menerus | LED dapat berkedip cepat/tidak stabil |

---

# Kesimpulan

Interrupt memungkinkan Arduino merespon tombol dengan cepat tanpa polling terus-menerus. Fungsi `attachInterrupt()` digunakan untuk menghubungkan interrupt dengan ISR. ISR harus dibuat singkat dan sederhana agar sistem tetap stabil. Setiap mode interrupt memiliki karakteristik berbeda yang mempengaruhi perilaku LED.
