#pragma once

#define USE_SPI_4W  1
#define USE_IIC     0

#define IIC_CMD        0X00
#define IIC_RAM        0X40

#define SPI_PORT spi0

/****************************************************************************************
    //Use the  library function definition
*****************************************************************************************/
//GPIO config
#define OLED_CS  17
#define OLED_RST 15
#define OLED_DC  19