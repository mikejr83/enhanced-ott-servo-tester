#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#include "RunMode.h"

void PrintSplashScreen(AppConfig &appConfig, Adafruit_SSD1351 &oled);
void PrintTitleScreen(Adafruit_SSD1351 &oled);

void PrintMode(Adafruit_SSD1351 &oled, AppConfig &appConfig, RunMode runMode, ServoData *servoData);
