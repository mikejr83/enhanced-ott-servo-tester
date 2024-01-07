#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#include "Settings.h"
#include "SplashImageData.h"
#include "TextPrinter.h"

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

float p = 3.1415926;

void testlines(uint16_t color)
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

void testdrawtext(char *text, uint16_t color)
{
  oled.setCursor(0, 0);
  oled.setTextColor(color);
  oled.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2)
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

void testdrawrects(uint16_t color)
{
  oled.fillScreen(BLACK);
  for (uint16_t x = 0; x < oled.height() - 1; x += 6)
  {
    oled.drawRect((oled.width() - 1) / 2 - x / 2, (oled.height() - 1) / 2 - x / 2, x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
  oled.fillScreen(BLACK);
  for (uint16_t x = oled.height() - 1; x > 6; x -= 6)
  {
    oled.fillRect((oled.width() - 1) / 2 - x / 2, (oled.height() - 1) / 2 - x / 2, x, x, color1);
    oled.drawRect((oled.width() - 1) / 2 - x / 2, (oled.height() - 1) / 2 - x / 2, x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
  for (uint8_t x = radius; x < oled.width() - 1; x += radius * 2)
  {
    for (uint8_t y = radius; y < oled.height() - 1; y += radius * 2)
    {
      oled.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
  for (uint8_t x = 0; x < oled.width() - 1 + radius; x += radius * 2)
  {
    for (uint8_t y = 0; y < oled.height() - 1 + radius; y += radius * 2)
    {
      oled.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles()
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

void testroundrects()
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

void tftPrintTest()
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

void mediabuttons()
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
void lcdTestPattern(void)
{
  static const uint16_t PROGMEM colors[] =
      {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, BLACK, WHITE};

  for (uint8_t c = 0; c < 8; c++)
  {
    oled.fillRect(0, oled.height() * c / 8, oled.width(), oled.height() / 8,
                 pgm_read_word(&colors[c]));
  }
}

void setup(void)
{
  Serial.begin(115200);

  oled.begin();

  Serial.println("init");

  // You can optionally rotate the display by running the line below.
  // Note that a value of 0 means no rotation, 1 means 90 clockwise,
  // 2 means 180 degrees clockwise, and 3 means 270 degrees clockwise.
  // oled.setRotation(1);
  // NOTE: The test pattern at the start will NOT be rotated!  The code
  // for rendering the test pattern talks directly to the display and
  // ignores any rotation.

  uint16_t time = millis();
  oled.fillRect(0, 0, 128, 128, BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  oled.drawRGBBitmap(0, 0, (const uint16_t *)logoSplash.pixel_data, 128, 128);
  delay(2500);
  oled.fillScreen(BLACK);
  pintTitleScreen(oled);
  delay(2500);
}

void loop()
{
  lcdTestPattern();
  delay(500);

  oled.invert(true);
  delay(100);
  oled.invert(false);
  delay(100);

  oled.fillScreen(BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", WHITE);
  delay(500);

  // tft print function!
  tftPrintTest();
  delay(500);

  // a single pixel
  oled.drawPixel(oled.width() / 2, oled.height() / 2, GREEN);
  delay(500);

  // line draw test
  testlines(YELLOW);
  delay(500);

  // optimized lines
  testfastlines(RED, BLUE);
  delay(500);

  testdrawrects(GREEN);
  delay(1000);

  testfillrects(YELLOW, MAGENTA);
  delay(1000);

  oled.fillScreen(BLACK);
  testfillcircles(10, BLUE);
  testdrawcircles(10, WHITE);
  delay(1000);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  Serial.println("done");
  delay(1000);
}