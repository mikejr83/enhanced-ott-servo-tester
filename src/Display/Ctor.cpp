#include "Display.h"

Display::Display(Adafruit_SSD1351 &oled, AppConfig &appConfig, ServoData *servoData)
    : oled(oled), appConfig(appConfig), servoData(servoData)
{
    // ctor
}