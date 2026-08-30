#include <Arduino.h>
#include "Ubod.h"

// --------------------------------------------------
// Test Sapad
// --------------------------------------------------

class TestSapad : public Sapad {
};

// --------------------------------------------------
// Helpers
// --------------------------------------------------

void printResult(const char* label, bool passed) {
    Serial.print(label);
    Serial.print(": ");
    Serial.println(passed ? "PASS" : "FAIL");
}

const char* enablementName(const Salpakan* salpakan) {
    if (salpakan == nullptr) {
        return "N/A";
    }

    return salpakan->isEnabled()
        ? "ENABLED"
        : "DISABLED";
}

const char* availabilityName(const Salpakan* salpakan) {
    if (salpakan == nullptr) {
        return "N/A";
    }

    return salpakan->isOccupied()
        ? "OCCUPIED"
        : "FREE";
}

// --------------------------------------------------
// Salalayan Overview
// --------------------------------------------------

template <unsigned int Capacity>
void printSalalayanOverview(
    const char* label,
    const Salalayan<Capacity>& salalayan
) {
    Serial.println();
    Serial.println(label);
    Serial.println("------------------------------------------------------------");

    Serial.print("Name: ");
    Serial.println(
        salalayan.name()[0] != '\0'
            ? salalayan.name()
            : "(unnamed)"
    );

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

    Serial.println();

    Serial.println("+----+----------+------------+-----------+");
    Serial.println("| ID | SAPAD    | ENABLEMENT | AVAIL     |");
    Serial.println("+----+----------+------------+-----------+");

    for (unsigned int id = 1; id <= Capacity; ++id) {

        const Salpakan* salpakan = salalayan.get(id);

        Serial.print("| ");

        if (id < 10) {
            Serial.print(id);
            Serial.print("  ");
        } else {
            Serial.print(id);
            Serial.print(" ");
        }

        Serial.print("| ");

        if (salpakan->hasSapad()) {
            Serial.print("ATTACHED ");
        } else {
            Serial.print("NONE     ");
        }

        Serial.print("| ");

        if (salpakan->isEnabled()) {
            Serial.print("ENABLED    ");
        } else {
            Serial.print("DISABLED   ");
        }

        Serial.print("| ");

        if (salpakan->isOccupied()) {
            Serial.print("OCCUPIED  ");
        } else {
            Serial.print("FREE      ");
        }

        Serial.println("|");
    }

    Serial.println("+----+----------+------------+-----------+");
}

// --------------------------------------------------
// Experiment Objects
// --------------------------------------------------

Salalayan<4> sensor("Sensor");
Salalayan<3> control("Control");
Salalayan<2> communication("Communication");

TestSapad imu;
TestSapad gnss;
TestSapad backupImu;

TestSapad motorControl;
TestSapad navigation;

TestSapad primaryLink;
TestSapad backupLink;

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {

    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("============================================================");
    Serial.println("             UBOD v0.1.19 EXPERIMENT");
    Serial.println("      Heterogeneous Salalayan Composition");
    Serial.println("============================================================");


    // --------------------------------------------------
    // [1] Initial Composition
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Salalayan Composition");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Sensor capacity == 4",
        sensor.capacity() == 4
    );

    printResult(
        "Control capacity == 3",
        control.capacity() == 3
    );

    printResult(
        "Communication capacity == 2",
        communication.capacity() == 2
    );


    // --------------------------------------------------
    // [2] Attach Sensor Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Sensor Group");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Attach IMU to Sensor #1",
        sensor.attach(1, &imu)
    );

    printResult(
        "Attach GNSS to Sensor #2",
        sensor.attach(2, &gnss)
    );

    printResult(
        "Attach Backup IMU to Sensor #3",
        sensor.attach(3, &backupImu)
    );

    printResult(
        "Enable Sensor #1",
        sensor.enable(1)
    );

    printResult(
        "Enable Sensor #2",
        sensor.enable(2)
    );

    printSalalayanOverview(
        "Sensor Salalayan State",
        sensor
    );


    // --------------------------------------------------
    // [3] Attach Control Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Control Group");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Attach Motor Control to Control #1",
        control.attach(1, &motorControl)
    );

    printResult(
        "Attach Navigation to Control #2",
        control.attach(2, &navigation)
    );

    printResult(
        "Enable Control #1",
        control.enable(1)
    );

    printSalalayanOverview(
        "Control Salalayan State",
        control
    );


    // --------------------------------------------------
    // [4] Attach Communication Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Communication Group");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Attach Primary Link to Communication #1",
        communication.attach(1, &primaryLink)
    );

    printResult(
        "Attach Backup Link to Communication #2",
        communication.attach(2, &backupLink)
    );

    printResult(
        "Enable Communication #1",
        communication.enable(1)
    );

    printResult(
        "Enable Communication #2",
        communication.enable(2)
    );

    printSalalayanOverview(
        "Communication Salalayan State",
        communication
    );


    // --------------------------------------------------
    // [5] Local Salpakan Identity
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Local Salpakan Identity");
    Serial.println("------------------------------------------------------------");

    Salpakan* sensorSlot1 = sensor.get(1);
    Salpakan* controlSlot1 = control.get(1);
    Salpakan* communicationSlot1 = communication.get(1);

    printResult(
        "Sensor has Salpakan #1",
        sensorSlot1 != nullptr &&
        sensorSlot1->id() == 1
    );

    printResult(
        "Control has Salpakan #1",
        controlSlot1 != nullptr &&
        controlSlot1->id() == 1
    );

    printResult(
        "Communication has Salpakan #1",
        communicationSlot1 != nullptr &&
        communicationSlot1->id() == 1
    );

    printResult(
        "Local Salpakan #1 objects are different",
        sensorSlot1 != controlSlot1 &&
        sensorSlot1 != communicationSlot1 &&
        controlSlot1 != communicationSlot1
    );


    // --------------------------------------------------
    // [6] Independent Accounting
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Independent Accounting");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Sensor Used == 3",
        sensor.used() == 3
    );

    printResult(
        "Control Used == 2",
        control.used() == 2
    );

    printResult(
        "Communication Used == 2",
        communication.used() == 2
    );

    printResult(
        "Communication is FULL",
        communication.isFull()
    );

    printResult(
        "Sensor is not FULL",
        !sensor.isFull()
    );


    // --------------------------------------------------
    // [7] Independent Enablement
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Independent Enablement");
    Serial.println("------------------------------------------------------------");

    printResult(
        "Sensor Enabled == 2",
        sensor.enabled() == 2
    );

    printResult(
        "Control Enabled == 1",
        control.enabled() == 1
    );

    printResult(
        "Communication Enabled == 2",
        communication.enabled() == 2
    );

    printResult(
        "Control has disabled occupied Salpakan",
        control.get(2)->isOccupied() &&
        !control.get(2)->isEnabled()
    );


    // --------------------------------------------------
    // [8] Cross-Group Isolation
    // --------------------------------------------------

    Serial.println();
    Serial.println("[8] Cross-Group Isolation");
    Serial.println("------------------------------------------------------------");

    unsigned int sensorUsedBefore = sensor.used();
    unsigned int controlUsedBefore = control.used();

    communication.disable(1);

    printResult(
        "Communication #1 disabled",
        !communication.get(1)->isEnabled()
    );

    printResult(
        "Sensor accounting unaffected",
        sensor.used() == sensorUsedBefore
    );

    printResult(
        "Control accounting unaffected",
        control.used() == controlUsedBefore
    );

    printResult(
        "Sensor enablement unaffected",
        sensor.enabled() == 2
    );


    // --------------------------------------------------
    // [9] Architectural Summary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[9] Architectural Boundary");
    Serial.println("------------------------------------------------------------");

    Serial.println("Multiple Salalayan instances form structural groups.");
    Serial.println("Each Salalayan owns its local Salpakan namespace.");
    Serial.println("Capacity is independently defined per Salalayan.");
    Serial.println("Occupancy and enablement remain locally independent.");
    Serial.println("No system-wide registry or Silid class is introduced.");


    // --------------------------------------------------

    Serial.println();
    Serial.println("============================================================");
    Serial.println("               EXPERIMENT COMPLETE");
    Serial.println("============================================================");
}

void loop() {
}