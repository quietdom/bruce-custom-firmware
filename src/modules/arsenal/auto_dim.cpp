// ═══════════════════════════════════════════════════════════
// Arsenal - Auto Dim on Attack
// Reduces screen brightness when any attack is active
// Restores when attacks stop — harder to spot in the field
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "arsenal_background.h"
#include "core/display.h"
#include <globals.h>

static bool autoDimEnabled = true;
static int originalBrightness = -1;
static const int DIM_BRIGHTNESS = 10;  // very dim (0-255 scale)
static bool currentlyDimmed = false;

// Call this when an attack starts
void arsenal_dim_on_attack(void) {
    if (!autoDimEnabled) return;
    if (currentlyDimmed) return;

    originalBrightness = currentScreenBrightness;
    analogWrite(TFT_BL, DIM_BRIGHTNESS);
    currentScreenBrightness = DIM_BRIGHTNESS;
    currentlyDimmed = true;
}

// Call this when attacks stop
void arsenal_dim_restore(void) {
    if (!currentlyDimmed) return;
    if (originalBrightness > 0) {
        analogWrite(TFT_BL, originalBrightness);
        currentScreenBrightness = originalBrightness;
    }
    currentlyDimmed = false;
}

// Toggle auto-dim feature
void arsenal_auto_dim_toggle(void) {
    autoDimEnabled = !autoDimEnabled;
    if (!autoDimEnabled && currentlyDimmed) {
        arsenal_dim_restore();
    }
}

bool arsenal_auto_dim_is_enabled(void) {
    return autoDimEnabled;
}

bool arsenal_is_dimmed(void) {
    return currentlyDimmed;
}
