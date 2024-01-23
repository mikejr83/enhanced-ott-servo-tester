#include "AppConfig.h"

void AppConfig::begin(void)
{
    if (!load())
    {
        reset();
        save();
    }
}