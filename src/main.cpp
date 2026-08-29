#include <Arduino.h>
#include "Ubod.h"

Salalayan salalayan;

// --------------------------------------------------
// Test Sapad
// --------------------------------------------------

Sapad imu;
Sapad gnss;
Sapad telemetry;
Sapad diagnostics;


// --------------------------------------------------
// Helper Functions
// --------------------------------------------------

void printResult(const char* test, bool result) {
    Serial.print(test);
    Serial.print(": ");
    Serial.println(result ? "PASS" : "FAIL");
}

const char* enablementText(const Salpakan* salpakan) {
    return salpakan->isEnabled()
        ? "ENABLED"
        : "DISABLED";
}

const char* availabilityText(const Salpakan* salpakan) {
    return salpakan->isOccupied()
        ? "OCCUPIED"
        : "FREE";
}

void printTable() {
    Serial.println();
    Serial.println("+----+----------+------------+-----------+");
    Serial.println("| ID | SAPAD    | ENABLEMENT | AVAIL     |");
    Serial.println("+----+----------+------------+-----------+");

    for (
        unsigned int id = 1;
        id <= salalayan.capacity();
        ++id
    ) {
        Salpakan* salpakan = salalayan.get(id);

        Serial.print("| ");
        Serial.print(salpakan->id());

        Serial.print("  | ");

        if (salpakan->hasSapad()) {
            Serial.print("ATTACHED ");
        } else {
            Serial.print("NONE     ");
        }

        Serial.print("| ");
        Serial.print(enablementText(salpakan));

        if (salpakan->isEnabled()) {
            Serial.print("    ");
        } else {
            Serial.print("   ");
        }

        Serial.print("| ");
        Serial.print(availabilityText(salpakan));

        if (salpakan->isOccupied()) {
            Serial.print("  ");
        } else {
            Serial.print("      ");
        }

        Serial.println("|");
    }

    Serial.println("+----+----------+------------+-----------+");
}

void printAccounting() {
    Serial.println();
    Serial.print("Capacity: ");
    Serial.println(salalayan.capacity());

    Serial.print("Used: ");
    Serial.println(salalayan.used());

    Serial.print("Free: ");
    Serial.println(salalayan.free());

    Serial.print("Enabled: ");
    Serial.println(salalayan.enabled());

    Serial.print("Disabled: ");
    Serial.println(salalayan.disabled());

    Serial.print("Empty: ");
    Serial.println(salalayan.isEmpty() ? "YES" : "NO");

    Serial.print("Full: ");
    Serial.println(salalayan.isFull() ? "YES" : "NO");
}


// --------------------------------------------------
// Experiment
// --------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("============================================================");
    Serial.println("             UBOD v0.1.18 EXPERIMENT");
    Serial.println("       Salalayan Structural Introspection");
    Serial.println("============================================================");


    // --------------------------------------------------
    // [1] Initial Accounting
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Initial Salalayan State");
    Serial.println("------------------------------------------------------------");

    printAccounting();
    printTable();

    printResult(
        "Salalayan initially EMPTY",
        salalayan.isEmpty()
    );

    printResult(
        "Used == 0",
        salalayan.used() == 0
    );

    printResult(
        "Enabled == 0",
        salalayan.enabled() == 0
    );


    // --------------------------------------------------
    // [2] Attach Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Attach Sapad");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Attach IMU to #1",
        salalayan.attach(1, &imu)
    );

    printResult(
        "Attach GNSS to #2",
        salalayan.attach(2, &gnss)
    );

    printResult(
        "Attach Telemetry to #3",
        salalayan.attach(3, &telemetry)
    );

    printAccounting();
    printTable();


    // --------------------------------------------------
    // [3] Occupancy Accounting
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Occupancy Accounting");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Used == 3",
        salalayan.used() == 3
    );

    printResult(
        "Free == Capacity - 3",
        salalayan.free() == salalayan.capacity() - 3
    );

    printResult(
        "Used + Free == Capacity",
        salalayan.used() +
        salalayan.free()
        ==
        salalayan.capacity()
    );


    // --------------------------------------------------
    // [4] Enable Selected Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Enable Selected Salpakan");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Enable Salpakan #1",
        salalayan.enable(1)
    );

    printResult(
        "Enable Salpakan #3",
        salalayan.enable(3)
    );

    printAccounting();
    printTable();


    // --------------------------------------------------
    // [5] Enablement Accounting
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Enablement Accounting");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Enabled == 2",
        salalayan.enabled() == 2
    );

    printResult(
        "Disabled == Capacity - 2",
        salalayan.disabled() ==
        salalayan.capacity() - 2
    );

    printResult(
        "Enabled + Disabled == Capacity",
        salalayan.enabled() +
        salalayan.disabled()
        ==
        salalayan.capacity()
    );


    // --------------------------------------------------
    // [6] Occupancy vs Enablement
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Occupancy vs Enablement");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Used != Enabled",
        salalayan.used() != salalayan.enabled()
    );

    printResult(
        "Enabled <= Used",
        salalayan.enabled() <= salalayan.used()
    );

    Serial.println();
    Serial.println(
        "Occupied Salpakan may remain DISABLED."
    );

    Serial.println(
        "Enablement and occupancy are separate states."
    );


    // --------------------------------------------------
    // [7] Disable Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Disable Salpakan");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Disable Salpakan #1",
        salalayan.disable(1)
    );

    printAccounting();
    printTable();

    printResult(
        "Enabled == 1",
        salalayan.enabled() == 1
    );


    // --------------------------------------------------
    // [8] Fill Salalayan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[8] Fill Remaining Salpakan");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Attach Diagnostics to #4",
        salalayan.attach(4, &diagnostics)
    );

    printAccounting();
    printTable();

    printResult(
        "Salalayan is FULL",
        salalayan.isFull()
    );

    printResult(
        "Used == Capacity",
        salalayan.used() == salalayan.capacity()
    );


    // --------------------------------------------------
    // [9] Full Does Not Mean Enabled
    // --------------------------------------------------

    Serial.println();
    Serial.println("[9] Full vs Enabled");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Salalayan is FULL",
        salalayan.isFull()
    );

    printResult(
        "Not all Salpakan are ENABLED",
        salalayan.enabled() <
        salalayan.capacity()
    );

    Serial.println();
    Serial.println(
        "FULL describes attachment occupancy."
    );

    Serial.println(
        "ENABLED describes operational enablement."
    );


    // --------------------------------------------------
    // [10] Detach Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[10] Detach Sapad");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Detach Sapad from #2",
        salalayan.detach(2)
    );

    printAccounting();
    printTable();

    printResult(
        "Salalayan is no longer FULL",
        !salalayan.isFull()
    );

    printResult(
        "Used == Capacity - 1",
        salalayan.used() ==
        salalayan.capacity() - 1
    );


    // --------------------------------------------------
    // [11] Accounting Invariants
    // --------------------------------------------------

    Serial.println();
    Serial.println("[11] Accounting Invariants");
    Serial.println("------------------------------------------------------------");

    bool occupancyInvariant =
        salalayan.used() +
        salalayan.free()
        ==
        salalayan.capacity();

    bool enablementInvariant =
        salalayan.enabled() +
        salalayan.disabled()
        ==
        salalayan.capacity();

    bool structuralInvariant =
        salalayan.enabled()
        <=
        salalayan.used();

    printResult(
        "Used + Free == Capacity",
        occupancyInvariant
    );

    printResult(
        "Enabled + Disabled == Capacity",
        enablementInvariant
    );

    printResult(
        "Enabled <= Used",
        structuralInvariant
    );


    // --------------------------------------------------
    // [12] Architectural Boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[12] Architectural Boundary");
    Serial.println("------------------------------------------------------------");

    Serial.println(
        "Salalayan provides structural introspection."
    );

    Serial.println(
        "Occupancy and enablement remain separate dimensions."
    );

    Serial.println(
        "No Sapad lifecycle or execution behavior is added."
    );

    Serial.println(
        "No system policy or scheduler is introduced."
    );


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