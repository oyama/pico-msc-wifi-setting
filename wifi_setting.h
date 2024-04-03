#ifndef _WIFI_SETTING_H
#define _WIFI_SETTING_H

#include <string.h>
#include <hardware/flash.h>
#include <hardware/sync.h>

#define WIFI_SETTING_MAGIC "WIFI"

typedef struct {
    uint8_t magic[4];
    uint8_t ssid[33];
    uint8_t password[64];
} wifi_setting_t;


bool wifisetting_read(wifi_setting_t *setting);
void wifisetting_write(wifi_setting_t *setting);

#endif
