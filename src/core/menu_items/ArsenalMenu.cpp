#include "ArsenalMenu.h"
#include "core/display.h"
#include "core/utils.h"
#include "modules/arsenal/arsenal.h"
#include "modules/arsenal/arsenal_background.h"

void ArsenalMenu::optionsMenu() {
    options = {
        {"WiFi Arsenal",   [this]() { wifiArsenalMenu(); }  },
        {"BLE Arsenal",    [this]() { bleArsenalMenu(); }   },
        {"Intelligence",   [this]() { intelligenceMenu(); } },
        {"Evasion",        [this]() { evasionMenu(); }      },
        {"Combos",         arsenal_combo_menu                },
        {"Scheduler",      arsenal_attack_scheduler          },
        {"Scripts",        arsenal_script_browser            },
        {"Session Log",    arsenal_session_log_menu          },
        {"Jam All",        arsenal_jam_all                   },
        {"Dashboard",      arsenal_remote_dashboard         },
    };

    // Auto-start background OPSEC monitoring on first Arsenal visit
    if (!arsenal_background_is_running()) {
        arsenal_background_start();
    }

    addOptionToMainMenu();
    loopOptions(options, MENU_TYPE_SUBMENU, "Arsenal");
}

void ArsenalMenu::wifiArsenalMenu() {
    options = {
        {"Network Scanner",    arsenal_network_scanner          },
        {"DHCP Starvation",    arsenal_dhcp_starvation          },
        {"Karma Attack",       arsenal_karma_attack             },
        {"DNS Spoofer",        arsenal_dns_spoofer              },
        {"Portal Templates",   arsenal_captive_portal_templates },
        {"Auto-Phish Portal",  arsenal_captive_portal_autophish },
        {"Cred Forward",       arsenal_cred_forward             },
        {"WiFi Brute Force",   arsenal_wifi_bruteforce          },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "WiFi Arsenal");
}

void ArsenalMenu::bleArsenalMenu() {
    options = {
        {"BLE Tracker",        arsenal_ble_tracker              },
        {"Name Spammer",       arsenal_bt_name_spammer          },
        {"AirTag Spoofer",     arsenal_airtag_spoofer           },
        {"Audio Jammer",       arsenal_bt_audio_jammer          },
        {"Notif Spoofer",      arsenal_sms_notification_spoofer },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "BLE Arsenal");
}

void ArsenalMenu::intelligenceMenu() {
    options = {
        {"Fingerprinter",      arsenal_device_fingerprinter     },
        {"OPSEC Monitor",      arsenal_opsec_monitor            },
        {"OUI Lookup",         arsenal_oui_lookup               },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Intelligence");
}

void ArsenalMenu::evasionMenu() {
    options = {
        {"MAC Rotator",        arsenal_mac_rotator              },
        {"Channel Hopper",     arsenal_channel_hopper           },
        {"Decoy Traffic",      arsenal_decoy_traffic            },
        {"Identity Cloner",    arsenal_identity_cloner          },
        {"QR Poisoner",        arsenal_qr_poisoner              },
        {"Back",               [this]() { optionsMenu(); }      },
    };
    loopOptions(options, MENU_TYPE_SUBMENU, "Evasion");
}

void ArsenalMenu::jamAllMenu() {
    arsenal_jam_all();
}

void ArsenalMenu::dashboardMenu() {
    arsenal_remote_dashboard();
}

void ArsenalMenu::drawIcon(float scale) {
    clearIconArea();

    // Crosshair/target icon - unique to Arsenal
    int r1 = scale * 22;  // outer ring
    int r2 = scale * 14;  // inner ring
    int r3 = scale * 4;   // center dot
    int lineLen = scale * 28;

    // Outer ring
    tft.drawCircle(iconCenterX, iconCenterY, r1, bruceConfig.priColor);
    // Inner ring
    tft.drawCircle(iconCenterX, iconCenterY, r2, bruceConfig.priColor);
    // Center dot
    tft.fillCircle(iconCenterX, iconCenterY, r3, bruceConfig.priColor);

    // Crosshair lines
    // Top
    tft.drawLine(iconCenterX, iconCenterY - lineLen, iconCenterX, iconCenterY - r1 - 2, bruceConfig.priColor);
    // Bottom
    tft.drawLine(iconCenterX, iconCenterY + r1 + 2, iconCenterX, iconCenterY + lineLen, bruceConfig.priColor);
    // Left
    tft.drawLine(iconCenterX - lineLen, iconCenterY, iconCenterX - r1 - 2, iconCenterY, bruceConfig.priColor);
    // Right
    tft.drawLine(iconCenterX + r1 + 2, iconCenterY, iconCenterX + lineLen, iconCenterY, bruceConfig.priColor);
}
