#ifndef __ARSENAL_MENU_H__
#define __ARSENAL_MENU_H__

#include "MenuItemInterface.h"

class ArsenalMenu : public MenuItemInterface {
public:
    ArsenalMenu() : MenuItemInterface("Arsenal") {}

    void optionsMenu(void);
    void drawIcon(float scale);

    // Submenus
    void wifiArsenalMenu(void);
    void bleArsenalMenu(void);
    void intelligenceMenu(void);
    void evasionMenu(void);
    void jamAllMenu(void);
    void dashboardMenu(void);

    bool hasTheme() { return false; }
    String themePath() { return ""; }
};

#endif
