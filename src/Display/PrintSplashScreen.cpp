#include "Display.h"

#ifndef SUPPRESS_SPLASH
#include "SplashImageData.h"
#endif

void Display::PrintSplashScreen()
{
    ClearScreen();

    if (appConfig.data.showSplash && appConfig.data.splashDisplayTime <= MAX_SPLASH_DISPLAYTIME)
    {
        PRINT("\nShowing splash screen and title for a total time of: ", appConfig.data.splashDisplayTime)
#ifndef SUPPRESS_SPLASH
        oled.drawRGBBitmap(0, 0, (const uint16_t *)logoSplash.pixel_data, 128, 128);
        delay(appConfig.data.splashDisplayTime / 2);
        oled.fillScreen(BLACK);
#endif
        PrintTitleScreen();
        delay(appConfig.data.splashDisplayTime / 2);
        oled.fillScreen(BLACK);
    }
}