#include <Arduino.h>
#include "Ubod.h"

namespace {
    constexpr unsigned int MaxUbodInstances = 8;
    unsigned int registeredIds[MaxUbodInstances] = {};
    unsigned int registeredCount = 0;

    void unregisterId(unsigned int id) {
        for (unsigned int i = 0; i < registeredCount; ++i) {
            if (registeredIds[i] == id) {
                registeredIds[i] = registeredIds[registeredCount - 1];
                --registeredCount;
                return;
            }
        }
    }
}

UbodCore::UbodCore(unsigned int id) : _id(id) {
    for (unsigned int i = 0; i < registeredCount; ++i) {
        if (registeredIds[i] == _id) {
            _idValid = false;
            _state = UbodState::Invalid;
            return;
        }
    }

    if (registeredCount < MaxUbodInstances) {
        registeredIds[registeredCount] = _id;
        ++registeredCount;
        _idValid = true;
    }
}

void UbodCore::release() {
    if (!_idValid) { return; }

    _finalUptime = millis() - _startTime;
    unregisterId(_id);
    _idValid = false;
    _state = UbodState::Released;
}

unsigned int UbodCore::id() const {
    return _id;
}

bool UbodCore::isIdValid() const {
    return _idValid;
}

bool UbodCore::isNameValid(const char* name) const {
    if (name == nullptr || name[0] == '\0') { return false; }
    unsigned int i = 0;
    bool hasNonWhiteSpace = false;
    while (name[i] != '\0' && i < MaxNameLength) {
        if (name[i] != ' ' && 
            name[i] != '\t' &&
            name[i] != '\n' &&
            name[i] != '\r') {
                hasNonWhiteSpace = true;
        }
        ++i;
    }
    return name[i] == '\0' && hasNonWhiteSpace;
}

bool UbodCore::setName(const char* name) {
    if (!_idValid || _state == UbodState::Released) { return false; }
    if (!isNameValid(name)) { return false; }
    unsigned int i = 0;
    while (name[i] != '\0' && i < MaxNameLength) { ++i; }
    if (name[i] != '\0') { return false; }
    for (unsigned int j = 0; j < i; ++j) { _name[j] = name[j]; }
    _name[i] = '\0';
    return true;
}

const char* UbodCore::name() const {
    return _name;
}

bool UbodCore::occupy() {
    if (!_idValid || _state == UbodState::Released) { return false; }
    if (_availability == UbodAvailability::Occupied) { return false; }
    _availability = UbodAvailability::Occupied;
    return true;
}

bool UbodCore::free() {
    if (!_idValid || _state == UbodState::Released) { return false; }
    if (_availability == UbodAvailability::Free) { return false; }
    _availability = UbodAvailability::Free;
    return true;
}

UbodAvailability UbodCore::availability() const {
    return _availability;
}

bool UbodCore::isFree() const {
    return _availability == UbodAvailability::Free;
}

bool UbodCore::isOccupied() const {
    return _availability == UbodAvailability::Occupied;
}

void UbodCore::begin() {
    if (!_idValid || _state == UbodState::Released) { return; }

    _state = UbodState::Ready;
    _startTime = millis();
}

// Update the state of the UbodCore
void UbodCore::update() {
    if (!_idValid || _state == UbodState::Released) { return; }

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

// Get the uptime of the UbodCore
unsigned long UbodCore::uptime() const {
    if (_state == UbodState::Released) {
        return _finalUptime;
    }

    return millis() - _startTime;
}