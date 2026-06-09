🌐 [English](README.md) | [Portugues](docs/README_PT.md) | [Italiano](docs/README_IT.md) | [Francais](docs/README_FR.md) | 🇷🇺 [Русский](docs/README_RU.md) | 🇨🇳 [中文](docs/README_ZH.md) | [Polski](docs/README_PL.md) | [Nederlands](docs/README_NL.md) | [Turkce](docs/README_TR.md) | [Deutsch](docs/README_DE.md) | Tiếng Việt [Tiếng Việt](docs/README_VN.md) | [Espanol](docs/README_ES.md) | [Indonesia](docs/README_ID.md) | 🇸🇦 [العربية](docs/README_AR.md)

<p align="center">
  <img src="media/bruce_banner.jpg" alt="Bruce Arsenal" width="700">
</p>

<h1 align="center">🎯 Bruce Arsenal</h1>

<p align="center">
  <b>Custom offensive security firmware for ESP32 devices</b><br>
  <i>72 tools - One firmware - Multiple devices</i>
</p>

---

## What Is This

A modified [Bruce Firmware](https://github.com/pr3y/Bruce) with a custom **Arsenal** module - 72 offensive security tools accessible from a single menu. All original Bruce features remain intact.

## Installation

1. Download the `.bin` from [Releases](../../releases)
2. Flash via [ESP Web Flasher](https://espressif.github.io/esptool-js/) (Chrome/Edge) or OTA via Arsenal Dashboard

---

## Arsenal Tools (72)

| # | Tool | Full | LITE |
|---|------|------|------|
| | **WiFi Arsenal** | | |
| 1 | Network Scanner | ✅ | ✅ |
| 2 | DHCP Starvation | ✅ | ✅ |
| 3 | Karma Attack | ✅ | ✅ |
| 4 | DNS Spoofer | ✅ | ✅ |
| 5 | Auto-Phish Portal | ✅ | ✅ |
| 6 | Cred Forward | ✅ | ✅ |
| 7 | Auth Flood | ✅ | ✅ |
| 8 | AP Clone Flood | ✅ | ✅ |
| 9 | SSL Strip Lite | ✅ | ✅ |
| 10 | DNS Tunnel | ✅ | ✅ |
| 11 | WPS PIN Attack | ✅ | ✅ |
| | **BLE Arsenal** | | |
| 12 | BLE Tracker | ✅ | ✅ |
| 13 | BT Name Spammer | ✅ | ✅ |
| 14 | AirTag Spoofer | ✅ | ✅ |
| 15 | Audio Jammer | ✅ | ✅ |
| 16 | Notification Spoofer | ✅ | ✅ |
| 17 | BT Rickroll | ✅ | ✅ |
| | **Intelligence** | | |
| 18 | Device Fingerprinter | ✅ | ✅ |
| 19 | OPSEC Monitor | ✅ | ✅ |
| 20 | OUI Lookup | ✅ | ✅ |
| 21 | Probe Log | ✅ | ✅ |
| 22 | Banner Grabber | ✅ | ✅ |
| 23 | SmartHome Scan | ✅ | ✅ |
| 24 | Channel Chart | ✅ | ✅ |
| 25 | People Counter | ✅ | ✅ |
| | **Evasion** | | |
| 26 | MAC Rotator | ✅ | ✅ |
| 27 | Channel Hopper | ✅ | ✅ |
| 28 | Decoy Traffic | ✅ | ✅ |
| 29 | Identity Cloner | ✅ | ✅ |
| 30 | Time Randomizer | ✅ | ✅ |
| | **Phishing** | | |
| 31 | Win Update Phish | ✅ | ✅ |
| 32 | WiFi Speed Phish | ✅ | ✅ |
| 33 | OAuth Phish | ✅ | ✅ |
| 34 | Device Found Phish | ✅ | ✅ |
| | **Sub-GHz / RF** | | |
| 35 | NRF24 MouseJack | ✅ | ✅ |
| 36 | Doorbell Replay | ✅ | ✅ |
| 37 | Garage Brute Force | ✅ | ✅ |
| 38 | Keyfob Logger | ✅ | ✅ |
| 39 | Frequency Scanner | ✅ | ✅ |
| 40 | Flipper Import | ✅ | ✅ |
| | **Detection** | | |
| 41 | Flipper Detector | ✅ | ✅ |
| 42 | Hacker Detector | ✅ | ✅ |
| 43 | RF Silence Enforcer | ✅ | ✅ |
| | **Comms** | | |
| 44 | ESP-NOW Chat | ✅ | ✅ |
| 45 | ESP-NOW C2 | ✅ | ✅ |
| 46 | Dead Drop Mesh | ✅ | ✅ |
| 47 | IR Data Transfer | ✅ | ✅ |
| 48 | Multi-Device Sync | ✅ | ✅ |
| | **Utility** | | |
| 49 | NFC Biz Card | ✅ | ✅ |
| 50 | Attack Stats | ✅ | ✅ |
| | **Arsenal Core** | | |
| 51 | Jam All | ✅ | ✅ |
| 52 | Combos | ✅ | ✅ |
| 53 | Scheduler | ✅ | ✅ |
| 54 | Script Browser | ✅ | ✅ |
| 55 | Session Log | ✅ | ✅ |

---

## Board Compatibility

| Board | Flash | Status |
|-------|-------|--------|
| **ESP32-S3 (Full - all 55 tools)** | | |
| LilyGo T-Embed CC1101 | 16MB | 🟢 |
| LilyGo T-Deck Pro | 16MB | 🟢 |
| LilyGo T-Deck | 16MB | 🟢 |
| LilyGo T-Display S3 | 16MB | 🟢 |
| LilyGo T-Display S3 Touch | 16MB | 🟢 |
| LilyGo T-Display S3 MMC | 16MB | 🟢 |
| LilyGo T-Display S3 Touch MMC | 16MB | 🟢 |
| LilyGo T-HMI | 16MB | 🟢 |
| LilyGo T-LoRa Pager | 16MB | 🟢 |
| LilyGo T-Watch S3 | 16MB | 🟢 |
| M5Stack Cardputer | 8MB | 🟢 |
| M5Stack CoreS3 | 16MB | 🟢 |
| M5Stack StickS3 | 16MB | 🟢 |
| ESP32-S3 DevKitC-1 | 16MB | 🟢 |
| Smoochiee Board | 16MB | 🟢 |
| **ESP32-C5** | | |
| ESP32-C5 | 4MB | 🟢 |
| ESP32-C5 TFT | 4MB | 🟢 |
| **ESP32 (LITE - 55 tools, reduced for 4MB/8MB)** | | |
| M5Stack Core 4MB | 4MB | 🟢 |
| M5Stack Core 16MB | 16MB | 🟢 |
| M5Stack CPlus 1.1 | 4MB | 🟢 |
| CYD-2432S028 | 4MB | 🟢 |
| CYD-2USB | 4MB | 🟢 |
| CYD-2432W328C | 4MB | 🟢 |
| CYD-2432W328R | 4MB | 🟢 |
| CYD-3248S035R | 4MB | 🟢 |
| CYD-3248S035C | 4MB | 🟢 |
| Elecrow 2.4B | 4MB | 🟢 |
| Elecrow 2.8B | 4MB | 🟢 |
| Elecrow 3.5B | 4MB | 🟢 |
| LilyGo T-Display TTGO | 4MB | 🟢 |
| Marauder Mini | 4MB | 🟢 |
| Marauder V4-V6 | 4MB | 🟢 |
| Marauder V7 | 4MB | 🟢 |
| Marauder V6.1 | 4MB | 🟢 |
| Awok Mini | 4MB | 🟢 |
| Awok Touch | 4MB | 🟢 |
| WaveSentry R1 | 4MB | 🟢 |
| Phantom S024R | 4MB | 🟢 |
| **Known Limitations** | | |
| M5Stack CPlus2 | - | 🔴 DRAM overflow |
| M5Stack Core2 | - | 🔴 DRAM overflow |

---

## Remote Dashboard

Arsenal > Dashboard. Connect to `ArsenalNet` (password: `arsenal32`). Open `192.168.4.1`.

- Start/stop all 55 tools from phone
- Browse/upload/delete files on SD card
- OTA firmware updates
- Drag-and-drop script upload

## Custom Combos

Create `.txt` in `/arsenal/combos/` with one feature per line:

```
mac_rotator
channel_hopper
decoy_traffic
ble_tracker
```

## SD Card Layout

```
/arsenal/
  badusb/       DuckyScript payloads (.txt)
  subghz/       Sub-GHz signal captures (.sub)
  ir/           IR remote files (.ir)
  portals/      Evil portal HTML templates
  nfc/          NFC card dumps (.nfc)
  rfid/         125kHz RFID captures (.rfid)
  scripts/      JavaScript automation (.js)
  combos/       Custom combo presets (.txt)
  logs/         Session logs
  creds.txt     Captured credentials
```

---

## Credits

- [Bruce Firmware](https://github.com/pr3y/Bruce) by pr3y
- Arsenal module by quietdom

## Disclaimer

For authorized security testing and educational purposes only.
