/************************************************
 *  Next generation weather station base
 *  
 *  FT81x graphics driver is copied from jamesbowman / gd2-lib
 *  (https://github.com/jamesbowman/gd2-lib.git)
 *  
 *  
 ************************************************/

#include <EEPROM.h>
#include <SPI.h>
#include "GD2.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing WeatherNG graphics controller FT810...");
  GD.begin(0);
  Serial.println("Initialized.");
}

void loop()
{
  GD.ClearColorRGB(0x0000ff);

  GD.Clear();

  // X centered at upper left corner
  GD.cmd_text(0, 0 , 31, OPT_CENTER, "X");

  // Text centered on screen
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "WeatherNG");
  GD.cmd_text(GD.w / 2, GD.h / 2 + 30 , 28, OPT_CENTER, "Hello, world !");

  // X centered at lower right corner
  GD.cmd_text(GD.w, GD.h, 31, OPT_CENTER, "X");


  GD.swap();
}
