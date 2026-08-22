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
    Serial.println("      UBOD v0.1.9 EXPERIMENT");
    Serial.println("==================================");

    UbodContainer container;

    Serial.println();
    Serial.println("Initial container status:");
    printContainerStatus(container);

    Serial.println();
    
    Serial.println("Occupy Core 1:");
    Serial.println(
        container.occupy(1) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Occupy Core 1 again:");
    Serial.println(
        container.occupy(1) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Occupy Core 4:");
    Serial.println(
        container.occupy(4) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Occupy Core 5:");
    Serial.println(
        container.occupy(5) ? "SUCCESS" : "FAILED"
    );
    
    Serial.println();
    Serial.println("Free Core 1:");
    Serial.println(
        container.free(1) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Free Core 1 again:");
    Serial.println(
        container.free(1) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Free Core 0:");
    Serial.println(
        container.free(0) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Free Core 5:");
    Serial.println(
        container.free(5) ? "SUCCESS" : "FAILED"
    );

    // printContainerStatus(container);

    // Serial.println();
    // Serial.println("Finding free slot...");

    // UbodCore* freeCore = container.findFree();

    // printCore("Found", freeCore);

    // if (freeCore != nullptr) {
    //     freeCore->occupy();
    // }

    // Serial.println();
    // Serial.println("After occupying discovered slot:");
    // printContainerStatus(container);

    // Serial.println();
    // Serial.println("Testing invalid ID lookup:");

    // printCore("ID 0", container.get(0));
    // printCore("ID 5", container.get(5));

    // Serial.println();
    // Serial.println("Occupying remaining free slot...");

    // freeCore = container.findFree();

    // if (freeCore != nullptr) {
    //     freeCore->occupy();
    // }

    // printContainerStatus(container);

    // Serial.println();
    // Serial.println("Searching when all slots are occupied:");

    // freeCore = container.findFree();

    // printCore("Found", freeCore);

    // Serial.println();
    // Serial.println("Freeing Core 2...");

    // container.get(2)->free();

    // printContainerStatus(container);

    // Serial.println();
    // Serial.println("Finding free slot again:");

    // freeCore = container.findFree();

    // printCore("Found", freeCore);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}