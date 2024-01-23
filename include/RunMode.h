#pragma once

#include <Arduino.h>

#include "ServoOps.h"

enum RunMode : uint8_t
{
    RUN_MANUAL_INIT,
    RUN_MANUAL,
    RUN_SWEEP_INIT,
    RUN_SWEEP_WAITING,
    RUN_SWEEP,
    RUN_RCHECK_INIT,
    RUN_RCHECK,
    RUN_RCHECK_PAUSE,
    RUN_ESC_INIT,
    RUN_ESC
};

void HandleRunMode(AppConfig &appConfig, ServoData *servoData, RunMode runMode);

const char* RunModeToString(RunMode runMode);