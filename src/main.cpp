#include <Arduino.h>
#include "Ibutod.h"

// --------------------------------------------------
// Experiment 22 — Sapad Execution Boundary
// --------------------------------------------------

class TestSapad : public Sapad {
    public:
        void run() override {
            _runCount++;
        }

        unsigned int runCount() const {
            return _runCount;
        }

    private:
        unsigned int _runCount = 0;
};

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("=== Ibutod Experiment 22 ===");

    Salalayan<2> salalayan("Experiment");
    TestSapad sapad;

    Serial.println();
    Serial.println("[1] Initial state");

    Serial.print("Occupied: ");
    Serial.println(salalayan.get(1)->isOccupied() ? "YES" : "NO");

    Serial.print("Enabled: ");
    Serial.println(salalayan.get(1)->isEnabled() ? "YES" : "NO");

    Serial.println();
    Serial.println("[2] Attach Sapad");

    bool attached = salalayan.attach(1, &sapad);
    Serial.print("Attach: ");
    Serial.println(attached ? "PASS" : "FAIL");

    Serial.print("Occupied: ");
    Serial.println(
        salalayan.get(1)->isOccupied() ? "PASS" : "FAIL"
    );

    Serial.println();
    Serial.println("[3] Enable Salpakan");

    bool enabled = salalayan.enable(1);
    Serial.print("Enable: ");
    Serial.println(enabled ? "PASS" : "FAIL");

    Serial.println();
    Serial.println("[4] Run Sapad");

    sapad.run();

    Serial.print("Run count: ");
    Serial.println(sapad.runCount());

    Serial.println(
        sapad.runCount() == 1 ? "[PASS] Sapad executed"
                               : "[FAIL] Sapad execution"
    );

    Serial.println();
    Serial.println("[5] Run Sapad again");

    sapad.run();

    Serial.print("Run count: ");
    Serial.println(sapad.runCount());

    Serial.println(
        sapad.runCount() == 2 ? "[PASS] Sapad executed twice"
                              : "[FAIL] Sapad execution count"
    );

    Serial.println();
    Serial.println("=== Experiment 22 COMPLETE ===");
}

void loop() {
}