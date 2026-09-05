#include <Arduino.h>
#include "Ibutod.h"

// ============================================================
// Helper Functions
// ============================================================

void printDivider() {
    Serial.println("------------------------------------------------------------");
}

void printResult(const char* label, bool result) {
    Serial.print(label);
    Serial.print(": ");
    Serial.println(result ? "PASS" : "FAIL");
}

void printSalalayanState(
    const char* title,
    const Salalayan<4>& salalayan
) {
    Serial.println();
    Serial.println(title);
    printDivider();

    Serial.print("Capacity: ");
    Serial.println(salalayan.capacity());

    Serial.print("Occupied: ");
    Serial.println(salalayan.countOccupied());

    Serial.print("Free: ");
    Serial.println(salalayan.countFree());

    Serial.print("Enabled: ");
    Serial.println(salalayan.countEnabled());

    Serial.print("Disabled: ");
    Serial.println(salalayan.countDisabled());

    Serial.print("Empty: ");
    Serial.println(salalayan.isEmpty() ? "YES" : "NO");

    Serial.print("Full: ");
    Serial.println(salalayan.isFull() ? "YES" : "NO");
}


// ============================================================
// Experiment Objects
// ============================================================

class IMU : public Sapad {
};

class GNSS : public Sapad {
};

class Telemetry : public Sapad {
};

class Diagnostics : public Sapad {
};


// ============================================================
// Experiment
// ============================================================

void setup() {

    Serial.begin(115200);
    delay(1500);

    Serial.println();
    Serial.println("============================================================");
    Serial.println("             IBUTOD v0.1.20 EXPERIMENT");
    Serial.println("          Salalayan Counting API Refinement");
    Serial.println("============================================================");
    Serial.println();

    Salalayan<4> system("System");

    IMU imu;
    GNSS gnss;
    Telemetry telemetry;
    Diagnostics diagnostics;


    // ========================================================
    // [1] Initial State
    // ========================================================

    Serial.println("[1] Initial Counting State");
    printDivider();

    printSalalayanState(
        "Initial Salalayan State",
        system
    );

    printResult(
        "Capacity == 4",
        system.capacity() == 4
    );

    printResult(
        "Occupied == 0",
        system.countOccupied() == 0
    );

    printResult(
        "Free == 4",
        system.countFree() == 4
    );

    printResult(
        "Enabled == 0",
        system.countEnabled() == 0
    );

    printResult(
        "Disabled == 4",
        system.countDisabled() == 4
    );


    // ========================================================
    // [2] Attach Sapad
    // ========================================================

    Serial.println();
    Serial.println("[2] Occupancy Counting");
    printDivider();

    printResult(
        "Attach IMU to #1",
        system.attach(1, &imu)
    );

    printResult(
        "Attach GNSS to #2",
        system.attach(2, &gnss)
    );

    printResult(
        "Attach Telemetry to #3",
        system.attach(3, &telemetry)
    );

    printSalalayanState(
        "After Three Attachments",
        system
    );

    printResult(
        "Occupied == 3",
        system.countOccupied() == 3
    );

    printResult(
        "Free == 1",
        system.countFree() == 1
    );


    // ========================================================
    // [3] Occupancy Invariant
    // ========================================================

    Serial.println();
    Serial.println("[3] Occupancy Accounting Invariant");
    printDivider();

    printResult(
        "Occupied + Free == Capacity",
        system.countOccupied() +
        system.countFree() ==
        system.capacity()
    );

    printResult(
        "Salalayan is not EMPTY",
        !system.isEmpty()
    );

    printResult(
        "Salalayan is not FULL",
        !system.isFull()
    );


    // ========================================================
    // [4] Enable Salpakan
    // ========================================================

    Serial.println();
    Serial.println("[4] Enablement Counting");
    printDivider();

    printResult(
        "Enable Salpakan #1",
        system.enable(1)
    );

    printResult(
        "Enable Salpakan #3",
        system.enable(3)
    );

    printSalalayanState(
        "After Enabling #1 and #3",
        system
    );

    printResult(
        "Enabled == 2",
        system.countEnabled() == 2
    );

    printResult(
        "Disabled == 2",
        system.countDisabled() == 2
    );


    // ========================================================
    // [5] Enablement Invariant
    // ========================================================

    Serial.println();
    Serial.println("[5] Enablement Accounting Invariant");
    printDivider();

    printResult(
        "Enabled + Disabled == Capacity",
        system.countEnabled() +
        system.countDisabled() ==
        system.capacity()
    );

    printResult(
        "Enabled <= Occupied",
        system.countEnabled() <=
        system.countOccupied()
    );


    // ========================================================
    // [6] Occupancy vs Enablement
    // ========================================================

    Serial.println();
    Serial.println("[6] Independent Counting Dimensions");
    printDivider();

    printResult(
        "Occupied != Enabled",
        system.countOccupied() !=
        system.countEnabled()
    );

    printResult(
        "Occupied Salpakan may remain DISABLED",
        system.countOccupied() > system.countEnabled()
    );

    Serial.println();
    Serial.println(
        "Occupancy and enablement remain separate dimensions."
    );


    // ========================================================
    // [7] Fill Remaining Salpakan
    // ========================================================

    Serial.println();
    Serial.println("[7] Full Capacity Counting");
    printDivider();

    printResult(
        "Attach Diagnostics to #4",
        system.attach(4, &diagnostics)
    );

    printSalalayanState(
        "Full Salalayan State",
        system
    );

    printResult(
        "Occupied == Capacity",
        system.countOccupied() ==
        system.capacity()
    );

    printResult(
        "Free == 0",
        system.countFree() == 0
    );

    printResult(
        "Salalayan is FULL",
        system.isFull()
    );


    // ========================================================
    // [8] Disable and Detach
    // ========================================================

    Serial.println();
    Serial.println("[8] Counting After State Changes");
    printDivider();

    printResult(
        "Disable Salpakan #1",
        system.disable(1)
    );

    printResult(
        "Detach Sapad from #1",
        system.detach(1)
    );

    printSalalayanState(
        "After Disable and Detach",
        system
    );

    printResult(
        "Occupied == 3",
        system.countOccupied() == 3
    );

    printResult(
        "Free == 1",
        system.countFree() == 1
    );

    printResult(
        "Enabled == 1",
        system.countEnabled() == 1
    );

    printResult(
        "Disabled == 3",
        system.countDisabled() == 3
    );


    // ========================================================
    // [9] Final Invariants
    // ========================================================

    Serial.println();
    Serial.println("[9] Final Accounting Invariants");
    printDivider();

    printResult(
        "Occupied + Free == Capacity",
        system.countOccupied() +
        system.countFree() ==
        system.capacity()
    );

    printResult(
        "Enabled + Disabled == Capacity",
        system.countEnabled() +
        system.countDisabled() ==
        system.capacity()
    );

    printResult(
        "Enabled <= Occupied",
        system.countEnabled() <=
        system.countOccupied()
    );


    // ========================================================
    // [10] API Boundary
    // ========================================================

    Serial.println();
    Serial.println("[10] API Refinement Boundary");
    printDivider();

    Serial.println(
        "countOccupied() describes Salpakan occupancy."
    );

    Serial.println(
        "countFree() describes available Salpakan."
    );

    Serial.println(
        "countEnabled() describes enabled Salpakan."
    );

    Serial.println(
        "countDisabled() describes disabled Salpakan."
    );

    Serial.println(
        "No lifecycle behavior was changed."
    );

    Serial.println(
        "No Sapad execution behavior was introduced."
    );

    Serial.println(
        "No ownership model was changed."
    );


    // ========================================================
    // Complete
    // ========================================================

    Serial.println();
    Serial.println("============================================================");
    Serial.println("               EXPERIMENT COMPLETE");
    Serial.println("============================================================");
}


void loop() {
    // Experiment complete.
}