#include <string>
#include <cmath>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "ESPRotary.h"

#define CLK 12
#define DT 33

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
ESPRotary r;

float increment = 0.25;
float temperature = 0.0; // This will eventually be read by thermocouple

int t = millis();

void setup() {
  Wire.begin(22, 20);
  lcd.begin(16, 2);
  Serial.begin(115200); 

  delay(100);

  r.begin(DT, CLK, 4);
  r.setIncrement(1);
  r.enableSpeedup(true);
  r.setSpeedupInterval(200);
  r.setSpeedupIncrement(8);
  initdisplay();

}

void loop() {
  r.loop();
  
  if (millis() - t > 500) {
    display();
    t = millis();
  }
}
void initdisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Trgt: ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
}

void display() {
  lcd.setCursor(6, 0);
  float targetTemp = 0.25 * r.getPosition();
  lcd.print(targetTemp);
  int length = std::to_string(targetTemp).length() - 4;
  lcd.setCursor(6+length, 0);
  lcd.print(" C ");

  lcd.setCursor(6, 1);
  lcd.print(temperature);
  length = std::to_string(temperature).length() - 4;
  lcd.setCursor(6+length, 1);
  lcd.print(" C ");
}