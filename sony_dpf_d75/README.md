
# Description

 Sony DPF-D75 is digital photo frame. This repository contain
 dumps, tools, scripts and sources, that may help someone hack this thing.

 CPU archeticture is MIPS32 little endian. frame uses ThreadX RTOS,
 libtiff that vulnurable to cve-2012-5581, lua interpretator.

 Frame have 2MB spi flash, that contain first stage firmware.
 then there is nand storage it too contain firmware that is newer.
 DRAM 256K, located at address 0xA0000000 probably.
 Screen resolution 768x480.

 There fat12 filesystem on SPI flash dump.
 lua files can be extracted from '.lar' files using python scripts.
 lua files compiled. use 'tools/luadec' to decompile.

 Have functional UART console. Easy to find it UART connector.
 just not soldered 4 pin connector, solder it and then use cheap USB-TTL
 convertors to communicate with frame. baudrate **115200**.

 FW version: 1.26.1.11

# Programming
 You can run custom code on this thing, by loading images from sd card by
 using UART console.
 In order to compile source code use `mipsel-linux-gnu-gcc`

 ### type
    - `cd D:/` - set current directory to SD card storage.
    - `read patch.bin 0x80141c18` - overwrite code in clockinfo command
    - `read program.bin 0x802a0000` - free space address
    - `clockinfo` - trigger code execution
