#include <Arduino.h>
#include "Ubod.h"

const char* availabilityText(UbodAvailability availability) {
    switch (availability) {
        case UbodAvailability::Free:
            return "FREE";

        case UbodAvailability::Occupied:
            return "OCCUPIED";
    }

    return "UNKNOWN";
}

void printCore(const char* label, const UbodCore& core) {
    Serial.print(label);
    Serial.print(" | ID: ");
    Serial.print(core.id());

    Serial.print(" | Name: \"");
    Serial.print(core.name());
    Serial.print("\"");

    Serial.print(" | availability: ");
    Serial.print(availabilityText(core.availability()));

    Serial.print(" | state: ");

    switch (core.state()) {
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
    delay(1000);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      UBOD v0.1.7 EXPERIMENT");
    Serial.println("==================================");
    Serial.println();

    UbodCore coreA(1);
    UbodCore coreB(2);

    coreA.setName("primary");
    coreB.setName("sensor");

    Serial.println("Initial availability:");
    printCore("Core A", coreA);
    printCore("Core B", coreB);

    Serial.println();
    Serial.println("Occupying Core A:");

    Serial.print("Core A occupy(): ");
    Serial.println(
        coreA.occupy()
            ? "SUCCESS"
            : "FAILED"
    );

    printCore("Core A", coreA);

    Serial.println();
    Serial.println("Attempting to occupy Core A again:");

    Serial.print("Core A occupy(): ");
    Serial.println(
        coreA.occupy()
            ? "SUCCESS"
            : "FAILED"
    );

    printCore("Core A", coreA);

    Serial.println();
    Serial.println("Freeing Core A:");

    Serial.print("Core A free(): ");
    Serial.println(
        coreA.free()
            ? "SUCCESS"
            : "FAILED"
    );

    printCore("Core A", coreA);

    Serial.println();
    Serial.println("Attempting to free Core A again:");

    Serial.print("Core A free(): ");
    Serial.println(
        coreA.free()
            ? "SUCCESS"
            : "FAILED"
    );

    printCore("Core A", coreA);

    Serial.println();
    Serial.println("Testing independent availability:");

    coreA.occupy();

    Serial.print("Core A: ");
    Serial.println(availabilityText(coreA.availability()));

    Serial.print("Core B: ");
    Serial.println(availabilityText(coreB.availability()));

    Serial.println();
    Serial.println("Testing lifecycle separation:");

    coreB.begin();

    Serial.print("Core B state: ");
    Serial.print(
        coreB.state() == UbodState::Ready
            ? "READY"
            : "OTHER"
    );

    Serial.print(" | availability: ");
    Serial.println(
        availabilityText(coreB.availability())
    );

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}