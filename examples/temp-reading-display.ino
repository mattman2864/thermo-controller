#include <string>
#include <cmath>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Rotary encoder pins
#define CLK 33
#define DT 12

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

float increment = 1;
float temperature = 0.0; // This will eventually be read by thermocouple

int t = millis();

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
volatile int dir = 0;

void IRAM_ATTR encoderChange() {
  if (digitalRead(DT) == LOW) {
    dir = -1;
  } else {
    dir = 1;
  }
}

void setup() {
  Wire.begin(22, 20);
  lcd.begin(16, 2);
  sensors.begin();
  Serial.begin(115200);

  delay(100);

  // Set encoder pins as inputs
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  // Call updateEncoder() when a change is seen on CLK pin
  attachInterrupt(digitalPinToInterrupt(CLK), encoderChange, RISING);

  initdisplay();
}

void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  if (dir) {
    counter += dir;
    dir = 0;
  }
  
  if (millis() - t > 1000) {
    display();
    t = millis();
  }
  
  Serial.println(counter);
}

void initdisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Trgt: ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
}

void display() {
  lcd.setCursor(6, 0);
  float targetTemp = increment * counter;
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