#pragma once

/*
This file is divided into sections to make the configuration of the hardware 
and tweaking of how it runs a little bit easier.

First sections will deal with getting the hardware configured, ie pins.

The next section deals with the configuration of the hardware:
* Screen config and colors

The last important section deals with application configuration:
* absolute limits of servos
* servo names

*/

// OLED pins
#define SCLK_PIN 13
#define MOSI_PIN 11
#define DC_PIN 26
#define CS_PIN 10
#define RST_PIN 25

// Key inputs pins
#define BUTTON_PIN 2

#define X_AXIS_PIN A0
#define Y_AXIS_PIN A1

#define X_AXIS_DEADBAND 15
#define Y_AXIS_DEADBAND 10

// BEGIN SCREEN CONFIG

/*
You can optionally rotate the display by running the line below.
Note that a value of:
0 means no rotation, 
1 means 90 clockwise,
2 means 180 degrees clockwise, 
and 
3 means 270 degrees clockwise.
*/ 
#define DISPLAY_ROTATION 0

// Screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128 

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define GREEN_DARK 0x03c2
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// END OF HARDWARE CONFIG
// BEGIN OF RUNTIME CONFIG

// UI Defaults
#define MAX_SPLASH_DISPLAYTIME 5000
#define SHOW_SPLASH  true
#define SCREEN_REFRESH_RATE 24 //Hz

#define LONG_PRESS_MS 3000
#define DOUBLE_PRESS_THRESHOLD 1000

// Applies an expo curve similar to an RC transmitter
#define JOY_EXPO .4
#define JOY_MAX_MOVE_PER_CYCLE 25

#define NUM_PROFILE 3

#define SWP_LINEAR 0   // index 0
#define SWP_SINE   1   // index 1
#define SWP_SQUARE 2   // index 2

// Servo Hardware
#define MAX_SERVO 7

#define SERVO_UPDATE_FREQ       50       // standard servo update frequency in Hz
#define SERVO_LOWER_HARDLIMIT  500       // servo abs lower hard limit
#define SERVO_UPPER_HARDLIMIT 2500       // servo abs upper hard limit

const char servoNames[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

#define DEBUG   1  // enable debugging output

#if DEBUG
#define PRINT(s, n)  do { Serial.print(F(s)); Serial.println(n); } while (false);
#define PRINTS(s)    do { Serial.print(F(s)); } while (false);
#define PRINTSLN(s)  do { Serial.println(F(s)); } while (false);
#define PRINTX(s, x) do { Serial.print(F(s)); Serial.print(F("x")); Serial.println(x, HEX); }  while (false);
#else
#define PRINT(s, n)
#define PRINTS(s)
#define PRINTSLN(s)
#define PRINTX(s, x)
#endif // DEBUG

