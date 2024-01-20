#pragma once

#include <ArduinoLog.h>

// OLED pins
#define SCLK_PIN 18
#define MOSI_PIN 19
#define DC_PIN 20
#define CS_PIN 22
#define RST_PIN 21

// Screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128 

// Key inputs pins
#define BUTTON_PIN 0

#define X_AXIS_PIN 26
#define Y_AXIS_PIN 27

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define LOG_LEVEL LOG_LEVEL_TRACE
// #define LOG_LEVEL LOG_LEVEL_NOTICE
// #define LOG_LEVEL LOG_LEVEL_INFO
// #define DISABLE_LOGGING 