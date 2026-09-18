#include <Arduino.h>
#include "Ibutod.h"

// --------------------------------------------------
// Experiment 22-F — Final Sapad Invariants
// --------------------------------------------------

class TestSapad : public Sapad {
    public:
        explicit TestSapad(unsigned int increment)
            : _increment(increment)
        {
        }

        void run() override {
            _value += _increment;
        }

        unsigned int value() const {
            return _value;
        }

    private:
        unsigned int _increment;
        unsigned int _value = 0;
};

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("=== Ibutod Experiment 22-F ===");

    Salalayan<3> salalayan("Experiment");

    TestSapad sapadA(1);
    TestSapad sapadB(10);

    // --------------------------------------------------
    // [1] Initial invariants
    // --------------------------------------------------

    Serial.println();
    Serial.println("[1] Verify initial invariants");

    bool initialState =
        salalayan.countOccupied() == 0 &&
        salalayan.countFree() == 3 &&
        salalayan.countEnabled() == 0 &&
        salalayan.countDisabled() == 3 &&
        salalayan.countOccupied() + salalayan.countFree()
            == salalayan.capacity() &&
        salalayan.countEnabled() + salalayan.countDisabled()
            == salalayan.capacity() &&
        salalayan.countEnabled() <= salalayan.countOccupied();

    Serial.println(
        initialState
            ? "[PASS] Initial invariants"
            : "[FAIL] Initial invariants"
    );

    // --------------------------------------------------
    // [2] Attach two Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[2] Attach two Sapad");

    bool attachedA = salalayan.attach(1, &sapadA);
    bool attachedB = salalayan.attach(2, &sapadB);

    Serial.print("Attach Sapad A: ");
    Serial.println(attachedA ? "PASS" : "FAIL");

    Serial.print("Attach Sapad B: ");
    Serial.println(attachedB ? "PASS" : "FAIL");

    bool afterAttach =
        salalayan.countOccupied() == 2 &&
        salalayan.countFree() == 1 &&
        salalayan.countEnabled() == 0 &&
        salalayan.countDisabled() == 3 &&
        salalayan.countOccupied() + salalayan.countFree()
            == salalayan.capacity() &&
        salalayan.countEnabled() + salalayan.countDisabled()
            == salalayan.capacity() &&
        salalayan.countEnabled() <= salalayan.countOccupied();

    Serial.println(
        afterAttach
            ? "[PASS] Occupancy and enablement invariants"
            : "[FAIL] Occupancy and enablement invariants"
    );

    // --------------------------------------------------
    // [3] Enable one occupied Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[3] Enable Salpakan 1");

    bool enabledA = salalayan.enable(1);

    Serial.print("Enable Salpakan 1: ");
    Serial.println(enabledA ? "PASS" : "FAIL");

    bool afterEnable =
        salalayan.countOccupied() == 2 &&
        salalayan.countFree() == 1 &&
        salalayan.countEnabled() == 1 &&
        salalayan.countDisabled() == 2 &&
        salalayan.countOccupied() + salalayan.countFree()
            == salalayan.capacity() &&
        salalayan.countEnabled() + salalayan.countDisabled()
            == salalayan.capacity() &&
        salalayan.countEnabled() <= salalayan.countOccupied();

    Serial.println(
        afterEnable
            ? "[PASS] Enablement invariants"
            : "[FAIL] Enablement invariants"
    );

    // --------------------------------------------------
    // [4] Reject enabling an empty Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[4] Reject enablement of empty Salpakan");

    bool enabledEmpty = salalayan.enable(3);

    Serial.print("Enable empty Salpakan: ");
    Serial.println(
        !enabledEmpty
            ? "PASS"
            : "FAIL"
    );

    bool emptyStillDisabled =
        !salalayan.get(3)->isEnabled();

    Serial.println(
        emptyStillDisabled
            ? "[PASS] Empty Salpakan remains disabled"
            : "[FAIL] Empty Salpakan became enabled"
    );

    // --------------------------------------------------
    // [5] Execute Sapad through Salpakan
    // --------------------------------------------------

    Serial.println();
    Serial.println("[5] Execute Sapad through Salpakan");

    Sapad* sapad1 = salalayan.get(1)->sapad();
    Sapad* sapad2 = salalayan.get(2)->sapad();

    if (sapad1 != nullptr) {
        sapad1->run();
    }

    if (sapad2 != nullptr) {
        sapad2->run();
    }

    Serial.print("Sapad A value: ");
    Serial.println(sapadA.value());

    Serial.print("Sapad B value: ");
    Serial.println(sapadB.value());

    bool execution =
        sapadA.value() == 1 &&
        sapadB.value() == 10;

    Serial.println(
        execution
            ? "[PASS] Sapad execution preserved"
            : "[FAIL] Sapad execution behavior"
    );

    // --------------------------------------------------
    // [6] Reject detach while enabled
    // --------------------------------------------------

    Serial.println();
    Serial.println("[6] Reject detach while enabled");

    bool detachEnabled = salalayan.detach(1);

    Serial.print("Detach enabled Salpakan: ");
    Serial.println(
        !detachEnabled
            ? "PASS"
            : "FAIL"
    );

    bool stillOccupied =
        salalayan.get(1)->isOccupied();

    bool stillEnabled =
        salalayan.get(1)->isEnabled();

    Serial.println(
        stillOccupied
            ? "[PASS] Salpakan remains occupied"
            : "[FAIL] Salpakan became free"
    );

    Serial.println(
        stillEnabled
            ? "[PASS] Salpakan remains enabled"
            : "[FAIL] Salpakan became disabled"
    );

    // --------------------------------------------------
    // [7] Disable then detach
    // --------------------------------------------------

    Serial.println();
    Serial.println("[7] Disable then detach");

    bool disabledA = salalayan.disable(1);
    bool detachedA = salalayan.detach(1);

    Serial.print("Disable Salpakan 1: ");
    Serial.println(disabledA ? "PASS" : "FAIL");

    Serial.print("Detach Sapad A: ");
    Serial.println(detachedA ? "PASS" : "FAIL");

    bool afterDetach =
        salalayan.countOccupied() == 1 &&
        salalayan.countFree() == 2 &&
        salalayan.countEnabled() == 0 &&
        salalayan.countDisabled() == 3 &&
        !salalayan.get(1)->isOccupied() &&
        !salalayan.get(1)->isEnabled();

    Serial.println(
        afterDetach
            ? "[PASS] Detach restored Free + Disabled state"
            : "[FAIL] Detach state"
    );

    // --------------------------------------------------
    // [8] Reattach Sapad A
    // --------------------------------------------------

    Serial.println();
    Serial.println("[8] Reattach Sapad A");

    bool reattachedA = salalayan.attach(1, &sapadA);

    Serial.print("Reattach Sapad A: ");
    Serial.println(reattachedA ? "PASS" : "FAIL");

    bool afterReattach =
        salalayan.get(1)->isOccupied() &&
        !salalayan.get(1)->isEnabled() &&
        salalayan.countOccupied() == 2 &&
        salalayan.countFree() == 1 &&
        salalayan.countEnabled() == 0 &&
        salalayan.countDisabled() == 3;

    Serial.println(
        afterReattach
            ? "[PASS] Reattach restored Occupied + Disabled state"
            : "[FAIL] Reattach state"
    );

    // --------------------------------------------------
    // [9] Execute reattached Sapad
    // --------------------------------------------------

    Serial.println();
    Serial.println("[9] Execute reattached Sapad");

    Sapad* reattachedSapad = salalayan.get(1)->sapad();

    if (reattachedSapad != nullptr) {
        reattachedSapad->run();
    }

    Serial.print("Sapad A value: ");
    Serial.println(sapadA.value());

    Serial.println(
        sapadA.value() == 2
            ? "[PASS] Reattached Sapad executed"
            : "[FAIL] Reattached Sapad execution"
    );

    // --------------------------------------------------
    // [10] Final invariants
    // --------------------------------------------------

    Serial.println();
    Serial.println("[10] Verify final invariants");

    bool finalInvariants =
        salalayan.countOccupied() + salalayan.countFree()
            == salalayan.capacity() &&
        salalayan.countEnabled() + salalayan.countDisabled()
            == salalayan.capacity() &&
        salalayan.countEnabled() <= salalayan.countOccupied() &&
        salalayan.get(1)->isOccupied() &&
        !salalayan.get(1)->isEnabled() &&
        salalayan.get(2)->isOccupied() &&
        !salalayan.get(2)->isEnabled() &&
        salalayan.get(3)->isFree() &&
        !salalayan.get(3)->isEnabled();

    Serial.println(
        finalInvariants
            ? "[PASS] Final invariants"
            : "[FAIL] Final invariants"
    );

    Serial.println();
    Serial.println("=== Experiment 22-F COMPLETE ===");
}

void loop() {
}