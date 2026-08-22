#include <Arduino.h>
#include <Ubod.h>

UbodCore coreA(1);
UbodCore coreB(2);
UbodCore coreC(1);

void printState(const char* name, const UbodCore& core)
{
  Serial.print(name);
  Serial.print(" | ID: ");
  Serial.print(core.id());
  Serial.print(" | ID valid: ");
  Serial.print(core.isIdValid() ? "YES" : "NO");
  Serial.print(" | state: ");

  switch (core.state())
  {
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

  Serial.print(" | uptime: ");
  Serial.print(core.uptime());
  Serial.println(" ms");
}

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==================================");
  Serial.println("      UBOD v0.1.4 EXPERIMENT");
  Serial.println("==================================");

  // --------------------------------------------------
  // 1. Identity validation
  // --------------------------------------------------

  Serial.println();
  Serial.println("Identity validation:");

  printState("Core A", coreA);
  printState("Core B", coreB);
  printState("Core C", coreC);

  // --------------------------------------------------
  // 2. Begin valid instances
  // --------------------------------------------------

  coreA.begin();
  coreB.begin();
  coreC.begin();

  Serial.println();
  Serial.println("Post-begin state:");

  printState("Core A", coreA);
  printState("Core B", coreB);
  printState("Core C", coreC);

  // --------------------------------------------------
  // 3. Run valid instances
  // --------------------------------------------------

  coreA.update();
  coreB.update();
  coreC.update();

  Serial.println();
  Serial.println("Post-update state:");

  printState("Core A", coreA);
  printState("Core B", coreB);
  printState("Core C", coreC);

  // --------------------------------------------------
  // 4. Release Core A
  // --------------------------------------------------

  Serial.println();
  Serial.println("Releasing Core A...");

  coreA.release();

  printState("Core A", coreA);

  // --------------------------------------------------
  // 5. Attempt to reuse released ID
  // --------------------------------------------------

  Serial.println();
  Serial.println("Creating Core D with released ID 1...");

  UbodCore coreD(1);

  printState("Core D", coreD);

  coreD.begin();

  Serial.println();
  Serial.println("Core D after begin:");

  printState("Core D", coreD);

  // --------------------------------------------------
  // 6. Attempt to revive Core A
  // --------------------------------------------------

  Serial.println();
  Serial.println("Attempting to restart Core A...");

  coreA.begin();
  coreA.update();

  printState("Core A", coreA);

  Serial.println();
  Serial.println("==================================");
  Serial.println("      EXPERIMENT COMPLETE");
  Serial.println("==================================");
}

void loop()
{
    // No continuous test required for v0.1.4.
}