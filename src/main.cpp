#include <Arduino.h>
#include "Ubod.h"

Salalayan salalayan;

// --------------------------------------------------
// Test Sapad
// --------------------------------------------------

Sapad primaryComms;

// --------------------------------------------------
// Helpers
// --------------------------------------------------

const char* availabilityText(SalpakanAvailability value) {
    return value == SalpakanAvailability::Free
        ? "FREE"
        : "OCCUPIED";
}

const char* enablementText(bool enabled) {
    return enabled
        ? "ENABLED"
        : "DISABLED";
}

void printTestResult(
    const char* test,
    bool result,
    const Salpakan* salpakan
) {
    Serial.print(result ? "[PASS] " : "[FAIL] ");
    Serial.println(test);

    if (salpakan == nullptr) {
        return;
    }

    Serial.print("        Enablement  : ");
    Serial.println(
        enablementText(salpakan->isEnabled())
    );

    Serial.print("        Availability : ");
    Serial.println(
        availabilityText(salpakan->availability())
    );

    Serial.print("        Sapad        : ");
    Serial.println(
        salpakan->hasSapad()
            ? "ATTACHED"
            : "NONE"
    );
}

void printSlot(const Salpakan* salpakan) {
    if (salpakan == nullptr) {
        Serial.println("| NOT FOUND |");
        return;
    }

    Serial.print("| ");
    Serial.print(salpakan->id());

    Serial.print(" | ");
    Serial.print(
        salpakan->hasSapad()
            ? "YES"
            : "NO"
    );

    Serial.print(" | ");
    Serial.print(
        availabilityText(
            salpakan->availability()
        )
    );

    Serial.print(" | ");
    Serial.print(
        enablementText(
            salpakan->isEnabled()
        )
    );

    Serial.println(" |");
}

void printTable(const Salalayan& salalayan) {
    Serial.println(
        "+----+-------+--------------+-----------+"
    );
    Serial.println(
        "| ID | SAPAD | AVAILABILITY | ENABLEMENT |"
    );
    Serial.println(
        "+----+-------+--------------+-----------+"
    );

    for (unsigned int i = 1;
         i <= salalayan.capacity();
         ++i) {

        printSlot(salalayan.get(i));
    }

    Serial.println(
        "+----+-------+--------------+-----------+"
    );
}

// --------------------------------------------------
// Experiment
// --------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(2000);

    Salpakan* salpakan = salalayan.get(1);

    Serial.println();
    Serial.println(
        "============================================================"
    );
    Serial.println(
        "                 UBOD v0.1.16 EXPERIMENT"
    );
    Serial.println(
        "              Salpakan Enablement Validation"
    );
    Serial.println(
        "============================================================"
    );

    // --------------------------------------------------
    // 1. Initial State
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Initial Salpakan State");
    Serial.println(
        "------------------------------------------------------------"
    );

    printTable(salalayan);

    printTestResult(
        "Initial Salpakan is DISABLED",
        !salpakan->isEnabled(),
        salpakan
    );

    printTestResult(
        "Initial Salpakan is FREE",
        salpakan->isFree(),
        salpakan
    );

    printTestResult(
        "Initial Salpakan has NO Sapad",
        !salpakan->hasSapad(),
        salpakan
    );

    // --------------------------------------------------
    // 2. Reject Enable Without Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Enable Without Sapad");
    Serial.println(
        "------------------------------------------------------------"
    );

    bool result = salpakan->enable();

    printTestResult(
        "enable() rejected without Sapad",
        !result,
        salpakan
    );

    printTestResult(
        "Salpakan remains DISABLED",
        !salpakan->isEnabled(),
        salpakan
    );

    // --------------------------------------------------
    // 3. Attach While Disabled
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Attach Sapad While Disabled");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->attach(&primaryComms);

    printTestResult(
        "attach(primaryComms)",
        result,
        salpakan
    );

    printTestResult(
        "Sapad is attached",
        salpakan->hasSapad(),
        salpakan
    );

    printTestResult(
        "Salpakan remains DISABLED",
        !salpakan->isEnabled(),
        salpakan
    );

    // --------------------------------------------------
    // 4. Enable Occupied Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Enable Occupied Salpakan");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->enable();

    printTestResult(
        "enable() with Sapad",
        result,
        salpakan
    );

    printTestResult(
        "Salpakan becomes ENABLED",
        salpakan->isEnabled(),
        salpakan
    );

    // --------------------------------------------------
    // 5. Reject Repeated Enable
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Reject Repeated Enable");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->enable();

    printTestResult(
        "Second enable() rejected",
        !result,
        salpakan
    );

    // --------------------------------------------------
    // 6. Reject Detach While Enabled
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Reject Detach While Enabled");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->detach();

    printTestResult(
        "detach() rejected while ENABLED",
        !result,
        salpakan
    );

    printTestResult(
        "Sapad remains attached",
        salpakan->hasSapad(),
        salpakan
    );

    printTestResult(
        "Salpakan remains ENABLED",
        salpakan->isEnabled(),
        salpakan
    );

    // --------------------------------------------------
    // 7. Disable Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Disable Salpakan");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->disable();

    printTestResult(
        "disable()",
        result,
        salpakan
    );

    printTestResult(
        "Salpakan becomes DISABLED",
        !salpakan->isEnabled(),
        salpakan
    );

    // --------------------------------------------------
    // 8. Detach After Disable
    // --------------------------------------------------

    Serial.println();
    Serial.println("[8] Detach After Disable");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->detach();

    printTestResult(
        "detach() while DISABLED",
        result,
        salpakan
    );

    printTestResult(
        "Sapad reference cleared",
        !salpakan->hasSapad(),
        salpakan
    );

    printTestResult(
        "Salpakan remains DISABLED",
        !salpakan->isEnabled(),
        salpakan
    );

    // --------------------------------------------------
    // 9. Reattach After Detach
    // --------------------------------------------------

    Serial.println();
    Serial.println("[9] Reattach After Detach");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->attach(&primaryComms);

    printTestResult(
        "Reattach primaryComms",
        result,
        salpakan
    );

    printTestResult(
        "Sapad is attached again",
        salpakan->hasSapad(),
        salpakan
    );

    printTestResult(
        "Reattached Salpakan remains DISABLED",
        !salpakan->isEnabled(),
        salpakan
    );

    // --------------------------------------------------
    // 10. Final Disable + Detach
    // --------------------------------------------------

    Serial.println();
    Serial.println("[10] Final Detach Sequence");
    Serial.println(
        "------------------------------------------------------------"
    );

    result = salpakan->detach();

    printTestResult(
        "detach() while DISABLED",
        result,
        salpakan
    );

    // --------------------------------------------------
    // 11. Final Invariants
    // --------------------------------------------------

    Serial.println();
    Serial.println("[11] Final Invariants");
    Serial.println(
        "------------------------------------------------------------"
    );

    bool invariant =
        !salpakan->hasSapad() &&
        salpakan->isFree() &&
        !salpakan->isEnabled();

    printTestResult(
        "No Sapad => FREE + DISABLED",
        invariant,
        salpakan
    );

    // --------------------------------------------------
    // 12. Experimental Contract
    // --------------------------------------------------

    Serial.println();
    Serial.println("[12] Experimental Contract");
    Serial.println(
        "------------------------------------------------------------"
    );

    Serial.println(
        "Disabled + Free     -> enable()  : REJECT"
    );

    Serial.println(
        "Disabled + Free     -> attach()  : ALLOW"
    );

    Serial.println(
        "Disabled + Occupied -> enable()  : ALLOW"
    );

    Serial.println(
        "Enabled  + Occupied -> enable()  : REJECT"
    );

    Serial.println(
        "Enabled  + Occupied -> detach()  : REJECT"
    );

    Serial.println(
        "Enabled  + Occupied -> disable() : ALLOW"
    );

    Serial.println(
        "Disabled + Occupied -> detach()  : ALLOW"
    );

    // --------------------------------------------------
    // Complete
    // --------------------------------------------------

    Serial.println();
    Serial.println(
        "============================================================"
    );
    Serial.println(
        "                  EXPERIMENT COMPLETE"
    );
    Serial.println(
        "============================================================"
    );
}

void loop() {
}