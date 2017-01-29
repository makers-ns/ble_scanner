# Arduino/Genuino 101 BLE Scanner
This is a simple example of BLE discovery on Intel Curie processor - Arduino/Genuino 101

We will will scan for Tile device and read RSSI. 
To display RSSI we will use WS2811 and change the color of a snowman.

When RSSI is low snowman will be blue (cold). When RSSI improves snowman becomes red (hot) :)
 
## Libraries and firmware used:
For this software lates Curie library and firmer is used. Make sure that you have everithing updated.
Follow this tutorial - https://www.hackster.io/Hulkco/upgrading-the-firmware-library-of-arduino-101-4d6b10
  
### BLE flashpack
https://github.com/01org/corelibs-arduino101/releases/download/2.0.0/flashpack_ble_v3.tar.bz2
### intel-arduino-tools 1.8.0+1.29-windows Release
https://github.com/01org/intel-arduino-tools/releases/tag/1.8.0%2B1.29-windows
### CurieBLE: corelibs-arduino101-2.0.0
https://github.com/01org/corelibs-arduino101/releases/tag/2.0.0

### Adafruit NeoPixel Library
https://github.com/adafruit/Adafruit_NeoPixel
