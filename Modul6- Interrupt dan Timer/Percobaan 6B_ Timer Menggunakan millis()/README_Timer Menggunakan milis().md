# Modul 6 - Percobaan 6B: Timer Menggunakan millis()

## Tujuan Percobaan
Percobaan ini bertujuan untuk memahami penggunaan fungsi `millis()` sebagai timer pada Arduino untuk membuat LED berkedip tanpa menggunakan `delay()`.
<img width="1600" height="900" alt="WhatsApp Image 2026-05-12 at 10 00 23" src="https://github.com/user-attachments/assets/ea6f36be-af24-40dc-9818-e344ac08fe2b" />
<img width="716" height="554" alt="image" src="https://github.com/user-attachments/assets/d7f75ac2-4eda-4bfd-8699-2fcb66224393" />


---

# 1. Jelaskan bagaimana fungsi millis() bekerja pada program tersebut!

Fungsi `millis()` digunakan untuk menghitung waktu sejak Arduino pertama kali dinyalakan dalam satuan milidetik (ms).

Pada program:
```cpp
unsigned long currentMillis = millis();
```

Baris tersebut mengambil waktu saat ini dari sistem Arduino.

Kemudian program membandingkan:
```cpp
currentMillis - previousMillis
```

Jika selisih waktunya sudah melebihi interval yang ditentukan, maka: status LED diubah, LED dinyalakan atau dimatikan, dan waktu terakhir disimpan kembali.

Contoh:
```cpp
if (currentMillis - previousMillis1 >= interval1)
```

Artinya:
- jika sudah lewat 1000 ms (1 detik),
- maka LED 1 akan berubah kondisi.

Metode ini memungkinkan Arduino menjalankan banyak proses tanpa menghentikan program utama.

---

# 2. Apa perbedaan utama antara delay() dan millis()?

| delay() | millis() |
|---|---|
| Bersifat blocking | Bersifat non-blocking |
| Program berhenti sementara | Program tetap berjalan |
| Tidak dapat menjalankan tugas lain saat delay berlangsung | Dapat menjalankan beberapa tugas sekaligus |
| Cocok untuk program sederhana | Cocok untuk multitasking sederhana |
| Kurang responsif | Lebih responsif |

Contoh:
```cpp
delay(1000);
```
Saat delay berjalan, Arduino tidak dapat mengerjakan proses lain.

Sedangkan pada `millis()`, Arduino tetap dapat membaca sensor atau menjalankan proses lain sambil menghitung waktu.

---

# 3. Mengapa metode millis() disebut non-blocking?

Karena `millis()` tidak menghentikan jalannya program utama.

Program tetap terus melakukan perulangan pada `loop()` sambil mengecek waktu menggunakan:
```cpp
if(currentMillis - previousMillis >= interval)
```

Dengan metode ini: Arduino tetap responsif, beberapa task dapat berjalan bersamaan, dan sistem lebih efisien dibanding menggunakan `delay()`.

---

# 4. Modifikasi Program

<img width="764" height="602" alt="image" src="https://github.com/user-attachments/assets/85fbba66-7b6f-4323-8398-15ffa963f635" />


## Spesifikasi
- LED pertama berkedip setiap 1 detik
- LED kedua berkedip setiap 500 ms
- Tanpa menggunakan `delay()`

---

# Source Code
```cpp
#include <Arduino.h>

// LED 1
unsigned long previousMillis1 = 0;
const long interval1 = 1000;
bool ledState1 = false;

// LED 2
unsigned long previousMillis2 = 0;
const long interval2 = 500;
bool ledState2 = false;

void setup() {
  pinMode(13, OUTPUT); // LED 1
  pinMode(12, OUTPUT); // LED 2
}

void loop() {

  // Waktu sekarang
  unsigned long currentMillis = millis();

  // LED 1 berkedip tiap 1 detik
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;

    ledState1 = !ledState1;
    digitalWrite(13, ledState1);
  }

  // LED 2 berkedip tiap 500 ms
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;

    ledState2 = !ledState2;
    digitalWrite(12, ledState2);
  }
}
```

---

# Penjelasan Program Per Baris

## Library Arduino
```cpp
#include <Arduino.h>
```
Digunakan untuk memanggil library utama Arduino.

---

## Variabel LED 1
```cpp
unsigned long previousMillis1 = 0;
```
Menyimpan waktu terakhir LED 1 berubah.

```cpp
const long interval1 = 1000;
```
Menentukan interval LED 1 sebesar 1000 ms (1 detik).

```cpp
bool ledState1 = false;
```
Menyimpan status LED 1 (ON/OFF).

---

## Variabel LED 2
```cpp
unsigned long previousMillis2 = 0;
```
Menyimpan waktu terakhir LED 2 berubah.

```cpp
const long interval2 = 500;
```
Menentukan interval LED 2 sebesar 500 ms.

```cpp
bool ledState2 = false;
```
Menyimpan status LED 2.

---

# Fungsi setup()

```cpp
void setup() {
```
Fungsi yang dijalankan sekali saat Arduino menyala.

```cpp
pinMode(13, OUTPUT);
```
Mengatur pin 13 sebagai output untuk LED 1.

```cpp
pinMode(12, OUTPUT);
```
Mengatur pin 12 sebagai output untuk LED 2.

---

# Fungsi loop()

```cpp
void loop() {
```
Fungsi utama yang berjalan terus-menerus.

---

## Mengambil waktu sekarang
```cpp
unsigned long currentMillis = millis();
```
Mengambil waktu saat ini dari sistem Arduino.

---

# Proses LED 1

```cpp
if (currentMillis - previousMillis1 >= interval1)
```
Mengecek apakah sudah lewat 1 detik.

```cpp
previousMillis1 = currentMillis;
```
Menyimpan waktu terakhir LED berubah.

```cpp
ledState1 = !ledState1;
```
Mengubah status LED menjadi kebalikan sebelumnya.

```cpp
digitalWrite(13, ledState1);
```
Menyalakan atau mematikan LED 1.

---

# Proses LED 2

```cpp
if (currentMillis - previousMillis2 >= interval2)
```
Mengecek apakah sudah lewat 500 ms.

```cpp
previousMillis2 = currentMillis;
```
Menyimpan waktu terakhir LED berubah.

```cpp
ledState2 = !ledState2;
```
Mengubah status LED 2.

```cpp
digitalWrite(12, ledState2);
```
Menyalakan atau mematikan LED 2.

---

# Hasil Percobaan

Hasil yang diperoleh:
- LED pada pin 13 berkedip setiap 1 detik.
- LED pada pin 12 berkedip setiap 500 ms.
- Kedua LED dapat berjalan bersamaan tanpa menggunakan `delay()`.

Hal ini menunjukkan bahwa metode `millis()` mampu menjalankan multitasking sederhana secara non-blocking.

---

# Kesimpulan

Fungsi `millis()` digunakan sebagai timer non-blocking untuk menghitung waktu tanpa menghentikan program utama. Dengan metode ini, Arduino dapat menjalankan beberapa proses secara bersamaan dan sistem menjadi lebih responsif dibanding menggunakan `delay()`.
