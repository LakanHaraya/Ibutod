#include <Arduino.h>
#include "Ubod.h"

namespace {
    constexpr unsigned int MaxUbodInstances = 8;
    unsigned int registeredIds[MaxUbodInstances] = {};
    unsigned int registeredCount = 0;
}

UbodCore::UbodCore(unsigned int id) : _id(id) {
    for (unsigned int i = 0; i < registeredCount; ++i) {
        if (registeredIds[i] == _id) {
            _idValid = false;
            return;
        }
    }

    if (registeredCount < MaxUbodInstances) {
        registeredIds[registeredCount] = _id;
        ++registeredCount;
        _idValid = true;
    }
}

unsigned int UbodCore::id() const {
    return _id;
}

bool UbodCore::isIdValid() const {
    return _idValid;
}

// Initialize the UbodCore
void UbodCore::begin() {
    if (!_idValid) { return; }

    _state = UbodState::Ready;
    _startTime = millis();
    // Initialization code here
}

// Update the state of the UbodCore
void UbodCore::update() {
    if (!_idValid) { return; }
    
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