#include "rotary.h"

RotaryEncoder encoder(33, 27, 13);

void setup() {
  encoder.init();
  Serial.begin(9600);
}

void loop() {
  encoder.loop();
  int dir = encoder.getDirection();
  bool button = encoder.getButtonPressed();
  if (button) {
    Serial.println("Button pressed!");
    encoder.count = 0; // Reset count on button press
  }
  if (dir != 0) {
    Serial.print("Count: ");
    Serial.print(encoder.count);
    Serial.print(" (");
    Serial.print(dir);
    Serial.println(")");
  }
}