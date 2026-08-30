#include <Arduino.h>
#include "Ibutod.h"

Salpakan::Salpakan()
    : _id(0),
      _idValid(false),
      _state(SalpakanState::Invalid),
      _startTime(0)
{
    // Default constructor is private to prevent
    // creating Salpakan without a valid Salpakan ID.
}

Salpakan::Salpakan(unsigned int id)
    : _id(id)
{
    _idValid = (_id > 0);
    if (!_idValid) { _state = SalpakanState::Invalid; }
}

unsigned int Salpakan::id() const { return _id; }

bool Salpakan::isIdValid() const { return _idValid; }

bool Salpakan::isNameValid(const char* name) const {
    if (name == nullptr || name[0] == '\0') { return false; }
    unsigned int i = 0;
    bool hasNonWhiteSpace = false;
    while (
        name[i] != '\0' &&
        i < MaxNameLength
    ) {
        if (
            name[i] != ' ' &&
            name[i] != '\t' &&
            name[i] != '\n' &&
            name[i] != '\r'
        ) {
            hasNonWhiteSpace = true;
        }
        ++i;
    }
    return name[i] == '\0' && hasNonWhiteSpace;
}

bool Salpakan::setName(const char* name) {
    if (!_idValid) { return false; }
    if (!isNameValid(name)) { return false; }
    unsigned int i = 0;
    while (
        name[i] != '\0' &&
        i < MaxNameLength
    ) {
        ++i;
    }
    if (name[i] != '\0') { return false; }
    for (unsigned int j = 0; j < i; ++j) {
        _name[j] = name[j];
    }
    _name[i] = '\0';
    return true;
}

const char* Salpakan::name() const { return _name; }

// --------------------------------------------------
// Pagkabit
// --------------------------------------------------

bool Salpakan::attach(Sapad* sapad) {
    if (!_idValid) { return false; }
    if (sapad == nullptr) { return false; }
    if (_sapad != nullptr) { return false; }
    _sapad = sapad;
    return true;
}

bool Salpakan::detach() {
    if (!_idValid) { return false; }
    if (_sapad == nullptr) { return false; }
    if (isEnabled()) { return false; }
    _sapad = nullptr;
    return true;
}

Sapad* Salpakan::sapad() { return _sapad; }

const Sapad* Salpakan::sapad() const { return _sapad; }

bool Salpakan::hasSapad() const { return _sapad != nullptr; }

SalpakanAvailability Salpakan::availability() const {
    return _sapad != nullptr ? SalpakanAvailability::Occupied : SalpakanAvailability::Free;
}

bool Salpakan::isFree() const { return _sapad == nullptr; }

bool Salpakan::isOccupied() const { return _sapad != nullptr; }

// --------------------------------------------------
// Enablement
// --------------------------------------------------

bool Salpakan::enable() {
    if (!_idValid) { return false; }
    if (_sapad == nullptr) { return false; }
    if (isEnabled()) { return false; }
    _enablement = SalpakanEnablement::Enabled;
    return true;
}

bool Salpakan::disable() {
    if (!_idValid) { return false; }
    if (!isEnabled()) { return false; }
    _enablement = SalpakanEnablement::Disabled;
    return true;
}

bool Salpakan::isEnabled() const { return _enablement == SalpakanEnablement::Enabled; }

// --------------------------------------------------
// Ikot-Buhay
// --------------------------------------------------

void Salpakan::begin() {
    if (!_idValid) { return; }
    _state = SalpakanState::Ready;
    _startTime = millis();
}

void Salpakan::update() {
    if (!_idValid) { return; }
    if (_state == SalpakanState::Ready) {
        _state = SalpakanState::Running;
    }
}

SalpakanState Salpakan::state() const { return _state; }

bool Salpakan::isReady() const { return _state == SalpakanState::Ready; }

unsigned long Salpakan::uptime() const { return millis() - _startTime; }
