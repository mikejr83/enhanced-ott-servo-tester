#pragma once

#include <Arduino.h>

#include "AppConfig.h"
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

class ModeHandler
{
private:
    AppConfig appConfig;
    ServoData *servoData;
    RunMode currentMode = RUN_MANUAL_INIT;

    uint32_t lastJoyRead = 0;

    void handleManual();

public:
    static const char *RunModeToString(RunMode runMode);

    ModeHandler(AppConfig &appConfig, ServoData *servoData);

    void HandleCurrentMode();
    RunMode NextRunMode();
    RunMode GetCurrentRunMode();
};