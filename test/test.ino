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
float targetTemp = 0.0;

int t = millis(); // Timeout for LCD updates
int u = millis(); // Timeout for LCD full refresh
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield(); // LCD object

float kp = 0.5;
float ki = 0.01;
float kd = 0.15;
float kt = 0.02;

float integral = 0.0;
float lastError = 0.0;

float minOutput = 0.0;
float maxOutput = 1.0;

int dt = millis();

// Initializing thermocouple
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  Wire.begin(22, 20); // SDA: 22, SCL: 20 for i2c
  lcd.begin(16, 2); // 16x2 lcd display
  delay(1000);
  initdisplay();
  sensors.begin(); // initializing thermocouple over onewire
  Serial.begin(115200); // initializing serial for debugging
  pinMode(27, OUTPUT); // initializing output PWM pin for cooler
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
  if (millis() - t > 250) {
    display();
    t = millis();
  }

  float output = calculate(temperature, millis() - dt);
  dt = millis();
  analogWrite(27, output * 255);
  
  Serial.print(targetTemp);
  Serial.print(", ");
  Serial.println(temperature);
}

// static text for display printed once for efficiency
void initdisplay() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Trgt: ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
}

// dynamic text displaying temperatures
void display() {
  lcd.setCursor(6, 0);
  lcd.print(targetTemp);
  lcd.setCursor(13, 0);
  lcd.print("C");

  lcd.setCursor(6, 1);
  lcd.print(temperature);
  lcd.setCursor(13, 1);
  lcd.print("C");
}

float calculate(float input, int dt) {
  if (dt == 0) return 0.0;
  float error = temperature - targetTemp;
  integral += error * dt;
  integral = max(-50.0f, min(integral, 50.0f));
  float derivative = (error - lastError) / dt;
  float tempDiff = temperature - 20;
  float output = kp * error + ki * integral + kd * derivative + kt * tempDiff;
  output = max(minOutput, min(output, maxOutput));
  lastError = error;
  return output;
}