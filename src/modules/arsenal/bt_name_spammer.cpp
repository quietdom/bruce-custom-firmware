// ═══════════════════════════════════════════════════════════
// Arsenal - Bluetooth Name Spammer
// Floods BLE advertisements with random/funny device names
// Nearby devices see hundreds of phantom Bluetooth devices
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <BLEAdvertising.h>
#include <BLEDevice.h>
#include <globals.h>

// NimBLE random address function
extern "C" int ble_hs_id_set_rnd(const uint8_t *rnd_addr);

// Funny/meme device names
static const char *SPAM_NAMES[] = {
    "FBI Surveillance Van #3",
    "NSA_PRISM_Node_7",
    "Putin's iPhone",
    "Area 51 Guest WiFi",
    "COVID-5G-Tower",
    "Your Mom's iPad",
    "Free Candy Van BT",
    "Hack Me If You Can",
    "Bill Gates Chip v2",
    "DROP TABLE devices;--",
    "Not A Virus Trust Me",
    "Illuminati HQ",
    "Skynet Core Node",
    "CIA Black Site #42",
    "Elon's Neuralink",
    "Hidden Camera #7",
    "Police Stingray",
    "DEA Monitoring",
    "Anonymous Member",
    "Witness Protection",
    "Time Traveler Phone",
    "Alien Mothership",
    "Matrix Backdoor",
    "Batcave Network",
    "Decepticon Relay",
    "HYDRA Base Alpha",
    "Bruce Was Here",
    "ur wifi is mine lol",
    "Hack In Progress...",
    "GET OUT OF MY SWAMP",
};
static const int NUM_NAMES = sizeof(SPAM_NAMES) / sizeof(SPAM_NAMES[0]);

void arsenal_bt_name_spammer(void) {
    ARSENAL_SAFE_RUN([]() {
        BLEDevice::init("");
        BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

        int nameIndex = 0;
        int totalSent = 0;
        unsigned long startTime = millis();

        while (true) {
            // Set device name and advertise
            BLEAdvertisementData advData;
            BLEAdvertisementData scanRespData;

            const char *name = SPAM_NAMES[nameIndex % NUM_NAMES];
            advData.setName(name);
            advData.setFlags(0x06);  // General discoverable + BR/EDR not supported

            pAdvertising->setAdvertisementData(advData);
            pAdvertising->setScanResponseData(scanRespData);

            // Randomize address for each advertisement
            uint8_t addr[6];
            for (int i = 0; i < 6; i++) addr[i] = random(256);
            addr[0] |= 0xC0;  // random static address type
            BLEDevice::getAdvertising()->stop();
            // NimBLE random address
            ble_hs_id_set_rnd(addr);

            pAdvertising->start();
            delay(50);  // Short burst
            pAdvertising->stop();

            totalSent++;
            nameIndex++;

            // Draw UI every few packets
            if (totalSent % 5 == 0) {
                drawMainBorderWithTitle("Name Spammer");
                int y = 45;
                int padX = 12;

                tft.setTextColor(TFT_MAGENTA, bruceConfig.bgColor);
                tft.setTextSize(FP);
                tft.setCursor(padX, y);
                tft.print("SPAMMING BLE NAMES");
                y += 16;

                tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
                tft.setCursor(padX, y);
                tft.printf("Names sent: %d", totalSent);
                y += 14;

                unsigned long elapsed = (millis() - startTime) / 1000;
                tft.setCursor(padX, y);
                tft.printf("Elapsed: %lus", elapsed);
                y += 14;

                tft.setCursor(padX, y);
                tft.printf("Rate: ~%d/sec", totalSent / max(1UL, elapsed));
                y += 18;

                tft.setTextColor(TFT_YELLOW, bruceConfig.bgColor);
                tft.setCursor(padX, y);
                String currentName = String(name).substring(0, 24);
                tft.print(">" + currentName);

                tft.setTextColor(TFT_RED, bruceConfig.bgColor);
                tft.drawCentreString("Esc to stop", tftWidth / 2, tftHeight - 20, 1);
            }

            if (check(EscPress)) break;
            esp_task_wdt_reset();
            delay(20);
        }

        pAdvertising->stop();
        BLEDevice::deinit(false);
    });
}
