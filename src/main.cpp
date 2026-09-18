#include <Arduino.h>
#include "Ibutod.h"

// --------------------------------------------------
// Experiment 22-E — Detach / Reattach Behavior
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
    Serial.println("=== Ibutod Experiment 22-E ===");

    Salalayan<2> salalayan("Experiment");

    TestSapad sapadA;
    TestSapad sapadB;

    Serial.println();
    Serial.println("[1] Attach Sapad A and B");

    bool attachedA = salalayan.attach(1, &sapadA);
    bool attachedB = salalayan.attach(2, &sapadB);

    Serial.print("Attach Sapad A: ");
    Serial.println(attachedA ? "PASS" : "FAIL");

    Serial.print("Attach Sapad B: ");
    Serial.println(attachedB ? "PASS" : "FAIL");

    Serial.println();
    Serial.println("[2] Enable both Salpakan");

    bool enabledA = salalayan.enable(1);
    bool enabledB = salalayan.enable(2);

    Serial.print("Enable Salpakan 1: ");
    Serial.println(enabledA ? "PASS" : "FAIL");

    Serial.print("Enable Salpakan 2: ");
    Serial.println(enabledB ? "PASS" : "FAIL");

    Serial.println();
    Serial.println("[3] Verify detach is blocked while enabled");

    bool detachWhileEnabled = salalayan.detach(1);

    Serial.print("Detach enabled Salpakan: ");
    Serial.println(
        !detachWhileEnabled
            ? "PASS"
            : "FAIL"
    );

    Serial.println();
    Serial.println("[4] Disable Salpakan 1");

    bool disabledA = salalayan.disable(1);

    Serial.print("Disable Salpakan 1: ");
    Serial.println(disabledA ? "PASS" : "FAIL");

    Serial.println();
    Serial.println("[5] Detach Sapad A");

    bool detachedA = salalayan.detach(1);

    Serial.print("Detach Sapad A: ");
    Serial.println(detachedA ? "PASS" : "FAIL");

    Serial.print("Salpakan 1 occupied: ");
    Serial.println(
        salalayan.get(1)->isOccupied()
            ? "FAIL"
            : "PASS"
    );

    Serial.print("Salpakan 1 enabled: ");
    Serial.println(
        salalayan.get(1)->isEnabled()
            ? "FAIL"
            : "PASS"
    );

    Serial.println();
    Serial.println("[6] Reattach Sapad A to Salpakan 1");

    bool reattachedA = salalayan.attach(1, &sapadA);

    Serial.print("Reattach Sapad A: ");
    Serial.println(reattachedA ? "PASS" : "FAIL");

    Serial.print("Salpakan 1 occupied: ");
    Serial.println(
        salalayan.get(1)->isOccupied()
            ? "PASS"
            : "FAIL"
    );

    Serial.println();
    Serial.println("[7] Execute reattached Sapad");

    Sapad* sapad = salalayan.get(1)->sapad();

    if (sapad != nullptr) {
        sapad->run();
    }

    Serial.print("Sapad A run count: ");
    Serial.println(sapadA.runCount());

    Serial.println(
        sapadA.runCount() == 1
            ? "[PASS] Reattached Sapad executed"
            : "[FAIL] Reattached Sapad execution"
    );

    Serial.println();
    Serial.println("=== Experiment 22-E COMPLETE ===");
}

void loop() {
}