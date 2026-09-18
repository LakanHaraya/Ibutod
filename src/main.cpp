#include <Arduino.h>
#include "Ibutod.h"

// --------------------------------------------------
// Experiment 22-C — Multiple Sapad Types
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
    Serial.println("=== Ibutod Experiment 22-C ===");

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
    Serial.println("[2] Enable both Salpakan");

    bool enabledSensor = salalayan.enable(1);
    bool enabledCounter = salalayan.enable(2);

    Serial.print("Enable Salpakan 1: ");
    Serial.println(enabledSensor ? "PASS" : "FAIL");

    Serial.print("Enable Salpakan 2: ");
    Serial.println(enabledCounter ? "PASS" : "FAIL");

    Serial.println();
    Serial.println("[3] Execute SensorSapad");

    sensorSapad.run();

    Serial.print("SensorSapad run count: ");
    Serial.println(sensorSapad.runCount());

    Serial.println(
        sensorSapad.runCount() == 1
            ? "[PASS] SensorSapad executed"
            : "[FAIL] SensorSapad execution"
    );

    Serial.println();
    Serial.println("[4] Execute CounterSapad");

    counterSapad.run();

    Serial.print("CounterSapad value: ");
    Serial.println(counterSapad.value());

    Serial.println(
        counterSapad.value() == 10
            ? "[PASS] CounterSapad executed"
            : "[FAIL] CounterSapad execution"
    );

    Serial.println();
    Serial.println("[5] Verify independent behavior");

    bool independent =
        sensorSapad.runCount() == 1 &&
        counterSapad.value() == 10;

    Serial.print("SensorSapad run count: ");
    Serial.println(sensorSapad.runCount());

    Serial.print("CounterSapad value: ");
    Serial.println(counterSapad.value());

    Serial.println(
        independent
            ? "[PASS] Sapad types retain independent behavior"
            : "[FAIL] Sapad type behavior"
    );

    Serial.println();
    Serial.println("=== Experiment 22-C COMPLETE ===");
}

void loop() {
}