#pragma once

#include <Arduino.h>

/**
 * @brief Servo signal options
 * 
 */
struct ServoInfo
{
    /**
     * @brief True if servo is enabled for output.
     *
     */
    bool enabled;
    /**
     * @brief Configured profile to use.
     *
     */
    uint8_t profileId;
};