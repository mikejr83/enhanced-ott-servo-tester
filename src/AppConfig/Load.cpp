#include "AppConfig.h"

#include <EEPROM.h>

bool AppConfig::load(void)
{
    EEPROM.get(_eepromBase, data);

    if (data.signature[0] != EEPROM_SIG[0] || data.signature[1] != EEPROM_SIG[1])
    {
        PRINTSLN("Configuration not loaded.");
        return (false);
    }

    PRINTSLN("Configuration loaded.");
    return (true);
}