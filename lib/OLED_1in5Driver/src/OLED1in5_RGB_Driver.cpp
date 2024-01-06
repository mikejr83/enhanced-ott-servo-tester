/*****************************************************************************
* | File      	:   OLED_Driver.cpp
* | Author      :   Waveshare team
* | Function    :   1.5inch RGB OLED Module Drive function
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2020-08-20
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "OLED1in5_RGB_Driver.h"
#include "Utilities.h"
#include "stdio.h"

OLED1in5_RGB_Driver::OLED1in5_RGB_Driver(int rstPin, int csPin, int dcPin) : rstPin(rstPin),
                                                                             csPin(csPin),
                                                                             dcPin(dcPin)
{
}

/*******************************************************************************
function:
            Hardware reset
*******************************************************************************/
void OLED1in5_RGB_Driver::Reset(void)
{
  digitalWrite(rstPin, HIGH);
  Driver_Delay_ms(100);
  digitalWrite(rstPin, LOW);
  Driver_Delay_ms(100);
  digitalWrite(rstPin, HIGH);
  Driver_Delay_ms(100);
}

/*******************************************************************************
function:
            Write register address and data
*******************************************************************************/
void OLED1in5_RGB_Driver::WriteReg(uint8_t Reg)
{
  digitalWrite(dcPin, LOW);
  digitalWrite(csPin, LOW);
  SPI4W_Write_Byte(Reg);
  digitalWrite(csPin, HIGH);
}

void OLED1in5_RGB_Driver::WriteData(uint8_t Data)
{
  digitalWrite(dcPin, HIGH);
  digitalWrite(csPin, LOW);
  SPI4W_Write_Byte(Data);
  digitalWrite(csPin, HIGH);
}

/*******************************************************************************
function:
        Common register initialization
*******************************************************************************/
void OLED1in5_RGB_Driver::InitReg(void)
{
  WriteReg(0xfd); // command lock
  WriteData(0x12);
  WriteReg(0xfd); // command lock
  WriteData(0xB1);

  WriteReg(0xae); // display off
  WriteReg(0xa4); // Normal Display mode

  WriteReg(0x15);  // set column address
  WriteData(0x00); // column address start 00
  WriteData(0x7f); // column address end 127
  WriteReg(0x75);  // set row address
  WriteData(0x00); // row address start 00
  WriteData(0x7f); // row address end 127

  WriteReg(0xB3);
  WriteData(0xF1);

  WriteReg(0xCA);
  WriteData(0x7F);

  WriteReg(0xa0);  // set re-map & data format
  WriteData(0x74); // Horizontal address increment

  WriteReg(0xa1);  // set display start line
  WriteData(0x00); // start 00 line

  WriteReg(0xa2); // set display offset
  WriteData(0x00);

  WriteReg(0xAB);
  WriteReg(0x01);

  WriteReg(0xB4);
  WriteData(0xA0);
  WriteData(0xB5);
  WriteData(0x55);

  WriteReg(0xC1);
  WriteData(0xC8);
  WriteData(0x80);
  WriteData(0xC0);

  WriteReg(0xC7);
  WriteData(0x0F);

  WriteReg(0xB1);
  WriteData(0x32);

  WriteReg(0xB2);
  WriteData(0xA4);
  WriteData(0x00);
  WriteData(0x00);

  WriteReg(0xBB);
  WriteData(0x17);

  WriteReg(0xB6);
  WriteData(0x01);

  WriteReg(0xBE);
  WriteData(0x05);

  WriteReg(0xA6);
}

/********************************************************************************
function:
            initialization
********************************************************************************/
void OLED1in5_RGB_Driver::Init(void)
{
  // Hardware reset
  Reset();

  // Set the initialization register
  InitReg();
  Driver_Delay_ms(200);

  // Turn on the OLED display
  WriteReg(0xAF);
}

/********************************************************************************
function:
            Clear screen
********************************************************************************/
void OLED1in5_RGB_Driver::Clear(void)
{
  UWORD i;

  WriteReg(0x15);
  WriteData(0);
  WriteData(127);
  WriteReg(0x75);
  WriteData(0);
  WriteData(127);
  // fill!
  WriteReg(0x5C);

  for (i = 0; i < OLED_1in5_RGB_WIDTH * OLED_1in5_RGB_HEIGHT * 2; i++)
  {
    WriteData(0x00);
  }
}

/********************************************************************************
function:   Draw a point
********************************************************************************/
void OLED1in5_RGB_Driver::Set_Point(UBYTE Xpoint, UBYTE Ypoint, UWORD Color)
{
  WriteReg(0x15);
  WriteData(Xpoint);
  WriteData(Xpoint);
  WriteReg(0x75);
  WriteData(Ypoint);
  WriteData(Ypoint);
  // fill!
  WriteReg(0x5C);

  WriteData(Color >> 8);
  WriteData(Color);
}

/********************************************************************************
function:   Update all memory to OLED
********************************************************************************/
void OLED1in5_RGB_Driver::Display(const UBYTE *Image)
{
  UWORD i, j, temp;

  WriteReg(0x15);
  WriteData(0);
  WriteData(127);
  WriteReg(0x75);
  WriteData(0);
  WriteData(127);
  // fill!
  WriteReg(0x5C);

  for (i = 0; i < OLED_1in5_RGB_HEIGHT; i++)
    for (j = 0; j < OLED_1in5_RGB_WIDTH * 2; j++)
    {
      temp = Image[j + i * 256];
      WriteData(temp);
    }
}

/********************************************************************************
function:   Update all memory to OLED
********************************************************************************/
void OLED1in5_RGB_Driver::Display_Part(const UBYTE *Image, UBYTE Xstart, UBYTE Ystart, UBYTE Xend, UBYTE Yend)
{
  UWORD i, j, temp;

  WriteReg(0x15);
  WriteData(Xstart);
  WriteData(Xend - 1);
  WriteReg(0x75);
  WriteData(Ystart);
  WriteData(Yend - 1);
  // fill!
  WriteReg(0x5C);

  for (i = 0; i < Yend - Ystart; i++)
    for (j = 0; j < (Xend - Xstart) * 2; j++)
    {
      temp = pgm_read_byte(&Image[j + i * (Xend - Xstart) * 2]);
      WriteData(temp);
    }
}
