#include <Arduino.h>
#include "Ubod.h"

UbodContainer ubod;

// --------------------------------------------------
// Test Engines
// --------------------------------------------------

UbodEngine primaryComms;
UbodEngine telemetry;

// --------------------------------------------------
// Helpers
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

    Serial.print(" | Availability: ");

    if (slot->isFree()) {
        Serial.print("FREE");
    } else {
        Serial.print("OCCUPIED");
    }

    Serial.print(" | Engine: ");

    if (slot->hasEngine()) {
        Serial.print("ATTACHED");
    } else {
        Serial.print("NONE");
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
    Serial.println("==================================");
    Serial.println("      UBOD v0.1.13 EXPERIMENT");
    Serial.println("==================================");


    // --------------------------------------------------
    // 1. Get Slot
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Getting Slot");

    UbodSlot* slot1 = ubod.get(1);

    if (slot1 == nullptr) {
        Serial.println("Failed to get Slot 1.");
        return;
    }

    slot1->setSlotName("primaryComms");

    printSlot(slot1);


    // --------------------------------------------------
    // 2. Initial Engine State
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Initial Engine State");

    Serial.print("Has Engine: ");
    Serial.println(slot1->hasEngine() ? "YES" : "NO");

    Serial.print("Engine Pointer: ");

    if (slot1->engine() == nullptr) {
        Serial.println("nullptr");
    } else {
        Serial.println("NOT NULL");
    }


    // --------------------------------------------------
    // 3. Null Attachment Test
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Null Attachment Test");

    Serial.print("attach(nullptr): ");

    if (ubod.attach(1, nullptr)) { Serial.println("UNEXPECTED SUCCESS"); }
    else { Serial.println("REJECTED"); }

    printSlot(slot1);


    // --------------------------------------------------
    // 4. Attach Engine
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Attach Engine");

    Serial.print("attach(&primaryComms): ");

    if (ubod.attach(1, &primaryComms)) { Serial.println("SUCCESS"); } 
    else { Serial.println("FAILED"); }

    printSlot(slot1);


    // --------------------------------------------------
    // 5. Pointer Identity Test
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Pointer Identity Test");

    UbodEngine* attachedEngine = slot1->engine();

    Serial.print("Slot engine == primaryComms: ");

    if (attachedEngine == &primaryComms) {
        Serial.println("YES");
    } else {
        Serial.println("NO");
    }


    // --------------------------------------------------
    // 6. Duplicate Attachment Test
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Duplicate Attachment Test");

    Serial.print("attach(&telemetry): ");

    if (ubod.attach(1, &telemetry)) { Serial.println("UNEXPECTED SUCCESS"); } 
    else { Serial.println("REJECTED"); }

    printSlot(slot1);


    // --------------------------------------------------
    // 7. Detach Engine
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Detach Engine");

    Serial.print("detach(): ");

    if (ubod.detach(1)) { Serial.println("SUCCESS"); }
    else { Serial.println("FAILED"); }

    printSlot(slot1);


    // --------------------------------------------------
    // 8. Verify Detached State
    // --------------------------------------------------

    Serial.println();
    Serial.println("[8] Verify Detached State");

    Serial.print("Has Engine: ");
    Serial.println(slot1->hasEngine() ? "YES" : "NO");

    Serial.print("Engine Pointer: ");

    if (slot1->engine() == nullptr) {
        Serial.println("nullptr");
    } else {
        Serial.println("NOT NULL");
    }


    // --------------------------------------------------
    // 9. Reattach Another Engine
    // --------------------------------------------------

    Serial.println();
    Serial.println("[9] Reattach Another Engine");

    Serial.print("attach(&telemetry): ");

    if (ubod.attach(1, &telemetry)) { Serial.println("SUCCESS"); }
    else { Serial.println("FAILED"); }

    printSlot(slot1);


    // --------------------------------------------------
    // Complete
    // --------------------------------------------------

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}


// --------------------------------------------------
// Loop
// --------------------------------------------------

void loop() {
}