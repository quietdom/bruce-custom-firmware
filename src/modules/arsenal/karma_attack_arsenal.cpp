// ═══════════════════════════════════════════════════════════
// Arsenal - Karma Attack (wrapper)
// Launches Bruce's existing karma attack from Arsenal menu
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "modules/wifi/karma_attack.h"
#include <globals.h>

void arsenal_karma_attack(void) {
    ARSENAL_SAFE_RUN([]() {
        karma_setup();
    });
}
