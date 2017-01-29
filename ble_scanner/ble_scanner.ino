/*********************************************************************************
  Copyright (c) 2017 ChedaDSP@Makers-NS. All right reserved.

  This is a simple example of BLE discovery on Intel Curie BLE processor.
  
  We will will scan for Tile device and read RSSI. 
  https://www.thetileapp.com/en-gb/how-it-works 
  
  To display RSSI we will use WS2811 and change the color of a snowman.
  When RSSI is low snowman will be blue (cold). When RSSI improves snowman becomes red (hot) :)
  
  Libraries and firmware used:
  
  BLE flashpack
  https://github.com/01org/corelibs-arduino101/releases/download/2.0.0/flashpack_ble_v3.tar.bz2
  intel-arduino-tools 1.8.0+1.29-windows Release
  https://github.com/01org/intel-arduino-tools/releases/tag/1.8.0%2B1.29-windows
  CurieBLE - Version: corelibs-arduino101-2.0.0
  https://github.com/01org/corelibs-arduino101/releases/tag/2.0.0
  Adafruit NeoPixel Library
  https://github.com/adafruit/Adafruit_NeoPixel

  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*****************************************************************************/ 

#include <CurieBLE.h>
#include <Adafruit_NeoPixel.h>

// We will try to dicsover and read RSSI this device name.
// Change these constants acording to expected RSSI range
String deviceName  = "Tile";
#define RSSI_MIN -80
#define RSSI_MAX -44

// We use Adafruit NeoPixel libdary to drive WS2811 LED strip.
int dataPin = 6;  // Arduino PWM data pin D6
int pixels = 1;   // number of WS2811 LEDs
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, dataPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);

  //WS2811 LED strip initialization
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  // BLE object is actually now defined in CurieBLE.h
  BLE.begin();
  // When device is discovered handle centralDiscovered() is called.
  BLE.setEventHandler(BLEDiscovered, centralDiscovered);
  Serial.println("Snowman starts scanning for " + deviceName + "!");
  BLE.scan(true);
}

void loop() 
{
  BLE.poll(); // This is BLE pulling loop. 
}

void centralDiscovered(BLEDevice peripheral) 
{
  if (peripheral.hasLocalName()) 
  {
    if (peripheral.localName().indexOf(deviceName) != -1) 
    {
      int devRSSI = peripheral.rssi();
      // Update WS2811 LED strip color based on RSSI
      int hottnes = map(devRSSI, RSSI_MIN, RSSI_MAX, 0, 255);
      hottnes = constrain(hottnes, 0, 255);
      uint32_t color = strip.Color(hottnes, 0, 255 - hottnes);
      for(uint16_t i=0; i<strip.numPixels(); i++)
      {
        strip.setPixelColor(i, color);
        strip.show();
      }

      Serial.print("Rssi: ");
      Serial.println(devRSSI);
      Serial.print("Hottnes: ");
      Serial.println(hottnes);
    }
    else
    {
      Serial.print("Lost!");
    }
  }
}
