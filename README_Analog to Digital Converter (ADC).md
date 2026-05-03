## Percobaan 1 Analog to Digital Converter (ADC)
1. Persiapan bahan
2. Membuat rangkaian yang menghubungkan Arduino
    <img width="1600" height="900" alt="WhatsApp Image 2026-04-28 at 09 35 09" src="https://github.com/user-attachments/assets/92a87eaa-c72e-45b1-ab62-2300db3015fa" />


## Pertanyaan Praktikum

#### 1. Apa fungsi perintah `analogRead()` pada rangkaian praktikum ini?

Perintah `analogRead()` digunakan untuk membaca nilai tegangan analog dari pin input (misalnya dari potensiometer). Nilai yang dibaca akan dikonversi oleh ADC (Analog to Digital Converter) menjadi data digital dengan rentang 0–1023.

---

#### 2. Mengapa diperlukan fungsi `map()` dalam program tersebut?

Fungsi `map()` digunakan untuk mengubah (mengonversi) rentang nilai dari satu skala ke skala lain. 

Pada praktikum ini: Nilai dari `analogRead()` berada pada rentang **0–1023**, sedangkan sudut servo berada pada rentang **0–180 derajat**. Sehingga diperlukan fungsi `map()` untuk menyesuaikan nilai input agar sesuai dengan kebutuhan output servo.

Contoh:
```cpp
int sudut = map(nilaiADC, 0, 1023, 0, 180);

```

---

#### 3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023.
```cpp
#include <Servo.h>

Servo myServo;
int potPin = A0;
int nilaiADC;
int sudut;

void setup() {
  myServo.attach(9);
}

void loop() {
  nilaiADC = analogRead(potPin);
  
  // Mapping dari 0–1023 menjadi 30–150 derajat
  sudut = map(nilaiADC, 0, 1023, 30, 150);
  
  myServo.write(sudut);
  delay(15);
}

```

##### Penjelasan program

`analogRead(potPin)` digunakan untuk membaca nilai dari potensiometer dalam rentang **0–1023**.

Fungsi `map()` digunakan untuk mengubah nilai tersebut ke rentang **30–150 derajat**, sehingga:
  - Servo tidak akan bergerak penuh (**0–180°**)
  - Pergerakan menjadi lebih terbatas dan terkontrol

`myServo.write(sudut)` berfungsi untuk mengatur posisi servo sesuai dengan nilai sudut hasil mapping. 

`delay(15)` digunakan untuk memberikan jeda agar pergerakan servo terlihat lebih halus dan tidak terlalu cepat.
