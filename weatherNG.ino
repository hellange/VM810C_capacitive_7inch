#include <EEPROM.h>
#include <SPI.h>

#include "GD2.h"

void setup()
{

  Serial.begin(9600); // JCB
  Serial.println("Hello2");

  GD.begin(0);
  GD.wr32(REG_HCYCLE, 900);//548
  GD.wr32(REG_HOFFSET, 43);
  GD.wr32(REG_HSIZE, 800);
  GD.wr32(REG_HSYNC0, 0);
  GD.wr32(REG_HSYNC1, 41);
  GD.wr32(REG_VCYCLE, 500);
  GD.wr32(REG_VOFFSET, 12);
  GD.wr32(REG_VSIZE, 480);
  GD.wr32(REG_VSYNC0, 0);
  GD.wr32(REG_VSYNC1, 10);
  GD.wr32(REG_DITHER, 1);
  GD.wr32(REG_PCLK_POL, 1);//1
  GD.wr32(REG_PCLK, 3);//5
  GD.wr(REG_ROTATE, 0);
  GD.wr(REG_SWIZZLE, 0);//3 for GD2

  Serial.println("Hello2");

}

void loop()
{
  GD.ClearColorRGB(0x0000ff);

  GD.Clear();

  GD.cmd_text(GD.w, GD.h, 31, OPT_CENTER, "Hello world");
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "Hello world");
 

  GD.swap();
}
