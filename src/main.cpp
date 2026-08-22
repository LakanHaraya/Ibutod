#include <Arduino.h>
#include "Ubod.h"

void printContainer(const char* name, UbodContainer& container) {
    Serial.print(name);
    Serial.print(" | Capacity: ");
    Serial.print(container.capacity());
    Serial.print(" | Used: ");
    Serial.print(container.used());
    Serial.print(" | Free: ");
    Serial.println(container.free());
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("==================================");
    Serial.println("      UBOD CONTAINER EXPERIMENT");
    Serial.println("==================================");

    UbodContainer containerA;
    UbodContainer containerB;

    Serial.println();
    Serial.println("Initial status:");

    printContainer("Container A", containerA);
    printContainer("Container B", containerB);

    Serial.println();
    Serial.println("Occupying Core 1 in Container A...");

    Serial.println(
        containerA.occupy(1) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Status after occupying Container A:");

    printContainer("Container A", containerA);
    printContainer("Container B", containerB);

    Serial.println();
    Serial.println("Occupying Core 1 in Container B...");

    Serial.println(
        containerB.occupy(1) ? "SUCCESS" : "FAILED"
    );

    Serial.println();
    Serial.println("Final status:");

    printContainer("Container A", containerA);
    printContainer("Container B", containerB);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}