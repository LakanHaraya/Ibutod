#include <Arduino.h>
#include <Ibutod.h>

// --------------------------------------------------
// Experiment 22-B — Multiple Sapad Instances
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
    Serial.println("=== Ibutod Experiment 22-B ===");

    Salalayan<2> salalayan("Experiment");
    TestSapad sapadA;
    TestSapad sapadB;

    Serial.println();
    Serial.println("[1] Attach two Sapad instances");

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
    Serial.println("[3] Run Sapad A");

    sapadA.run();

    Serial.print("Sapad A run count: ");
    Serial.println(sapadA.runCount());

    Serial.println(
    sapadA.runCount() == 1
        ? "[PASS] Sapad A executed"
        : "[FAIL] Sapad A execution"
    );

    Serial.println();
    Serial.println("[4] Run Sapad B");

    sapadB.run();

    Serial.print("Sapad B run count: ");
    Serial.println(sapadB.runCount());

    Serial.println(
    sapadB.runCount() == 1
        ? "[PASS] Sapad B executed"
        : "[FAIL] Sapad B execution"
    );

    Serial.println();
    Serial.println("[5] Verify independent execution state");

    bool independent =
        sapadA.runCount() == 1 &&
        sapadB.runCount() == 1;

    Serial.print("Sapad A count: ");
    Serial.println(sapadA.runCount());

    Serial.print("Sapad B count: ");
    Serial.println(sapadB.runCount());

    Serial.println(
        independent
            ? "[PASS] Sapad instances are independent"
            : "[FAIL] Sapad instances share execution state"
    );

    Serial.println();
    Serial.println("=== Experiment 22-B COMPLETE ===");
}

void loop() {
}