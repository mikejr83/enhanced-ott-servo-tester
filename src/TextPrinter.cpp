
#include <Adafruit_SSD1351.h>

#include "Settings.h"
#include "TextPrinter.h"

void pintTitleScreen(Adafruit_SSD1351 oled)
{
    oled.setCursor(0,0);
    oled.setTextColor(BLUE);
    oled.setTextSize(3);
    oled.print("Enhanced OTT");
}