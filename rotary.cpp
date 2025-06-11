#include "rotary.h"

RotaryEncoder::RotaryEncoder(int CLK, int DT, int SW)
  : PIN1(CLK), PIN2(DT), SWITCH(SW), count(0), dir(1), lastButtonPress(0), button(false) {}

void RotaryEncoder::init() {
  pinMode(PIN1, INPUT_PULLUP);
  pinMode(PIN2, INPUT_PULLUP);
  pinMode(SWITCH, INPUT_PULLUP);
  lastCLK = digitalRead(PIN1);
}

void RotaryEncoder::loop() {
  int nowCLK = digitalRead(PIN1);
    dir = 0;
    // check when CLK changes to 1
    if (nowCLK != lastCLK && nowCLK == 1) {
    if (digitalRead(PIN2) == nowCLK) {
        // PIN1 and PIN2 are equal -> clockwise
        count++;
        dir = 1;
    } else {
        // PIN1 and PIN2 are not equal -> counter-clockwise
        count--;
        dir = -1;
    }
    }
    lastCLK = nowCLK;

    button = false;
    if (digitalRead(SWITCH) == LOW) {
    if (millis() - lastButtonPress > 50) {
        button = true;
    }
    lastButtonPress = millis();
    }
    delay(1);
}

int RotaryEncoder::getDirection() {
  return dir;
}

bool RotaryEncoder::getButtonPressed() {
  return button;
}