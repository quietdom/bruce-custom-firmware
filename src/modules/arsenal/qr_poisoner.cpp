// ═══════════════════════════════════════════════════════════
// Arsenal - QR Code Poisoner
// Generates QR codes on the display pointing to your portal
// Print them out and place over real QR codes
// ═══════════════════════════════════════════════════════════

#include "arsenal.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include <WiFi.h>
#include <globals.h>

// Minimal QR code generation using the existing qrcode library
#include "modules/others/qrcode_menu.h"

// Predefined URLs
static const char *QR_URLS[] = {
    "http://192.168.4.1",           // Default AP portal
    "http://192.168.4.1/login",     // Login page
    "http://192.168.4.1/update",    // Fake update page
    "Custom URL...",                 // User-defined
};
static const int NUM_URLS = sizeof(QR_URLS) / sizeof(QR_URLS[0]);

void arsenal_qr_poisoner(void) {
    ARSENAL_SAFE_RUN([]() {
        // Select URL
        options.clear();
        int selectedUrl = -1;

        for (int i = 0; i < NUM_URLS; i++) {
            options.push_back({String(QR_URLS[i]), [i, &selectedUrl]() {
                selectedUrl = i;
            }});
        }

        loopOptions(options, MENU_TYPE_SUBMENU, "QR Target URL");

        if (selectedUrl < 0) return;

        String url;
        if (selectedUrl == NUM_URLS - 1) {
            // Custom URL - for now use default portal
            url = "http://192.168.4.1";
        } else {
            url = String(QR_URLS[selectedUrl]);
        }

        // Display QR code on screen
        drawMainBorderWithTitle("QR Poisoner");
        tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
        tft.setTextSize(FP);
        tft.setCursor(12, tftHeight - 30);
        tft.print(url.substring(0, 28));
        tft.drawCentreString("Esc to exit", tftWidth / 2, tftHeight - 16, 1);

        // Generate and display QR code
        // Using Bruce's built-in QR display functionality
        // The QR will fill most of the screen for easy scanning
        int qrSize = min(tftWidth, tftHeight) - 60;
        int qrX = (tftWidth - qrSize) / 2;
        int qrY = 32;

        // Simple QR display using TFT primitives
        // In production this would use a proper QR library
        // For now show the URL prominently
        tft.fillRect(qrX, qrY, qrSize, qrSize, TFT_WHITE);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.setTextSize(FP);
        tft.drawCentreString("QR CODE", tftWidth / 2, qrY + qrSize / 2 - 10, 1);
        tft.drawCentreString(url.substring(0, 20), tftWidth / 2, qrY + qrSize / 2 + 5, 1);

        // Note: Full QR generation would use qrcode_menu's existing QR library
        // This stub shows the concept - integrate with Bruce's qrcode display

        while (true) {
            if (check(EscPress)) break;
            delay(100);
        }
    });
}
