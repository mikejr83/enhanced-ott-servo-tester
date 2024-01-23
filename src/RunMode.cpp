#include "settings.h"

#include <Arduino.h>

#include "AppConfig.h"
#include "RunMode.h"
#include "ServoOps.h"

void HandleRunMode(AppConfig &appConfig, ServoData *servoData, RunMode runMode)
{
    // now check if we need to process anything else
    // based on the current run mode
    switch (runMode)
    {
    // MANUAL mode --------------------------------
    case RUN_MANUAL_INIT:
        // dataChanged = true;
        runMode = RUN_MANUAL;
        break;

    case RUN_MANUAL:
        // encoderMenuUI();
        break;

    // SWEEP mode ---------------------------------
    case RUN_SWEEP_INIT:
        PRINTS("\n> SWEEP INIT");
        for (uint8_t i = 0; i < MAX_SERVO; i++)
            if (appConfig.data.servo[i].enabled)
                DoServoSweep(appConfig, servoData, i, true);
        runMode = RUN_SWEEP_WAITING;
        PRINTS(" -> SWEEP WAIT");
        break;

    case RUN_SWEEP_WAITING:
        // encoderMenuUI();
        break;

    case RUN_SWEEP:
        // PRINTS("\nSWEEP RUN");
        for (uint8_t i = 0; i < MAX_SERVO; i++)
            if (appConfig.data.servo[i].enabled)
                DoServoSweep(appConfig, servoData, i, true);
        // encoderMenuUI();
        break;

    // RECEIVER CHECK mode ----------------------
    case RUN_RCHECK_INIT:
        PRINTS("\n> RCHECK INIT");
#if USE_RCV
        rcvCheckData.timeSig = rcvCheckData.timeGap = 0;
        runMode = RUN_RCHECK;
#else
        runMode = RUN_ESC_INIT;
#endif
        break;

#if USE_RCV
    case RUN_RCHECK:
        rcvCheckData.timeSig = pulseIn(RCV_PIN, HIGH, 100000UL);
        rcvCheckData.timeGap = pulseIn(RCV_PIN, LOW, 100000UL);
        dataChanged = true;
        rcvCheckData.timePause = millis();
        runMode = RUN_RCHECK_PAUSE;
        break;

    case RUN_RCHECK_PAUSE:
        if (millis() - rcvCheckData.timePause >= RCV_PAUSE_TIME)
            runMode = RUN_RCHECK;
        encoderMenuUI();
        break;
#endif

    // ESC mode ---------------------------------
    case RUN_ESC_INIT:
        PRINTS("\n> ESC INIT");
#if USE_ESC
        escState = true; // always start sequence with this HIGH
        runMode = RUN_ESC;
#else
        runMode = RUN_MANUAL_INIT;
#endif
        break;

#if USE_ESC
    case RUN_ESC:
        encoderMenuUI();
        if (C.data.servo[escOutput].enabled)
            setServoSPPct(escOutput, escState ? 100 : 0);
        break;
#endif

    default:
        runMode = RUN_MANUAL_INIT;
        break;
    }
}