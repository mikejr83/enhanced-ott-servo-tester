#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#include "AppConfig.h"
#include "ModeHandler.h"

class Display
{
private:
    RunMode lastRunMode = RunMode::RUN_MANUAL_INIT;
    ManualModeSubMode lastManualSubMode = ManualModeSubMode::HOLD_POSITION;
    void printModeTitle(const char *titleBuf);
    void printServoPositions();

protected:
    Adafruit_SSD1351 oled;
    AppConfig appConfig;
    ServoData *servoData;

public:
    static void DrawCenteredLineTextString(Adafruit_SSD1351 &oled, const char *buf, int x, int y);

    Display(Adafruit_SSD1351 &oled, AppConfig &appConfig, ServoData *servoData);

    void ClearScreen();

    void PrintSplashScreen();
    void PrintTitleScreen();

    void PrintMode(RunMode runMode, ManualModeSubMode manualSubMode);
};