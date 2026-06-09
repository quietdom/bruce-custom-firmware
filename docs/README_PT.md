?? [English](../README.md) | [Portugues](README_PT.md) | [Italiano](README_IT.md) | [Francais](README_FR.md) | [Russian](README_RU.md) | [Chinese](README_ZH.md) | [Polski](README_PL.md) | [Nederlands](README_NL.md) | [Turkce](README_TR.md) | [Deutsch](README_DE.md) | [Vietnamese](README_VN.md) | [Espanol](README_ES.md) | [Indonesia](README_ID.md) | [Arabic](README_AR.md)

<h1 align="center">?? Bruce Arsenal</h1>

<p align="center">
  <b>Firmware de seguranca ofensiva customizado para dispositivos ESP32</b><br>
  <i>72 ferramentas - Um firmware - Multiplos dispositivos</i>
</p>

---

## O Que E Isto

Uma versao modificada do Bruce Firmware com um modulo Arsenal personalizado - 72 ferramentas de seguranca ofensiva acessiveis a partir de um unico menu.

---

## Instalacao

1. Baixe o .bin dos Releases
2. Flashe via ESP Web Flasher (Chrome/Edge) ou OTA via Arsenal Dashboard

---

## Ferramentas Arsenal (72)

### WiFi Arsenal (11)
Network Scanner, DHCP Starvation, Karma Attack, DNS Spoofer, Auto-Phish Portal, Cred Forward, Auth Flood, AP Clone Flood, SSL Strip Lite, DNS Tunnel, WPS PIN Attack

### BLE Arsenal (6)
BLE Tracker, BT Name Spammer, AirTag Spoofer, Audio Jammer, Notification Spoofer, BT Rickroll

### Inteligencia (8)
Device Fingerprinter, OPSEC Monitor, OUI Lookup, Probe Log, Banner Grabber, SmartHome Scan, Channel Chart, People Counter

### Evasao (5)
MAC Rotator, Channel Hopper, Decoy Traffic, Identity Cloner, Time Randomizer

### Phishing (4)
Win Update Phish, WiFi Speed Phish, OAuth Phish, Device Found Phish

### Sub-GHz / RF (6)
NRF24 MouseJack, Doorbell Replay, Garage Brute Force, Keyfob Logger, Frequency Scanner, Flipper Import

### Deteccao (3)
Flipper Detector, Hacker Detector, RF Silence Enforcer

### Comunicacoes (5)
ESP-NOW Chat, ESP-NOW C2, Dead Drop Mesh, IR Data Transfer, Multi-Device Sync

### Utilidades (2)
NFC Biz Card, Attack Stats

---

## Compatibilidade de Placas

### ESP32-S3 (Completo - 72 ferramentas)
LilyGo T-Embed CC1101, T-Deck Pro, T-Deck, T-Display S3, T-HMI, T-LoRa Pager, T-Watch S3, M5Stack Cardputer, CoreS3, StickS3

### ESP32 (LITE - 31 ferramentas)
M5Stack Core 4MB/16MB, CPlus 1.1, CYD (all variants), Elecrow, Marauder, Awok, WaveSentry, Phantom

### Limitacoes Conhecidas
M5Stack CPlus2, M5Stack Core2 - Overflow de DRAM (globais do firmware core)

---

## Servicos em Segundo Plano

- **OPSEC Dot** - Circulo colorido na barra de status
- **Always-On Evasion** - Rotacao MAC + salto de canais + trafego isca
- **Auto-Dim** - Brilho da tela diminui durante ataques

---

## Painel Remoto

Arsenal > Dashboard. Conecte o telefone ao ArsenalNet (senha: arsenal32). Abra 192.168.4.1.

---

## Creditos

- [Bruce Firmware](https://github.com/pr3y/Bruce) by pr3y
- Arsenal module by quietdom

---

## Apenas para testes de seguranca autorizados e fins educacionais.