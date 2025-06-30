// Blinks an LED attached to a MCP23XXX pin.

// ok to include only the one needed
// both included here to make things simple for example
#include <Adafruit_MCP23X17.h>

#define LED_PIN 7     // MCP23XXX pin LED is attached to
#define ALT_LED 6

// uncomment appropriate line
Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("MCP23017 Blink Test!");

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C()) {
    Serial.println("Error.");
    while (1);
  }

  // configure pin for output
  mcp.pinMode(LED_PIN, OUTPUT);
  mcp.pinMode(ALT_LED, OUTPUT);

  Serial.println("Looping...");
}

void loop() {
  mcp.digitalWrite(LED_PIN, HIGH);
  mcp.digitalWrite(ALT_LED, LOW);
  delay(500);
  mcp.digitalWrite(LED_PIN, LOW);
  mcp.digitalWrite(ALT_LED, HIGH);
  delay(500);
}
