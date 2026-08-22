#include <Arduino.h>
#include <Ubod.h>

void setup() {
  Ubod.begin();
}

void loop() {
  Ubod.update();
}