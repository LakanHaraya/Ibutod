#include <Arduino.h>
#include <cstring>
#include "Ubod.h"

void printCore(const UbodCore* core) {
    if (core == nullptr) {
        Serial.println("  nullptr");
        return;
    }

    Serial.print("  ID: ");
    Serial.print(core->id());
    Serial.print(" | Name: \"");
    Serial.print(core->name());
    Serial.println("\"");
}

void printMatches(
    const char* name,
    UbodCore** results,
    unsigned int count
) {
    Serial.print("Matches for \"");
    Serial.print(name);
    Serial.println("\":");

    if (count == 0) {
        Serial.println("  NONE");
        return;
    }

    for (unsigned int i = 0; i < count; ++i) {
        Serial.print("  #");
        Serial.print(i + 1);
        Serial.print(" -> ");
        printCore(results[i]);
    }

    Serial.print("Total matches: ");
    Serial.println(count);
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("==================================");
    Serial.println("      UBOD v0.1.10 EXPERIMENT");
    Serial.println("==================================");

    UbodContainer container;

    // --------------------------------------------------
    // Assign names
    // --------------------------------------------------

    container.get(1)->setName("comms");
    container.get(2)->setName("sensor");
    container.get(3)->setName("sensor");
    container.get(4)->setName("telemetry");

    Serial.println();
    Serial.println("Assigned names:");

    for (unsigned int id = 1; id <= container.capacity(); ++id) {
        const UbodCore* core = container.get(id);

        Serial.print("Core ");
        Serial.print(id);
        Serial.print(" | Name: \"");
        Serial.print(core->name());
        Serial.println("\"");
    }

    // --------------------------------------------------
    // Multiple-match search
    // --------------------------------------------------

    UbodCore* results[UbodContainer::Capacity] = {};

    Serial.println();
    Serial.println("Searching for \"sensor\"...");

    unsigned int count =
        container.findByName(
            "sensor",
            results,
            UbodContainer::Capacity
        );

    printMatches("sensor", results, count);

    // --------------------------------------------------
    // Search with smaller result buffer
    // --------------------------------------------------

    UbodCore* limitedResults[1] = {};

    Serial.println();
    Serial.println("Searching for \"sensor\" with maxResults = 1...");

    count =
        container.findByName(
            "sensor",
            limitedResults,
            1
        );

    printMatches("sensor", limitedResults, count);

    // --------------------------------------------------
    // Missing name
    // --------------------------------------------------

    Serial.println();
    Serial.println("Searching for \"control\"...");

    count =
        container.findByName(
            "control",
            results,
            UbodContainer::Capacity
        );

    printMatches("control", results, count);

    // --------------------------------------------------
    // nullptr protection
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing nullptr name:");

    count =
        container.findByName(
            nullptr,
            results,
            UbodContainer::Capacity
        );

    Serial.print("Result count: ");
    Serial.println(count);

    // --------------------------------------------------
    // nullptr result buffer
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing nullptr result buffer:");

    count =
        container.findByName(
            "sensor",
            nullptr,
            UbodContainer::Capacity
        );

    Serial.print("Result count: ");
    Serial.println(count);

    // --------------------------------------------------
    // Zero result capacity
    // --------------------------------------------------

    Serial.println();
    Serial.println("Testing maxResults = 0:");

    count =
        container.findByName(
            "sensor",
            results,
            0
        );

    Serial.print("Result count: ");
    Serial.println(count);

    Serial.println();
    Serial.println("==================================");
    Serial.println("      EXPERIMENT COMPLETE");
    Serial.println("==================================");
}

void loop() {
}