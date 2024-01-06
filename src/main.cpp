#include "settings.h"

#include "OLED1in5_RGB_Driver.h"
#include "GUI_paint.h"
#include "Debug.h"
#include "SplashImageData.h"
#include "Utilities.h"
#include <SPI.h>

OLED1in5_RGB_Driver *oledDriver;
OLEDPainter *painter;

void setup()
{
  //set Serial
  Serial.begin(115200);
  SPI.begin();

  oledDriver = new OLED1in5_RGB_Driver(OLED_RST, OLED_CS, OLED_DC);
  painter = new OLEDPainter(*oledDriver);
  
  Serial.print(F("OLED_Init()...\r\n"));
  oledDriver->Init();
  delay(250); 
  oledDriver->Clear();  
  
  //1.Create a new image size
  UBYTE *BlackImage;
  UWORD Imagesize = ((OLED_1in5_WIDTH%2==0)? (OLED_1in5_WIDTH/2): (OLED_1in5_WIDTH/2+1)) * OLED_1in5_HEIGHT;
  if((BlackImage = (UBYTE *)malloc(Imagesize/8)) == NULL) { //No enough memory
      Serial.print("Failed to apply for black memory...\r\n");
      return;
  }
  Serial.print("Paint_NewImage\r\n");
  painter->NewImage(BlackImage, OLED_1in5_RGB_WIDTH, OLED_1in5_RGB_HEIGHT, 270, BLACK);  
  painter->SetScale(65);

  oledDriver->Display_Part(splashImageData, 0, 0, 128, 128);
  delay(5000);
}

void loop()
{
  // 2.Write directly to memory through the GUI 
    Serial.print("Drawing:page 1\r\n");
    painter->DrawPoint(20, 20, BLUE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    painter->DrawPoint(40, 20, BRED, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    painter->DrawPoint(60, 20, GRED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    
    painter->DrawLine(10, 10, 10, 25, GBLUE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    painter->DrawLine(30, 10, 30, 25, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    painter->DrawLine(50, 10, 50, 25, MAGENTA, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    painter->DrawLine(70, 10, 70, 25, GREEN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    
    painter->DrawCircle(30, 90, 20, CYAN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    painter->DrawRectangle(15, 75, 45, 105, BROWN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);   
    painter->DrawCircle(80, 80, 25, BROWN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    painter->DrawRectangle(65, 65, 95, 95, CYAN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Driver_Delay_ms(2000);      
    oledDriver->Clear(); 
    
    // Drawing on the image
    Serial.print("Drawing:page 2\r\n");
    for(UBYTE i=0; i<16; i++){
      painter->DrawRectangle(0, i*8, 127, (i+1)*8, i*4095, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }     
    Driver_Delay_ms(2000);
    oledDriver->Clear();  
    
    // Drawing on the image
    Serial.print("Drawing:page 3\r\n");     
    painter->DrawString_EN(10, 0, "waveshare", &Font16, BLACK, BLUE);
    painter->DrawNum(10, 30, "123.4567", &Font12, 2, RED, BLACK); 
    Driver_Delay_ms(2000);    
    oledDriver->Clear();   
    
    // show the array image
    Serial.print("Drawing:page 4\r\n");
    oledDriver->Display_Part(splashImageData, 0, 0, 128, 128);
    Driver_Delay_ms(2000);    
    oledDriver->Clear();  
}