#include <string>
#include <cmath>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Thermocouple data pin
#define ONE_WIRE_BUS 32

// LCD backlight colors
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7


float increment = 1; // Target temperature change in C per button press
float temperature = 0.0; // Thermocouple reading in deg C

int t = millis(); // Timeout for LCD updates
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield(); // LCD object

// Initializing thermocouple
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  Wire.begin(22, 20); // SDA: 22, SCL: 20 for i2c
  lcd.begin(16, 2); // 16x2 lcd display
  sensors.begin(); // initializing thermocouple over onewire
  Serial.begin(115200); // initializing serial for debugging
  
  // Printing static text only once for efficiency and faster clock times
  initdisplay();
}

void loop() {
  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    if (buttons & BUTTON_UP) {
      targetTemp += increment;
    }
    if (buttons & BUTTON_DOWN) {
      targetTemp -= increment;
    }
  }

  // record temperatures retrieved by thermocouple sensors
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  
  // update display every 1000ms
  // I would rather do this in a backround process but I'm not sure how to do that
  if (millis() - t > 500) {
    display();
    t = millis();
  }
}

// static text for display printed once for efficiency
void initdisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Trgt: ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
}

// dynamic text displaying temperatures
void display() {
  lcd.setCursor(6, 0);
  float targetTemp = increment * counter;
  lcd.print(targetTemp);
//   int length = std::to_string(targetTemp).length() - 4;
  lcd.setCursor(12, 0);
  lcd.print("C");

  lcd.setCursor(6, 1);
  lcd.print(temperature);
//   length = std::to_string(temperature).length() - 4;
  lcd.setCursor(12, 1);
  lcd.print("C");
}