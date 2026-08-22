#include <Arduino.h>
#include "Ubod.h"

void printCore(const char* label, const UbodCore& core) {
  Serial.print(label);
  Serial.print(" | ID: ");
  Serial.print(core.id());
  Serial.print(" | Name: \"");
  Serial.print(core.name());
  Serial.print("\" | valid: ");
  Serial.print(core.isIdValid() ? "YES" : "NO");
  Serial.print(" | state: ");

  switch (core.state()) {
    case UbodState::Initializing:
      Serial.print("INITIALIZING");
      break;
    case UbodState::Ready:
      Serial.print("READY");
      break;
    case UbodState::Running:
      Serial.print("RUNNING");
      break;
    case UbodState::Released:
      Serial.print("RELEASED");
      break;
    case UbodState::Invalid:
      Serial.print("INVALID");
      break;
  }

  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("==================================");
  Serial.println("      UBOD v0.1.5 EXPERIMENT");
  Serial.println("==================================");
  Serial.println();

  UbodCore coreA(1);
  UbodCore coreB(2);
  UbodCore coreC(3);

  Serial.println("Assigning names:");

  Serial.print("Core A: ");
  Serial.println(coreA.setName("primary") ? "SUCCESS" : "FAILED");

  Serial.print("Core B: ");
  Serial.println(coreB.setName("sensor") ? "SUCCESS" : "FAILED");

  Serial.print("Core C: ");
  Serial.println(coreC.setName("telemetry") ? "SUCCESS" : "FAILED");

  Serial.println();
  printCore("Core A", coreA);
  printCore("Core B", coreB);
  printCore("Core C", coreC);

  Serial.println();
  Serial.println("Testing duplicate names:");

  Serial.print("Core C -> \"primary\": ");
  Serial.println(coreC.setName("primary") ? "SUCCESS" : "FAILED");

  printCore("Core C", coreC);

  Serial.println();
  Serial.println("Testing rename:");

  Serial.print("Core B -> \"diagnostic\": ");
  Serial.println(coreB.setName("diagnostic") ? "SUCCESS" : "FAILED");

  printCore("Core B", coreB);

  Serial.println();
  Serial.println("Testing invalid long name:");

  Serial.print("Core A -> long name: ");
  Serial.println(
    coreA.setName("this-name-is-way-too-long")
      ? "SUCCESS"
      : "FAILED"
  );

  printCore("Core A", coreA);

  Serial.println();
  Serial.println("Testing release:");

  coreA.begin();
  coreA.update();
  coreA.release();

  printCore("Core A", coreA);

  Serial.println();
  Serial.println("Attempting rename after release:");

  Serial.print("Core A -> \"released\": ");
  Serial.println(
    coreA.setName("released")
      ? "SUCCESS"
      : "FAILED"
  );

  printCore("Core A", coreA);

  Serial.println();
  Serial.println("==================================");
  Serial.println("      EXPERIMENT COMPLETE");
  Serial.println("==================================");
}

void loop() {
}