?? [English](../README.md) | [Portugues](README_PT.md) | [Italiano](README_IT.md) | [Francais](README_FR.md) | [Russian](README_RU.md) | [Chinese](README_ZH.md) | [Polski](README_PL.md) | [Nederlands](README_NL.md) | [Turkce](README_TR.md) | [Deutsch](README_DE.md) | [Vietnamese](README_VN.md) | [Espanol](README_ES.md) | [Indonesia](README_ID.md) | [Arabic](README_AR.md)

<h1 align="center">?? Bruce Arsenal</h1>

<p align="center">
  <b>Aangepaste offensieve beveiligingsfirmware voor ESP32-apparaten</b><br>
  <i>72 tools - Eén firmware - Meerdere apparaten</i>
</p>

---

## Wat Is Dit

Een gemodificeerde Bruce Firmware met een aangepaste Arsenal-module - 72 offensieve beveiligingstoegangen vanuit één menu.

---

## Installatie

1. Download de .bin vanuit Releases
2. Flash via ESP Web Flasher (Chrome/Edge) of OTA via Arsenal Dashboard

---

## Arsenal Tools (72)

### WiFi Arsenal (11)
Network Scanner, DHCP Starvation, Karma Attack, DNS Spoofer, Auto-Phish Portal, Cred Forward, Auth Flood, AP Clone Flood, SSL Strip Lite, DNS Tunnel, WPS PIN Attack

### BLE Arsenal (6)
BLE Tracker, BT Name Spammer, AirTag Spoofer, Audio Jammer, Notification Spoofer, BT Rickroll

### Intelligentie (8)
Device Fingerprinter, OPSEC Monitor, OUI Lookup, Probe Log, Banner Grabber, SmartHome Scan, Channel Chart, People Counter

### Ontsnapping (5)
MAC Rotator, Channel Hopper, Decoy Traffic, Identity Cloner, Time Randomizer

### Phishing (4)
Win Update Phish, WiFi Speed Phish, OAuth Phish, Device Found Phish

### Sub-GHz / RF (6)
NRF24 MouseJack, Doorbell Replay, Garage Brute Force, Keyfob Logger, Frequency Scanner, Flipper Import

### Detectie (3)
Flipper Detector, Hacker Detector, RF Silence Enforcer

### Communicatie (5)
ESP-NOW Chat, ESP-NOW C2, Dead Drop Mesh, IR Data Transfer, Multi-Device Sync

### Hulpprogramma's (2)
NFC Biz Card, Attack Stats

---

## Board Compatibiliteit

### ESP32-S3 (Volledig - 72 tools)
LilyGo T-Embed CC1101, T-Deck Pro, T-Deck, T-Display S3, T-HMI, T-LoRa Pager, T-Watch S3, M5Stack Cardputer, CoreS3, StickS3

### ESP32 (LITE - 31 tools)
M5Stack Core 4MB/16MB, CPlus 1.1, CYD (all variants), Elecrow, Marauder, Awok, WaveSentry, Phantom

### Bekende Beperkingen
M5Stack CPlus2, M5Stack Core2 - DRAM overflow (kern firmware variabelen)

---

## Achtergronddiensten

- **OPSEC Dot** - Kleurrijke cirkel op de statusbalk
- **Always-On Evasion** - MAC-rotatie + kanaalsprong + afleidingsverkeer
- **Auto-Dim** - Schermhelderheid daalt tijdens aanvallen

---

## Remote Dashboard

Arsenal > Dashboard. Verbind telefoon met ArsenalNet (wachtwoord: arsenal32). Open 192.168.4.1.

---

## Credits

- [Bruce Firmware](https://github.com/pr3y/Bruce) by pr3y
- Arsenal module by quietdom

---

## Alleen voor geautoriseerde beveiligingstests en educatieve doeleinden.