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

---

## Installation

1. Download the `.bin` from [Releases](../../releases)
2. Flash via [ESP Web Flasher](https://espressif.github.io/esptool-js/) (Chrome/Edge) or OTA via Arsenal Dashboard

---

## Arsenal Tools (72)

### WiFi Arsenal (11)

| Tool | Full | LITE |
|------|------|------|
| Network Scanner | ✅ | ✅ |
| DHCP Starvation | ✅ | ✅ |
| Karma Attack | ✅ | ✅ |
| DNS Spoofer | ✅ | ✅ |
| Auto-Phish Portal | ✅ | ✅ |
| Cred Forward | ✅ | ✅ |
| Auth Flood | ✅ | ✅ |
| AP Clone Flood | ✅ | ✅ |
| SSL Strip Lite | ✅ | ✅ |
| DNS Tunnel | ✅ | ✅ |
| WPS PIN Attack | ✅ | ✅ |

### BLE Arsenal (6)

| Tool | Full | LITE |
|------|------|------|
| BLE Tracker | ✅ | ✅ |
| BT Name Spammer | ✅ | ✅ |
| AirTag Spoofer | ✅ | ✅ |
| Audio Jammer | ✅ | ✅ |
| Notification Spoofer | ✅ | ✅ |
| BT Rickroll | ✅ | ✅ |

### Intelligence (8)

| Tool | Full | LITE |
|------|------|------|
| Device Fingerprinter | ✅ | ✅ |
| OPSEC Monitor | ✅ | ✅ |
| OUI Lookup | ✅ | ✅ |
| Probe Log | ✅ | ✅ |
| Banner Grabber | ✅ | ✅ |
| SmartHome Scan | ✅ | ✅ |
| Channel Chart | ✅ | ✅ |
| People Counter | ✅ | ✅ |

### Evasion (5)

| Tool | Full | LITE |
|------|------|------|
| MAC Rotator | ✅ | ✅ |
| Channel Hopper | ✅ | ✅ |
| Decoy Traffic | ✅ | ✅ |
| Identity Cloner | ✅ | ✅ |
| Time Randomizer | ✅ | ✅ |

### Phishing (4)

| Tool | Full | LITE |
|------|------|------|
| Win Update Phish | ✅ | ✅ |
| WiFi Speed Phish | ✅ | ✅ |
| OAuth Phish | ✅ | ✅ |
| Device Found Phish | ✅ | ✅ |

### Sub-GHz / RF (6)

| Tool | Full | LITE |
|------|------|------|
| NRF24 MouseJack | ✅ | ✅ |
| Doorbell Replay | ✅ | ✅ |
| Garage Brute Force | ✅ | ✅ |
| Keyfob Logger | ✅ | ✅ |
| Frequency Scanner | ✅ | ✅ |
| Flipper Import | ✅ | ✅ |

### Detection (3)

| Tool | Full | LITE |
|------|------|------|
| Flipper Detector | ✅ | ✅ |
| Hacker Detector | ✅ | ✅ |
| RF Silence Enforcer | ✅ | ✅ |

### Comms (5)

| Tool | Full | LITE |
|------|------|------|
| ESP-NOW Chat | ✅ | ✅ |
| ESP-NOW C2 | ✅ | ✅ |
| Dead Drop Mesh | ✅ | ✅ |
| IR Data Transfer | ✅ | ✅ |
| Multi-Device Sync | ✅ | ✅ |

### Utility (2)

| Tool | Full | LITE |
|------|------|------|
| NFC Biz Card | ✅ | ✅ |
| Attack Stats | ✅ | ✅ |

### Arsenal Core (5)

| Tool | Full | LITE |
|------|------|------|
| Jam All | ✅ | ✅ |
| Combos | ✅ | ✅ |
| Scheduler | ✅ | ✅ |
| Script Browser | ✅ | ✅ |
| Session Log | ✅ | ✅ |

---

## Board Compatibility

### ESP32-S3 (Full - all 72 tools)

| Board | Flash | Status |
|-------|-------|--------|
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

### ESP32-C5

| Board | Flash | Status |
|-------|-------|--------|
| ESP32-C5 | 4MB | 🟢 |
| ESP32-C5 TFT | 4MB | 🟢 |

### ESP32 (LITE - 31 tools, reduced for 4MB/8MB boards)

| Board | Flash | Status |
|-------|-------|--------|
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

### Known Limitations

| Board | Issue |
|-------|-------|
| M5Stack CPlus2 | DRAM overflow (core firmware globals) 🔴 |
| M5Stack Core2 | DRAM overflow (core firmware globals) 🔴 |

---

## Background Services

| Service | Description |
|---------|-------------|
| OPSEC Dot | Colored circle on status bar (green/yellow/red) |
| Always-On Evasion | MAC rotation + channel hopping + decoy traffic |
| Auto-Dim | Screen brightness drops during attacks |

---

## Remote Dashboard

Arsenal > Dashboard. Connect phone to `ArsenalNet` (password: `arsenal32`). Open `192.168.4.1`.

- Start/stop all 72 tools from phone
- Browse/upload/delete files on SD card
- OTA firmware updates
- Drag-and-drop script upload

---

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

## Custom Combos

Create `.txt` in `/arsenal/combos/` with one feature per line:

```
mac_rotator
channel_hopper
decoy_traffic
ble_tracker
```

---

## Languages

English, Portugues, Italiano, Francais, Russian, Chinese, Polski, Nederlands, Turkce, Deutsch, Tiếng Việt, Espanol, Indonesia, Arabic

---

## Credits

- [Bruce Firmware](https://github.com/pr3y/Bruce) by pr3y
- Arsenal module by quietdom
- Script collection: [BruceFlipperScripts](https://github.com/Unknown3613/BruceFlipperScripts)

---

## Disclaimer

For authorized security testing and educational purposes only. Do not use against networks or devices you don't own or have explicit permission to test.
