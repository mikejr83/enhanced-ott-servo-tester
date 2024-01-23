
#include <Adafruit_SSD1351.h>

#include "Settings.h"

#include "AppConfig.h"
#include "DisplayOps.h"
#ifndef SUPPRESS_SPLASH
#include "SplashImageData.h"
#endif

void drawCenteredLineTextString(Adafruit_SSD1351 &oled, const char *buf, int x, int y);

void drawCenteredScreenTextString(Adafruit_GFX &oled, const char *buf, int x, int y);

void PrintSplashScreen(AppConfig &appConfig, Adafruit_SSD1351 &oled)
{
    oled.fillRect(0, 0, 128, 128, BLACK);
    delay(250);

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

void PrintMode(Adafruit_SSD1351 &oled, const char *modeBuf)
{
    char buf[30];
    String a(modeBuf);
    strcpy(buf, "Mode: ");
    strcat(buf, modeBuf);

    drawCenteredLineTextString(oled, buf, 0, 0);
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