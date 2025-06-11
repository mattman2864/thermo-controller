#pragma once
#include <Arduino.h>

class RotaryEncoder {
  public:
    int PIN1, PIN2, SWITCH;
    int count, lastCLK, dir;
    long lastButtonPress;
    bool button;
    RotaryEncoder(int CLK, int DT, int SW);
    void init();
    void loop();
    int getDirection();
    bool getButtonPressed();
};