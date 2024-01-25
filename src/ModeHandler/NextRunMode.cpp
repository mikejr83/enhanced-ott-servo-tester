#include "ModeHandler.h"

RunMode ModeHandler::NextRunMode()
{
    switch (currentMode)
    {
    // MANUAL mode --------------------------------
    case RUN_MANUAL_INIT:
    case RUN_MANUAL:
        currentMode = RUN_SWEEP_INIT;
        break;

    // SWEEP mode ---------------------------------
    case RUN_SWEEP_INIT:
    case RUN_SWEEP_WAITING:
    case RUN_SWEEP:
#if USE_RCV
        currentMode = RUN_RCHECK_INIT;
#else
        currentMode = RUN_MANUAL_INIT;
#endif
        break;

    // RECEIVER CHECK mode ----------------------
    case RUN_RCHECK_INIT:
    case RUN_RCHECK:
    case RUN_RCHECK_PAUSE:
#if USE_ESC
        currentMode = RUN_ESC_INIT;
#else
        currentMode = RUN_MANUAL_INIT;
#endif
        break;

    // ESC mode ---------------------------------
    case RUN_ESC_INIT:
    case RUN_ESC:
        currentMode = RUN_MANUAL_INIT;
        break;

    default:
        currentMode = RUN_MANUAL_INIT;
        break;
    }

    return currentMode;
}

RunMode ModeHandler::GetCurrentRunMode()
{
    return currentMode;
}
