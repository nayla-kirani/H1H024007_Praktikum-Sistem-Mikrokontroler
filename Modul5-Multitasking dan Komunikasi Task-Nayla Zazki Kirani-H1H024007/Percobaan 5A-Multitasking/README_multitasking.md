## Percobaan 5A Multitasking
1. Persiapan bahan
2. Membuat rangkaian yang menghubungkan Arduino
   <img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/5669bfb9-96b0-4d81-9fce-2f31b0a4b417" />

# Wiring
   <img width="828" height="731" alt="Screenshot 2026-05-11 113601" src="https://github.com/user-attachments/assets/44593e29-86c9-44af-a851-b657ad767bf4" />

Link Tinkercad: https://www.tinkercad.com/things/llwZZFQntUw-wiring-diagram-multitasking-led-dengan-rtos?sharecode=e1a4j2a9O3u-Nu107HDgiimI-Mye3RdMDD4EKliihFk

# Pertanyaan Praktikum

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task pada program FreeRTOS berjalan secara **concurrent (multitasking)**, bukan benar-benar bersamaan secara paralel karena Arduino Uno hanya memiliki satu core processor.

Task berjalan secara **bergantian sangat cepat** sesuai pengaturan scheduler FreeRTOS. Scheduler akan membagi waktu eksekusi untuk setiap task sehingga terlihat seperti berjalan bersamaan.

Mekanisme yang terjadi:

- `TaskBlink1` mengontrol LED 1
- `TaskBlink2` mengontrol LED 2
- `TaskReadPot` membaca nilai potensiometer

Saat sebuah task menjalankan:

```cpp
vTaskDelay()
```

task tersebut akan masuk kondisi **blocked/delay**, lalu scheduler memberikan kesempatan kepada task lain untuk berjalan.

Karena itu semua task dapat berjalan secara teratur tanpa saling menghentikan.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Untuk menambahkan task keempat pada FreeRTOS, langkah-langkahnya adalah:

### 1. Membuat fungsi task baru

Contoh:

```cpp
void TaskBaru(void *pvParameters) {
  for (;;) {
    Serial.println("Task Keempat");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```

---

### 2. Membuat task menggunakan `xTaskCreate()`

Tambahkan pada `setup()`:

```cpp
xTaskCreate(TaskBaru, "Task4", 128, NULL, 1, NULL);
```

Penjelasan parameter:

| Parameter | Fungsi |
|---|---|
| `TaskBaru` | Nama fungsi task |
| `"Task4"` | Nama task |
| `128` | Stack memory |
| `NULL` | Parameter task |
| `1` | Prioritas task |
| `NULL` | Handle task |

---

### 3. Scheduler menjalankan task

Setelah task dibuat, FreeRTOS scheduler otomatis mengatur pergantian eksekusi antar task.

---

## 3. Modifikasi Program dengan Potensiometer untuk Mengontrol Kecepatan LED
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/8aa5b23b-8f6f-4d67-8b37-2bf368926d82" />

### Program Modifikasi

```cpp
#include <Arduino_FreeRTOS.h>

// PIN 
const int potPin = A0;
const int led1   = 8;
const int led2   = 7;

// GLOBAL 
int delayValue = 200; // default

// TASK 
void TaskReadPot(void *pvParameters);
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Create Tasks
  xTaskCreate(TaskReadPot, "ReadPot", 128, NULL, 2, NULL);
  xTaskCreate(TaskBlink1,  "Blink1",  128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2,  "Blink2",  128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
  // kosong
}

// TASK READ POT 
void TaskReadPot(void *pvParameters) {
  int potValue;

  for (;;) {
    potValue = analogRead(potPin);

    // Mapping nilai ADC (0-1023) ke delay (50 - 1000 ms)
    delayValue = map(potValue, 0, 1023, 50, 1000);

    Serial.print("Pot: ");
    Serial.print(potValue);
    Serial.print(" | Delay: ");
    Serial.println(delayValue);

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

// TASK BLINK 1 
void TaskBlink1(void *pvParameters) {
  for (;;) {
    digitalWrite(led1, HIGH);
    vTaskDelay(delayValue / portTICK_PERIOD_MS);

    digitalWrite(led1, LOW);
    vTaskDelay(delayValue / portTICK_PERIOD_MS);
  }
}

// TASK BLINK 2
void TaskBlink2(void *pvParameters) {
  for (;;) {
    digitalWrite(led2, HIGH);
    vTaskDelay((delayValue + 100) / portTICK_PERIOD_MS);

    digitalWrite(led2, LOW);
    vTaskDelay((delayValue + 100) / portTICK_PERIOD_MS);
  }
}
```

---

# Penjelasan Program

Program dimodifikasi dengan menambahkan sensor potensiometer pada pin `A0`.

Potensiometer digunakan untuk mengatur kecepatan kedipan LED secara realtime menggunakan FreeRTOS multitasking.

Program memiliki tiga task:

| Task | Fungsi |
|---|---|
| `TaskReadPot` | Membaca nilai potensiometer |
| `TaskBlink1` | Mengontrol LED 1 |
| `TaskBlink2` | Mengontrol LED 2 |

---

## Cara Kerja Program

### 1. Membaca Potensiometer

Nilai analog dari potensiometer dibaca menggunakan:

```cpp
analogRead(potPin);
```

Nilai ADC berada pada rentang:

```text
0 - 1023
```

---

### 2. Mengubah Nilai Delay

Nilai ADC diubah menjadi delay menggunakan fungsi:

```cpp
map(potValue, 0, 1023, 50, 1000);
```

Artinya:

| Nilai Potensiometer | Delay LED |
|---|---|
| Kecil | LED berkedip cepat |
| Besar | LED berkedip lambat |

Rentang delay:

```text
50 ms - 1000 ms
```

---

### 3. Task LED Berjalan Bersamaan

`TaskBlink1` dan `TaskBlink2` menggunakan nilai `delayValue` untuk menentukan kecepatan blinking LED.

Karena menggunakan FreeRTOS:

- Semua task berjalan multitasking
- Pembacaan sensor tetap berjalan saat LED berkedip
- Sistem menjadi responsif dan realtime

---

# Hasil Percobaan

Hasil yang diperoleh:

- LED dapat berkedip dengan kecepatan yang berubah-ubah sesuai putaran potensiometer
- Semakin besar nilai potensiometer, LED berkedip semakin lambat
- Semakin kecil nilai potensiometer, LED berkedip semakin cepat
- Serial Monitor menampilkan nilai ADC dan delay secara realtime

Contoh output Serial Monitor:

```text
Pot: 120 | Delay: 160
Pot: 500 | Delay: 520
Pot: 900 | Delay: 885
```

---

# Kesimpulan

Pada percobaan ini berhasil diterapkan konsep multitasking menggunakan FreeRTOS pada Arduino.

Dengan menambahkan potensiometer:

- Sistem dapat membaca input sensor secara realtime
- Kecepatan LED dapat dikontrol secara dinamis
- FreeRTOS memungkinkan beberapa task berjalan secara concurrent dengan scheduler

Praktikum ini menunjukkan bahwa RTOS sangat membantu dalam pengelolaan banyak task pada sistem embedded agar berjalan lebih terstruktur dan efisien.
