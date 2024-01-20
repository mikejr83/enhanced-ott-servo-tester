#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <ArduinoLog.h>

#include "Settings.h"
#include "SplashImageData.h"
#include "TextPrinter.h"

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

uint32_t lastCheck = 0;



void setup(void)
{
  Serial.begin(115200);

#ifndef DISABLE_LOGGING
  Log.begin(LOG_LEVEL, &Serial);
#endif

  oled.begin();

  Serial.println("init");

  // You can optionally rotate the display by running the line below.
  // Note that a value of 0 means no rotation, 1 means 90 clockwise,
  // 2 means 180 degrees clockwise, and 3 means 270 degrees clockwise.
  // oled.setRotation(1);
  // NOTE: The test pattern at the start will NOT be rotated!  The code
  // for rendering the test pattern talks directly to the display and
  // ignores any rotation.

  uint16_t time = millis();
  oled.fillRect(0, 0, 128, 128, BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  oled.drawRGBBitmap(0, 0, (const uint16_t *)logoSplash.pixel_data, 128, 128);
  delay(2500);
  oled.fillScreen(BLACK);
  pintTitleScreen(oled);
  delay(2500);

  oled.fillScreen(BLACK);
}

void loop()
{

  Serial.println("done");
  delay(1000);
}