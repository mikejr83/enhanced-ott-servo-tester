#include "AppConfig.h"

#include <EEPROM.h>

void AppConfig::save(void)
{
    PRINTSLN("UI Configuration:");
    PRINT("mSplash: ", data.splashDisplayTime);

    PRINTSLN("--------------------\n\nGlobal Configuration:");
    PRINT("Upper: ", data.limHigh);
    PRINT("Lower: ", data.limLow);

    PRINTSLN("--------------------\n\nProfile Configuration:");
    for (uint8_t i = 0; i < NUM_PROFILE; i++)
    {
        PRINT("Profile:        ", i + 1);
        PRINT("Lower:          ", data.profile[i].low);
        PRINT("Upper:          ", data.profile[i].high);
        PRINT("Home:           ", data.profile[i].home);
        PRINT("Sweep Type:     ", data.profile[i].sweepType);
        PRINT("Sweep Duration: ", data.profile[i].sweepTime);
        PRINT("Sweep Pause:    ", data.profile[i].sweepPause);

        PRINTSLN("----------");
    }

    PRINTSLN("--------------------\n\nServo Configuration:");
    for (uint8_t i = 0; i < MAX_SERVO; i++)
    {
        PRINT("Servo: ", i );
        PRINT("Enabled:    ", data.servo[i].enabled);
        PRINT("Profile Id: ", data.servo[i].profileId);

        PRINTSLN("----------");
    }

    EEPROM.put(_eepromBase, data);

    PRINTSLN("Configuration saved!");
}