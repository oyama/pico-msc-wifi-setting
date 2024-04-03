# Example of WI-FI setup with USB mass storage class for Raspberry Pi Pico W

This project shows an example of setting up WI-FI for Raspberry Pi Pico W via a USB Mass storage class file.
The file system, which mimics FAT12, hooks access into the `WIFI.TXT` file for reading and writing to PICO's flash memory.

## Build

```
git clone https://github.com/raspberrypi/pico-sdk.git --branch master
cd pico-sdk; git submodule update --init; cd ..
mkdir build
cd build
cmake ..
make
```

Now you have `msc_wifi_setting.uf2` and can drag and drop it onto your Raspberry Pi Pico to install and run it.
