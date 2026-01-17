#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DMDESP.h>
#include <fonts/EMKotak5x7.h>
#include <fonts/ElektronMart6x16.h>
#include <time.h>

// ================= FONT & DMD =================
#define FontInfo   EMKotak5x7
#define FontJam    ElektronMart6x16
#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

// ================= VAR WIFI & TIME =================
const char* AP_NAME = "P10-JAM-FRENDI";
const char* AP_PASS = "frendix45";
WiFiManager wm;

int Jam, Men, Det;
struct tm timeinfo;
unsigned long lastWifiCheck = 0;
int reconnectCount = 0;
bool portalRunning = false;

// ================= DISPLAY HELPER =================
void drawColon(bool on) {
  if (!on) return;
  Disp.drawLine(15, 3, 15, 3); Disp.drawLine(14, 4, 14, 4);
  Disp.drawLine(16, 4, 16, 4); Disp.drawLine(15, 5, 15, 5);
  Disp.drawLine(15, 4, 15, 4);
  Disp.drawLine(15, 10, 15, 10); Disp.drawLine(14, 11, 14, 11);
  Disp.drawLine(16, 11, 16, 11); Disp.drawLine(15, 12, 15, 12);
  Disp.drawLine(15, 11, 15, 11);
}

void showMessage(const char* text) {
  Disp.clear();
  Disp.setFont(FontInfo);
  Disp.drawText(0, 4, text);
  Disp.loop();
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  Disp.start();
  Disp.setBrightness(1);

  WiFi.mode(WIFI_STA);
  wm.setConfigPortalBlocking(false); // Kunci agar jam tetap jalan
  wm.setConfigPortalTimeout(180);

  showMessage("CONNECTING");

  // Percobaan koneksi pertama
  if (!wm.autoConnect(AP_NAME, AP_PASS)) {
    Serial.println("Portal Aktif atau Gagal Konek");
  }

  // Sinkronisasi Waktu
  configTime(7 * 3600, 0, "id.pool.ntp.org", "pool.ntp.org");
}

// ================= LOOP =================
void loop() {
  // Selalu panggil process() agar WiFiManager tetap bekerja di background
  wm.process();

  // 1. Ambil Waktu Lokal
  time_t now = time(nullptr);
  localtime_r(&now, &timeinfo);
  Jam = timeinfo.tm_hour;
  Men = timeinfo.tm_min;
  Det = timeinfo.tm_sec;

  // 2. Logika Reconnect Cerdas
  if (millis() - lastWifiCheck > 10000) { // Cek tiap 15 detik
    lastWifiCheck = millis();

    if (WiFi.status() != WL_CONNECTED) {
      reconnectCount++;

      // Jika internet putus, paksa ESP untuk terus mencoba connect ke SSID yang ada
      WiFi.begin();

      // Jika sudah gagal 10x, nyalakan portal (jika belum nyala)
      if (reconnectCount >= 10 && !portalRunning) {
        wm.startConfigPortal(AP_NAME, AP_PASS);
        portalRunning = true;
      }
    } else {
      // Jika terhubung kembali (baik lewat portal atau otomatis)
      if (portalRunning) {
        wm.stopConfigPortal(); // Matikan portal jika internet sudah balik
        portalRunning = false;
      }
      reconnectCount = 0;
    }
  }

  // 3. Tampilan P10 (Utama)
  char buffJam[3], buffMen[3];
  sprintf(buffJam, "%02d", Jam);
  sprintf(buffMen, "%02d", Men);

  Disp.clear();

  // Indikator Portal Aktif: Jika portal jalan, tampilkan titik di pojok
  if (portalRunning) {
    Disp.drawLine(0, 0, 0, 0);
  }

  Disp.setFont(FontJam);
  Disp.drawText(0, 0, buffJam);

  // Logika baru:
  // Jika konek internet -> kedip mengikuti detik
  // Jika putus internet -> titik diam terus (ON) agar tahu ada masalah
  bool colonBlink;
  if (WiFi.status() == WL_CONNECTED) {
    colonBlink = (Det % 2 == 0); // Berkedip normal
  } else {
    colonBlink = true; // Menyala terus (diam) sebagai tanda WiFi putus
  }

  drawColon(colonBlink);

  Disp.drawText(18, 0, buffMen);

  Disp.loop();
}
