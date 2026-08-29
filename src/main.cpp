#include <Arduino.h>
#include "Ubod.h"

Salalayan sensor("Sensor");

Sapad imu;
Sapad gnss;

// --------------------------------------------------
// Helpers
// --------------------------------------------------

void printResult(const char* test, bool result) {
    Serial.print(test);
    Serial.print(": ");
    Serial.println(result ? "PASS" : "FAIL");
}

const char* availabilityText(SalpakanAvailability availability) {
    return availability == SalpakanAvailability::Free
        ? "FREE"
        : "OCCUPIED";
}

const char* enablementText(const Salpakan* salpakan) {
    if (salpakan == nullptr) {
        return "N/A";
    }

    return salpakan->isEnabled()
        ? "ENABLED"
        : "DISABLED";
}

void printSalalayan() {
    Serial.println();
    Serial.println("+----+----------------+----------+------------+-----------+");
    Serial.println("| ID | NAME           | SAPAD    | ENABLEMENT | AVAIL     |");
    Serial.println("+----+----------------+----------+------------+-----------+");

    for (unsigned int id = 1; id <= sensor.capacity(); ++id) {
        const Salpakan* salpakan = sensor.get(id);

        Serial.print("| ");
        Serial.print(id);
        Serial.print("  | ");

        if (salpakan != nullptr) {
            Serial.print(salpakan->name());
        }

        Serial.print(" | ");

        if (salpakan != nullptr && salpakan->hasSapad()) {
            Serial.print("ATTACHED ");
        } else {
            Serial.print("NONE     ");
        }

        Serial.print(" | ");

        Serial.print(enablementText(salpakan));
        Serial.print("    ");

        Serial.print("| ");

        if (salpakan != nullptr) {
            Serial.print(availabilityText(salpakan->availability()));
        }

        Serial.println("      |");
    }

    Serial.println("+----+----------------+----------+------------+-----------+");
}

// --------------------------------------------------
// Experiment
// --------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("============================================================");
    Serial.println("             UBOD v0.1.17 EXPERIMENT");
    Serial.println("      Salalayan Identity & Mediated Control");
    Serial.println("============================================================");

    // --------------------------------------------------
    // 1. Unnamed Salalayan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Optional Salalayan Name");
    Serial.println("------------------------------------------------------------");

    Salalayan unnamed;

    printResult(
        "Unnamed Salalayan has empty name",
        unnamed.name()[0] == '\0'
    );

    printResult(
        "Named Salalayan is Sensor",
        strcmp(sensor.name(), "Sensor") == 0
    );

    // --------------------------------------------------
    // 2. Rename / Clear Name
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Salalayan Naming");
    Serial.println("------------------------------------------------------------");

    bool result = unnamed.setName("Test");

    printResult(
        "setName(Test)",
        result
    );

    printResult(
        "Name == Test",
        strcmp(unnamed.name(), "Test") == 0
    );

    result = unnamed.setName(nullptr);

    printResult(
        "setName(nullptr) clears name",
        result
    );

    printResult(
        "Name is empty after clear",
        unnamed.name()[0] == '\0'
    );

    // --------------------------------------------------
    // 3. Initial Salpakan State
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Initial Salpakan State");
    Serial.println("------------------------------------------------------------");

    Salpakan* slot1 = sensor.get(1);
    Salpakan* slot2 = sensor.get(2);

    printResult(
        "Salpakan #1 exists",
        slot1 != nullptr
    );

    printResult(
        "Salpakan #2 exists",
        slot2 != nullptr
    );

    printResult(
        "Salpakan #1 initially FREE",
        slot1 != nullptr && slot1->isFree()
    );

    printResult(
        "Salpakan #1 initially DISABLED",
        slot1 != nullptr && !slot1->isEnabled()
    );

    printSalalayan();

    // --------------------------------------------------
    // 4. Attach Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Attach Sapad");
    Serial.println("------------------------------------------------------------");

    result = sensor.attach(1, &imu);

    printResult(
        "Attach IMU to Salpakan #1",
        result
    );

    result = sensor.attach(2, &gnss);

    printResult(
        "Attach GNSS to Salpakan #2",
        result
    );

    printSalalayan();

    // --------------------------------------------------
    // 5. Enable Through Salalayan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Salalayan-Mediated Enable");
    Serial.println("------------------------------------------------------------");

    result = sensor.enable(1);

    printResult(
        "sensor.enable(1)",
        result
    );

    printResult(
        "Salpakan #1 is ENABLED",
        slot1->isEnabled()
    );

    printSalalayan();

    // --------------------------------------------------
    // 6. Disable Through Salalayan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Salalayan-Mediated Disable");
    Serial.println("------------------------------------------------------------");

    result = sensor.disable(1);

    printResult(
        "sensor.disable(1)",
        result
    );

    printResult(
        "Salpakan #1 is DISABLED",
        !slot1->isEnabled()
    );

    printSalalayan();

    // --------------------------------------------------
    // 7. Enable Empty Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Enable Empty Salpakan");
    Serial.println("------------------------------------------------------------");

    Salpakan* slot3 = sensor.get(3);

    result = sensor.enable(3);

    printResult(
        "Enable empty Salpakan #3 rejected",
        !result
    );

    printResult(
        "Salpakan #3 remains DISABLED",
        slot3 != nullptr && !slot3->isEnabled()
    );

    printSalalayan();

    // --------------------------------------------------
    // 8. Invalid ID
    // --------------------------------------------------

    Serial.println();
    Serial.println("[8] Invalid Salpakan ID");
    Serial.println("------------------------------------------------------------");

    result = sensor.enable(0);

    printResult(
        "enable(0) rejected",
        !result
    );

    result = sensor.disable(0);

    printResult(
        "disable(0) rejected",
        !result
    );

    result = sensor.enable(sensor.capacity() + 1);

    printResult(
        "enable(Capacity + 1) rejected",
        !result
    );

    // --------------------------------------------------
    // 9. Attachment Boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[9] Attachment Boundary");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Salpakan #1 still has IMU",
        slot1->sapad() == &imu
    );

    printResult(
        "Salpakan #2 still has GNSS",
        slot2->sapad() == &gnss
    );

    printResult(
        "Salpakan #1 is OCCUPIED",
        slot1->isOccupied()
    );

    printResult(
        "Salpakan #2 is OCCUPIED",
        slot2->isOccupied()
    );

    // --------------------------------------------------
    // 10. Disable Before Detach
    // --------------------------------------------------

    Serial.println();
    Serial.println("[10] Disable Before Detach");
    Serial.println("------------------------------------------------------------");

    result = sensor.disable(1);

    printResult(
        "Disable Salpakan #1",
        result
    );

    result = sensor.detach(1);

    printResult(
        "Detach IMU from Salpakan #1",
        result
    );

    printResult(
        "Salpakan #1 is FREE",
        slot1->isFree()
    );

    printResult(
        "Salpakan #1 has no Sapad",
        !slot1->hasSapad()
    );

    printResult(
        "Salpakan #1 remains DISABLED",
        !slot1->isEnabled()
    );

    printSalalayan();

    // --------------------------------------------------
    // 11. Final Invariant
    // --------------------------------------------------

    Serial.println();
    Serial.println("[11] Final Invariant");
    Serial.println("------------------------------------------------------------");

    bool invariant =
        slot1 != nullptr &&
        slot1->isFree() &&
        !slot1->hasSapad() &&
        !slot1->isEnabled();

    printResult(
        "FREE Salpakan has no Sapad and is DISABLED",
        invariant
    );

    // --------------------------------------------------
    // 12. Architectural Boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[12] Architectural Boundary");
    Serial.println("------------------------------------------------------------");

    Serial.println("Salalayan provides mediated Salpakan control.");
    Serial.println("Salpakan retains its own enablement state.");
    Serial.println("Salalayan does not own Sapad objects.");
    Serial.println("No lifecycle behavior was added to Salalayan.");
    Serial.println("No scheduler or system policy was introduced.");

    // --------------------------------------------------
    // Complete
    // --------------------------------------------------

    Serial.println();
    Serial.println("============================================================");
    Serial.println("               EXPERIMENT COMPLETE");
    Serial.println("============================================================");
}

void loop() {
}