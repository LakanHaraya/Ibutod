#include <Arduino.h>
#include "Ubod.h"

UbodContainer ubod;

// --------------------------------------------------
// Helper: Print Slot Information
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
        slot->isSlotIdValid() ? "VALID" : "INVALID"
    );

    Serial.print(" | Attachment: ");

    if (slot->isFree()) {
        Serial.print("FREE");
    }
    else {
        Serial.print("OCCUPIED");
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
// Setup
// --------------------------------------------------

void setup() {

    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("==========================================");
    Serial.println("        EKSPERIMENTONG UBOD v0.1.12");
    Serial.println("   Semantika ng Attachment / Detachment");
    Serial.println("==========================================");


    // --------------------------------------------------
    // 1. Container Overview
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Container Overview");

    Serial.print("Capacity: ");
    Serial.println(ubod.capacity());

    Serial.print("Used: ");
    Serial.println(ubod.used());

    Serial.print("Free: ");
    Serial.println(ubod.free());


    // --------------------------------------------------
    // 2. Get Slots
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Acquiring Slots");

    UbodSlot* slot1 = ubod.get(1);
    UbodSlot* slot2 = ubod.get(2);
    UbodSlot* slot3 = ubod.get(3);

    printSlot(slot1);
    printSlot(slot2);
    printSlot(slot3);


    // --------------------------------------------------
    // 3. Slot Naming
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Assigning Slot Names");

    Serial.print("Slot 1 -> primaryComms: ");

    if (slot1->setSlotName("primaryComms")) {
        Serial.println("SUCCESS");
    }
    else {
        Serial.println("FAILED");
    }


    Serial.print("Slot 2 -> sensorTask: ");

    if (slot2->setSlotName("sensorTask")) {
        Serial.println("SUCCESS");
    }
    else {
        Serial.println("FAILED");
    }


    Serial.print("Slot 3 -> telemetry: ");

    if (slot3->setSlotName("telemetry")) {
        Serial.println("SUCCESS");
    }
    else {
        Serial.println("FAILED");
    }


    Serial.println();
    Serial.println("Slots after naming:");

    printSlot(slot1);
    printSlot(slot2);
    printSlot(slot3);


    // --------------------------------------------------
    // 4. Slot Lifecycle
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Slot Lifecycle");

    Serial.println("Slot 1 before begin():");
    printSlot(slot1);


    Serial.println();
    Serial.println("Calling begin()...");

    slot1->begin();

    printSlot(slot1);


    Serial.println();
    Serial.println("Calling update()...");

    slot1->update();

    printSlot(slot1);


    // --------------------------------------------------
    // 5. Attachment
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Attachment Test");

    Serial.println(
        "Concept: attach() marks the Slot as OCCUPIED."
    );

    Serial.println(
        "No concrete Engine object is attached yet."
    );


    Serial.print("Slot 1 attach(): ");

    if (slot1->attach()) {
        Serial.println("SUCCESS");
    }
    else {
        Serial.println("FAILED");
    }

    printSlot(slot1);


    // --------------------------------------------------
    // 6. Duplicate Attachment
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Duplicate Attachment Test");

    Serial.print("Slot 1 attach() again: ");

    if (slot1->attach()) {
        Serial.println("UNEXPECTED SUCCESS");
    }
    else {
        Serial.println("REJECTED (EXPECTED)");
    }

    printSlot(slot1);


    // --------------------------------------------------
    // 7. Container Attachment API
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Container Attachment API");

    Serial.print("Container attach Slot 2: ");

    if (ubod.attach(2)) {
        Serial.println("SUCCESS");
    }
    else {
        Serial.println("FAILED");
    }

    printSlot(slot2);


    // --------------------------------------------------
    // 8. Container Statistics
    // --------------------------------------------------

    Serial.println();
    Serial.println("[8] Attachment Statistics");

    Serial.print("Used / Occupied: ");
    Serial.println(ubod.used());

    Serial.print("Free: ");
    Serial.println(ubod.free());


    // --------------------------------------------------
    // 9. Find Free Slot
    // --------------------------------------------------

    Serial.println();
    Serial.println("[9] Finding Free Slot");

    UbodSlot* freeSlot = ubod.findFree();

    if (freeSlot != nullptr) {

        Serial.print("First free Slot found: ");

        printSlot(freeSlot);

    }
    else {

        Serial.println("No FREE Slot available.");
    }


    // --------------------------------------------------
    // 10. Detachment
    // --------------------------------------------------

    Serial.println();
    Serial.println("[10] Detachment Test");

    Serial.println(
        "Concept: detach() releases the Slot from OCCUPIED state."
    );


    Serial.print("Slot 1 detach(): ");

    if (slot1->detach()) {
        Serial.println("SUCCESS");
    }
    else {
        Serial.println("FAILED");
    }

    printSlot(slot1);


    // --------------------------------------------------
    // 11. Duplicate Detachment
    // --------------------------------------------------

    Serial.println();
    Serial.println("[11] Duplicate Detachment Test");

    Serial.print("Slot 1 detach() again: ");

    if (slot1->detach()) {
        Serial.println("UNEXPECTED SUCCESS");
    }
    else {
        Serial.println("REJECTED (EXPECTED)");
    }

    printSlot(slot1);


    // --------------------------------------------------
    // 12. Container Detachment API
    // --------------------------------------------------

    Serial.println();
    Serial.println("[12] Container Detachment API");

    Serial.print("Container detach Slot 2: ");

    if (ubod.detach(2)) {
        Serial.println("SUCCESS");
    }
    else {
        Serial.println("FAILED");
    }

    printSlot(slot2);


    // --------------------------------------------------
    // 13. Slot Lookup
    // --------------------------------------------------

    Serial.println();
    Serial.println("[13] Slot Lookup by Name");

    UbodSlot* results[4] = {};

    unsigned int count = ubod.findBySlotName(
        "telemetry",
        results,
        4
    );

    Serial.print("Matches for \"telemetry\": ");
    Serial.println(count);

    for (unsigned int i = 0; i < count; ++i) {
        printSlot(results[i]);
    }


    // --------------------------------------------------
    // 14. Final Statistics
    // --------------------------------------------------

    Serial.println();
    Serial.println("[14] Final Container Statistics");

    Serial.print("Capacity: ");
    Serial.println(ubod.capacity());

    Serial.print("Used / Occupied: ");
    Serial.println(ubod.used());

    Serial.print("Free: ");
    Serial.println(ubod.free());


    // --------------------------------------------------
    // 15. Semantic Summary
    // --------------------------------------------------

    Serial.println();
    Serial.println("[15] v0.1.12 Semantic Summary");

    Serial.println(
        "attach() -> Slot becomes OCCUPIED"
    );

    Serial.println(
        "detach() -> Slot becomes FREE"
    );

    Serial.println(
        "release() is removed"
    );

    Serial.println(
        "Released state is removed"
    );

    Serial.println(
        "Concrete Engine attachment is not implemented yet"
    );


    // --------------------------------------------------
    // Complete
    // --------------------------------------------------

    Serial.println();
    Serial.println("==========================================");
    Serial.println("        NAKOMPLETO ANG EKSPERIMENTO");
    Serial.println("==========================================");
}


void loop() {
}