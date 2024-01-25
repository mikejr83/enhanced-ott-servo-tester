#include "ModeHandler.h"

const char *ModeHandler::RunModeToString(RunMode runMode)
{
    switch (runMode)
    {
    // MANUAL mode --------------------------------
    case RUN_MANUAL_INIT:
    case RUN_MANUAL:
        return "Manual";

    // SWEEP mode ---------------------------------
    case RUN_SWEEP_INIT:
    case RUN_SWEEP_WAITING:
    case RUN_SWEEP:
        return "Sweep";

    // RECEIVER CHECK mode ----------------------
    case RUN_RCHECK_INIT:
    case RUN_RCHECK:
    case RUN_RCHECK_PAUSE:
        return "RX";

    // ESC mode ---------------------------------
    case RUN_ESC_INIT:
    case RUN_ESC:
        return "ESC";

    default:
        return "Manual";
    }
}

const char *ModeHandler::ManualSubModeToString(ManualModeSubMode runMode)
{
    switch (runMode)
    {
    case ManualModeSubMode::HOLD_POSITION:
        return "Hold At Position";

    case ManualModeSubMode::HOME:
        return "Home";

    case ManualModeSubMode::JOYSTICK_INPUT:
        return "Joystick";
    default:
        return "Hold At Position";
    }
}