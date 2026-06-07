#ifndef __ARSENAL_BACKGROUND_H__
#define __ARSENAL_BACKGROUND_H__

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════
// Arsenal Background Services
// Runs persistent background tasks:
//   - OPSEC monitoring (global status dot)
//   - Always-on evasion (MAC rotate + channel hop + decoy)
//   - Combo presets (user-defined attack chains)
// ═══════════════════════════════════════════════════════════

// OPSEC threat levels
enum ArsenalOpsecLevel {
    OPSEC_CLEAR = 0,    // Green
    OPSEC_CAUTION = 1,  // Yellow
    OPSEC_DANGER = 2    // Red
};

// Global state accessible from anywhere
extern volatile ArsenalOpsecLevel g_opsecLevel;
extern volatile bool g_arsenalEvasionActive;
extern volatile bool g_arsenalLowPowerMode;
extern volatile int g_arsenalDeauthsDetected;
extern volatile int g_arsenalCredsCapture;

// Background task control
void arsenal_background_start(void);
void arsenal_background_stop(void);
bool arsenal_background_is_running(void);

// Draw the OPSEC dot on the status bar (called from drawStatusBar)
void arsenal_draw_opsec_dot(void);

// Evasion toggle (always-on mode)
void arsenal_evasion_toggle(void);
bool arsenal_evasion_is_active(void);

// Combo presets
void arsenal_combo_menu(void);

#endif
