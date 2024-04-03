#include "wifi_setting.h"
#include <stdio.h>
#include "pico/stdlib.h"


const uint32_t FLASH_TARGET_OFFSET = 0x1F0000;

bool wifisetting_read(wifi_setting_t *setting) {
    const uint8_t *data = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);
    memcpy(setting, data, sizeof(wifi_setting_t));
    return memcmp(setting->magic, WIFI_SETTING_MAGIC, sizeof(setting->magic)) == 0;
}


void wifisetting_write(wifi_setting_t *setting) {
    uint8_t buffer[FLASH_PAGE_SIZE];

    printf("wifisetting_write(\"%s\", \"%s\")\n", setting->ssid, setting->password);
    memcpy(setting->magic, WIFI_SETTING_MAGIC, sizeof(setting->magic));
    memcpy(buffer, setting, sizeof(wifi_setting_t));

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, buffer, FLASH_PAGE_SIZE);
    restore_interrupts(ints);
}
