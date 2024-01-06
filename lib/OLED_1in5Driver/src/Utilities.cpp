#include "Utilities.h"

/********************************************************************************
  function: Hardware interface
  note:
  SPI4W_Write_Byte(value) :
    hardware SPI
  I2C_Write_Byte(value, cmd):
    hardware I2C
********************************************************************************/
void SPI4W_Write_Byte(uint8_t DATA)
{
  SPI.transfer(DATA);
}

void I2C_Write_Byte(uint8_t value, uint8_t Cmd)
{
  uint8_t Addr = 0x3c;
  Wire.beginTransmission(Addr);
  Wire.write(Cmd);
  Wire.write(value);
  Wire.endTransmission();
}

/********************************************************************************
  function: Delay function
  note:
  Driver_Delay_ms(xms) : Delay x ms
  Driver_Delay_us(xus) : Delay x us
********************************************************************************/
void Driver_Delay_ms(unsigned long xms)
{
  delay(xms);
}

void Driver_Delay_us(int xus)
{
  for (int j = xus; j > 0; j--);
}