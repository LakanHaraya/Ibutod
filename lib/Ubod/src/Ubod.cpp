#include <Arduino.h>
#include "Ubod.h"

// Initialize the UbodCore
void UbodCore::begin() {
    _state = UbodState::Ready;
    _startTime = millis();
    // Initialization code here
}

// Update the state of the UbodCore
void UbodCore::update() {
    if (_state == UbodState::Ready) {
        _state = UbodState::Running;
    }
}

// Get the current state of the UbodCore
UbodState UbodCore::state() const {
    return _state;
}

// Check if the UbodCore is ready
bool UbodCore::isReady() const {
    return _state == UbodState::Ready;
}

// Get the uptime of the UbodCore in milliseconds
unsigned long UbodCore::uptime() const {
    return millis() - _startTime;
}