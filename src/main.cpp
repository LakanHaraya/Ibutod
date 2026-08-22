#include <Arduino.h>
#include <Ubod.h>

UbodCore coreA;
UbodCore coreB;

void setup() {
  Serial.begin(115200);

  delay(1000); // Wait for Serial to initialize

  Serial.println("==================================");
  Serial.println("      UBOD v0.1.1 EXPERIMENT      ");
  Serial.println("==================================");

  coreA.begin();
  coreB.begin();

  Serial.println("Core A: Initialized");
  Serial.println("Core B: Initialized");

  Serial.print("Core A ready: ");
  Serial.println(coreA.isReady() ? "YES" : "NO");

  Serial.print("Core B ready: ");
  Serial.println(coreB.isReady() ? "YES" : "NO");
}

void loop() {
  coreA.update();
  coreB.update();

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint >= 1000 ){
    lastPrint = millis();

    Serial.print("Core A uptime: ");
    Serial.print(coreA.uptime());
    Serial.print(" ms | ");

    Serial.print("Core B uptime: ");
    Serial.print(coreB.uptime());
    Serial.println(" ms");
  }
}