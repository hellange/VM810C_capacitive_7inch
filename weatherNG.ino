/************************************************
 *  Next generation weather station base
 *  
 *  FT81x graphics driver is copied from jamesbowman / gd2-lib
 *  (https://github.com/jamesbowman/gd2-lib.git)
 *  
 *  Connections:

 VM810C          UNO

 SCK             13
 MOSI            11          
 MISO            12
 CS               8 
 5V              5V
 GND            GND


 ER-TPC070-6    UNO

 1                          GND
 2              A4          SDA
 3              A5          SCL
 4                          RESET
 5              2           INT
 6                          NC
 7              3.3V        VDD
 8                          VDD
 9                          GND
 10             GND         GND
 
 ************************************************/

#include <EEPROM.h>
#include <SPI.h>
#include "GD2.h"
#include "Wire.h"
#include "FT5xx6.h"

#define CTP_INT           2    // touch data ready for read from touch panel
FT5xx6 cmt = FT5xx6(CTP_INT);

void serialDebugOutput(int nr_of_touches, word *coordinates) {
  for (byte i = 0; i < nr_of_touches; i++){

    word x = coordinates[i * 2];
    word y= coordinates[i * 2 + 1];
    
    Serial.print("x");
    Serial.print(i);
    Serial.print("=");
    Serial.print(x);
    Serial.print(",");
    Serial.print("y");
    Serial.print(i);
    Serial.print("=");
    Serial.println(y);
  }
}

void printRawRegisterValuesToSerial(byte *registers) {
    // print raw register values
    for (int i = 0;i < FT5xx6_NUMBER_OF_REGISTERS ; i++){
      Serial.print(registers[i],HEX);
      Serial.print(",");
    }
    Serial.println("");
}
void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing FT5xx6 capacitive touch controller...");
  cmt.init(true);
  Serial.println("Initializing WeatherNG graphics controller FT810...");
  GD.begin(0);
  Serial.println("Done.");

}

byte nr_of_touches = 0;
byte registers[FT5xx6_NUMBER_OF_REGISTERS];
word coordinates[10];

void drawMainText() {
  GD.ClearColorRGB(0x0000ff);
  GD.Clear();

  // X centered at upper left corner
  GD.cmd_text(0, 0 , 31, OPT_CENTER, "X");

  // Text centered on screen
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "WeatherNG");
  GD.cmd_text(GD.w / 2, GD.h / 2 + 30 , 28, OPT_CENTER, "Hello, world !");

  // X centered at lower right corner
  GD.cmd_text(GD.w, GD.h, 31, OPT_CENTER, "X");
}



  
void drawCircle(word x, word y, word pixels) {
  GD.PointSize(16 * pixels);
  GD.Begin(POINTS);
  //GD.Vertex2ii(x, y); // vertex2ii only handles up to 512 pixels !!! Use 2f instead
  GD.Vertex2f(x * 16, y * 16);
}

void loop()
{
    drawMainText();

    if (cmt.touched()){
      serialDebugOutput(nr_of_touches, coordinates);
      //printRawRegisterValuesToSerial(registers);
      cmt.getRegisterInfo(registers);
      nr_of_touches = cmt.getTouchPositions(coordinates, registers);
      for (byte i = 0; i < nr_of_touches; i++){
        word x = coordinates[i * 2];
        word y = coordinates[i * 2 + 1];
        GD.ColorA(128); // 50% transparent
        GD.ColorRGB(0xff0000); // red
        drawCircle(x, y, 30);
        GD.ColorRGB(0xff8000); // orange
        drawCircle(x, y, 60);
      }
    }
    GD.swap();    
    delay(50);
}
