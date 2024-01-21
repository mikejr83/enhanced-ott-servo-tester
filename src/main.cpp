#include "Settings.h"

#include <menu.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#include <menuIO/analogAxisIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <menuIO/adafruitGfxOut.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <EasyButton.h>
// #include <ArduinoLog.h>

#include "SplashImageData.h"
#include "TextPrinter.h"
#include "OTTMenu.h"

void handlePress();

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

volatile bool showMenu = false;
EasyButton button(BUTTON_PIN);

uint32_t lastCheck = 0;

using namespace Menu;

// define menu colors --------------------------------------------------------
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
const colorDef<uint16_t> colors[6] MEMMODE = {
    {{BLACK, BLACK}, {BLACK, BLACK, BLACK}},           // bgColor
    {{BLACK, WHITE}, {WHITE, BLUE, RED}},              // fgColor
    {{GREEN_DARK, WHITE}, {GREEN_DARK, GREEN, GREEN}}, // valColor
    {{GREEN_DARK, WHITE}, {GREEN_DARK, GREEN, GREEN}}, // unitColor
    {{BLACK, BLACK}, {BLACK, BLACK, BLACK}},           // cursorColor
    {{BLACK, BLACK}, {BLACK, WHITE, WHITE}},           // titleColor
};

// analog joystick parameters
//  uint8_t pin,
//  uint8_t sensivity=5,
//  bool inv=false,
//  int center=512,
//  int inertia=6,
//  int bufferSz=1,
//  navCmds posCmd=upCmd,
//  navCmds negCmd=downCmd
analogAxis<Y_AXIS_PIN, 5, false> ay;
analogAxis<X_AXIS_PIN, 5, false> ax;

int test = 500;

result systemExit();
altMENU(confirmExit, exitMenu, "Exit?", doNothing, noEvent, wrapStyle, (Menu::_menuData | Menu::_canNav), OP("Yes", systemExit, enterEvent), EXIT("Cancel"));

MENU(mainMenu, "Main menu", doNothing, noEvent, wrapStyle,
     OP("Op1", doNothing, noEvent),
     OP("Op2", doNothing, noEvent),
     FIELD(test, "Test", "ms", 0, 1000, 100, 1, doNothing, noEvent, wrapStyle),
     SUBMENU(exitMenu));

keyMap btnsMap[] = {{-1, defaultNavCodes[enterCmd].ch}}; // negative pin numbers use internal pull-up, this is on when low
keyIn<1> btns(btnsMap);                                  // 1 is the number of keys

serialIn menuSerialIn(Serial);

MENU_INPUTS(in, &ay, &btns, &menuSerialIn);

#define MAX_DEPTH 2
#define FONT_SCALE 2
MENU_OUTPUTS(out, MAX_DEPTH, ADAGFX_OUT(oled, colors, FONT_SCALE * 6, FONT_SCALE * 9, {0, 0, SCREEN_WIDTH / FONT_SCALE * 6, SCREEN_HEIGHT / FONT_SCALE * 9}), SERIAL_OUT(Serial));

NAVROOT(nav, mainMenu, MAX_DEPTH, in, out);

// when menu is suspended
result idle(menuOut &o, idleEvent e)
{
  showMenu = false;
Serial.println("Idling");
  return proceed;
}

result systemExit()
{
  nav.reset();
  nav.idleOn(); // suspend the menu system
  return quit;
}

void buttonPressedTwoSeconds();
void buttonISR();

void setup(void)
{
  Serial.begin(115200);

  // Initialize the button.
  button.begin();

  button.onPressedFor(3000, handlePress);

  // if (button.supportsInterrupt())
  // {
  //   button.enableInterrupt(buttonISR);
  //   Serial.println("Button will be used through interrupts");
  // }

  // #ifndef DISABLE_LOGGING
  //   Log.begin(LOG_LEVEL, &Serial);
  // #endif

  oled.begin();

  nav.idleTask = idle;

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

  oled.fillScreen(BLACK);
}

void loop()
{
  if (showMenu)
  {
    nav.poll();
  }
  else
  {
    oled.drawRGBBitmap(0, 0, (const uint16_t *)logoSplash.pixel_data, 128, 128);
  }

  button.read();
}

void buttonPressedTwoSeconds()
{
  Serial.println("Button pressed for two seconds");
}

void buttonISR()
{
  // When button is being used through external interrupts, parameter INTERRUPT must be passed to read() function.
  button.read();
}

void handlePress()
{
  Serial.println("Button pressed");
  nav.idleOff();
  showMenu = true;
}