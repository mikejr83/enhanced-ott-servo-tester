/******************************************************************************
**************************Hardware interface layer*****************************
* | file      	:	DEV_Config.h
* |	version		  :	V1.0
* | date		    :	2020-06-16
* | function	  :	Provide the hardware underlying interface	
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <SPI.h>
#include <Wire.h>
#include <avr/pgmspace.h>
/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#ifndef USE_SPI_4W
#define USE_SPI_4W  1
#endif
#ifndef USE_IIC
#define USE_IIC     0
#endif

#ifndef IIC_CMD
#define IIC_CMD        0X00
#endif
#ifndef IIC_RAM
#define IIC_RAM        0X40
#endif

/****************************************************************************************
    //Use the  library function definition
*****************************************************************************************/
//GPIO config
#ifndef OLED_CS
#define OLED_CS 10
#endif
#define OLED_CS_0     digitalWrite(OLED_CS, LOW)
#define OLED_CS_1     digitalWrite(OLED_CS, HIGH)

#ifndef OLED_RST
#define OLED_RST 8
#endif
#define OLED_RST_0    digitalWrite(OLED_RST, LOW)
#define OLED_RST_1    digitalWrite(OLED_RST, HIGH)

#ifndef OLED_DC
#define OLED_DC 7
#endif
#define OLED_DC_0     digitalWrite(OLED_DC, LOW)
#define OLED_DC_1     digitalWrite(OLED_DC, HIGH)

#endif
