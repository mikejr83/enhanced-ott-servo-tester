/******************************************************************************
**************************Hardware interface layer*****************************
* | file      	:	DEV_Config.h
* |	version		  :	V1.0
* | date		    :	2020-06-16
* | function	  :	Provide the hardware underlying interface	
******************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <SPI.h>
#include <Wire.h>
#include <avr/pgmspace.h>
/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define USE_SPI_4W  1

/****************************************************************************************
    //Use the  library function definition
*****************************************************************************************/
//GPIO config
#define OLED_CS  22
#define OLED_RST 21
#define OLED_DC  20

#define OLED_CS_0     digitalWrite(OLED_CS, LOW)
#define OLED_CS_1     digitalWrite(OLED_CS, HIGH)

#define OLED_RST_0    digitalWrite(OLED_RST, LOW)
#define OLED_RST_1    digitalWrite(OLED_RST, HIGH)

#define OLED_DC_0     digitalWrite(OLED_DC, LOW)
#define OLED_DC_1     digitalWrite(OLED_DC, HIGH)

#endif
