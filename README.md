# ESP8266-P10-Digital-Clock-WiFiManager-NTP  
Sistem ini dirancang sebagai **jam digital berbasis ESP8266 dan Panel LED P10** yang mampu menampilkan waktu secara real-time menggunakan **sinkronisasi NTP (Network Time Protocol)**. Sistem dilengkapi dengan **WiFiManager non-blocking**, sehingga jam tetap berjalan meskipun portal konfigurasi WiFi aktif. Jam ini cocok digunakan untuk **sekolah, masjid, ruang publik, laboratorium, maupun display informasi digital**. [Frendi RoboTech]

---

# 🧩 Fitur Utama Sistem

## 🔹 Sistem Jam Digital Berbasis ESP8266
ESP8266 bertindak sebagai pusat pengendali sistem jam dan konektivitas jaringan:

* Sinkronisasi waktu otomatis via **NTP**
* Zona waktu **GMT +7 (WIB)**
* Konfigurasi WiFi menggunakan **WiFiManager**
* Portal WiFi **non-blocking** (jam tetap berjalan)
* Auto reconnect WiFi cerdas
* Indikator visual saat WiFi terputus
* Tampilan jam & menit pada **Panel LED P10**
* Kecerahan panel dapat diatur

---

## 🔹 Logika Kerja Sistem Jam

### 1. Inisialisasi Sistem
* Inisialisasi Panel LED P10
* Inisialisasi font jam & teks
* ESP8266 masuk mode WiFi STA
* Menampilkan pesan **CONNECTING**

### 2. Koneksi WiFi
* ESP mencoba terhubung ke WiFi terakhir
* Jika gagal → Config Portal otomatis aktif
* Portal bersifat **non-blocking**

### 3. Sinkronisasi Waktu
* NTP Server:
  * `id.pool.ntp.org`
  * `pool.ntp.org`
* Waktu lokal disesuaikan dengan WIB

### 4. Manajemen Koneksi Cerdas
* Cek koneksi setiap 10 detik
* Jika WiFi terputus:
  * Reconnect otomatis
  * Gagal ≥ 10x → Portal aktif
* WiFi kembali normal → Portal mati otomatis

---

# ⏰ Sistem Tampilan Jam P10

## Tampilan Utama
Panel LED P10 menampilkan:
* **Jam (HH)** di kiri
* **Menit (MM)** di kanan
* **Titik dua (:) custom** di tengah

### Logika Titik Dua (Colon)
| Kondisi WiFi | Tampilan |
|-------------|----------|
| WiFi Terhubung | Berkedip tiap 1 detik |
| WiFi Terputus | Menyala terus |

### Indikator Portal Aktif
* Titik kecil di pojok kiri atas panel
* Menandakan Config Portal sedang aktif

---

# ⚙ Struktur Hardware

## ESP8266
* NodeMCU / Wemos D1 Mini
* Mode WiFi: Station + Config Portal

## Panel LED
* Panel LED **P10 1x1**
* Library: **DMDESP**

---

# 📚 Library yang Digunakan

| Library | Fungsi |
|-------|--------|
| ESP8266WiFi | Koneksi WiFi |
| WiFiManager | Manajemen WiFi |
| DMDESP | Kontrol panel LED |
| EMKotak5x7 | Font teks |
| ElektronMart6x16 | Font jam |
| time.h | Sinkronisasi waktu |

---

# 🧠 Alur Kerja Sistem (Flow System)

## ⏱️ Alur Jam Digital
1. ESP8266 menyala
2. Cek koneksi WiFi
3. Sinkronisasi waktu NTP
4. Tampilkan jam & menit
5. Update waktu realtime
6. Monitor status WiFi
7. Aktifkan portal jika koneksi gagal

---

# 📶 Informasi Config Portal WiFi
Jika gagal konek WiFi, ESP membuat Access Point:
* SSID : P10-JAM-FRENDI
* PASS : frendix45

Akses melalui browser:
* 192.168.4.1
---

# 📌 Kelebihan Sistem
* Jam tetap berjalan tanpa internet
* WiFiManager non-blocking
* Stabil untuk pemakaian jangka panjang
* Indikator visual status WiFi
* Cocok untuk display publik
* Mudah dikembangkan

---

# 📦 Pengembangan Lanjutan
* Tanggal & hari
* RTC backup
* Running text
* Auto brightness (LDR)
* MQTT / Web Dashboard
* Sinkronisasi waktu lokal

---

 ## 📧 **Contacs us :** 
* [Frendi RoboTech](https://www.instagram.com/frendi.co/)
* [Whatsapp : +6287888227410](https://wa.me/+6287888227410)
* [Email    : frendirobotech@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendirobotech@gmail.com) atau [Email    : frendix45@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendix45@gmail.com)

---

## 👨‍💻 Author
Dikembangkan oleh: **Imam Sa'id Nurfrendi**  
Komunitas: **Reog Robotic & Robotech Electronics**  
Lisensi: **Open Source (MIT)**
