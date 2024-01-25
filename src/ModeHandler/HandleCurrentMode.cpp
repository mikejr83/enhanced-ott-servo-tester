#include "ModeHandler.h"

#include "settings.h"

#include <Arduino.h>

#include "ServoOps.h"

void ModeHandler::HandleCurrentMode()
{
    // now check if we need to process anything else
    // based on the current run mode
    switch (currentMode)
    {
    // MANUAL mode --------------------------------
    case RUN_MANUAL_INIT:
        // dataChanged = true;
        currentMode = RUN_MANUAL;
        break;

    case RUN_MANUAL:
        handleManual();
        break;

    // SWEEP mode ---------------------------------
    case RUN_SWEEP_INIT:
        PRINTS("\n> SWEEP INIT");
        for (uint8_t i = 0; i < MAX_SERVO; i++)
            if (appConfig.data.servo[i].enabled)
                DoServoSweep(appConfig, servoData, i, true);
        currentMode = RUN_SWEEP_WAITING;
        PRINTS(" -> SWEEP WAIT");
        break;

    case RUN_SWEEP_WAITING:
        // encoderMenuUI();
        currentMode = RUN_SWEEP;
        break;

    case RUN_SWEEP:
        // PRINTS("\nSWEEP RUN");
        for (uint8_t i = 0; i < MAX_SERVO; i++)
            if (appConfig.data.servo[i].enabled)
                DoServoSweep(appConfig, servoData, i, false);
        // encoderMenuUI();
        break;

    // RECEIVER CHECK mode ----------------------
    case RUN_RCHECK_INIT:
        PRINTS("\n> RCHECK INIT");
#if USE_RCV
        rcvCheckData.timeSig = rcvCheckData.timeGap = 0;
        currentMode = RUN_RCHECK;
#else
        currentMode = RUN_ESC_INIT;
#endif
        break;

#if USE_RCV
    case RUN_RCHECK:
        rcvCheckData.timeSig = pulseIn(RCV_PIN, HIGH, 100000UL);
        rcvCheckData.timeGap = pulseIn(RCV_PIN, LOW, 100000UL);
        dataChanged = true;
        rcvCheckData.timePause = millis();
        currentMode = RUN_RCHECK_PAUSE;
        break;

    case RUN_RCHECK_PAUSE:
        if (millis() - rcvCheckData.timePause >= RCV_PAUSE_TIME)
            currentMode = RUN_RCHECK;
        encoderMenuUI();
        break;
#endif

    // ESC mode ---------------------------------
    case RUN_ESC_INIT:
        PRINTS("\n> ESC INIT");
#if USE_ESC
        escState = true; // always start sequence with this HIGH
        currentMode = RUN_ESC;
#else
        currentMode = RUN_MANUAL_INIT;
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
        currentMode = RUN_MANUAL_INIT;
        break;
    }
}

void ModeHandler::handleManual()
{
    switch (currentManualSubMode)
    {
    case ManualModeSubMode::HOME:
        SetAllServoHome(appConfig, servoData);
        break;

    case ManualModeSubMode::HOLD_POSITION:
        if (millis() - lastJoyRead > 250)
        {
            lastJoyRead = millis();

            int xVal = analogRead(X_AXIS_PIN);
            int yVal = analogRead(Y_AXIS_PIN);

            // PRINT("Raw X: ", xVal);
            // PRINT("Raw Y: ", yVal);

            xVal = abs(xVal - 511) < X_AXIS_DEADBAND ? 511 : xVal;
            yVal = abs(yVal - 511) < Y_AXIS_DEADBAND ? 511 : yVal;

            // PRINT("Deadbanded X: ", xVal);
            // PRINT("Deadbanded Y: ", yVal);

            double xPercentage = (double)map(xVal, 0, 1023, -100, 100) / (double)100;
            double yPercentage = (double)map(yVal, 0, 1023, -100, 100) / (double)100;

            xPercentage = JOY_EXPO * pow(xPercentage, 3) + (1 - JOY_EXPO) * xPercentage;
            yPercentage = JOY_EXPO * pow(yPercentage, 3) + (1 - JOY_EXPO) * yPercentage;

            int moveBy = abs(xPercentage) > abs(yPercentage) ? (JOY_MAX_MOVE_PER_CYCLE * xPercentage) : (JOY_MAX_MOVE_PER_CYCLE * yPercentage);

            DoManualUpdate(appConfig, servoData, moveBy);
        }
        break;

    case ManualModeSubMode::JOYSTICK_INPUT:
        if (millis() - lastJoyRead > 250)
        {
            lastJoyRead = millis();
            int xVal = analogRead(X_AXIS_PIN);
            int yVal = analogRead(Y_AXIS_PIN);

            xVal = abs(xVal - 511) < X_AXIS_DEADBAND ? 511 : xVal;
            yVal = abs(yVal - 511) < Y_AXIS_DEADBAND ? 511 : yVal;

            double xPercentage = (double)map(xVal, 0, 1023, -100, 100) / (double)100;
            double yPercentage = (double)map(yVal, 0, 1023, -100, 100) / (double)100;

            xPercentage = JOY_EXPO * pow(xPercentage, 3) + (1 - JOY_EXPO) * xPercentage;
            yPercentage = JOY_EXPO * pow(yPercentage, 3) + (1 - JOY_EXPO) * yPercentage;

            DoManualUpdateToPercentage(appConfig, servoData, abs(xPercentage) > abs(yPercentage) ? xPercentage : yPercentage);
        }
        break;
    }
}