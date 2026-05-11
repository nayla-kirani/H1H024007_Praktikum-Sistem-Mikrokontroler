# Percobaan 5B - Komunikasi Task

<img width="1897" height="1002" alt="Screenshot 2026-05-05 094700" src="https://github.com/user-attachments/assets/ae2ec2b6-d928-47d2-9c6c-6c0a505e5c12" />


# Pertanyaan Praktikum

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task pada program FreeRTOS berjalan secara **concurrent (multitasking)**, bukan benar-benar paralel karena Arduino Uno hanya memiliki satu processor/core.

Task berjalan secara **bergantian sangat cepat** sesuai pengaturan scheduler FreeRTOS sehingga terlihat berjalan bersamaan.

Pada program ini terdapat dua task:

| Task | Fungsi |
|---|---|
| `read_data` | Membaca data sensor |
| `display` | Menampilkan data ke Serial Monitor |

Mekanisme kerja:

1. Task `read_data` membaca data sensor
2. Data dikirim ke queue menggunakan:

```cpp
xQueueSend()
```

3. Task `display` menerima data dari queue menggunakan:

```cpp
xQueueReceive()
```

4. Scheduler FreeRTOS mengatur pergantian eksekusi task secara otomatis

Saat sebuah task menjalankan:

```cpp
vTaskDelay()
```

atau menunggu queue, processor diberikan kepada task lain. Karena itu kedua task dapat berjalan dengan stabil tanpa saling mengganggu.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program ini **tidak terlalu berpotensi mengalami race condition** karena komunikasi data menggunakan **Queue FreeRTOS**.

Queue bekerja sebagai media komunikasi yang aman antar task.

Mekanismenya:

- Task pengirim memasukkan data ke queue
- Task penerima mengambil data dari queue
- Queue mengatur sinkronisasi data secara otomatis

Karena data tidak diakses langsung secara bersamaan oleh dua task, maka kemungkinan race condition menjadi sangat kecil. Jika tanpa queue dan kedua task mengakses variabel global secara bersamaan, maka race condition dapat terjadi karena data bisa berubah saat sedang digunakan task lain.

---

## 3. Modifikasi Program Menggunakan Sensor DHT

### Program Modifikasi

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

// DHT CONFIG
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// STRUCT
struct readings {
  float temp;
  float hum;
};

// QUEUE
QueueHandle_t my_queue;

// TASK
void read_data(void *pvParameters);
void display_data(void *pvParameters);

void setup() {
  Serial.begin(9600);

  dht.begin();

  // Membuat queue
  my_queue = xQueueCreate(5, sizeof(struct readings));

  // Membuat task
  xTaskCreate(read_data, "ReadData", 128, NULL, 1, NULL);
  xTaskCreate(display_data, "Display", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
  // kosong
}

// TASK READ SENSOR
void read_data(void *pvParameters) {

  struct readings sensorData;

  for (;;) {

    sensorData.temp = dht.readTemperature();
    sensorData.hum  = dht.readHumidity();

    // Kirim data ke queue
    xQueueSend(my_queue, &sensorData, portMAX_DELAY);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// TASK DISPLAY
void display_data(void *pvParameters) {

  struct readings sensorData;

  for (;;) {

    if (xQueueReceive(my_queue, &sensorData, portMAX_DELAY) == pdPASS) {

      Serial.print("Suhu : ");
      Serial.print(sensorData.temp);
      Serial.println(" C");

      Serial.print("Kelembapan : ");
      Serial.print(sensorData.hum);
      Serial.println(" %");

      Serial.println("====================");
    }
  }
}
```

---

# Penjelasan Program

Program dimodifikasi dengan menggunakan sensor DHT11 untuk membaca suhu dan kelembapan secara realtime.

Program menggunakan konsep multitasking dan komunikasi antar task menggunakan Queue FreeRTOS.

---

# Struktur Program

Program memiliki dua task utama:

| Task | Fungsi |
|---|---|
| `read_data` | Membaca data suhu dan kelembapan dari DHT11 |
| `display_data` | Menampilkan data pada Serial Monitor |

---

# Cara Kerja Program

## 1. Membaca Sensor DHT11

Data suhu dan kelembapan dibaca menggunakan:

```cpp
dht.readTemperature();
dht.readHumidity();
```

Data kemudian disimpan dalam struct:

```cpp
struct readings
```

---

## 2. Mengirim Data ke Queue

Data sensor dikirim menggunakan:

```cpp
xQueueSend()
```

Queue digunakan sebagai media komunikasi antar task.

---

## 3. Menampilkan Data

Task `display_data` menerima data menggunakan:

```cpp
xQueueReceive()
```

Setelah data diterima, nilai suhu dan kelembapan ditampilkan pada Serial Monitor.

---

# Hasil Percobaan

Hasil percobaan menunjukkan bahwa:

- Sensor DHT11 berhasil membaca suhu dan kelembapan secara realtime
- Data tampil dinamis pada Serial Monitor
- Queue berhasil mengirim data antar task tanpa error
- FreeRTOS mampu menjalankan multitasking dengan baik

Contoh output Serial Monitor:

```text
Suhu : 29.00 C
Kelembapan : 72.00 %
====================

Suhu : 30.00 C
Kelembapan : 70.00 %
====================
```

---

# Kesimpulan

Pada percobaan ini berhasil diterapkan komunikasi antar task menggunakan Queue FreeRTOS.

Dengan menggunakan sensor DHT11:

- Data sensor dapat dibaca secara realtime
- Komunikasi antar task menjadi lebih aman dan terstruktur
- Queue membantu mengurangi kemungkinan race condition
- Sistem multitasking berjalan stabil pada Arduino menggunakan FreeRTOS

Praktikum ini menunjukkan bahwa RTOS sangat berguna untuk mengatur banyak task dan komunikasi data pada sistem embedded.
