#include <Arduino.h>
#include <Ibutod.h>

// --------------------------------------------------
// Minimal Sapad Types
// --------------------------------------------------

class IMUSapad : public Sapad {};
class GNSSSapad : public Sapad {};
class TelemetrySapad : public Sapad {};

IMUSapad imu;
GNSSSapad gnss;
TelemetrySapad telemetry;


// --------------------------------------------------
// Helpers
// --------------------------------------------------

void printDivider() {
    Serial.println("------------------------------------------------------------");
}

void printResult(const char* label, bool result) {
    Serial.print(label);
    Serial.print(": ");
    Serial.println(result ? "PASS" : "FAIL");
}

void printSalalayanState(const Salalayan<4>& salalayan) {
    Serial.println();
    Serial.println("Salalayan Structural State");
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


// --------------------------------------------------
// Experiment
// --------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("============================================================");
    Serial.println("             IBUTOD v0.1.21 EXPERIMENT");
    Serial.println("          Salpakan Structural Purification");
    Serial.println("============================================================");

    Salalayan<4> salalayan("Structural");


    // --------------------------------------------------
    // [1] Initial Structural State
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Initial Structural State");
    printDivider();

    printResult(
        "Salalayan starts EMPTY",
        salalayan.isEmpty()
    );

    printResult(
        "Occupied == 0",
        salalayan.countOccupied() == 0
    );

    printResult(
        "Enabled == 0",
        salalayan.countEnabled() == 0
    );

    printSalalayanState(salalayan);


    // --------------------------------------------------
    // [2] Structural Attachment
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Structural Attachment");
    printDivider();

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

    printResult(
        "Occupied == 3",
        salalayan.countOccupied() == 3
    );

    printResult(
        "Free == 1",
        salalayan.countFree() == 1
    );

    printSalalayanState(salalayan);


    // --------------------------------------------------
    // [3] Enablement Remains Structural
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Salpakan Enablement");
    printDivider();

    printResult(
        "Enable Salpakan #1",
        salalayan.enable(1)
    );

    printResult(
        "Enable Salpakan #3",
        salalayan.enable(3)
    );

    printResult(
        "Enabled == 2",
        salalayan.countEnabled() == 2
    );

    printResult(
        "Disabled == 2",
        salalayan.countDisabled() == 2
    );

    printSalalayanState(salalayan);


    // --------------------------------------------------
    // [4] Enablement Boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Enablement Boundary");
    printDivider();

    Salpakan* first = salalayan.get(1);
    Salpakan* second = salalayan.get(2);
    Salpakan* fourth = salalayan.get(4);

    printResult(
        "Salpakan #1 is ENABLED",
        first != nullptr && first->isEnabled()
    );

    printResult(
        "Salpakan #2 remains DISABLED",
        second != nullptr && !second->isEnabled()
    );

    printResult(
        "Free Salpakan #4 cannot be ENABLED",
        fourth != nullptr && !fourth->enable()
    );


    // --------------------------------------------------
    // [5] Detachment Boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Structural Detachment");
    printDivider();

    printResult(
        "Cannot detach ENABLED Salpakan #1",
        !salalayan.detach(1)
    );

    printResult(
        "Disable Salpakan #1",
        salalayan.disable(1)
    );

    printResult(
        "Detach Sapad from #1",
        salalayan.detach(1)
    );

    printResult(
        "Salpakan #1 becomes FREE",
        first != nullptr && first->isFree()
    );

    printResult(
        "Occupied == 2",
        salalayan.countOccupied() == 2
    );

    printSalalayanState(salalayan);


    // --------------------------------------------------
    // [6] Structural Identity
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Structural Identity");
    printDivider();

    Salpakan* one = salalayan.get(1);
    Salpakan* two = salalayan.get(2);
    Salpakan* invalid = salalayan.get(5);

    printResult(
        "Salpakan #1 exists",
        one != nullptr && one->id() == 1
    );

    printResult(
        "Salpakan #2 exists",
        two != nullptr && two->id() == 2
    );

    printResult(
        "Out-of-range Salpakan rejected",
        invalid == nullptr
    );


    // --------------------------------------------------
    // [7] Architectural Boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Architectural Boundary");
    printDivider();

    Serial.println(
        "Salpakan retains structural responsibilities."
    );

    Serial.println(
        "Attachment remains supported."
    );

    Serial.println(
        "Occupancy remains supported."
    );

    Serial.println(
        "Enablement remains supported."
    );

    Serial.println(
        "Runtime lifecycle is intentionally absent."
    );

    Serial.println(
        "Sapad execution behavior remains undefined."
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
    // Experiment intentionally performs no runtime execution.
}