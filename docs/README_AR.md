?? [English](../README.md) | [Portugues](README_PT.md) | [Italiano](README_IT.md) | [Francais](README_FR.md) | [Russian](README_RU.md) | [Chinese](README_ZH.md) | [Polski](README_PL.md) | [Nederlands](README_NL.md) | [Turkce](README_TR.md) | [Deutsch](README_DE.md) | [Vietnamese](README_VN.md) | [Espanol](README_ES.md) | [Indonesia](README_ID.md) | [Arabic](README_AR.md)

<h1 align="center">?? Bruce Arsenal</h1>

<p align="center">
  <b>برنامج مخصص لأمن الهجوم لأجهزة ESP32</b><br>
  <i>72 أداة - برنامج واحد - أجهزة متعددة</i>
</p>

---

## ما هذا

نسخة معدلة من Bruce Firmware مع وحدة Arsenal مخصصة - 72 أداة أمن هجومية متاحة من قائمة واحدة.

---

## التثبيت

1. قم بتنزيل .bin من Releases
2.  flashed عبر ESP Web Flasher أو OTA عبر Arsenal Dashboard

---

## أدوات Arsenal (72)

### WiFi Arsenal (11)
Network Scanner, DHCP Starvation, Karma Attack, DNS Spoofer, Auto-Phish Portal, Cred Forward, Auth Flood, AP Clone Flood, SSL Strip Lite, DNS Tunnel, WPS PIN Attack

### BLE Arsenal (6)
BLE Tracker, BT Name Spammer, AirTag Spoofer, Audio Jammer, Notification Spoofer, BT Rickroll

### الاستخبارات (8)
Device Fingerprinter, OPSEC Monitor, OUI Lookup, Probe Log, Banner Grabber, SmartHome Scan, Channel Chart, People Counter

### الهروب (5)
MAC Rotator, Channel Hopper, Decoy Traffic, Identity Cloner, Time Randomizer

### التصيد (4)
Win Update Phish, WiFi Speed Phish, OAuth Phish, Device Found Phish

### Sub-GHz / RF (6)
NRF24 MouseJack, Doorbell Replay, Garage Brute Force, Keyfob Logger, Frequency Scanner, Flipper Import

### الكشف (3)
Flipper Detector, Hacker Detector, RF Silence Enforcer

### الاتصالات (5)
ESP-NOW Chat, ESP-NOW C2, Dead Drop Mesh, IR Data Transfer, Multi-Device Sync

### الأدوات المساعدة (2)
NFC Biz Card, Attack Stats

---

## توافق الألواح

### ESP32-S3 (كامل - 72 أدوات)
LilyGo T-Embed CC1101, T-Deck Pro, T-Deck, T-Display S3, T-HMI, T-LoRa Pager, T-Watch S3, M5Stack Cardputer, CoreS3, StickS3

### ESP32 (LITE - 31 أدوات)
M5Stack Core 4MB/16MB, CPlus 1.1, CYD (all variants), Elecrow, Marauder, Awok, WaveSentry, Phantom

### قيود معروفة
M5Stack CPlus2, M5Stack Core2 - فيضان DRAM (متغيرات البرنامج الأساسي)

---

## الخدمات الخلفية

- **OPSEC Dot** - دائرة ملونة على شريط الحالة
- **Always-On Evasion** - تدوير MAC + قفز القنوات + حركة المرور الخداعية
- **Auto-Dim** - تقل سطوع الشاشة أثناء الهجمات

---

## لوحة التحكم

Arsenal > Dashboard. اتصل الهاتف بـ ArsenalNet (كلمة المرور: arsenal32). افتح 192.168.4.1.

---

## الاعتمادات

- [Bruce Firmware](https://github.com/pr3y/Bruce) by pr3y
- Arsenal module by quietdom

---

## لأغراض اختبار الأمان المصرح بها والتعليم فقط.