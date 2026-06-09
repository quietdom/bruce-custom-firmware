?? [English](../README.md) | [Portugues](README_PT.md) | [Italiano](README_IT.md) | [Francais](README_FR.md) | [Russian](README_RU.md) | [Chinese](README_ZH.md) | [Polski](README_PL.md) | [Nederlands](README_NL.md) | [Turkce](README_TR.md) | [Deutsch](README_DE.md) | [Vietnamese](README_VN.md) | [Espanol](README_ES.md) | [Indonesia](README_ID.md) | [Arabic](README_AR.md)

<h1 align="center">?? Bruce Arsenal</h1>

<p align="center">
  <b>Firmware di sicurezza offensiva personalizzato per dispositivi ESP32</b><br>
  <i>72 strumenti - Un firmware - Dispositivi multipli</i>
</p>

---

## Cos'E

Una versione modificata di Bruce Firmware con un modulo Arsenal personalizzato - 72 strumenti di sicurezza offensiva accessibili da un singolo menu.

---

## Installazione

1. Scarica il .bin dai Releases
2. Flasha tramite ESP Web Flasher (Chrome/Edge) o OTA via Arsenal Dashboard

---

## Strumenti Arsenal (72)

### WiFi Arsenal (11)
Network Scanner, DHCP Starvation, Karma Attack, DNS Spoofer, Auto-Phish Portal, Cred Forward, Auth Flood, AP Clone Flood, SSL Strip Lite, DNS Tunnel, WPS PIN Attack

### BLE Arsenal (6)
BLE Tracker, BT Name Spammer, AirTag Spoofer, Audio Jammer, Notification Spoofer, BT Rickroll

### Intelligenza (8)
Device Fingerprinter, OPSEC Monitor, OUI Lookup, Probe Log, Banner Grabber, SmartHome Scan, Channel Chart, People Counter

### Evasione (5)
MAC Rotator, Channel Hopper, Decoy Traffic, Identity Cloner, Time Randomizer

### Phishing (4)
Win Update Phish, WiFi Speed Phish, OAuth Phish, Device Found Phish

### Sub-GHz / RF (6)
NRF24 MouseJack, Doorbell Replay, Garage Brute Force, Keyfob Logger, Frequency Scanner, Flipper Import

### Rilevamento (3)
Flipper Detector, Hacker Detector, RF Silence Enforcer

### Comunicazioni (5)
ESP-NOW Chat, ESP-NOW C2, Dead Drop Mesh, IR Data Transfer, Multi-Device Sync

### Utilita (2)
NFC Biz Card, Attack Stats

---

## Compatibilita Schede

### ESP32-S3 (Completo - 72 strumenti)
LilyGo T-Embed CC1101, T-Deck Pro, T-Deck, T-Display S3, T-HMI, T-LoRa Pager, T-Watch S3, M5Stack Cardputer, CoreS3, StickS3

### ESP32 (LITE - 31 strumenti)
M5Stack Core 4MB/16MB, CPlus 1.1, CYD (all variants), Elecrow, Marauder, Awok, WaveSentry, Phantom

### Limitazioni Noti
M5Stack CPlus2, M5Stack Core2 - Overflow DRAM (variabili globali firmware core)

---

## Servizi in Secondo Piano

- **OPSEC Dot** - Cerchio colorato nella barra di stato
- **Always-On Evasion** - Rotazione MAC + salto canali + traffico esca
- **Auto-Dim** - Luminosita schermo si riduce durante gli attacchi

---

## Pannello Remoto

Arsenal > Dashboard. Collega il telefono a ArsenalNet (password: arsenal32). Apri 192.168.4.1.

---

## Crediti

- [Bruce Firmware](https://github.com/pr3y/Bruce) by pr3y
- Arsenal module by quietdom

---

## Solo per test di sicurezza autorizzati e scopi educativi.