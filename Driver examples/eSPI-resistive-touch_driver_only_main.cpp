#include <Arduino.h>

#include "SPI.h"
#include "TouchScreen.h"
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

#define YP 26  // must be an analog pin, use "An" notation!
#define XM 25  // must be an analog pin, use "An" notation!
#define YM 32   // can be a digital pin
#define XP 33   // can be a digital pin

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one I am using, its 340 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 340);

void setup() {
  Serial.begin(9600);
  Serial.println("hELLO");

  tft.begin();
  tft.fillScreen(0xffff);
  delay(500);
  tft.fillScreen(0x0000);
  delay(200);
  tft.fillScreen(ILI9341_RED);
  delay(200);
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