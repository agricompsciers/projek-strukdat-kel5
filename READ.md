Proyek ini adalah implementasi struktur data **Hash Map** menggunakan C++ untuk mengelola sistem penjadwalan ruangan. File *executable* (`.exe`) sudah tersedia, sehingga kamu tidak perlu melakukan kompilasi ulang. Proyek ini dilengkapi dengan *Python script* untuk men-generate data dummy dan otomatisasi skenario *testing*.

## Persiapan (Prerequisites)

Pastikan perangkat kamu sudah terinstal **Python 3.x** untuk menjalankan script *generator*. Clone repo github ini.

---

## Cara Menjalankan Program

### Tahap 1: Generate Dataset 
Program C++ membutuhkan file `jadwal.txt` agar Hash Map memiliki data awal (tidak kosong) saat pertama kali dijalankan.

1. Buka Terminal / Command Prompt dan arahkan ke direktori proyek ini.
2. Jalankan script dataset generator:
   ```bash
   python generator_dataset.py
   ```
3. Pastikan file `jadwal.txt` (berisi 1000 baris data) sudah terbuat di folder yang sama dengan file `.exe`.

### Tahap 2: Jalankan Aplikasi Utama
Karena file `.exe` sudah disediakan, kamu bisa langsung menjalankannya lewat terminal:

```bash
.\run_hashmap.exe
```
*(Atau kamu juga bisa langsung double-click pada file `run_hashmap.exe` di File Explorer).*

Program akan otomatis memuat 1000 data dari `jadwal.txt` secara instan, dan kamu bisa mulai melakukan operasi *Insert*, *Search*, *Update*, atau *Delete* lewat menu yang tersedia.

---

## Panduan Testing Otomatis (Stress Test)

Jika kamu ingin menguji performa dan kecepatan eksekusi program tanpa harus mengetik manual satu per satu, gunakan fitur generator skenario tes berikut:

**1. Generate Skenario Tes:**
Jalankan script *use-case* untuk membuat 1000 perintah acak otomatis.
```bash
python generator_usecase.py
```
Perintah ini akan menghasilkan file bernama `test_cases.txt`.

**2. Jalankan Tes Otomatis:**
Gunakan *Input Redirection* (`<`) untuk memasukkan file skenario tersebut langsung ke dalam program. Program akan berpura-pura menjadi *user* yang mengetik semua perintah itu dalam hitungan milidetik.

Jalankan perintah ini di terminal:
```bash
.\run_hashmap.exe < test_cases.txt
```

Setelah eksekusi selesai, program akan menampilkan total waktu eksekusi dalam milidetik (ms) di layar terminal.