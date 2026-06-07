#ifndef __ARSENAL_DASHBOARD_H__
#define __ARSENAL_DASHBOARD_H__

#include <Arduino.h>

// Arsenal Remote Web Dashboard
// Serves a mobile-friendly web UI for controlling Arsenal features
// Includes OTA firmware update capability

void arsenal_dashboard_start(void);
void arsenal_dashboard_stop(void);
bool arsenal_dashboard_is_active(void);

// OTA
void arsenal_ota_handle_upload(void);

#endif
