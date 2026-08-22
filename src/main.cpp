#include <Arduino.h>
#include <Ubod.h>

UbodCore coreA;
UbodCore coreB;

void setup() {
  Serial.begin(115200);

  delay(1000); // Wait for Serial to initialize

  Serial.println("==================================");
  Serial.println("      UBOD v0.1.2 EXPERIMENT      ");
  Serial.println("==================================");

  Serial.println("Core A: initial state:");
  Serial.println("Core B: initial state:");
  
  coreA.begin();

  Serial.println("Core A: begin()");
  Serial.print("Core A state: ");
  Serial.println(
    coreA.state() == UbodState::Ready ? "READY" : "OTHER"
  );

  // Mahalagang eksperimento: 
  // Isang segundo ang pagitan ng inisyalisasyon ng `coreA` at `coreB`.
  delay(1000);

  coreB.begin();

  Serial.println("Core B: begin()");
  Serial.print("Core B state: ");
  Serial.println(
    coreB.state() == UbodState::Ready ? "READY" : "OTHER"
  );
}

void loop() {
  coreA.update();

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint >= 1000 ){
    lastPrint = millis();

    coreB.update();

    Serial.println("");

    Serial.print("Core A uptime: ");
    Serial.print(coreA.uptime());
    Serial.print(" ms | state: ");
    Serial.println(
      coreA.state() == UbodState::Running ? "RUNNING" : "OTHER"
    );

    Serial.print("Core B uptime: ");
    Serial.print(coreB.uptime());
    Serial.print(" ms | state: ");
    Serial.println(
      coreB.state() == UbodState::Running ? "RUNNING" : "OTHER"
    );
  }
}