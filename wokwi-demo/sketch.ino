// Arsenal Demo - Wokwi Simulation
// ESP32-S3 + SSD1306 OLED + 4 navigation buttons

#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SDA_PIN 8
#define SCL_PIN 9

// Button pins
#define BTN_UP    4
#define BTN_DOWN  5
#define BTN_SEL   6
#define BTN_BACK  7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Menu state
int menuIndex = 0;
int currentScreen = 0;  // 0=main menu, 1=wifi, 2=ble, 3=intel, 4=evasion, 5=jamall, 6=opsec, 7=ble tracker

// Debounce
unsigned long lastPress = 0;
const int debounceDelay = 200;

// Main menu
const char* mainMenu[] = {
  "WiFi Arsenal",
  "BLE Arsenal",
  "Intelligence",
  "Evasion",
  "Combos",
  "Jam All",
  "OPSEC Monitor",
  "BLE Tracker"
};
const int mainMenuCount = 8;

// WiFi submenu
const char* wifiMenu[] = {
  "Network Scanner",
  "DHCP Starvation",
  "Karma Attack",
  "DNS Spoofer",
  "Portal Templates",
  "Auto-Phish",
  "Cred Forward",
  "WiFi Brute Force",
  "<< Back"
};
const int wifiMenuCount = 9;

// BLE submenu
const char* bleMenu[] = {
  "BLE Tracker",
  "Name Spammer",
  "AirTag Spoofer",
  "Audio Jammer",
  "Notif Spoofer",
  "<< Back"
};
const int bleMenuCount = 6;

// Intel submenu
const char* intelMenu[] = {
  "Fingerprinter",
  "OPSEC Monitor",
  "OUI Lookup",
  "<< Back"
};
const int intelMenuCount = 4;

// Evasion submenu
const char* evasionMenu[] = {
  "MAC Rotator",
  "Channel Hopper",
  "Decoy Traffic",
  "Identity Cloner",
  "QR Poisoner",
  "<< Back"
};
const int evasionMenuCount = 6;

bool btnPressed(int pin) {
  if (digitalRead(pin) == LOW && millis() - lastPress > debounceDelay) {
    lastPress = millis();
    return true;
  }
  return false;
}

void drawMenu(const char* title, const char** items, int count, int selected) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Header
  display.setCursor(0, 0);
  display.print(title);
  // OPSEC dot
  display.fillCircle(122, 4, 3, SSD1306_WHITE);
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  // Items (show 5 visible)
  int startIdx = selected > 2 ? selected - 2 : 0;
  if (startIdx + 5 > count) startIdx = count - 5;
  if (startIdx < 0) startIdx = 0;

  for (int i = 0; i < 5 && (startIdx + i) < count; i++) {
    int idx = startIdx + i;
    int y = 13 + i * 10;

    if (idx == selected) {
      display.fillRect(0, y, 128, 10, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.setCursor(4, y + 1);
    display.print(items[idx]);
  }

  // Footer
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 56);
  display.print("UP/DN:nav SEL:enter");
  display.display();
}

void drawJamAll() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("JAM ALL       00:42");
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);

  const char* bands[] = {"WiFi 2.4", "BLE", "Sub-GHz", "NRF24"};
  bool active[] = {true, true, true, false};

  for (int i = 0; i < 4; i++) {
    int y = 12 + i * 12;
    display.setCursor(0, y);
    display.print(bands[i]);

    int barX = 55;
    int barW = 50;
    display.drawRect(barX, y, barW, 8, SSD1306_WHITE);
    if (active[i]) {
      int fill = random(20, barW - 2);
      display.fillRect(barX + 1, y + 1, fill, 6, SSD1306_WHITE);
    }

    display.setCursor(110, y);
    display.print(active[i] ? "ON" : "--");
  }

  display.setCursor(25, 56);
  display.print("[BACK] STOP ALL");
  display.display();
}

void drawOpsec() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(20, 0);
  display.print("OPSEC: CLEAR");
  display.drawCircle(10, 4, 4, SSD1306_WHITE);
  display.fillCircle(10, 4, 2, SSD1306_WHITE);
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  display.setCursor(0, 14);  display.print("Deauths at us:  0");
  display.setCursor(0, 24);  display.print("Probe floods:   0");
  display.setCursor(0, 34);  display.print("Directed probes:0");
  display.setCursor(0, 44);  display.print("Anomalies:      0");

  display.setCursor(0, 56);  display.print("[BACK] You're safe");
  display.display();
}

void drawBLETracker() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(25, 0);
  display.print("BLE TRACKER");
  display.drawLine(0, 9, 128, 9, SSD1306_WHITE);

  // Radar
  int cx = 64, cy = 36;
  display.drawCircle(cx, cy, 8, SSD1306_WHITE);
  display.drawCircle(cx, cy, 16, SSD1306_WHITE);
  display.drawCircle(cx, cy, 24, SSD1306_WHITE);

  // Crosshair
  display.drawLine(cx - 26, cy, cx + 26, cy, SSD1306_WHITE);
  display.drawLine(cx, cy - 26, cx, cy + 26, SSD1306_WHITE);

  // Devices
  display.fillCircle(cx + 6, cy - 4, 2, SSD1306_WHITE);
  display.fillCircle(cx - 12, cy + 8, 2, SSD1306_WHITE);
  display.fillCircle(cx + 20, cy + 2, 2, SSD1306_WHITE);
  display.fillCircle(cx - 5, cy - 18, 2, SSD1306_WHITE);

  // Center (you)
  display.fillRect(cx - 1, cy - 1, 3, 3, SSD1306_WHITE);

  display.setCursor(0, 56);
  display.print("4 devices [BACK]");
  display.display();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_SEL, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 failed!");
    while (true);
  }

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Boot splash
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 8);
  display.print("ARSENAL");
  display.setTextSize(1);
  display.setCursor(20, 32);
  display.print("T-Embed CC1101");
  display.setCursor(25, 48);
  display.print("26 features");
  display.display();
  delay(2000);

  currentScreen = 0;
  menuIndex = 0;
  drawMenu("ARSENAL", mainMenu, mainMenuCount, menuIndex);
}

void loop() {
  // Navigation
  if (btnPressed(BTN_UP)) {
    menuIndex--;
    if (menuIndex < 0) menuIndex = 0;
    redraw();
  }

  if (btnPressed(BTN_DOWN)) {
    int maxIdx = getMenuCount() - 1;
    menuIndex++;
    if (menuIndex > maxIdx) menuIndex = maxIdx;
    redraw();
  }

  if (btnPressed(BTN_SEL)) {
    handleSelect();
  }

  if (btnPressed(BTN_BACK)) {
    if (currentScreen != 0) {
      currentScreen = 0;
      menuIndex = 0;
      redraw();
    }
  }

  delay(10);
}

int getMenuCount() {
  switch (currentScreen) {
    case 0: return mainMenuCount;
    case 1: return wifiMenuCount;
    case 2: return bleMenuCount;
    case 3: return intelMenuCount;
    case 4: return evasionMenuCount;
    default: return mainMenuCount;
  }
}

void redraw() {
  switch (currentScreen) {
    case 0: drawMenu("ARSENAL", mainMenu, mainMenuCount, menuIndex); break;
    case 1: drawMenu("WiFi Arsenal", wifiMenu, wifiMenuCount, menuIndex); break;
    case 2: drawMenu("BLE Arsenal", bleMenu, bleMenuCount, menuIndex); break;
    case 3: drawMenu("Intelligence", intelMenu, intelMenuCount, menuIndex); break;
    case 4: drawMenu("Evasion", evasionMenu, evasionMenuCount, menuIndex); break;
    case 5: drawJamAll(); break;
    case 6: drawOpsec(); break;
    case 7: drawBLETracker(); break;
  }
}

void handleSelect() {
  if (currentScreen == 0) {
    // Main menu selections
    switch (menuIndex) {
      case 0: currentScreen = 1; menuIndex = 0; break;  // WiFi
      case 1: currentScreen = 2; menuIndex = 0; break;  // BLE
      case 2: currentScreen = 3; menuIndex = 0; break;  // Intel
      case 3: currentScreen = 4; menuIndex = 0; break;  // Evasion
      case 4: // Combos
        display.clearDisplay();
        display.setCursor(0, 0); display.print("COMBOS");
        display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
        display.setCursor(0, 14); display.print("> Stealth Mode");
        display.setCursor(0, 24); display.print("  Full Attack");
        display.setCursor(0, 34); display.print("  Passive Recon");
        display.setCursor(0, 44); display.print("  + Create New");
        display.setCursor(0, 56); display.print("[BACK]");
        display.display();
        currentScreen = 99;
        return;
      case 5: currentScreen = 5; break;  // Jam All
      case 6: currentScreen = 6; break;  // OPSEC
      case 7: currentScreen = 7; break;  // BLE Tracker
    }
    redraw();
  } else if (currentScreen >= 1 && currentScreen <= 4) {
    // Check if "Back" selected
    int count = getMenuCount();
    if (menuIndex == count - 1) {
      currentScreen = 0;
      menuIndex = 0;
      redraw();
    } else {
      // Show "running" feedback
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(20, 25);
      display.print("Running...");
      display.setCursor(10, 40);
      const char** menu;
      switch(currentScreen) {
        case 1: menu = wifiMenu; break;
        case 2: menu = bleMenu; break;
        case 3: menu = intelMenu; break;
        case 4: menu = evasionMenu; break;
        default: menu = mainMenu;
      }
      display.print(menu[menuIndex]);
      display.display();
      delay(1500);
      redraw();
    }
  }
}
