#include "Display.h"

// typedef drawCenteredLineTextString =

void Display::PrintMode(RunMode runMode)
{
    // print the title first
    printModeTitle(RunModeToString(runMode));

    switch (runMode)
    {
    case RUN_MANUAL:
    case RUN_MANUAL_INIT:

        break;

    default:
        break;
    }

    printServoPositions();
}

void Display::printModeTitle(const char *titleBuf)
{
    oled.setTextColor(GREEN);
    oled.setTextSize(2);

    Display::DrawCenteredLineTextString(oled, titleBuf, 0, 0);
}

void Display::printServoPositions()
{
    ServoData enabledServos[MAX_SERVO];
    int totalEnabled = 0;
    for (int i = 0; i < MAX_SERVO; i++)
    {
        if (appConfig.data.servo[i].enabled)
        {
            enabledServos[totalEnabled++] = servoData[i];
        }
    }

    double perRow = 2;
    int rows = ceil(totalEnabled / perRow);
    int baseOffset = (128 - rows * 9) - 3;

    oled.setTextSize(1);

    for (int i = 0; i < rows; i++)
    {
        String servoName[(int)perRow];
        String currentValue[(int)perRow];
        String lineOfText = "";
        for (int j = i * perRow, k = 0; j < (i * perRow + perRow) && j < totalEnabled; j++, k++)
        {
            servoName[k] = String((char)(65 + j));
            servoName[k].append(": ");
            lineOfText.append(servoName[k]);
            currentValue[k] = String(enabledServos[j].curV);
            lineOfText.append(currentValue[k]);
            lineOfText.append(F("ms "));
        }

        PRINT("Line: ", lineOfText);

        char buf[lineOfText.length()];
        lineOfText.toCharArray(buf, lineOfText.length());

        int y = baseOffset + i * 9;

        int16_t x1, y1;
        uint16_t w, h;
        oled.getTextBounds(buf, 0, y, &x1, &y1, &w, &h);

        oled.setCursor((SCREEN_WIDTH - w) / 2, y);

        for (int i = 0; i < perRow; i++)
        {
            oled.setTextColor(WHITE, BLACK);
            oled.print(servoName[i]);

            oled.setTextColor(GREEN, BLACK);
            oled.print(currentValue[i]);

            oled.setTextColor(GREEN_DARK, BLACK);
            oled.print(F("ms "));
        }
    }
}