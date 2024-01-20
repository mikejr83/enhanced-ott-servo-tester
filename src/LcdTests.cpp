#include "settings.h"

#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

float p = 3.1415926;

void testlines(Adafruit_SSD1351 oled, uint16_t color)
{

    oled.fillScreen(BLACK);
    for (uint16_t x = 0; x < oled.width() - 1; x += 6)
    {
        oled.drawLine(0, 0, x, oled.height() - 1, color);
    }
    for (uint16_t y = 0; y < oled.height() - 1; y += 6)
    {
        oled.drawLine(0, 0, oled.width() - 1, y, color);
    }

    oled.fillScreen(BLACK);
    for (uint16_t x = 0; x < oled.width() - 1; x += 6)
    {
        oled.drawLine(oled.width() - 1, 0, x, oled.height() - 1, color);
    }
    for (uint16_t y = 0; y < oled.height() - 1; y += 6)
    {
        oled.drawLine(oled.width() - 1, 0, 0, y, color);
    }

    oled.fillScreen(BLACK);
    for (uint16_t x = 0; x < oled.width() - 1; x += 6)
    {
        oled.drawLine(0, oled.height() - 1, x, 0, color);
    }
    for (uint16_t y = 0; y < oled.height() - 1; y += 6)
    {
        oled.drawLine(0, oled.height() - 1, oled.width() - 1, y, color);
    }

    oled.fillScreen(BLACK);
    for (uint16_t x = 0; x < oled.width() - 1; x += 6)
    {
        oled.drawLine(oled.width() - 1, oled.height() - 1, x, 0, color);
    }
    for (uint16_t y = 0; y < oled.height() - 1; y += 6)
    {
        oled.drawLine(oled.width() - 1, oled.height() - 1, 0, y, color);
    }
}

void testdrawtext(Adafruit_SSD1351 oled, char *text, uint16_t color)
{
    oled.setCursor(0, 0);
    oled.setTextColor(color);
    oled.print(text);
}

void testfastlines(Adafruit_SSD1351 oled, uint16_t color1, uint16_t color2)
{
    oled.fillScreen(BLACK);
    for (uint16_t y = 0; y < oled.height() - 1; y += 5)
    {
        oled.drawFastHLine(0, y, oled.width() - 1, color1);
    }
    for (uint16_t x = 0; x < oled.width() - 1; x += 5)
    {
        oled.drawFastVLine(x, 0, oled.height() - 1, color2);
    }
}

void testdrawrects(Adafruit_SSD1351 oled, uint16_t color)
{
    oled.fillScreen(BLACK);
    for (uint16_t x = 0; x < oled.height() - 1; x += 6)
    {
        oled.drawRect((oled.width() - 1) / 2 - x / 2, (oled.height() - 1) / 2 - x / 2, x, x, color);
    }
}

void testfillrects(Adafruit_SSD1351 oled, uint16_t color1, uint16_t color2)
{
    oled.fillScreen(BLACK);
    for (uint16_t x = oled.height() - 1; x > 6; x -= 6)
    {
        oled.fillRect((oled.width() - 1) / 2 - x / 2, (oled.height() - 1) / 2 - x / 2, x, x, color1);
        oled.drawRect((oled.width() - 1) / 2 - x / 2, (oled.height() - 1) / 2 - x / 2, x, x, color2);
    }
}

void testfillcircles(Adafruit_SSD1351 oled, uint8_t radius, uint16_t color)
{
    for (uint8_t x = radius; x < oled.width() - 1; x += radius * 2)
    {
        for (uint8_t y = radius; y < oled.height() - 1; y += radius * 2)
        {
            oled.fillCircle(x, y, radius, color);
        }
    }
}

void testdrawcircles(Adafruit_SSD1351 oled, uint8_t radius, uint16_t color)
{
    for (uint8_t x = 0; x < oled.width() - 1 + radius; x += radius * 2)
    {
        for (uint8_t y = 0; y < oled.height() - 1 + radius; y += radius * 2)
        {
            oled.drawCircle(x, y, radius, color);
        }
    }
}

void testtriangles(Adafruit_SSD1351 oled)
{
    oled.fillScreen(BLACK);
    int color = 0xF800;
    int t;
    int w = oled.width() / 2;
    int x = oled.height();
    int y = 0;
    int z = oled.width();
    for (t = 0; t <= 15; t += 1)
    {
        oled.drawTriangle(w, y, y, x, z, x, color);
        x -= 4;
        y += 4;
        z -= 4;
        color += 100;
    }
}

void testroundrects(Adafruit_SSD1351 oled)
{
    oled.fillScreen(BLACK);
    int color = 100;

    int x = 0;
    int y = 0;
    int w = oled.width();
    int h = oled.height();
    for (int i = 0; i <= 24; i++)
    {
        oled.drawRoundRect(x, y, w, h, 5, color);
        x += 2;
        y += 3;
        w -= 4;
        h -= 6;
        color += 1100;
        Serial.println(i);
    }
}

void tftPrintTest(Adafruit_SSD1351 oled)
{
    oled.fillScreen(BLACK);
    oled.setCursor(0, 5);
    oled.setTextColor(RED);
    oled.setTextSize(1);
    oled.println("Hello World!");
    oled.setTextColor(YELLOW);
    oled.setTextSize(2);
    oled.println("Hello World!");
    oled.setTextColor(BLUE);
    oled.setTextSize(3);
    oled.print(1234.567);
    delay(1500);
    oled.setCursor(0, 5);
    oled.fillScreen(BLACK);
    oled.setTextColor(WHITE);
    oled.setTextSize(0);
    oled.println("Hello World!");
    oled.setTextSize(1);
    oled.setTextColor(GREEN);
    oled.print(p, 6);
    oled.println(" Want pi?");
    oled.println(" ");
    oled.print(8675309, HEX); // print 8,675,309 out in HEX!
    oled.println(" Print HEX!");
    oled.println(" ");
    oled.setTextColor(WHITE);
    oled.println("Sketch has been");
    oled.println("running for: ");
    oled.setTextColor(MAGENTA);
    oled.print(millis() / 1000);
    oled.setTextColor(WHITE);
    oled.print(" seconds.");
}

void mediabuttons(Adafruit_SSD1351 oled)
{
    // play
    oled.fillScreen(BLACK);
    oled.fillRoundRect(25, 10, 78, 60, 8, WHITE);
    oled.fillTriangle(42, 20, 42, 60, 90, 40, RED);
    delay(500);
    // pause
    oled.fillRoundRect(25, 90, 78, 60, 8, WHITE);
    oled.fillRoundRect(39, 98, 20, 45, 5, GREEN);
    oled.fillRoundRect(69, 98, 20, 45, 5, GREEN);
    delay(500);
    // play color
    oled.fillTriangle(42, 20, 42, 60, 90, 40, BLUE);
    delay(50);
    // pause color
    oled.fillRoundRect(39, 98, 20, 45, 5, RED);
    oled.fillRoundRect(69, 98, 20, 45, 5, RED);
    // play color
    oled.fillTriangle(42, 20, 42, 60, 90, 40, GREEN);
}

/**************************************************************************/
/*!
    @brief  Renders a simple test pattern on the screen
*/
/**************************************************************************/
void lcdTestPattern(Adafruit_SSD1351 oled)
{
    static const uint16_t PROGMEM colors[] =
        {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, BLACK, WHITE};

    for (uint8_t c = 0; c < 8; c++)
    {
        oled.fillRect(0, oled.height() * c / 8, oled.width(), oled.height() / 8,
                      pgm_read_word(&colors[c]));
    }
}