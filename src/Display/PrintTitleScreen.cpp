#include "settings.h"

#include "Display.h"

void Display::PrintTitleScreen()
{
    oled.setCursor(0, 0);
    oled.setTextColor(BLUE);
    oled.setTextSize(2);
    Display::DrawCenteredLineTextString(oled, "Enhanced", 0, 0);
    oled.setTextColor(WHITE);
    Display::DrawCenteredLineTextString(oled, "Over", 0, 20);
    Display::DrawCenteredLineTextString(oled, "The Top", 0, 40);
    oled.setTextColor(RED);
    Display::DrawCenteredLineTextString(oled, "Servo", 0, 60);
    Display::DrawCenteredLineTextString(oled, "Tester", 0, 80);
}