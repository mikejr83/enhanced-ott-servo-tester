/*****************************************************************************
* | File      	:   OLED_Driver.h
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
#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H		

#include "Config.h"

/********************************************************************************
function:	
		Define the full screen height length of the display
********************************************************************************/

#define OLED_1in5_RGB_WIDTH  128//OLED width
#define OLED_1in5_RGB_HEIGHT 128 //OLED height

void SPI4W_Write_Byte(uint8_t DATA);
void I2C_Write_Byte(uint8_t value, uint8_t Cmd);

void Driver_Delay_ms(unsigned long xms);
void Driver_Delay_us(int xus);

void OLED_1in5_rgb_Init(void);
void OLED_1in5_rgb_Clear(void);
void OLED_1in5_rgb_Set_Point(UBYTE Xpoint, UBYTE Ypoint, UWORD Color);
void OLED_1in5_rgb_Display(const UBYTE *Image);
void OLED_1in5_rgb_Display_Part(const UBYTE *Image, UBYTE Xstart, UBYTE Ystart, UBYTE Xend, UBYTE Yend);

#endif  
	 
