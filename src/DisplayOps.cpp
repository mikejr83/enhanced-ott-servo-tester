
#include <Adafruit_SSD1351.h>

#include "Settings.h"

#include "AppConfig.h"
#include "DisplayOps.h"
#ifndef SUPPRESS_SPLASH
#include "SplashImageData.h"
#endif
#include "RunMode.h"

void drawCenteredLineTextString(Adafruit_SSD1351 &oled, const char *buf, int x, int y);
void drawCenteredScreenTextString(Adafruit_GFX &oled, const char *buf, int x, int y);
void printModeTitle(Adafruit_SSD1351 &oled, const char *titleBuf);
void printServoPositions(Adafruit_SSD1351 &oled, SystemData &data, ServoData *servoData);

void ClearScreen(Adafruit_SSD1351 &oled)
{
    oled.fillScreen(BLACK);
    delay(250);
}

void PrintSplashScreen(AppConfig &appConfig, Adafruit_SSD1351 &oled)
{
    ClearScreen(oled);

    if (appConfig.data.showSplash && appConfig.data.splashDisplayTime <= MAX_SPLASH_DISPLAYTIME)
    {
        PRINT("\nShowing splash screen and title for a total time of: ", appConfig.data.splashDisplayTime)
#ifndef SUPPRESS_SPLASH
        oled.drawRGBBitmap(0, 0, (const uint16_t *)logoSplash.pixel_data, 128, 128);
        delay(appConfig.data.splashDisplayTime / 2);
        oled.fillScreen(BLACK);
#endif
        PrintTitleScreen(oled);
        delay(appConfig.data.splashDisplayTime / 2);
        oled.fillScreen(BLACK);
    }
}

void PrintTitleScreen(Adafruit_SSD1351 &oled)
{
    oled.setCursor(0, 0);
    oled.setTextColor(BLUE);
    oled.setTextSize(2);
    drawCenteredLineTextString(oled, "Enhanced", 0, 0);
    oled.setTextColor(WHITE);
    drawCenteredLineTextString(oled, "Over", 0, 20);
    drawCenteredLineTextString(oled, "The Top", 0, 40);
    oled.setTextColor(RED);
    drawCenteredLineTextString(oled, "Servo", 0, 60);
    drawCenteredLineTextString(oled, "Tester", 0, 80);
}

void PrintMode(Adafruit_SSD1351 &oled, AppConfig &appConfig, RunMode runMode, ServoData *servoData)
{
    // print the title first
    printModeTitle(oled, RunModeToString(runMode));

    switch (runMode)
    {
    case RUN_MANUAL:
    case RUN_MANUAL_INIT:

        break;

    default:
        break;
    }

    printServoPositions(oled, appConfig.data, servoData);
}

void drawCenteredLineTextString(Adafruit_SSD1351 &oled, const char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    oled.getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calc width of new string
    oled.setCursor((SCREEN_WIDTH - w) / 2, y);
    oled.print(buf);
}

void drawCenteredScreenTextString(Adafruit_SSD1351 &oled, const char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    oled.getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calc width of new string
    oled.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2);
    oled.print(buf);
}

void printModeTitle(Adafruit_SSD1351 &oled, const char *titleBuf)
{
    oled.setTextColor(GREEN);
    oled.setTextSize(2);

    drawCenteredLineTextString(oled, titleBuf, 0, 0);
}

void printServoPositions(Adafruit_SSD1351 &oled, SystemData &data, ServoData *servoData)
{
    ServoData enabledServos[MAX_SERVO];
    int totalEnabled = 0;
    for (int i = 0; i < MAX_SERVO; i++)
    {
        if (data.servo[i].enabled)
        {
            enabledServos[totalEnabled++] = servoData[i];
        }
    }

    double perRow = 2;
    int rows = ceil(totalEnabled / perRow);
    int baseOffset = (128 - rows * 9) - 3;

    // oled.drawRect(0, baseOffset - 2, SCREEN_WIDTH, 128 - baseOffset, BLACK);
    for (int i = 0; i < rows; i++)
    {
        String lineOfText = "";
        for (int j = i * perRow; j < (i * perRow + perRow) && j < totalEnabled; j++)
        {
            lineOfText.append((char)(65 + j));
            lineOfText.append(": ");
            lineOfText.append(enabledServos[j].curV);
            lineOfText.append("ms ");
        }

        PRINT("Line: ", lineOfText);

        char buf[lineOfText.length()];
        lineOfText.toCharArray(buf, lineOfText.length());

        oled.setTextColor(WHITE, BLACK);
        oled.setTextSize(1);

        int y = baseOffset + i * 9;
        drawCenteredLineTextString(oled, buf, 0, y);
    }
}