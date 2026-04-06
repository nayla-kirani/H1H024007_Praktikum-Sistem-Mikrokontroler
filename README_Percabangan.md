## Percobaan 1A: Percabangan

#### 1. Pada kondisi apa program masuk ke blok `if`?

Program akan masuk ke blok `if` ketika:

```
timeDelay <= 100
```

Artinya, saat delay sudah sangat kecil (LED berkedip sangat cepat), maka:

* Program memberikan jeda `delay(3000)`
* Nilai `timeDelay` di-reset ke 1000

---

#### 2. Pada kondisi apa program masuk ke blok `else`?

Program masuk ke blok `else` ketika:

```
timeDelay > 100
```

Pada kondisi ini:

Nilai `timeDelay` dikurangi 100 dan LED akan berkedip semakin cepat secara bertahap

---

#### 3. Apa fungsi dari perintah delay(timeDelay)?

Fungsi `delay(timeDelay)` digunakan untuk:

Memberikan jeda waktu dalam milidetik dan Mengatur kecepatan kedipan LED

Keterangan:

* Delay besar → LED lambat
* Delay kecil → LED cepat

---

#### 4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

```cpp
const int ledPin = 6;      // Menentukan pin LED
int timeDelay = 1000;      // Delay awal (lambat)
bool faseTurun = true;     // Penanda arah perubahan

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin sebagai output
}

void loop() {
  digitalWrite(ledPin, HIGH); // LED menyala
  delay(timeDelay);

  digitalWrite(ledPin, LOW);  // LED mati
  delay(timeDelay);

  if (faseTurun) {
    timeDelay -= 100; // Mempercepat

    if (timeDelay <= 100) {
      faseTurun = false; // Ubah ke fase melambat
    }
  } else {
    timeDelay += 100; // Memperlambat

    if (timeDelay >= 1000) {
      delay(2000);      // Jeda sebelum mati
      timeDelay = 1000; // Reset
      faseTurun = true; // ulang
    }
  }
}
```

---
