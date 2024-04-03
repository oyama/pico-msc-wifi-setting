#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>

#include <bsp/board.h>
#include <tusb.h>

#include "wifi_setting.h"


void wifi_task(void) {
    int status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
    if (status == CYW43_LINK_UP) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    } else if (status == CYW43_LINK_DOWN || status == CYW43_LINK_NONET || status == CYW43_LINK_BADAUTH) {
        wifi_setting_t wifi_setting;
        if (!wifisetting_read(&wifi_setting)) {
            // init wifi setting
            strncpy(wifi_setting.ssid, "SET_SSID", sizeof(wifi_setting.ssid));
            strncpy(wifi_setting.password, "SET_PASSWORD", sizeof(wifi_setting.password));
            wifisetting_write(&wifi_setting);
        }
        printf("Wi-Fi connect: %s\n", wifi_setting.ssid);
        int rc = cyw43_arch_wifi_connect_async(wifi_setting.ssid, wifi_setting.password, CYW43_AUTH_WPA2_AES_PSK);
        if (rc != PICO_OK) {
            printf("wifi_connect_async fail rc=%d\n", rc);
        }
    }
}

int main() {
    board_init();
    tud_init(BOARD_TUD_RHPORT);
    cyw43_arch_init();
    stdio_init_all();

    cyw43_arch_enable_sta_mode();
    while (true) {
         wifi_task();
         tud_task();
         cyw43_arch_poll();
    }
    cyw43_arch_deinit();
}
