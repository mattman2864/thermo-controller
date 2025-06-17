#include "rotary.h"

RotaryEncoder encoder(12, 33, 27);

void setup() {
  globalCount = &(encoder.count);
  attachInterrupt(digitalPinToInterrupt(encoder.PIN1), RotaryEncoder::increment, RISING);
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
  if (encoder.change) {
    Serial.print("Count: ");
    Serial.print(encoder.count);
    Serial.print(" (");
    Serial.print(dir);
    Serial.println(")");
  }
}