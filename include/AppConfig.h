#pragma once

#include "settings.h"

#include <Arduino.h>

#include "ServoInfo.h"

/**
 * @brief Settings for a profile.
 *
 */
struct ProfileInfo
{
    /**
     * @brief Setting for 0% of range.
     * 
     */
    uint16_t low;
    /**
     * @brief Setting for 100% of range.
     * 
     */
    uint16_t high;
    /**
     * @brief Setting for home position as percentage.
     * 
     */
    uint8_t home;
    /**
     * @brief Sweep type.
     * 
     */
    uint8_t sweepType; 
    /**
     * @brief Duration in milliseconds for one low->high or high->low sweep.
     * 
     */
    uint16_t sweepTime;
    /**
     * @brief Pause between sweep movements in milliseconds.
     * 
     */
    uint16_t sweepPause;
};

class AppConfig
{
protected:
    const uint16_t EEPROM_ADDR = 0;
    const uint8_t EEPROM_SIG[2] = {0x11, 0xee};

    uint16_t _eepromBase;

public:
    struct
    {
        uint8_t signature[2];

        // UI options
        bool showSplash = true;
        uint8_t tmMenu;   // menu timeout in seconds
        /**
         * @brief Splash screen time. 
         * This is the total time to display splashscreens and will
         * be shown. This value is in milliseconds.
         */
        uint32_t splashDisplayTime;
        bool autoPage;    // automatically page through the main display

        // Safety limits for signal setting
        uint16_t limLow;  // low limit in milliseconds
        uint16_t limHigh; // high limit in milliseconds

        /**
         * @brief Servo signal options.
         * 
         */
        ServoInfo servo[MAX_SERVO];

        /**
         * @brief Profile information.
         * 
         */
        ProfileInfo profile[NUM_PROFILE];

    } data;

    AppConfig(uint16_t eepromBase = 0);

    void reset(void);
    void begin(void);
    void save(void);
    bool load(void);
};