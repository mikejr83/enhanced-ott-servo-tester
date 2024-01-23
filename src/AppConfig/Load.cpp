#include "AppConfig.h"

#ifdef USE_EEPROM
#include <EEPROM.h>
#endif

bool AppConfig::load(void)
{
    #ifdef USE_EEPROM
    EEPROM.get(_eepromBase, data);

    if (data.signature[0] != EEPROM_SIG[0] || data.signature[1] != EEPROM_SIG[1])
    {
        PRINTSLN("Configuration not loaded.");
        return (false);
    }

    PRINTSLN("Configuration loaded.");
    return (true);
    #else
    return false;
    #endif

}