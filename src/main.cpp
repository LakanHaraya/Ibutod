#include <Arduino.h>
#include <Ubod.h>

UbodCore coreA(1);
UbodCore coreB(2);
UbodCore coreC(1);

void setup() {
  Serial.begin(115200);

  delay(1000); // Wait for Serial to initialize

  Serial.println("==================================");
  Serial.println("      UBOD v0.1.3 EXPERIMENT      ");
  Serial.println("==================================");

  Serial.print("Core A ID: ");
  Serial.print(coreA.id());
  Serial.print(" | valid: ");
  Serial.println(coreA.isIdValid() ? "YES" : "NO");

  Serial.print("Core B ID: ");
  Serial.print(coreB.id());
  Serial.print(" | valid: ");
  Serial.println(coreB.isIdValid() ? "YES" : "NO");

  Serial.print("Core C ID: ");
  Serial.print(coreC.id());
  Serial.print(" | valid: ");
  Serial.println(coreC.isIdValid() ? "YES" : "NO");

  coreA.begin();
  coreB.begin();
  coreC.begin();

  Serial.println();
  Serial.println("Post-begin state:");

  Serial.print("Core A: ");
  Serial.println(
    coreA.state() == UbodState::Ready ? "READY" : "NOT READY"
  );

  Serial.print("Core B: ");
  Serial.println(
    coreB.state() == UbodState::Ready ? "READY" : "NOT READY"
  );

  Serial.print("Core C: ");
  Serial.println(
    coreC.state() == UbodState::Ready ? "READY" : "NOT READY"
  );
}

void loop() {
  coreA.update();
  coreB.update();
  coreC.update();

  Serial.println("");

  Serial.print("Core A state: ");
  Serial.println(
    coreA.state() == UbodState::Running ? "RUNNING" : "OTHER"
  );

  Serial.print("Core B state: ");
  Serial.println(
    coreB.state() == UbodState::Running ? "RUNNING" : "OTHER"
  );

  Serial.print("Core C state: ");
  Serial.println(
    coreC.state() == UbodState::Running ? "RUNNING" : "OTHER"
  );

  delay(1000);
}