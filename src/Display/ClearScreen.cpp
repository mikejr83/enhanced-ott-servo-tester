#include "Display.h"

void Display::ClearScreen()
{
    oled.fillScreen(BLACK);
    delay(250);
}