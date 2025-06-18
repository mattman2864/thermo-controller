#define CLK 33
#define DT 12

volatile int dir = 0;
volatile bool timerflag = false;
int timer = millis();
int num = 0;

void update() {
  if (digitalRead(DT) == LOW) {
    dir = 1;
  } else {
    dir = -1;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(DT, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  attachInterrupt(CLK, update, RISING);
}

void loop() {
  if (dir && timerflag) {
    num += dir;
    // Serial.print(num);
    // Serial.print(" : ");
    Serial.println(dir);
    timerflag = false;
    timer = millis();
  }
  if ((!timerflag) && (millis() - timer >= 0)) {
    timerflag = true;
  }
  dir = 0;
}
