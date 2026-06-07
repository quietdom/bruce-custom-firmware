#ifndef __ARSENAL_H__
#define __ARSENAL_H__

#include <globals.h>
#include <esp_task_wdt.h>
#include "core/utils.h"

// ═══════════════════════════════════════════════════════════
// Arsenal Module - Master header
// All feature entry points declared here
// ═══════════════════════════════════════════════════════════

// Crash-safety wrapper - wraps feature entry points
// Checks heap before running, catches exceptions
#define ARSENAL_SAFE_RUN(func)                                    \
    do {                                                          \
        if (ESP.getFreeHeap() < 20000) {                          \
            Serial.println("[Arsenal] Low memory, aborting.");     \
            displayRedStripe("Low memory!", TFT_WHITE, TFT_RED);  \
            delay(1500);                                          \
            return;                                               \
        }                                                         \
        func();                                                   \
    } while (0)

// WiFi Arsenal
void arsenal_network_scanner(void);
void arsenal_dhcp_starvation(void);
void arsenal_karma_attack(void);
void arsenal_dns_spoofer(void);
void arsenal_captive_portal_templates(void);
void arsenal_captive_portal_autophish(void);
void arsenal_wifi_bruteforce(void);
void arsenal_cred_forward(void);

// BLE Arsenal
void arsenal_ble_tracker(void);
void arsenal_bt_name_spammer(void);
void arsenal_airtag_spoofer(void);
void arsenal_bt_audio_jammer(void);
void arsenal_sms_notification_spoofer(void);

// Intelligence
void arsenal_device_fingerprinter(void);
void arsenal_opsec_monitor(void);
void arsenal_oui_lookup(void);

// Evasion
void arsenal_mac_rotator(void);
void arsenal_channel_hopper(void);
void arsenal_decoy_traffic(void);
void arsenal_identity_cloner(void);
void arsenal_qr_poisoner(void);

// Nuclear
void arsenal_jam_all(void);

// Dashboard
void arsenal_remote_dashboard(void);

// Script Browser
void arsenal_script_browser(void);

// WiFi Brute Force
void arsenal_wifi_bruteforce(void);

// Attack Scheduler
void arsenal_attack_scheduler(void);

// Session Log
void arsenal_log_start(void);
void arsenal_log_event(const char *category, const char *message);
void arsenal_log_event(const char *category, String message);
void arsenal_log_stop(void);
void arsenal_session_log_menu(void);

// Auto Dim
void arsenal_dim_on_attack(void);
void arsenal_dim_restore(void);
void arsenal_auto_dim_toggle(void);
bool arsenal_auto_dim_is_enabled(void);
bool arsenal_is_dimmed(void);

// Combo Presets (from arsenal_background.h)
// arsenal_combo_menu() is declared in arsenal_background.h

#endif
