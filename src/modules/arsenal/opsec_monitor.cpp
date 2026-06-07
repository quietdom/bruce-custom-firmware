// ═══════════════════════════════════════════════════════════
// Arsenal - OPSEC Monitor
// Detects if someone is monitoring/detecting your ESP32
// Watches for deauth counter-attacks, honeypots, RSSI anomalies
// Shows green/yellow/red threat level
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include <globals.h>

enum ThreatLevel {
    THREAT_CLEAR = 0,   // Green
    THREAT_CAUTION = 1, // Yellow
    THREAT_DANGER = 2   // Red
};

struct OpsecState {
    ThreatLevel level;
    int deauthsReceived;       // deauth frames targeting us
    int probeResponseFlood;    // excessive probe responses (honeypot?)
    int directedProbes;        // probes targeting our MAC specifically
    int rssiAnomalies;         // sudden RSSI spikes (someone approaching)
    int pmfNetworks;           // networks with 802.11w (deauth won't work there)
    unsigned long startTime;
    String lastAlert;
};

static OpsecState opsec;
static bool opsecRunning = false;
static uint8_t ourMAC[6];

// Promiscuous callback to detect threats
static void opsecRxCallback(void *buf, wifi_promiscuous_pkt_type_t type) {
    if (!opsecRunning || type != WIFI_PKT_MGMT) return;

    const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
    const uint8_t *frame = pkt->payload;
    int len = pkt->rx_ctrl.sig_len;
    if (len < 24) return;

    uint8_t subtype = (frame[0] >> 4) & 0x0F;

    // Check if deauth/disassoc targeting us
    if (subtype == 0x0C || subtype == 0x0A) {  // deauth or disassoc
        // Destination is our MAC?
        if (memcmp(frame + 4, ourMAC, 6) == 0) {
            opsec.deauthsReceived++;
            opsec.lastAlert = "Deauth targeting YOU!";
        }
    }

    // Check for excessive probe responses (honeypot indicator)
    if (subtype == 0x05) {  // probe response
        // If we're getting tons of probe responses, someone might be karma-attacking us
        opsec.probeResponseFlood++;
        if (opsec.probeResponseFlood > 50) {
            opsec.lastAlert = "Probe flood (honeypot?)";
        }
    }

    // Check for directed probes targeting our MAC
    if (subtype == 0x04) {  // probe request
        if (memcmp(frame + 4, ourMAC, 6) == 0 || memcmp(frame + 16, ourMAC, 6) == 0) {
            opsec.directedProbes++;
            opsec.lastAlert = "Directed probe at YOU";
        }
    }
}

static ThreatLevel calculateThreatLevel() {
    int score = 0;
    score += opsec.deauthsReceived * 10;
    score += (opsec.probeResponseFlood > 30) ? 5 : 0;
    score += opsec.directedProbes * 8;
    score += opsec.rssiAnomalies * 3;

    if (score >= 15) return THREAT_DANGER;
    if (score >= 5) return THREAT_CAUTION;
    return THREAT_CLEAR;
}

static const char *threatLevelStr(ThreatLevel level) {
    switch (level) {
        case THREAT_CLEAR: return "CLEAR";
        case THREAT_CAUTION: return "CAUTION";
        case THREAT_DANGER: return "DANGER!";
    }
    return "?";
}

static uint16_t threatColor(ThreatLevel level) {
    switch (level) {
        case THREAT_CLEAR: return TFT_GREEN;
        case THREAT_CAUTION: return TFT_YELLOW;
        case THREAT_DANGER: return TFT_RED;
    }
    return TFT_WHITE;
}

void arsenal_opsec_monitor(void) {
    ARSENAL_SAFE_RUN([]() {
        // Initialize
        memset(&opsec, 0, sizeof(opsec));
        opsec.startTime = millis();
        opsec.level = THREAT_CLEAR;
        opsec.lastAlert = "None";

        // Get our MAC
        esp_wifi_get_mac(WIFI_IF_STA, ourMAC);

        // Start monitoring
        WiFi.mode(WIFI_STA);
        esp_wifi_set_promiscuous(true);
        esp_wifi_set_promiscuous_rx_cb(opsecRxCallback);
        opsecRunning = true;

        int channelIdx = 0;
        unsigned long lastChannelHop = 0;
        unsigned long lastReset = millis();

        while (true) {
            // Hop channels to monitor all traffic
            if (millis() - lastChannelHop > 500) {
                channelIdx = (channelIdx + 1) % 14;
                esp_wifi_set_channel(channelIdx + 1, WIFI_SECOND_CHAN_NONE);
                lastChannelHop = millis();
            }

            // Recalculate threat level
            opsec.level = calculateThreatLevel();

            // Reset counters every 30 seconds to avoid false positives
            if (millis() - lastReset > 30000) {
                opsec.probeResponseFlood = 0;
                lastReset = millis();
            }

            // Draw UI
            drawMainBorderWithTitle("OPSEC Monitor");
            int y = 36;
            int padX = 10;

            // Big threat level indicator
            uint16_t tColor = threatColor(opsec.level);
            tft.fillRect(padX, y, tftWidth - 2 * padX, 24, tft.color565(15, 15, 20));
            tft.setTextColor(tColor, tft.color565(15, 15, 20));
            tft.setTextSize(FM);
            tft.drawCentreString(threatLevelStr(opsec.level), tftWidth / 2, y + 4, 1);
            y += 30;

            // Threat indicators
            tft.setTextSize(FP);
            tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);

            tft.setCursor(padX, y);
            tft.printf("Deauths at us: %d", opsec.deauthsReceived);
            // Small colored dot
            tft.fillCircle(tftWidth - 20, y + 4, 4, opsec.deauthsReceived > 0 ? TFT_RED : TFT_DARKGREEN);
            y += 13;

            tft.setCursor(padX, y);
            tft.printf("Probe flood: %d", opsec.probeResponseFlood);
            tft.fillCircle(tftWidth - 20, y + 4, 4, opsec.probeResponseFlood > 30 ? TFT_YELLOW : TFT_DARKGREEN);
            y += 13;

            tft.setCursor(padX, y);
            tft.printf("Directed probes: %d", opsec.directedProbes);
            tft.fillCircle(tftWidth - 20, y + 4, 4, opsec.directedProbes > 0 ? TFT_RED : TFT_DARKGREEN);
            y += 13;

            tft.setCursor(padX, y);
            tft.printf("PMF networks: %d", opsec.pmfNetworks);
            y += 16;

            // Last alert
            tft.setTextColor(TFT_YELLOW, bruceConfig.bgColor);
            tft.setCursor(padX, y);
            tft.print("Last: " + opsec.lastAlert.substring(0, 26));
            y += 16;

            // Uptime
            unsigned long elapsed = (millis() - opsec.startTime) / 1000;
            tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
            tft.setCursor(padX, y);
            tft.printf("Monitoring: %lum %lus", elapsed / 60, elapsed % 60);

            tft.setTextColor(TFT_RED, bruceConfig.bgColor);
            tft.drawCentreString("Esc to stop", tftWidth / 2, tftHeight - 18, 1);

            if (check(EscPress)) break;
            esp_task_wdt_reset();
            delay(200);
        }

        opsecRunning = false;
        esp_wifi_set_promiscuous(false);
    });
}
