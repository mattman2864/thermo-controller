#include "rotary.h"

Button::RotaryButton(int CLK, int DT, int SW)
  : SWITCH(SW), lastButtonPress(0), button(false) {}

void RotaryButton::init() {
  pinMode(SWITCH, INPUT_PULLUP);
}

void RotaryButton::loop() {
  button = false;
  if (digitalRead(SWITCH) == LOW) {
  if (millis() - lastButtonPress > 50) {
      button = true;
  }
  lastButtonPress = millis();
  }
  delay(1);
}
bool RotaryButton::getButtonPressed() {
  return button;
}