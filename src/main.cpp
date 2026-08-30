#include <Arduino.h>
#include <Ubod.h>

Sapad imu;
Sapad gnss;
Sapad telemetry;
Sapad diagnostics;


// --------------------------------------------------
// Helper
// --------------------------------------------------

void printResult(const char* label, bool result) {
    Serial.print(label);
    Serial.print(": ");
    Serial.println(result ? "PASS" : "FAIL");
}


template <unsigned int Capacity>
void printSalalayanInfo(
    const char* label,
    const Salalayan<Capacity>& salalayan
) {
    Serial.println();
    Serial.println(label);
    Serial.println("----------------------------------------");

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
// Setup
// --------------------------------------------------

void setup() {

    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("============================================================");
    Serial.println("              UBOD TEMPLATE SMOKE TEST");
    Serial.println("        Configurable Salalayan Capacity Validation");
    Serial.println("============================================================");


    // ==================================================
    // [1] Minimum Capacity
    // ==================================================

    Serial.println();
    Serial.println("[1] Salalayan<1>");
    Serial.println("------------------------------------------------------------");

    Salalayan<1> single("Single");

    printResult(
        "Capacity == 1",
        single.capacity() == 1
    );

    printResult(
        "Initially empty",
        single.isEmpty()
    );

    printSalalayanInfo(
        "Salalayan<1> State",
        single
    );


    // ==================================================
    // [2] Small Capacity
    // ==================================================

    Serial.println();
    Serial.println("[2] Salalayan<2>");
    Serial.println("------------------------------------------------------------");

    Salalayan<2> small("Small");

    printResult(
        "Capacity == 2",
        small.capacity() == 2
    );

    printResult(
        "Attach IMU to #1",
        small.attach(1, &imu)
    );

    printResult(
        "Attach GNSS to #2",
        small.attach(2, &gnss)
    );

    printResult(
        "Salalayan is FULL",
        small.isFull()
    );

    printSalalayanInfo(
        "Salalayan<2> State",
        small
    );


    // ==================================================
    // [3] Previous Default Capacity
    // ==================================================

    Serial.println();
    Serial.println("[3] Salalayan<4>");
    Serial.println("------------------------------------------------------------");

    Salalayan<4> standard("Standard");

    printResult(
        "Capacity == 4",
        standard.capacity() == 4
    );

    printResult(
        "Attach IMU to #1",
        standard.attach(1, &imu)
    );

    printResult(
        "Attach Telemetry to #3",
        standard.attach(3, &telemetry)
    );

    printResult(
        "Enable #1",
        standard.enable(1)
    );

    printSalalayanInfo(
        "Salalayan<4> State",
        standard
    );


    // ==================================================
    // [4] Larger Capacity
    // ==================================================

    Serial.println();
    Serial.println("[4] Salalayan<8>");
    Serial.println("------------------------------------------------------------");

    Salalayan<8> large("Large");

    printResult(
        "Capacity == 8",
        large.capacity() == 8
    );

    printResult(
        "Attach Diagnostics to #8",
        large.attach(8, &diagnostics)
    );

    printResult(
        "Enable #8",
        large.enable(8)
    );

    printResult(
        "Salpakan #8 exists",
        large.get(8) != nullptr
    );

    printResult(
        "Salpakan #9 rejected",
        large.get(9) == nullptr
    );

    printSalalayanInfo(
        "Salalayan<8> State",
        large
    );


    // ==================================================
    // [5] Local Identity
    // ==================================================

    Serial.println();
    Serial.println("[5] Local Salpakan Identity");
    Serial.println("------------------------------------------------------------");

    Salpakan* singleSlot =
        single.get(1);

    Salpakan* smallSlot =
        small.get(1);

    Salpakan* standardSlot =
        standard.get(1);

    printResult(
        "Salalayan<1> has Salpakan #1",
        singleSlot != nullptr &&
        singleSlot->id() == 1
    );

    printResult(
        "Salalayan<2> has Salpakan #1",
        smallSlot != nullptr &&
        smallSlot->id() == 1
    );

    printResult(
        "Salalayan<4> has Salpakan #1",
        standardSlot != nullptr &&
        standardSlot->id() == 1
    );

    printResult(
        "Local Salpakan objects are different",
        singleSlot != smallSlot &&
        smallSlot != standardSlot &&
        singleSlot != standardSlot
    );


    // ==================================================
    // [6] Independent Accounting
    // ==================================================

    Serial.println();
    Serial.println("[6] Independent Accounting");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Single Used == 0",
        single.used() == 0
    );

    printResult(
        "Small Used == 2",
        small.used() == 2
    );

    printResult(
        "Standard Used == 2",
        standard.used() == 2
    );

    printResult(
        "Large Used == 1",
        large.used() == 1
    );


    // ==================================================
    // [7] Enablement Boundary
    // ==================================================

    Serial.println();
    Serial.println("[7] Enablement Boundary");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Small has no enabled Salpakan",
        small.enabled() == 0
    );

    printResult(
        "Standard has one enabled Salpakan",
        standard.enabled() == 1
    );

    printResult(
        "Large has one enabled Salpakan",
        large.enabled() == 1
    );

    printResult(
        "Enablement remains local to each Salalayan",
        standard.enabled() != large.enabled() ||
        standard.capacity() != large.capacity()
    );

    printResult(
        "Standard enablement unaffected by Large",
        standard.enabled() == 1 &&
        large.enabled() == 1
    );


    // ==================================================
    // Final
    // ==================================================

    Serial.println();
    Serial.println("============================================================");
    Serial.println("              SMOKE TEST COMPLETE");
    Serial.println("============================================================");
}


void loop() {
}