#include <Arduino.h>
#include "Ubod.h"

UbodContainer ubod;

void printSlot(const UbodSlot* slot) {
    if (slot == nullptr) {
        Serial.println("Slot: NOT FOUND");
        return;
    }

    Serial.print("Slot #");
    Serial.print(slot->slotId());

    Serial.print(" | Slot Name: \"");
    Serial.print(slot->slotName());
    Serial.print("\"");

    Serial.print(" | ID valid: ");
    Serial.print(slot->isSlotIdValid() ? "YES" : "NO");

    Serial.print(" | availability: ");

    if (slot->isFree()) {
        Serial.print("FREE");
    } else {
        Serial.print("OCCUPIED");
    }

    Serial.print(" | state: ");

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

        case UbodSlotState::Released:
            Serial.print("RELEASED");
            break;

        case UbodSlotState::Invalid:
            Serial.print("INVALID");
            break;
    }

    Serial.println();
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      UBOD v0.1.11 EXPERIMENT");
    Serial.println("==================================");

    // --------------------------------------------------
    // 1. Container
    // --------------------------------------------------

    Serial.println();
    Serial.println("Container:");

    Serial.print("Capacity: ");
    Serial.println(ubod.capacity());

    Serial.print("Used: ");
    Serial.println(ubod.used());

    Serial.print("Free: ");
    Serial.println(ubod.free());

    // --------------------------------------------------
    // 2. Slot identity
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Slot identity:");

    UbodSlot* slot1 = ubod.get(1);
    UbodSlot* slot2 = ubod.get(2);

    printSlot(slot1);
    printSlot(slot2);

    // --------------------------------------------------
    // 3. Slot naming
    // --------------------------------------------------

    Serial.println();
    Serial.println("Assigning Slot Names:");

    Serial.print("Slot 1 -> \"comms\": ");

    if (slot1->setSlotName("comms")) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }

    Serial.print("Slot 2 -> \"sensor\": ");

    if (slot2->setSlotName("sensor")) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }

    printSlot(slot1);
    printSlot(slot2);

    // --------------------------------------------------
    // 4. Slot lifecycle
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Slot lifecycle:");

    slot1->begin();

    Serial.println("After begin():");
    printSlot(slot1);

    slot1->update();

    Serial.println("After update():");
    printSlot(slot1);

    // --------------------------------------------------
    // 5. Slot availability
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Slot availability:");

    Serial.print("Slot 1 occupy(): ");

    if (slot1->occupy()) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }

    printSlot(slot1);

    Serial.print("Slot 1 free(): ");

    if (slot1->free()) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }

    printSlot(slot1);

    // --------------------------------------------------
    // 6. Slot lookup by Slot Name
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Slot Name lookup:");

    UbodSlot* results[4] = {};

    unsigned int count = ubod.findBySlotName(
        "sensor",
        results,
        4
    );

    Serial.print("Matches for \"sensor\": ");
    Serial.println(count);

    for (unsigned int i = 0; i < count; ++i) {
        printSlot(results[i]);
    }

    // --------------------------------------------------
    // 7. Slot / Engine conceptual boundary
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Slot / Engine boundary:");

    Serial.println("UbodSlot represents a resource slot.");
    Serial.println("Slot ID identifies the slot.");
    Serial.println("Slot Name names the slot.");
    Serial.println("No Core Engine is attached yet.");

    // --------------------------------------------------
    // 8. Release
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Slot release:");

    slot1->release();

    printSlot(slot1);

    Serial.println();
    Serial.println("Release completed.");
    Serial.println("Engine attachment/detachment is not implemented.");

    // --------------------------------------------------
    // Complete
    // --------------------------------------------------

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}