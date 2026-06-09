?? [English](../README.md) | [Portugues](README_PT.md) | [Italiano](README_IT.md) | [Francais](README_FR.md) | [Russian](README_RU.md) | [Chinese](README_ZH.md) | [Polski](README_PL.md) | [Nederlands](README_NL.md) | [Turkce](README_TR.md) | [Deutsch](README_DE.md) | [Vietnamese](README_VN.md) | [Espanol](README_ES.md) | [Indonesia](README_ID.md) | [Arabic](README_AR.md)

<h1 align="center">?? Bruce Arsenal</h1>

<p align="center">
  <b>Firmware keamanan ofensif khusus untuk perangkat ESP32</b><br>
  <i>72 alat - Satu firmware - Beberapa perangkat</i>
</p>

---

## Apa Ini

Versi modifikasi dari Bruce Firmware dengan模ules Arsenal khusus - 72 alat keamanan ofensif yang dapat diakses dari satu menu.

---

## Instalasi

1. Unduh .bin dari Releases
2. Flash via ESP Web Flasher (Chrome/Edge) atau OTA via Arsenal Dashboard

---

## Alat Arsenal (72)

### WiFi Arsenal (11)
Network Scanner, DHCP Starvation, Karma Attack, DNS Spoofer, Auto-Phish Portal, Cred Forward, Auth Flood, AP Clone Flood, SSL Strip Lite, DNS Tunnel, WPS PIN Attack

### BLE Arsenal (6)
BLE Tracker, BT Name Spammer, AirTag Spoofer, Audio Jammer, Notification Spoofer, BT Rickroll

### Intelijen (8)
Device Fingerprinter, OPSEC Monitor, OUI Lookup, Probe Log, Banner Grabber, SmartHome Scan, Channel Chart, People Counter

### Evasion (5)
MAC Rotator, Channel Hopper, Decoy Traffic, Identity Cloner, Time Randomizer

### Phishing (4)
Win Update Phish, WiFi Speed Phish, OAuth Phish, Device Found Phish

### Sub-GHz / RF (6)
NRF24 MouseJack, Doorbell Replay, Garage Brute Force, Keyfob Logger, Frequency Scanner, Flipper Import

### Deteksi (3)
Flipper Detector, Hacker Detector, RF Silence Enforcer

### Komunikasi (5)
ESP-NOW Chat, ESP-NOW C2, Dead Drop Mesh, IR Data Transfer, Multi-Device Sync

### Utilitas (2)
NFC Biz Card, Attack Stats

---

## Kompatibilitas Papan

### ESP32-S3 (Lengkap - 72 alat)
LilyGo T-Embed CC1101, T-Deck Pro, T-Deck, T-Display S3, T-HMI, T-LoRa Pager, T-Watch S3, M5Stack Cardputer, CoreS3, StickS3

### ESP32 (LITE - 31 alat)
M5Stack Core 4MB/16MB, CPlus 1.1, CYD (all variants), Elecrow, Marauder, Awok, WaveSentry, Phantom

### Keterbatasan yang Diketahui
M5Stack CPlus2, M5Stack Core2 - DRAM overflow (variabel global firmware core)

---

## Layanan Latar Belakang

- **OPSEC Dot** - Lingkaran berwarna di bilah status
- **Always-On Evasion** - Rotasi MAC + lompat kanal + lalu lintas umpan
- **Auto-Dim** - Kecerahan layar menurun selama serangan

---

## Dashboard Remote

Arsenal > Dashboard. Hubungkan telepon ke ArsenalNet (sandiran: arsenal32). Buka 192.168.4.1.

---

## Kredit

- [Bruce Firmware](https://github.com/pr3y/Bruce) by pr3y
- Arsenal module by quietdom

---

## Hanya untuk pengujian keamanan yang diizinkan dan tujuan pendidikan.