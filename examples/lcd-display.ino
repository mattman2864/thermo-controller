#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>


Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

void setup() {
  Wire.begin(22, 20);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  delay(1000);
  lcd.print("TEST PROGRAM :)");
  lcd.setBacklight(WHITE);
}

void loop() {

}