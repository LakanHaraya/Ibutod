#include <Arduino.h>
#include "Ibutod.h"

// --------------------------------------------------
// Experiment 22-D — Execution Through Salpakan
// --------------------------------------------------

class SensorSapad : public Sapad {
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

class CounterSapad : public Sapad {
    public:
        void run() override {
            _value += 10;
        }

        unsigned int value() const {
            return _value;
        }

    private:
        unsigned int _value = 0;
};

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("=== Ibutod Experiment 22-D ===");

    Salalayan<2> salalayan("Experiment");

    SensorSapad sensorSapad;
    CounterSapad counterSapad;

    Serial.println();
    Serial.println("[1] Attach different Sapad types");

    bool attachedSensor = salalayan.attach(1, &sensorSapad);
    bool attachedCounter = salalayan.attach(2, &counterSapad);

    Serial.print("Attach SensorSapad: ");
    Serial.println(attachedSensor ? "PASS" : "FAIL");

    Serial.print("Attach CounterSapad: ");
    Serial.println(attachedCounter ? "PASS" : "FAIL");

    Serial.println();
    Serial.println("[2] Retrieve Sapad through Salpakan");

    Sapad* sapad1 = salalayan.get(1)->sapad();
    Sapad* sapad2 = salalayan.get(2)->sapad();

    Serial.print("Salpakan 1 Sapad: ");
    Serial.println(sapad1 != nullptr ? "PASS" : "FAIL");

    Serial.print("Salpakan 2 Sapad: ");
    Serial.println(sapad2 != nullptr ? "PASS" : "FAIL");

    Serial.println();
    Serial.println("[3] Execute through Sapad pointers");

    if (sapad1 != nullptr) {
        sapad1->run();
    }

    if (sapad2 != nullptr) {
        sapad2->run();
    }

    Serial.print("SensorSapad run count: ");
    Serial.println(sensorSapad.runCount());

    Serial.print("CounterSapad value: ");
    Serial.println(counterSapad.value());

    bool executed =
        sensorSapad.runCount() == 1 &&
        counterSapad.value() == 10;

    Serial.println(
        executed
            ? "[PASS] Sapad executed through Salpakan"
            : "[FAIL] Sapad execution through Salpakan"
    );

    Serial.println();
    Serial.println("[4] Verify concrete behavior");

    bool behavior =
        sensorSapad.runCount() == 1 &&
        counterSapad.value() == 10;

    Serial.println(
        behavior
            ? "[PASS] Virtual execution preserved Sapad behavior"
            : "[FAIL] Virtual execution behavior"
    );

    Serial.println();
    Serial.println("=== Experiment 22-D COMPLETE ===");
}

void loop() {
}