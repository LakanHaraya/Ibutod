#include <Arduino.h>
#include "Ubod.h"

// ==================================================
// UBOD v0.1.15 EXPERIMENT
// Filipino Terminology Migration Validation
// ==================================================


// --------------------------------------------------
// Salalayan
// --------------------------------------------------

Salalayan salalayan;


// --------------------------------------------------
// Test Sapad
// --------------------------------------------------

Sapad primaryComms;
Sapad telemetry;
Sapad diagnostics;


// ==================================================
// Helpers
// ==================================================

const char* availabilityText(SalpakanAvailability availability) {
    switch (availability) {
        case SalpakanAvailability::Free:
            return "FREE";

        case SalpakanAvailability::Occupied:
            return "OCCUPIED";

        default:
            return "UNKNOWN";
    }
}


const char* stateText(SalpakanState state) {
    switch (state) {
        case SalpakanState::Initializing:
            return "INITIALIZING";

        case SalpakanState::Ready:
            return "READY";

        case SalpakanState::Running:
            return "RUNNING";

        case SalpakanState::Invalid:
            return "INVALID";

        default:
            return "UNKNOWN";
    }
}


void printLine() {
    Serial.println(
        "+-----+------------------+---------+-----------+-------------+---------------+"
    );
}


// --------------------------------------------------
// Salpakan Table
// --------------------------------------------------

void printSalpakanHeader() {
    printLine();

    Serial.println(
        "| ID  | NAME             | ID OK   | SAPAD     | AVAILABILITY| STATE         |"
    );

    printLine();
}


void printSalpakanRow(const Salpakan* salpakan) {
    if (salpakan == nullptr) {
        Serial.println("| --- | NOT FOUND        | ---     | ---       | ---         | ---           |");
        return;
    }

    char buffer[128];

    snprintf(
        buffer,
        sizeof(buffer),
        "| %-3u | %-16s | %-7s | %-9s | %-11s | %-13s |",
        salpakan->id(),
        salpakan->name(),
        salpakan->isIdValid() ? "YES" : "NO",
        salpakan->hasSapad() ? "ATTACHED" : "NONE",
        availabilityText(salpakan->availability()),
        stateText(salpakan->state())
    );

    Serial.println(buffer);
}


void printSalpakanTable() {
    printSalpakanHeader();

    for (unsigned int id = 1; id <= salalayan.capacity(); ++id) {
        printSalpakanRow(salalayan.get(id));
    }

    printLine();
}


// --------------------------------------------------
// Result Helper
// --------------------------------------------------

void printResult(const char* label, bool result) {
    Serial.print(label);
    Serial.print(": ");
    Serial.println(result ? "PASS" : "FAIL");
}


// --------------------------------------------------
// Section Helper
// --------------------------------------------------

void printSection(unsigned int number, const char* title) {
    Serial.println();
    Serial.print("[");
    Serial.print(number);
    Serial.print("] ");
    Serial.println(title);

    Serial.println(
        "------------------------------------------------------------"
    );
}


// ==================================================
// Experiment
// ==================================================

void setup() {

    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("============================================================");
    Serial.println("             UBOD v0.1.15 EXPERIMENT");
    Serial.println("       Filipino Terminology Migration Validation");
    Serial.println("============================================================");


    // --------------------------------------------------
    // 1. Salalayan Overview
    // --------------------------------------------------

    printSection(1, "Salalayan Overview");

    Serial.print("Capacity: ");
    Serial.println(salalayan.capacity());

    Serial.print("Used: ");
    Serial.println(salalayan.used());

    Serial.print("Free: ");
    Serial.println(salalayan.free());

    printSalpakanTable();


    // --------------------------------------------------
    // 2. Salpakan Identity
    // --------------------------------------------------

    printSection(2, "Salpakan Identity");

    Salpakan* salpakan1 = salalayan.get(1);
    Salpakan* salpakan2 = salalayan.get(2);
    Salpakan* salpakan3 = salalayan.get(3);
    Salpakan* salpakan4 = salalayan.get(4);

    printResult(
        "Salpakan #1 exists",
        salpakan1 != nullptr
    );

    printResult(
        "Salpakan #2 exists",
        salpakan2 != nullptr
    );

    printResult(
        "Salpakan #3 exists",
        salpakan3 != nullptr
    );

    printResult(
        "Salpakan #4 exists",
        salpakan4 != nullptr
    );

    printResult(
        "Salpakan #1 ID valid",
        salpakan1 != nullptr &&
        salpakan1->isIdValid()
    );

    printResult(
        "Salpakan #2 ID valid",
        salpakan2 != nullptr &&
        salpakan2->isIdValid()
    );

    printResult(
        "Salpakan #3 ID valid",
        salpakan3 != nullptr &&
        salpakan3->isIdValid()
    );

    printResult(
        "Salpakan #4 ID valid",
        salpakan4 != nullptr &&
        salpakan4->isIdValid()
    );

    printSalpakanTable();


    // --------------------------------------------------
    // 3. Naming Salpakan
    // --------------------------------------------------

    printSection(3, "Salpakan Naming");

    bool result;

    result = salpakan1->setName("Slot Name 1");
    printResult("Name Salpakan #1", result);

    result = salpakan2->setName("Slot Name 2");
    printResult("Name Salpakan #2", result);

    result = salpakan3->setName("Slot Name 3");
    printResult("Name Salpakan #3", result);

    // result = salpakan4->setName("Slot Name 4");
    printResult("Name Salpakan #4", result);

    printSalpakanTable();


    // --------------------------------------------------
    // 4. Initial Availability
    // --------------------------------------------------

    printSection(4, "Initial Salpakan Availability");

    bool allFree = true;

    for (
        unsigned int id = 1;
        id <= salalayan.capacity();
        ++id
    ) {
        Salpakan* salpakan = salalayan.get(id);

        if (
            salpakan == nullptr ||
            !salpakan->isFree() ||
            salpakan->hasSapad()
        ) {
            allFree = false;
            break;
        }
    }

    printResult(
        "All Salpakan initially FREE",
        allFree
    );

    printSalpakanTable();


    // --------------------------------------------------
    // 5. Attach Sapad
    // --------------------------------------------------

    printSection(5, "Attach Sapad");

    result = salalayan.attach(
        1,
        &primaryComms
    );

    printResult(
        "Attach primaryComms to Salpakan #1",
        result
    );


    result = salalayan.attach(
        2,
        &telemetry
    );

    printResult(
        "Attach telemetry to Salpakan #2",
        result
    );


    result = salalayan.attach(
        3,
        &diagnostics
    );

    printResult(
        "Attach diagnostics to Salpakan #3",
        result
    );

    printSalpakanTable();


    // --------------------------------------------------
    // 6. Sapad Attachment Identity
    // --------------------------------------------------

    printSection(6, "Sapad Attachment Identity");

    printResult(
        "Salpakan #1 -> primaryComms",
        salpakan1->sapad() == &primaryComms
    );

    printResult(
        "Salpakan #2 -> telemetry",
        salpakan2->sapad() == &telemetry
    );

    printResult(
        "Salpakan #3 -> diagnostics",
        salpakan3->sapad() == &diagnostics
    );


    // --------------------------------------------------
    // 7. Salalayan Accounting
    // --------------------------------------------------

    printSection(7, "Salalayan Accounting");

    Serial.print("Capacity: ");
    Serial.println(salalayan.capacity());

    Serial.print("Used: ");
    Serial.println(salalayan.used());

    Serial.print("Free: ");
    Serial.println(salalayan.free());

    printResult(
        "Used == 3",
        salalayan.used() == 3
    );

    printResult(
        "Free == Capacity - 3",
        salalayan.free() ==
        salalayan.capacity() - 3
    );


    // --------------------------------------------------
    // 8. Reject Second Sapad
    // --------------------------------------------------

    printSection(8, "Reject Second Sapad");

    result = salalayan.attach(
        1,
        &telemetry
    );

    printResult(
        "Second Sapad rejected",
        !result
    );

    printResult(
        "Original Sapad preserved",
        salpakan1->sapad() == &primaryComms
    );

    printSalpakanTable();


    // --------------------------------------------------
    // 9. Find Free Salpakan
    // --------------------------------------------------

    printSection(9, "Find Free Salpakan");

    Salpakan* freeSalpakan =
        salalayan.findFree();

    if (freeSalpakan != nullptr) {

        Serial.print(
            "First FREE Salpakan ID: "
        );

        Serial.println(
            freeSalpakan->id()
        );

        printResult(
            "Found Salpakan is FREE",
            freeSalpakan->isFree()
        );

    } else {

        Serial.println(
            "No FREE Salpakan found."
        );
    }


    // --------------------------------------------------
    // 10. Detach Sapad
    // --------------------------------------------------

    printSection(10, "Detach Sapad");

    result = salalayan.detach(2);

    printResult(
        "Detach telemetry from Salpakan #2",
        result
    );

    printResult(
        "Salpakan #2 has no Sapad",
        !salpakan2->hasSapad()
    );

    printResult(
        "Salpakan #2 becomes FREE",
        salpakan2->isFree()
    );

    printSalpakanTable();


    // --------------------------------------------------
    // 11. Reattach Different Sapad
    // --------------------------------------------------

    printSection(11, "Reattach Sapad");

    result = salalayan.attach(
        2,
        &primaryComms
    );

    printResult(
        "Attach Sapad to freed Salpakan",
        result
    );

    printResult(
        "Salpakan #2 now occupied",
        salpakan2->isOccupied()
    );

    printResult(
        "Salpakan #2 Sapad reference valid",
        salpakan2->sapad() ==
        &primaryComms
    );

    printSalpakanTable();


    // --------------------------------------------------
    // 12. Lookup by Name
    // --------------------------------------------------

    printSection(12, "Lookup Salpakan by Name");

    Salpakan* results[4] = {};

    unsigned int found =
        salalayan.findByName(
            "Slot Name 3",
            results,
            4
        );

    Serial.print(
        "Matches for \"Slot Name 3\": "
    );

    Serial.println(found);

    for (
        unsigned int i = 0;
        i < found;
        ++i
    ) {
        Serial.print(
            "Found Salpakan ID: "
        );

        Serial.println(
            results[i]->id()
        );
    }


    // --------------------------------------------------
    // 13. Multiple Salalayan
    // --------------------------------------------------

    printSection(13, "Local Salpakan Identity");

    Salalayan secondarySalalayan;

    Salpakan* primarySalpakan1 =
        salalayan.get(1);

    Salpakan* secondarySalpakan1 =
        secondarySalalayan.get(1);

    printResult(
        "Primary Salalayan has Salpakan #1",
        primarySalpakan1 != nullptr
    );

    printResult(
        "Secondary Salalayan has Salpakan #1",
        secondarySalpakan1 != nullptr
    );

    printResult(
        "Both have local ID == 1",
        primarySalpakan1->id() == 1 &&
        secondarySalpakan1->id() == 1
    );

    printResult(
        "They are different Salpakan objects",
        primarySalpakan1 != secondarySalpakan1
    );


    // --------------------------------------------------
    // 14. Lifecycle Boundary
    // --------------------------------------------------

    printSection(14, "Current Lifecycle Boundary");

    Serial.println(
        "Salpakan currently owns its experimental lifecycle."
    );

    Serial.println(
        "Sapad has no execution contract yet."
    );

    Serial.println(
        "Attachment does not start a Sapad."
    );

    Serial.println(
        "Attachment only establishes a modular relationship."
    );

    Serial.println(
        "Runtime coordination is intentionally deferred."
    );


    // --------------------------------------------------
    // 15. Terminology Validation
    // --------------------------------------------------

    printSection(15, "Canonical Terminology");

    Serial.println(
        "Silid"
    );

    Serial.println(
        "  -> Salalayan"
    );

    Serial.println(
        "       -> Salpakan"
    );

    Serial.println(
        "            -> Sapad"
    );


    // --------------------------------------------------
    // Complete
    // --------------------------------------------------

    Serial.println();
    Serial.println("============================================================");
    Serial.println("               EXPERIMENT COMPLETE");
    Serial.println("============================================================");
}


void loop() {
}