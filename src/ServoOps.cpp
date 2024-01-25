#include "settings.h"

#include <Arduino.h>
#include <Servo.h>

#include "AppConfig.h"
#include "ServoOps.h"
#include "ServoInfo.h"

void CheckMovement(ServoData *servoData, Servo *servo)
{
    // check if the servo needs to be moved
    for (uint8_t i = 0; i < MAX_SERVO; i++)
    {
        if (servoData[i].curV != servoData[i].setV)
        {
            servo[i].writeMicroseconds(servoData[i].setV);
            servoData[i].curV = servoData[i].setV;
        }
    }
}

void SetServoSPPct(AppConfig &appConfig, ServoData *servoData, uint8_t servoIndex, uint8_t percentage)
{
    // sanity checks
    if (servoIndex >= MAX_SERVO)
        return;
    if (percentage > 100)
        percentage = 100;

    // do the deed
    uint8_t id = appConfig.data.servo[servoIndex].profileId;
    uint32_t offset = appConfig.data.profile[id].high - appConfig.data.profile[id].low;

    offset = (offset * percentage) / 100L;
    // PRINT("\nPct ", pct);
    // PRINT(" range ", C.data.profile[id].high - C.data.profile[id].low);
    // PRINT(" = set Offset ", offset);
    servoData[servoIndex].setV = appConfig.data.profile[id].low + offset;
}

void SetAllServoHome(AppConfig &appConfig, ServoData *servoData)
{
    for (uint8_t i = 0; i < MAX_SERVO; i++)
    {
        if (appConfig.data.servo[i].enabled)
        {
            SetServoSPPct(appConfig, servoData, i, appConfig.data.profile[appConfig.data.servo[i].profileId].home);
        }
    }
}

void DoServoSweep(AppConfig &appConfig, ServoData *servoData, uint8_t s, bool restart)
{
    if (restart)
    {
        servoData[s].state = 0;
        return;
    }

    uint8_t id = appConfig.data.servo[s].profileId;

    switch (servoData[s].state)
    {
    case 0: // IDLE
        switch (appConfig.data.profile[id].sweepType)
        {
        case SWP_LINEAR:
        case SWP_SINE:
            servoData[s].timeDelta = 1000 / SERVO_UPDATE_FREQ;
            servoData[s].deltaPct = (100 * servoData[s].timeDelta) / appConfig.data.profile[id].sweepTime;
            break;

        case SWP_SQUARE:
            servoData[s].timeDelta = appConfig.data.profile[id].sweepTime;
            servoData[s].deltaPct = 100;
            break;
        }
        // PRINT("\n[", s);
        // PRINT("] Time Delta ", servoData[s].timeDelta);
        // PRINT(" Delta Pct ", servoData[s].deltaPct);
        servoData[s].timeStart = 0; // force the first update
        servoData[s].state = 1;     // start sweeping
        break;

    case 1: // SWEEPING
        if (millis() - servoData[s].timeStart >= servoData[s].timeDelta)
        {
            // now one deltaPCT advanced in the sweep
            servoData[s].sweepPct += servoData[s].deltaPct;
            // PRINT("\n[", s);
            // PRINT("] Current % ", servoData[s].sweepPct);
            if (servoData[s].sweepPct > 100)
                servoData[s].sweepPct = 100;
            if (servoData[s].sweepPct < 0)
                servoData[s].sweepPct = 0;
            // PRINT(" adjusted to % ", servoData[s].sweepPct);

            // Work out the servo setpoint value setting based on pct through and type of sweep
            switch (appConfig.data.profile[appConfig.data.servo[s].profileId].sweepType)
            {
            case SWP_LINEAR:
            case SWP_SQUARE:
                SetServoSPPct(appConfig, servoData, s, servoData[s].sweepPct);
                break;

            case SWP_SINE:
                servoData[s].setV = appConfig.data.profile[id].low;
                servoData[s].setV += sin((PI * servoData[s].sweepPct) / 100) * (appConfig.data.profile[id].high - appConfig.data.profile[id].low);
                // PRINT("\nSINE: Current V ", servoData[s].setV);
                break;
            }

            // reached the end of the sweep?
            if ((servoData[s].sweepPct >= 100 && servoData[s].deltaPct > 0) ||
                (servoData[s].sweepPct == 0 && servoData[s].deltaPct < 0))
            {
                PRINT("\n[", s);
                PRINTS("] SWEEP COMPLETE");
                servoData[s].state = 2;                         // time to wait for the pause time between sweeps
                servoData[s].deltaPct = -servoData[s].deltaPct; // reverse direction next run
                servoData[s].timeStart = millis();
            }
            else
            {
                // next time to do something in this state
                servoData[s].timeStart = servoData[s].timeStart + servoData[s].timeDelta;
            }
        }
        break;

    case 2: // PAUSING
        if (millis() - servoData[s].timeStart >= appConfig.data.profile[id].sweepPause)
        {
            PRINT("\n[", s);
            PRINTS("] PAUSE COMPLETE");
            servoData[s].state = 1;
            servoData[s].timeStart = millis();
        }
        break;
    }
}

void DoManualUpdate(AppConfig &appConfig, ServoData *servoData, short moveOffset)
{
    if (moveOffset == 0)
    {
        return;
    }

    for (int i = 0; i < MAX_SERVO; i++)
    {
        ServoInfo servoConfig = appConfig.data.servo[i];

        if (servoConfig.enabled)
        {
            ProfileInfo profileInfo = appConfig.data.profile[servoConfig.profileId];
            uint16_t movingTo = servoData[i].setV + moveOffset;
            // PRINT("Move offset: ", moveOffset);
            // PRINT("Current setV: ", servoData[i].setV)
            // PRINT("Moving to: ", movingTo);
            // PRINT("Profile high: ", profileInfo.high);
            // PRINT("Profile low: ", profileInfo.low);

            if (profileInfo.high < movingTo)
            {
                PRINT("Too high! Ackually moving: " , movingTo);
                movingTo = profileInfo.high;
            }
            else if (profileInfo.low > movingTo)
            {
                PRINT("Too low! Ackually moving: " , movingTo);
                movingTo = profileInfo.low;
            }

            servoData[i].setV = movingTo;
        }
    }
}