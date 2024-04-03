cmake_minimum_required(VERSION 3.13)
if(NOT PICO_SDK_PATH) 
  set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/pico-sdk)
endif()

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)


project(msc_wifi_setting_project C CXX ASM)

set(PICO_BOARD pico_w)
set(FAMILY rp2040)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


pico_sdk_init()
set(LWIP_DIR ${PICO_SDK_PATH}/lib/lwip/)
set(LWIP_INCLUDE_DIRS
    "${LWIP_DIR}/src/include"
    "${LWIP_DIR}/contrib"
)

add_executable(msc_wifi_setting
  main.c
  msc_disk.c
  usb_descriptors.c
  wifi_setting.c
)
target_include_directories(msc_wifi_setting PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../)
target_link_libraries(msc_wifi_setting
  pico_stdlib
  pico_cyw43_arch_none
  pico_cyw43_arch_lwip_threadsafe_background
  tinyusb_additions
  tinyusb_board
  tinyusb_device
  hardware_flash
  hardware_sync
)

pico_enable_stdio_usb(msc_wifi_setting 1)
pico_add_extra_outputs(msc_wifi_setting)
