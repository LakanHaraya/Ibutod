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

void printCore(const char* label, const UbodCore* core) {
    Serial.print(label);

    if (core == nullptr) {
        Serial.println(" -> NOT FOUND");
        return;
    }

    Serial.print(" | ID: ");
    Serial.print(core->id());

    Serial.print(" | Name: \"");
    Serial.print(core->name());
    Serial.print("\"");

    Serial.print(" | availability: ");
    Serial.println(availabilityText(core->availability()));
}

void printContainerStatus(const UbodContainer& container) {
    Serial.println();
    Serial.print("Capacity: ");
    Serial.println(container.capacity());

    Serial.print("Used: ");
    Serial.println(container.used());

    Serial.print("Free: ");
    Serial.println(container.free());

    for (unsigned int id = 1; id <= container.capacity(); ++id) {
        printCore("Slot", container.get(id));
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      UBOD v0.1.8 EXPERIMENT");
    Serial.println("==================================");

    UbodContainer container;

    Serial.println();
    Serial.println("Initial container status:");
    printContainerStatus(container);

    Serial.println();
    Serial.println("Occupying Core 1 and Core 2...");

    container.get(1)->occupy();
    container.get(2)->occupy();

    printContainerStatus(container);

    Serial.println();
    Serial.println("Finding free slot...");

    UbodCore* freeCore = container.findFree();

    printCore("Found", freeCore);

    if (freeCore != nullptr) {
        freeCore->occupy();
    }

    Serial.println();
    Serial.println("After occupying discovered slot:");
    printContainerStatus(container);

    Serial.println();
    Serial.println("Testing invalid ID lookup:");

    printCore("ID 0", container.get(0));
    printCore("ID 5", container.get(5));

    Serial.println();
    Serial.println("Occupying remaining free slot...");

    freeCore = container.findFree();

    if (freeCore != nullptr) {
        freeCore->occupy();
    }

    printContainerStatus(container);

    Serial.println();
    Serial.println("Searching when all slots are occupied:");

    freeCore = container.findFree();

    printCore("Found", freeCore);

    Serial.println();
    Serial.println("Freeing Core 2...");

    container.get(2)->free();

    printContainerStatus(container);

    Serial.println();
    Serial.println("Finding free slot again:");

    freeCore = container.findFree();

    printCore("Found", freeCore);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}