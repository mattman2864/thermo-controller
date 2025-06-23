# Thermoelectric Controller Project
- Started with micropython and now uses arduino C++
- Heat or cool a plate in order to test the thermal efficiency of microchips
- Started in January 2025 as part of PARI internship
## Functionality
- LCD screen for output temps
- Buttons to control target temperature
- Should in theory work with any microcontroller but only tested with ESP32
## Usage
- Requires downloading `Adafruit_RGBLCDShield` and `DallasTemperature` arduino libraries
- Copy any files into `test.ino` and run them using arduino IDE
- Change pin definitiions as needed