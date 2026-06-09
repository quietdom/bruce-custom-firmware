🌐 [English](../README.md) | [Portugues](README_PT.md) | [Italiano](README_IT.md) | [Francais](README_FR.md) | 🇷🇺 **Русский** | 🇨🇳 [中文](README_ZH.md) | [Polski](README_PL.md) | [Nederlands](README_NL.md) | [Turkce](README_TR.md) | [Deutsch](README_DE.md) | Tiếng Việt [Tiếng Việt](README_VN.md) | [Espanol](README_ES.md) | [Indonesia](README_ID.md) | 🇸🇦 [العربية](README_AR.md)

<p align="center">
  <img src="../media/bruce_banner.jpg" alt="Bruce Arsenal" width="700">
</p>

<h1 align="center">🎯 Bruce Arsenal</h1>

<p align="center">
  <b>Пользовательская прошивка для тестирования безопасности ESP32 устройств</b><br>
  <i>72 инструмента Full / 55 инструментов LITE - Одна прошивка - Несколько устройств</i>
</p>

---

Модифицированный [Bruce Firmware](https://github.com/pr3y/Bruce) с пользовательским модулем **Arsenal**. Все оригинальные функции Bruce остаются без изменений.

## Установка

1. Скачайте `.bin` из [Releases](../../releases)
2. Прошивка через [ESP Web Flasher](https://espressif.github.io/esptool-js/) (Chrome/Edge) или OTA через Arsenal Dashboard

---

## Инструменты Arsenal (72 Full / 55 LITE)

| # | Инструмент | Full | LITE | | # | Инструмент | Full | LITE |
|---|------|:----:|:----:|-|---|------|:----:|:----:|
| 1 | Network Scanner | ✅ | ✅ | | 37 | Keyfob Logger | ✅ | ❌ |
| 2 | DHCP Starvation | ✅ | ✅ | | 38 | Frequency Scanner | ✅ | ✅ |
| 3 | Karma Attack | ✅ | ✅ | | 39 | Flipper Import | ✅ | ✅ |
| 4 | DNS Spoofer | ✅ | ✅ | | 40 | Flipper Detector | ✅ | ❌ |
| 5 | Auto-Phish Portal | ✅ | ❌ | | 41 | Hacker Detector | ✅ | ❌ |
| 6 | Cred Forward | ✅ | ❌ | | 42 | RF Silence Enforcer | ✅ | ❌ |
| 7 | Auth Flood | ✅ | ✅ | | 43 | ESP-NOW Chat | ✅ | ❌ |
| 8 | AP Clone Flood | ✅ | ✅ | | 44 | ESP-NOW C2 | ✅ | ❌ |
| 9 | SSL Strip Lite | ✅ | ❌ | | 45 | Dead Drop Mesh | ✅ | ❌ |
| 10 | DNS Tunnel | ✅ | ✅ | | 46 | IR Data Transfer | ✅ | ❌ |
| 11 | WPS PIN Attack | ✅ | ✅ | | 47 | Multi-Device Sync | ✅ | ❌ |
| 12 | UPnP Port Opener | ✅ | ❌ | | 48 | NFC Biz Card | ✅ | ❌ |
| 13 | Default Cred Scanner | ✅ | ❌ | | 49 | Attack Stats | ✅ | ✅ |
| 14 | Rogue AP Detector | ✅ | ✅ | | 50 | Password Generator | ✅ | ✅ |
| 15 | WiFi Bruteforce | ✅ | ❌ | | 51 | Jam All | ✅ | ✅ |
| 16 | WPA Handshake Grabber | ✅ | ❌ | | 52 | Combos | ✅ | ✅ |
| 17 | Beacon Flood | ✅ | ❌ | | 53 | Scheduler | ✅ | ✅ |
| 18 | Selective Deauth | ✅ | ❌ | | 54 | Scripts | ✅ | ✅ |
| 19 | ARP Poisoner | ✅ | ❌ | | 55 | Session Log | ✅ | ✅ |
| 20 | BLE Tracker | ✅ | ❌ | | 56 | Config AP | ✅ | ✅ |
| 21 | BT Name Spammer | ✅ | ❌ | | 57 | Config Dashboard | ✅ | ✅ |
| 22 | AirTag Spoofer | ✅ | ❌ | | 58 | PIN Lock | ✅ | ✅ |
| 23 | Audio Jammer | ✅ | ❌ | | 59 | Remote Dashboard | ✅ | ❌ |
| 24 | Notification Spoofer | ✅ | ❌ | | 60 | SSID History Logger | ✅ | ✅ |
| 25 | BT Rickroll | ✅ | ❌ | | 61 | QR Poisoner | ✅ | ✅ |
| 26 | BT Device Profiler | ✅ | ❌ | | 62 | Auto-Dim | ✅ | ✅ |
| 27 | Device Fingerprinter | ✅ | ✅ | | 63 | OPSEC Background | ✅ | ✅ |
| 28 | OPSEC Monitor | ✅ | ✅ | | 64 | Network Scanner (Full) | ✅ | ✅ |
| 29 | OUI Lookup | ✅ | ✅ | | 65 | DHCP Starvation (Full) | ✅ | ✅ |
| 30 | Probe Log | ✅ | ✅ | | 66 | Karma Attack (Full) | ✅ | ✅ |
| 31 | Banner Grabber | ✅ | ✅ | | 67 | DNS Spoofer (Full) | ✅ | ✅ |
| 32 | SmartHome Scan | ✅ | ❌ | | 68 | Auth Flood (Full) | ✅ | ✅ |
| 33 | Channel Chart | ✅ | ✅ | | 69 | AP Clone Flood (Full) | ✅ | ✅ |
| 34 | People Counter | ✅ | ❌ | | 70 | DNS Tunnel (Full) | ✅ | ✅ |
| 35 | MAC Rotator | ✅ | ✅ | | 71 | WPS PIN Attack (Full) | ✅ | ✅ |
| 36 | Channel Hopper | ✅ | ✅ | | 72 | Rogue AP Detector (Full) | ✅ | ✅ |

---

## Совместимость плат

| Плата | Flash | Версия |
|-------|-------|--------|
| **ESP32-S3** | | |
| LilyGo T-Embed CC1101 | 16MB | Full |
| LilyGo T-Deck Pro | 16MB | Full |
| LilyGo T-Deck | 16MB | Full |
| LilyGo T-Display S3 | 16MB | Full |
| LilyGo T-Display S3 Touch | 16MB | Full |
| LilyGo T-Display S3 MMC | 16MB | Full |
| LilyGo T-Display S3 Touch MMC | 16MB | Full |
| LilyGo T-HMI | 16MB | Full |
| LilyGo T-LoRa Pager | 16MB | Full |
| LilyGo T-Watch S3 | 16MB | Full |
| M5Stack Cardputer | 8MB | Full |
| M5Stack CoreS3 | 16MB | Full |
| M5Stack StickS3 | 16MB | Full |
| ESP32-S3 DevKitC-1 | 16MB | Full |
| Smoochiee Board | 16MB | Full |
| **ESP32-C5** | | |
| ESP32-C5 | 4MB | Full |
| ESP32-C5 TFT | 4MB | Full |
| **ESP32** | | |
| M5Stack Core 4MB | 4MB | LITE |
| M5Stack Core 16MB | 16MB | LITE |
| M5Stack CPlus 1.1 | 4MB | LITE |
| CYD-2432S028 | 4MB | LITE |
| CYD-2USB | 4MB | LITE |
| CYD-2432W328C | 4MB | LITE |
| CYD-2432W328R | 4MB | LITE |
| CYD-3248S035R | 4MB | LITE |
| CYD-3248S035C | 4MB | LITE |
| Elecrow 2.4B | 4MB | LITE |
| Elecrow 2.8B | 4MB | LITE |
| Elecrow 3.5B | 4MB | LITE |
| LilyGo T-Display TTGO | 4MB | LITE |
| Marauder Mini | 4MB | LITE |
| Marauder V4-V6 | 4MB | LITE |
| Marauder V7 | 4MB | LITE |
| Marauder V6.1 | 4MB | LITE |
| Awok Mini | 4MB | LITE |
| Awok Touch | 4MB | LITE |
| WaveSentry R1 | 4MB | LITE |
| Phantom S024R | 4MB | LITE |
| **Известные проблемы** | | |
| M5Stack CPlus2 | - | DRAM overflow |
| M5Stack Core2 | - | DRAM overflow |

---

## Удаленная панель управления

Arsenal > Dashboard. Подключитесь к `ArsenalNet` (пароль: `arsenal32`). Откройте `192.168.4.1`.

## Благодарности

- [Bruce Firmware](https://github.com/pr3y/Bruce) от pr3y
- Модуль Arsenal от quietdom

## Отказ от ответственности

Только для авторизованного тестирования безопасности и образовательных целей.