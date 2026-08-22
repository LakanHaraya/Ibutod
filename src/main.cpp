#include <Arduino.h>
#include "Ubod.h"

void testName(
    UbodCore& core,
    const char* testName,
    const char* value
) {
    Serial.print(testName);
    Serial.print(" -> ");

    bool result = core.setName(value);

    Serial.println(result ? "ACCEPTED" : "REJECTED");

    Serial.print("Current name: \"");
    Serial.print(core.name());
    Serial.println("\"");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("==================================");
  Serial.println("      UBOD v0.1.6 EXPERIMENT");
  Serial.println("==================================");
  Serial.println();

  UbodCore core(1);

  Serial.println("Name validation tests:");
  Serial.println();

  testName(core, "Null name", nullptr);
  testName(core, "Empty name", "");
  testName(core, "Whitespace name", "   ");
  testName(core, "Normal name", "primary");
  testName(core, "Name with hyphen", "sensor-1");
  testName(core, "Name with underscore", "core_A");
  testName(core, "Numeric name", "123");
  testName(core, "Name with spaces", "main core");

  Serial.println();
  Serial.println("Testing maximum length:");

  testName(core, "15-character name", "123456789012345");
  testName(core, "16-character name", "9876543210987654");

  Serial.println();
  Serial.println("Testing duplicate names:");

  UbodCore coreB(2);

  Serial.print("Core B -> \"primary\": ");
  Serial.println(
    coreB.setName("primary")
      ? "ACCEPTED"
      : "REJECTED"
  );
  core.setName("primary");

  Serial.print("Core A current name: \"");
  Serial.print(core.name());
  Serial.println("\"");

  Serial.print("Core B current name: \"");
  Serial.print(coreB.name());
  Serial.println("\"");

  Serial.println();
  Serial.println("Testing rename:");

  testName(coreB, "Rename to diagnostic", "diagnostic");

  Serial.println();
  Serial.println("Testing release behavior:");

  coreB.begin();
  coreB.update();
  coreB.release();

  Serial.print("Rename released Core B: ");
  Serial.println(
    coreB.setName("released")
      ? "ACCEPTED"
      : "REJECTED"
  );

  Serial.print("Core B final name: \"");
  Serial.print(coreB.name());
  Serial.println("\"");

  Serial.println();
  Serial.println("==================================");
  Serial.println("      EXPERIMENT COMPLETE");
  Serial.println("==================================");
}

void loop() {
}