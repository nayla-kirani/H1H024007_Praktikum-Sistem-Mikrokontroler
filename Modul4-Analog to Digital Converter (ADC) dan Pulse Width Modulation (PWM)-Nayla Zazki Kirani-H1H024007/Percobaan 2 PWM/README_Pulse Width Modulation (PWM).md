## Percobaan 1 Analog to Digital Converter (ADC)
1. Persiapan bahan
2. Membuat rangkaian yang menghubungkan Arduino
   <img width="1600" height="900" alt="WhatsApp Image 2026-04-28 at 09 58 55" src="https://github.com/user-attachments/assets/2d9ab675-8dcc-40c4-bfb4-fa6c658924a6" />


## Pertanyaan Praktikum

#### 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()`!

LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()` karena fungsi ini menghasilkan sinyal PWM (Pulse Width Modulation). PWM bekerja dengan cara mengatur lebar pulsa (duty cycle) dari sinyal digital:

Semakin besar duty cycle → LED semakin terang

semakin kecil duty cycle → LED semakin redup  

Meskipun bukan sinyal analog murni, perubahan cepat antara HIGH dan LOW membuat LED tampak memiliki tingkat kecerahan yang berbeda.

---

#### 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?

Nilai ADC memiliki rentang **0–1023**, sedangkan PWM memiliki rentang **0–255**.  

Hubungannya adalah: 
- Nilai ADC harus dikonversi ke nilai PWM menggunakan fungsi `map()`
- Perbandingannya adalah sekitar **4:1** (1023 ≈ 4 × 255)

Contoh:
```cpp
int pwm = map(nilaiADC, 0, 1023, 0, 255);
```

---

#### 3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200
```cpp
int ledPin = 9;
int potPin = A0;
int nilaiADC;
int pwm;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  nilaiADC = analogRead(potPin);

  // Mapping ADC ke PWM
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // LED hanya menyala jika PWM di antara 50–200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm);
  } else {
    analogWrite(ledPin, 0); // LED mati
  }

  delay(10);
}
```
##### Penjelasan Program

`analogRead(potPin)` membaca nilai dari potensiometer dalam rentang **0–1023**

Fungsi `map()` digunakan untuk mengubah nilai tersebut menjadi rentang **0–255** agar sesuai dengan PWM

Kondisi `if (pwm >= 50 && pwm <= 200)` digunakan untuk membatasi LED agar:
  - Hanya menyala pada kecerahan sedang
  - Tidak terlalu redup (di bawah 50)
  - Tidak terlalu terang (di atas 200)

`analogWrite(ledPin, pwm)` mengatur kecerahan LED sesuai nilai PWM, `analogWrite(ledPin, 0)` mematikan LED jika nilai di luar rentang, `delay(10)` memberikan jeda agar perubahan kecerahan lebih stabil
