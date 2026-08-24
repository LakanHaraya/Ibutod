#include <Arduino.h>
#include <Ubod.h>

UbodContainer ubod;

void printSlot(const UbodCore* slot) {
    if (slot == nullptr) {
        Serial.println("Slot: NOT FOUND");
        return;
    }

    Serial.print("Slot #");
    Serial.print(slot->id());

    Serial.print(" | Slot Name: \"");
    Serial.print(slot->name());
    Serial.print("\"");

    Serial.print(" | availability: ");

    if (slot->isFree()) {
        Serial.print("FREE");
    } else {
        Serial.print("OCCUPIED");
    }

    Serial.print(" | state: ");

    switch (slot->state()) {
        case UbodState::Initializing:
            Serial.print("INITIALIZING");
            break;

        case UbodState::Ready:
            Serial.print("READY");
            break;

        case UbodState::Running:
            Serial.print("RUNNING");
            break;

        case UbodState::Released:
            Serial.print("RELEASED");
            break;

        case UbodState::Invalid:
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
    // 1. Core Slot identity
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Core Slot identity:");

    UbodCore* slot1 = ubod.get(1);
    UbodCore* slot2 = ubod.get(2);

    printSlot(slot1);
    printSlot(slot2);

    // --------------------------------------------------
    // 2. Slot Name
    // --------------------------------------------------

    Serial.println();
    Serial.println("Assigning Slot Names:");

    Serial.print("Slot 1 -> \"primary\": ");

    if (slot1->setName("primary")) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }

    Serial.print("Slot 2 -> \"sensor\": ");

    if (slot2->setName("sensor")) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }

    printSlot(slot1);
    printSlot(slot2);

    // --------------------------------------------------
    // 3. Slot lifecycle
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
    // 4. Slot availability
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

    Serial.print("Slot 2 availability: ");

    if (slot2->isFree()) {
        Serial.println("FREE");
    } else {
        Serial.println("OCCUPIED");
    }

    // --------------------------------------------------
    // 5. Core Slot != Core Engine
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Core Slot / Core Engine separation:");

    Serial.println("Slot 1 represents a resource slot.");
    Serial.println("Slot Name: primary");
    Serial.println("No Core Engine is assigned yet.");

    // --------------------------------------------------
    // 6. Release semantics
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing Slot release:");

    slot1->release();

    printSlot(slot1);

    Serial.println();
    Serial.println("After release():");
    Serial.println("The Core Slot is no longer valid for lifecycle operations.");
    Serial.println("Core Engine attachment/detachment is NOT implemented yet.");

    // --------------------------------------------------
    // 7. Container remains the Slot manager
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing UbodContainer:");

    Serial.print("Container capacity: ");
    Serial.println(ubod.capacity());

    Serial.print("Container used: ");
    Serial.println(ubod.used());

    Serial.print("Container free: ");
    Serial.println(ubod.free());

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}