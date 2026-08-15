#include <Arduino.h>

void blink() {
  Serial.println("Blinking...");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Serial.println("Blinking again...");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  blink();
}