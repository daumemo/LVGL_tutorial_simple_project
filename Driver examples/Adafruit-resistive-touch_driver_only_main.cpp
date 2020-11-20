#include <Arduino.h>

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include "Adafruit_SPIDevice.h"
#include "TouchScreen.h"

#define _cs   17  // goes to TFT CS
#define _dc   16  // goes to TFT DC
#define _mosi 23  // goes to TFT MOSI
#define _sclk 18  // goes to TFT SCK/CLK
#define _rst  5   // goes to TFT RESET

// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341((int8_t)_cs, (int8_t)_dc, _mosi, _sclk, (int8_t)_rst);

#define YP 26  // Y+ pin
#define XM 25  // X- pin (actually connected to X+ pin)
#define YM 32  // Y- pin
#define XP 33  // X+ pin (actually connected to X- pin)

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one I am using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 340);

void setup() {
  Serial.begin(9600);
  Serial.println("HELLO");

  tft.begin();
  tft.fillScreen(0xffff);
  delay(500);
  tft.fillScreen(0x0000);
  delay(500);
  tft.fillScreen(ILI9341_RED);
  delay(500);
  tft.fillScreen(ILI9341_GREEN);

  tft.setRotation(0);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println("Hello World!");
  analogReadResolution(10);
}

void loop() {
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
     Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
  }

  delay(100);
}