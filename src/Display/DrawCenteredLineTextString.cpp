#include "Display.h"

void Display::DrawCenteredLineTextString(Adafruit_SSD1351 &oled, const char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    oled.getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calc width of new string
    oled.setCursor((SCREEN_WIDTH - w) / 2, y);
    oled.print(buf);
}