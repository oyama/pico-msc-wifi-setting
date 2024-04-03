#ifndef _WIFI_SETTING_H
#define _WIFI_SETTING_H

#include <hardware/flash.h>
#include <hardware/sync.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>


#define WIFI_SETTING_MAGIC "WIFI"

typedef struct {
    uint8_t magic[4];
    uint8_t ssid[33];
    uint8_t password[64];
} wifi_setting_t;


/*
 * Read Wi-Fi configuration information from onboard flash memory.
 * Returns false if the memory area is not initialized.
 */
bool wifisetting_read(wifi_setting_t *setting);

/*
 * Write Wi-Fi configuration information to flash memory.
 */
void wifisetting_write(wifi_setting_t *setting);

/*
 * Parse configuration text file buffer and retrieve configuration information.
 */
bool wifisetting_parse(wifi_setting_t *setting, const uint8_t *buffer, size_t buffer_len);

/*
 * Encode the configuration structure into a text file
 */
void wifisetting_encode(uint8_t *buffer, wifi_setting_t *setting);

#endif
