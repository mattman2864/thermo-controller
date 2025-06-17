#pragma once
#include <Arduino.h>

class RotaryButton {
  public:
    int SWITCH;
    long lastButtonPress;
    bool button;
    RotaryButton(int SW);
    void init();
    void loop();
    bool getButtonPressed();
};