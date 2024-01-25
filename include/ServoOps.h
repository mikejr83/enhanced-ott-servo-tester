#pragma once

#include <Arduino.h>
#include <Servo.h>

struct ServoData
{
    uint16_t curV, setV; // current and setpoit value setting
    uint32_t timeStart;  // sweep start in microseconds
    uint16_t timeDelta;  // in microseconds
    int8_t deltaPct;     // percentage increment +/-
    int16_t sweepPct;    // Current percentage through
    uint8_t state;       // Current sweep ruinning state
};

void CheckMovement(ServoData *servoData, Servo *servo);

void SetServoSPPct(AppConfig &appConfig, ServoData *servoData, uint8_t servoIndex, uint8_t percentage);

void SetAllServoHome(AppConfig &appConfig, ServoData *servoData);

void DoServoSweep(AppConfig &appConfig, ServoData *servoData, uint8_t s, bool restart);
void DoManualUpdate(AppConfig &appConfig, ServoData *servoData, short moveOffset);
void DoManualUpdateToPercentage(AppConfig &appConfig, ServoData *servoData, double percentage);