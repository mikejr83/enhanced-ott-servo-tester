/******************************************************************************
**************************Hardware interface layer*****************************
* | file      	:	DEV_Config.h
* |	version		  :	V1.0
* | date		    :	2020-06-16
* | function	  :	Provide the hardware underlying interface	
******************************************************************************/
#pragma once

#include <SPI.h>
#include <Wire.h>
#include <avr/pgmspace.h>
/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define OLED_1in5_RGB_WIDTH  128//OLED width
#define OLED_1in5_RGB_HEIGHT 128 //OLED height