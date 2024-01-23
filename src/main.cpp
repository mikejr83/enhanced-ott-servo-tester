#include "Settings.h"

#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>

#include <menu.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#include <menuIO/analogAxisIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <menuIO/adafruitGfxOut.h>

#include <EasyButton.h>
// #include <ArduinoLog.h>

#include "AppConfig.h"
#include "SplashImageData.h"
#include "TextPrinter.h"
#include "OTTMenu.h"

// Button presses
void handleLongPress();
void handleDoublePress();
// Menu handlers
void handleGlobalServoLimits();
void handleSave();
void handleLoad();
void handleReset();

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);
EasyButton button(BUTTON_PIN);
AppConfig appConfig;

volatile bool showMenu = false;

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

/*
  uint8_t pin,//axis pin number
  uint8_t sensivity=5,
  bool inv=false,//invert axis direction
  int center=512,//calibration
  int inertia=6,//prevent rest drift
  int bufferSz=1,//how many clicks can accumulate
  navCmds posCmd=upCmd,//what is sent by positive axis click
  navCmds negCmd=downCmd//what is sent by negative axis click
*/
analogAxis<Y_AXIS_PIN, 5, false> ay;
analogAxis<X_AXIS_PIN, 5, false, 512, 6, 1, rightCmd, leftCmd> ax;

int upperLimit = 2000,
    lowerLimit = 1000;

result systemExit();
altMENU(confirmExit, exitMenu, "Exit?", doNothing, noEvent, wrapStyle,
        (Menu::_menuData | Menu::_canNav),
        OP("Yes", systemExit, enterEvent),
        EXIT("Cancel"));
        
MENU(profile1Menu, "Profile 1", doNothing, noEvent, noStyle,
     FIELD(appConfig.data.profile[0].low, "Lower", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     FIELD(appConfig.data.profile[0].high, "Upper", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     FIELD(appConfig.data.profile[0].home, "Home", "%", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     FIELD(appConfig.data.profile[0].sweepTime, "Sweep Time", "ms", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     FIELD(appConfig.data.profile[0].sweepPause, "Sweep Pause", "ms", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     EXIT("< Back"));
MENU(profile2Menu, "Profile 2", doNothing, noEvent, noStyle,
     FIELD(appConfig.data.profile[1].low, "Lower", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     FIELD(appConfig.data.profile[1].high, "Upper", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     FIELD(appConfig.data.profile[1].home, "Home", "%", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     FIELD(appConfig.data.profile[1].sweepTime, "Sweep Time", "ms", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     FIELD(appConfig.data.profile[1].sweepPause, "Sweep Pause", "ms", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     EXIT("< Back"));
MENU(profile3Menu, "Profile 3", doNothing, noEvent, noStyle,
     FIELD(appConfig.data.profile[2].low, "Lower", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     FIELD(appConfig.data.profile[2].high, "Upper", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     FIELD(appConfig.data.profile[2].home, "Home", "%", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     FIELD(appConfig.data.profile[2].sweepTime, "Sweep Time", "ms", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     FIELD(appConfig.data.profile[2].sweepPause, "Sweep Pause", "ms", 0, 100, 100, 1, doNothing, noEvent, wrapStyle),
     EXIT("< Back"));

MENU(profilesMenu, "Profiles", doNothing, noEvent, noStyle,
     SUBMENU(profile1Menu),
     SUBMENU(profile2Menu),
     SUBMENU(profile3Menu),
     EXIT("<Back"));

TOGGLE(appConfig.data.servo[0].enabled, servo0EnabledToggle, "Enabled? ", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));
TOGGLE(appConfig.data.servo[0].profileId, servo0ProfileToggle, "Profile: ", doNothing, noEvent, noStyle,
       VALUE("Profile 1", 0, doNothing, noEvent),
       VALUE("Profile 2", 1, doNothing, noEvent),
       VALUE("Profile 3", 2, doNothing, noEvent));

TOGGLE(appConfig.data.servo[1].enabled, servo1EnabledToggle, "Enabled? ", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));
TOGGLE(appConfig.data.servo[1].profileId, servo1ProfileToggle, "Profile: ", doNothing, noEvent, noStyle,
       VALUE("Profile 1", 0, doNothing, noEvent),
       VALUE("Profile 2", 1, doNothing, noEvent),
       VALUE("Profile 3", 2, doNothing, noEvent));

TOGGLE(appConfig.data.servo[2].enabled, servo2EnabledToggle, "Enabled? ", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));
TOGGLE(appConfig.data.servo[2].profileId, servo2ProfileToggle, "Profile: ", doNothing, noEvent, noStyle,
       VALUE("Profile 1", 0, doNothing, noEvent),
       VALUE("Profile 2", 1, doNothing, noEvent),
       VALUE("Profile 3", 2, doNothing, noEvent));

TOGGLE(appConfig.data.servo[3].enabled, servo3EnabledToggle, "Enabled? ", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));
TOGGLE(appConfig.data.servo[3].profileId, servo3ProfileToggle, "Profile: ", doNothing, noEvent, noStyle,
       VALUE("Profile 1", 0, doNothing, noEvent),
       VALUE("Profile 2", 1, doNothing, noEvent),
       VALUE("Profile 3", 2, doNothing, noEvent));

TOGGLE(appConfig.data.servo[4].enabled, servo4EnabledToggle, "Enabled? ", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));
TOGGLE(appConfig.data.servo[4].profileId, servo4ProfileToggle, "Profile: ", doNothing, noEvent, noStyle,
       VALUE("Profile 1", 0, doNothing, noEvent),
       VALUE("Profile 2", 1, doNothing, noEvent),
       VALUE("Profile 3", 2, doNothing, noEvent));

TOGGLE(appConfig.data.servo[5].enabled, servo5EnabledToggle, "Enabled? ", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));
TOGGLE(appConfig.data.servo[5].profileId, servo5ProfileToggle, "Profile: ", doNothing, noEvent, noStyle,
       VALUE("Profile 1", 0, doNothing, noEvent),
       VALUE("Profile 2", 1, doNothing, noEvent),
       VALUE("Profile 3", 2, doNothing, noEvent));

TOGGLE(appConfig.data.servo[6].enabled, servo6EnabledToggle, "Enabled? ", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));
TOGGLE(appConfig.data.servo[6].profileId, servo6ProfileToggle, "Profile: ", doNothing, noEvent, noStyle,
       VALUE("Profile 1", 0, doNothing, noEvent),
       VALUE("Profile 2", 1, doNothing, noEvent),
       VALUE("Profile 3", 2, doNothing, noEvent));

MENU(servo0, "Servo A", doNothing, noEvent, noStyle,
     SUBMENU(servo0EnabledToggle),
     SUBMENU(servo0ProfileToggle),
     EXIT("< Back"));
MENU(servo1, "Servo B", doNothing, noEvent, noStyle,
     SUBMENU(servo1EnabledToggle),
     SUBMENU(servo1ProfileToggle),
     EXIT("< Back"));
MENU(servo2, "Servo C", doNothing, noEvent, noStyle,
     SUBMENU(servo2EnabledToggle),
     SUBMENU(servo2ProfileToggle),
     EXIT("< Back"));
MENU(servo3, "Servo D", doNothing, noEvent, noStyle,
     SUBMENU(servo3EnabledToggle),
     SUBMENU(servo3ProfileToggle),
     EXIT("< Back"));
MENU(servo4, "Servo E", doNothing, noEvent, noStyle,
     SUBMENU(servo4EnabledToggle),
     SUBMENU(servo4ProfileToggle),
     EXIT("< Back"));
MENU(servo5, "Servo F", doNothing, noEvent, noStyle,
     SUBMENU(servo5EnabledToggle),
     SUBMENU(servo5ProfileToggle),
     EXIT("< Back"));
MENU(servo6, "Servo G", doNothing, noEvent, noStyle,
     SUBMENU(servo6EnabledToggle),
     SUBMENU(servo6ProfileToggle),
     EXIT("< Back"));

MENU(servos, "Servos", doNothing, noEvent, noStyle,
     SUBMENU(servo0),
     SUBMENU(servo1),
     SUBMENU(servo2),
     SUBMENU(servo3),
     SUBMENU(servo4),
     SUBMENU(servo5),
     SUBMENU(servo6),
     EXIT("< Back"));

MENU(signalLimitsMenu, "Signal Limits", doNothing, noEvent, noStyle,
     FIELD(appConfig.data.limHigh, "Upper", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     FIELD(appConfig.data.limLow, "Lower", "ms", SERVO_LOWER_HARDLIMIT, SERVO_UPPER_HARDLIMIT, 100, 1, handleGlobalServoLimits, exitEvent, wrapStyle),
     EXIT("< Back"));

TOGGLE(appConfig.data.showSplash, toggleShowSplash, "Show Splash Screen", doNothing, noEvent, noStyle,
       VALUE("Yes", true, doNothing, noEvent),
       VALUE("No", false, doNothing, noEvent));

MENU(generalConfigMenu, "General Configuration", doNothing, noEvent, noStyle,
     SUBMENU(toggleShowSplash),
     FIELD(appConfig.data.splashDisplayTime, "Splash Screen Display Length", "ms", 1000, MAX_SPLASH_DISPLAYTIME, 1000, 100, doNothing, noEvent, wrapStyle),
     EXIT("< Back"));

MENU(configMenu, "Configuration", doNothing, noEvent, noStyle,
     SUBMENU(profilesMenu),
     SUBMENU(servos),
     SUBMENU(signalLimitsMenu),
     SUBMENU(generalConfigMenu),
     OP("Save", handleSave, enterEvent),
     OP("Load", handleLoad, enterEvent),
     OP("Reset", handleReset, enterEvent),
     EXIT("< Back"));

MENU(mainMenu, "Main menu", doNothing, noEvent, wrapStyle,
     OP("Run Mode", doNothing, noEvent),
     SUBMENU(configMenu),
     SUBMENU(exitMenu));

#define MAX_DEPTH 4

keyMap btnsMap[] = {{-1, defaultNavCodes[enterCmd].ch}}; // negative pin numbers use internal pull-up, this is on when low
keyIn<1> btns(btnsMap);                                  // 1 is the number of keys

serialIn menuSerialIn(Serial);

MENU_INPUTS(in, &ay, &ax, &btns, &menuSerialIn);

#define FONT_SCALE 1
MENU_OUTPUTS(out,
             MAX_DEPTH,
             ADAGFX_OUT(oled, colors, FONT_SCALE * 6, FONT_SCALE * 9, {0, 0, SCREEN_WIDTH / FONT_SCALE * 6, SCREEN_HEIGHT / FONT_SCALE * 9}),
             SERIAL_OUT(Serial));

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

void setup(void)
{
  Serial.begin(115200);

  PRINTSLN("Beginning initialization...")

  // Initialize the button.
  button.begin();

  button.onPressedFor(3000, handleLongPress);
  button.onSequence(2, 1500, handleDoublePress);

  // Initialize the OLED
  oled.begin();

  // Initialize nav
  nav.idleTask = idle;

  // Initialize application configuration
  appConfig.begin();

  PRINTSLN("Initialization complete!")

  // You can optionally rotate the display by running the line below.
  // Note that a value of 0 means no rotation, 1 means 90 clockwise,
  // 2 means 180 degrees clockwise, and 3 means 270 degrees clockwise.
  // oled.setRotation(1);
  // NOTE: The test pattern at the start will NOT be rotated!  The code
  // for rendering the test pattern talks directly to the display and
  // ignores any rotation.

  oled.fillRect(0, 0, 128, 128, BLACK);
  delay(250);

  if (appConfig.data.showSplash && appConfig.data.splashDisplayTime <= MAX_SPLASH_DISPLAYTIME)
  {
    PRINT("\nShowing splash screen and title for a total time of: ", appConfig.data.splashDisplayTime)
    oled.drawRGBBitmap(0, 0, (const uint16_t *)logoSplash.pixel_data, 128, 128);
    delay(appConfig.data.splashDisplayTime / 2);
    oled.fillScreen(BLACK);
    pintTitleScreen(oled);
    delay(appConfig.data.splashDisplayTime / 2);
    oled.fillScreen(BLACK);
  }
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

  // if(millis() - lastCheck > 5000){
  //   lastCheck = millis();
  //   int xAxisRead = analogRead(X_AXIS_PIN);
  //   int yAxisRead = analogRead(Y_AXIS_PIN);

  //   Serial.print("X: ");
  //   Serial.println(xAxisRead);
  //   Serial.print("Y: ");
  //   Serial.println(yAxisRead);
  // }

  button.read();
}

void handleLongPress()
{
  PRINTSLN("Long Press - Starting Menu...");
  nav.idleOff();
  showMenu = true;
}

void handleDoublePress()
{
  if (showMenu)
  {
    PRINTSLN("Skip Handling Double Press in menu.");
  }
  else
  {
    PRINTSLN("Handling Double Press...");
  }
}

void handleGlobalServoLimits()
{
  for (uint8_t i = 0; i < NUM_PROFILE; i++)
  {
    PRINT("Checking max for profile ", i + 1);
    PRINT("Current max is: ", appConfig.data.profile[i].high);
    if (appConfig.data.profile[i].high > appConfig.data.limHigh)
    {
      PRINT("Setting max to: ", appConfig.data.limHigh);
      appConfig.data.profile[i].high = appConfig.data.limHigh;
    }
    if (appConfig.data.profile[i].low < appConfig.data.limLow)
    {
      PRINT("Setting min to: ", appConfig.data.limLow);
      appConfig.data.profile[i].low = appConfig.data.limLow;
    }
  }
}

void handleLoad()
{
  PRINTSLN("Handling load configuration...");
  appConfig.load();
}

void handleReset()
{
  PRINTSLN("Handling reset configuration...");
  appConfig.reset();
}

void handleSave()
{
  PRINTSLN("Handling save configuration...");
  appConfig.save();
}