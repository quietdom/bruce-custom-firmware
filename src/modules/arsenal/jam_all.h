#ifndef __ARSENAL_JAM_ALL_H__
#define __ARSENAL_JAM_ALL_H__

#include <Arduino.h>

// Band identifiers for Jam All
enum JamBand {
    JAM_WIFI_24 = 0,
    JAM_BLE,
    JAM_SUBGHZ,
    JAM_NRF24,
    JAM_BAND_COUNT
};

struct JamBandState {
    const char *name;
    bool enabled;
    bool available;  // hardware present?
    bool active;     // currently jamming?
    uint8_t level;   // activity level 0-10 for visualization
};

struct JamAllState {
    JamBandState bands[JAM_BAND_COUNT];
    unsigned long startTime;
    unsigned long timeout;      // auto-stop after this many ms (0 = no timeout)
    int selectedBand;           // currently highlighted band in GUI
    bool running;
};

void jamall_init(JamAllState &state);
void jamall_draw_gui(JamAllState &state);
void jamall_start_band(JamAllState &state, JamBand band);
void jamall_stop_band(JamAllState &state, JamBand band);
void jamall_start_all(JamAllState &state);
void jamall_stop_all(JamAllState &state);
void jamall_update(JamAllState &state);

#endif
