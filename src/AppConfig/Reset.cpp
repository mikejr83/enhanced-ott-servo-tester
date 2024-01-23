#include "AppConfig.h"

#include "settings.h"

void AppConfig::reset(void)
{
    data.signature[0] = EEPROM_SIG[0];
    data.signature[1] = EEPROM_SIG[1];

    // Global config presets
    data.tmMenu = 4;   // menu timeout in seconds
    data.showSplash = SHOW_SPLASH;
    data.splashDisplayTime = 3000; // slapsh screen timeout in seconds

    // Safety limits
    data.limLow = SERVO_LOWER_HARDLIMIT;  // low limit in microseconds
    data.limHigh = SERVO_UPPER_HARDLIMIT; // high limit in microseconds
    data.autoPage = true;                 // default to autopaging

    // Servo information
    for (uint8_t i = 0; i < MAX_SERVO; i++)
    {
        data.servo[i].enabled = true;
        data.servo[i].profileId = 0; // all use the same profile initially
    }

    // Profiles information
    for (uint8_t i = 0; i < NUM_PROFILE; i++)
    {
        data.profile[i].low = 1000;             // in microseconds
        data.profile[i].high = 2000;            // in microseconds
        data.profile[i].home = 0;               // percentage of range
        data.profile[i].sweepType = SWP_LINEAR; // one of the
        data.profile[i].sweepTime = 2000;       // in milliseconds
        data.profile[i].sweepPause = 200;       // in milliseconds
    }
    data.profile[0].home = 50; // set specific percentage value
    data.profile[1].home = 0;
    data.profile[2].home = 100;

    PRINTSLN("Configuration reset (not saved)");
}