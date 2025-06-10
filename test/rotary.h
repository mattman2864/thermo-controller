#include <Arduino.h>

class RotaryEncoder {
  public:
    int PIN1;
    int PIN2;
    int SWITCH;

    int count = 0;
    int lastCLK = digitalRead(PIN1);
    int dir = 1;
    bool button = false;
    RotaryEncoder(int CLK, int DT, int SW) {
      PIN1 = CLK;
      PIN2 = DT;
      SWITCH = SW;
    }

    void init() {
      pinMode(PIN1, INPUT_PULLUP);
      pinMode(PIN2, INPUT_PULLUP);
      pinMode(SWITCH, INPUT_PULLUP);
      
      lastCLK = digitalRead(CLK);
    }
}



void loop() {
  nowCLK = digitalRead(CLK);

  // check when CLK changes to 1
  if (nowCLK != lastCLK && nowCLK == 1) {
    if (digitalRead(DT) == nowCLK) {
      // CLK and DT are equal -> clockwise
      count++;
      dir = 1;
    } else {
      // CLK and DT are not equal -> counter-clockwise
      count--;
      dir = -1;
    }

    Serial.print("dir: ");
    Serial.print(dir);
    Serial.print(" | count: ");
    Serial.println(count);
  }
  lastCLK = nowCLK;

  if (digitalRead(SW) == LOW) {
    if (millis() - lastButtonPress > 50) {
      Serial.println("BUTTON");
    }
    lastButtonPress = millis();
  }


  delay(1);
}