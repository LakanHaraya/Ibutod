#include <Arduino.h>
#include "Ubod.h"

void printCore(const char* label, const UbodCore* core) {
    Serial.print(label);

    if (core == nullptr) {
        Serial.println("NOT FOUND");
        return;
    }

    Serial.print("ID: ");
    Serial.print(core->id());
    Serial.print(" | Name: \"");
    Serial.print(core->name());
    Serial.print("\" | availability: ");

    if (core->isFree()) {
        Serial.println("FREE");
    } else {
        Serial.println("OCCUPIED");
    }
}

void printContainer(UbodContainer& container) {
    Serial.println();
    Serial.print("Capacity: ");
    Serial.println(container.capacity());

    Serial.print("Used: ");
    Serial.println(container.used());

    Serial.print("Free: ");
    Serial.println(container.free());

    for (unsigned int id = 1; id <= container.capacity(); ++id) {
        const UbodCore* core = container.get(id);

        Serial.print("Slot | ID: ");
        Serial.print(core->id());
        Serial.print(" | Name: \"");
        Serial.print(core->name());
        Serial.print("\" | availability: ");

        if (core->isFree()) {
            Serial.println("FREE");
        } else {
            Serial.println("OCCUPIED");
        }
    }
}

void findAllByName(UbodContainer& container, const char* name) {
    Serial.print("Searching for name: \"");
    Serial.print(name);
    Serial.println("\"");

    unsigned int foundCount = 0;

    for (unsigned int id = 1; id <= container.capacity(); ++id) {
        const UbodCore* core = container.get(id);

        if (core == nullptr) {
            continue;
        }

        if (strcmp(core->name(), name) == 0) {
            ++foundCount;

            Serial.print("Found #");
            Serial.print(foundCount);
            Serial.print(" | ID: ");
            Serial.print(core->id());
            Serial.print(" | Name: \"");
            Serial.print(core->name());
            Serial.println("\"");
        }
    }

    if (foundCount == 0) {
        Serial.println("No matching Core Slots found.");
    } else {
        Serial.print("Total matches: ");
        Serial.println(foundCount);
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("==================================");
    Serial.println("      UBOD v0.1.10 EXPERIMENT");
    Serial.println("==================================");

    UbodContainer container;

    Serial.println();
    Serial.println("Initial container status:");
    printContainer(container);

    Serial.println();
    Serial.println("Assigning Core Names:");

    Serial.println(
        container.get(1)->setName("comms")
            ? "Core 1: SUCCESS"
            : "Core 1: FAILED"
    );

    Serial.println(
        container.get(2)->setName("sensor")
            ? "Core 2: SUCCESS"
            : "Core 2: FAILED"
    );

    Serial.println(
        container.get(3)->setName("sensor")
            ? "Core 3: SUCCESS"
            : "Core 3: FAILED"
    );

    Serial.println(
        container.get(4)->setName("telemetry")
            ? "Core 4: SUCCESS"
            : "Core 4: FAILED"
    );

    Serial.println();
    Serial.println("Container after naming:");
    printContainer(container);

    // --------------------------------------------------
    // First-match lookup
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing findByName() first-match behavior:");

    const UbodCore* core = container.findByName("sensor");

    printCore("findByName(\"sensor\") -> ", core);

    // --------------------------------------------------
    // Find all matching names
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing duplicate-name discovery:");

    findAllByName(container, "sensor");

    // --------------------------------------------------
    // Missing name
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing missing name:");

    core = container.findByName("control");

    printCore("findByName(\"control\") -> ", core);

    // --------------------------------------------------
    // Null name
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing null name:");

    core = container.findByName(nullptr);

    printCore("findByName(nullptr) -> ", core);

    // --------------------------------------------------
    // Availability independence
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing lookup independent of availability:");

    container.occupy(2);

    core = container.findByName("sensor");

    printCore("Occupied sensor -> ", core);

    // --------------------------------------------------
    // Free one duplicate
    // --------------------------------------------------

    Serial.println();
    Serial.println("Freeing Core 2:");

    Serial.println(
        container.free(2)
            ? "Core 2 free(): SUCCESS"
            : "Core 2 free(): FAILED"
    );

    // --------------------------------------------------
    // Final status
    // --------------------------------------------------

    Serial.println();
    Serial.println("Final container status:");
    printContainer(container);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}