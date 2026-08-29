#include <Arduino.h>
#include "Ubod.h"

UbodContainer ubod;

// --------------------------------------------------
// External Engines
// --------------------------------------------------
//
// Ang mga Engine ay nililikha sa labas ng Ubod.
// Hindi sila pagmamay-ari ng Ubod.
//
// Sa v0.1.14, UbodEngine ay minimal type boundary
// lamang. Wala pa itong execution behavior.
//

UbodEngine primaryComms;
UbodEngine telemetry;


// --------------------------------------------------
// Helper: Print Slot
// --------------------------------------------------

void printSlot(const UbodSlot* slot) {

    if (slot == nullptr) {
        Serial.println("Slot: NOT FOUND");
        return;
    }

    Serial.print("Slot #");
    Serial.print(slot->slotId());

    Serial.print(" | Name: \"");
    Serial.print(slot->slotName());
    Serial.print("\"");

    Serial.print(" | ID: ");
    Serial.print(
        slot->isSlotIdValid()
            ? "VALID"
            : "INVALID"
    );

    Serial.print(" | Engine: ");

    if (slot->hasEngine()) {
        Serial.print("ATTACHED");
    } else {
        Serial.print("NONE");
    }

    Serial.print(" | Availability: ");

    switch (slot->availability()) {

        case UbodSlotAvailability::Free:
            Serial.print("FREE");
            break;

        case UbodSlotAvailability::Occupied:
            Serial.print("OCCUPIED");
            break;
    }

    Serial.print(" | State: ");

    switch (slot->state()) {

        case UbodSlotState::Initializing:
            Serial.print("INITIALIZING");
            break;

        case UbodSlotState::Ready:
            Serial.print("READY");
            break;

        case UbodSlotState::Running:
            Serial.print("RUNNING");
            break;

        case UbodSlotState::Invalid:
            Serial.print("INVALID");
            break;
    }

    Serial.println();
}


// --------------------------------------------------
// Helper: Boolean Test
// --------------------------------------------------

void printTest(
    const char* label,
    bool passed
) {
    Serial.print(label);
    Serial.print(": ");
    Serial.println(
        passed
            ? "PASS"
            : "FAIL"
    );
}


// --------------------------------------------------
// Experiment
// --------------------------------------------------

void setup() {

    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("========================================");
    Serial.println("       UBOD v0.1.14 EXPERIMENT");
    Serial.println("========================================");


    // --------------------------------------------------
    // 1. Container
    // --------------------------------------------------

    Serial.println();
    Serial.println("1. Container");
    Serial.println("----------------------------------------");

    Serial.print("Capacity: ");
    Serial.println(ubod.capacity());

    Serial.print("Used: ");
    Serial.println(ubod.used());

    Serial.print("Free: ");
    Serial.println(ubod.free());


    // --------------------------------------------------
    // 2. Initial Slot
    // --------------------------------------------------

    Serial.println();
    Serial.println("2. Initial Slot State");
    Serial.println("----------------------------------------");

    UbodSlot* slot1 = ubod.get(1);

    printSlot(slot1);

    printTest(
        "Initial slot is FREE",
        slot1 != nullptr &&
        slot1->isFree()
    );

    printTest(
        "Initial slot has NO engine",
        slot1 != nullptr &&
        !slot1->hasEngine() &&
        slot1->engine() == nullptr
    );


    // --------------------------------------------------
    // 3. Slot Naming
    // --------------------------------------------------

    Serial.println();
    Serial.println("3. Slot Naming");
    Serial.println("----------------------------------------");

    bool result = slot1->setSlotName("primaryComms");

    printTest(
        "setSlotName(primaryComms)",
        result
    );

    Serial.print("Slot name: ");
    Serial.println(slot1->slotName());


    // --------------------------------------------------
    // 4. Reject nullptr Attachment
    // --------------------------------------------------

    Serial.println();
    Serial.println("4. Reject nullptr Attachment");
    Serial.println("----------------------------------------");

    result = ubod.attach(1, nullptr);

    printTest(
        "attach(nullptr) rejected",
        !result
    );

    printSlot(slot1);


    // --------------------------------------------------
    // 5. Attach First Engine
    // --------------------------------------------------

    Serial.println();
    Serial.println("5. Attach primaryComms");
    Serial.println("----------------------------------------");

    result = ubod.attach(
        1,
        &primaryComms
    );

    printTest(
        "attach(primaryComms)",
        result
    );

    printSlot(slot1);

    printTest(
        "engine() == primaryComms",
        slot1->engine() == &primaryComms
    );

    printTest(
        "Slot becomes OCCUPIED",
        slot1->isOccupied()
    );


    // --------------------------------------------------
    // 6. Attachment Identity
    // --------------------------------------------------

    Serial.println();
    Serial.println("6. Attachment Identity");
    Serial.println("----------------------------------------");

    printTest(
        "hasEngine() == true",
        slot1->hasEngine()
    );

    printTest(
        "engine() is not nullptr",
        slot1->engine() != nullptr
    );

    printTest(
        "availability() == OCCUPIED",
        slot1->availability()
            == UbodSlotAvailability::Occupied
    );


    // --------------------------------------------------
    // 7. Second Attachment
    // --------------------------------------------------
    //
    // One Engine per Slot ang target behavior.
    // Hindi dapat ma-overwrite ang kasalukuyang
    // attachment habang occupied ang Slot.
    //

    Serial.println();
    Serial.println("7. Reject Second Engine");
    Serial.println("----------------------------------------");

    result = ubod.attach(
        1,
        &telemetry
    );

    printTest(
        "attach(telemetry) rejected",
        !result
    );

    printTest(
        "Original Engine preserved",
        slot1->engine() == &primaryComms
    );

    printSlot(slot1);


    // --------------------------------------------------
    // 8. Container Accounting
    // --------------------------------------------------

    Serial.println();
    Serial.println("8. Container Accounting");
    Serial.println("----------------------------------------");

    Serial.print("Used: ");
    Serial.println(ubod.used());

    Serial.print("Free: ");
    Serial.println(ubod.free());

    printTest(
        "Used == 1",
        ubod.used() == 1
    );

    printTest(
        "Free == Capacity - 1",
        ubod.free()
            == ubod.capacity() - 1
    );


    // --------------------------------------------------
    // 9. Occupancy Invariant
    // --------------------------------------------------

    Serial.println();
    Serial.println("9. Occupancy Invariant");
    Serial.println("----------------------------------------");

    bool occupiedInvariant =
        slot1->hasEngine() &&
        slot1->engine() != nullptr &&
        slot1->isOccupied() &&
        !slot1->isFree() &&
        slot1->availability()
            == UbodSlotAvailability::Occupied;

    printTest(
        "Engine attached => OCCUPIED",
        occupiedInvariant
    );


    // --------------------------------------------------
    // 10. Detach
    // --------------------------------------------------

    Serial.println();
    Serial.println("10. Detach primaryComms");
    Serial.println("----------------------------------------");

    result = ubod.detach(1);

    printTest(
        "detach()",
        result
    );

    printSlot(slot1);

    printTest(
        "Engine reference cleared",
        slot1->engine() == nullptr
    );

    printTest(
        "Slot becomes FREE",
        slot1->isFree()
    );


    // --------------------------------------------------
    // 11. Reject Double Detach
    // --------------------------------------------------

    Serial.println();
    Serial.println("11. Reject Double Detach");
    Serial.println("----------------------------------------");

    result = ubod.detach(1);

    printTest(
        "Second detach() rejected",
        !result
    );

    printSlot(slot1);


    // --------------------------------------------------
    // 12. Reattach Different Engine
    // --------------------------------------------------

    Serial.println();
    Serial.println("12. Attach telemetry");
    Serial.println("----------------------------------------");

    result = ubod.attach(
        1,
        &telemetry
    );

    printTest(
        "attach(telemetry)",
        result
    );

    printTest(
        "engine() == telemetry",
        slot1->engine() == &telemetry
    );

    printSlot(slot1);


    // --------------------------------------------------
    // 13. Engine Ownership Boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("13. Engine Ownership Boundary");
    Serial.println("----------------------------------------");

    Serial.println(
        "Engine objects are created outside Ubod."
    );

    Serial.println(
        "Ubod stores only their addresses."
    );

    Serial.println(
        "Ubod does not create the Engine."
    );

    Serial.println(
        "Ubod does not destroy the Engine."
    );

    Serial.println(
        "detach() only clears the attachment."
    );


    // --------------------------------------------------
    // 14. Final Detach
    // --------------------------------------------------

    Serial.println();
    Serial.println("14. Final Detach");
    Serial.println("----------------------------------------");

    result = ubod.detach(1);

    printTest(
        "detach(telemetry)",
        result
    );

    printSlot(slot1);


    // --------------------------------------------------
    // 15. Final Invariant
    // --------------------------------------------------

    Serial.println();
    Serial.println("15. Final Slot Invariant");
    Serial.println("----------------------------------------");

    bool freeInvariant =
        slot1->engine() == nullptr &&
        !slot1->hasEngine() &&
        slot1->isFree() &&
        !slot1->isOccupied() &&
        slot1->availability()
            == UbodSlotAvailability::Free;

    printTest(
        "No Engine => FREE",
        freeInvariant
    );


    // --------------------------------------------------
    // 16. Lifecycle Boundary
    // --------------------------------------------------
    //
    // Mahalaga: ang Engine attachment at ang
    // Slot lifecycle state ay dalawang magkaibang
    // konsepto sa v0.1.14.
    //

    Serial.println();
    Serial.println("16. Slot Lifecycle Boundary");
    Serial.println("----------------------------------------");

    printSlot(slot1);

    Serial.println(
        "Attachment does not start the Slot."
    );

    Serial.println(
        "Attachment does not change lifecycle state."
    );

    Serial.println(
        "Lifecycle remains controlled by begin()/update()."
    );


    // --------------------------------------------------
    // Complete
    // --------------------------------------------------

    Serial.println();
    Serial.println("========================================");
    Serial.println("       EXPERIMENT COMPLETE");
    Serial.println("========================================");
}


void loop() {
}