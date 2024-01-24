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

    // oled.drawRect(0, baseOffset - 2, SCREEN_WIDTH, 128 - baseOffset, BLACK);
    for (int i = 0; i < rows; i++)
    {
        String lineOfText = "";
        for (int j = i * perRow; j < (i * perRow + perRow) && j < totalEnabled; j++)
        {
            lineOfText.append((char)(65 + j));
            lineOfText.append(": ");
            lineOfText.append(enabledServos[j].curV);
            lineOfText.append("ms ");
        }

        PRINT("Line: ", lineOfText);

        char buf[lineOfText.length()];
        lineOfText.toCharArray(buf, lineOfText.length());

        oled.setTextColor(WHITE, BLACK);
        oled.setTextSize(1);

        int y = baseOffset + i * 9;
        Display::DrawCenteredLineTextString(oled, buf, 0, y);
    }
}