#include <Arduino.h>
#include "Ubod.h"
#include <cstring>

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

// --------------------------------------------------
// Salalayan
// --------------------------------------------------

bool Salalayan::isNameValid(const char* name) const {
    if (name == nullptr || name[0] == '\0') { return false; }
    unsigned int i = 0;
    bool hasNonWhiteSpace = false;
    while (name[i] != '\0' && i < MaxNameLength) {
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

bool Salalayan::setName(const char* name) {
    if (name == nullptr) {
        _name[0] = '\0';
        return true;
    }
    if (!isNameValid(name)) { return false; }
    unsigned int i = 0; 
    while (
        name[i] != '\0' &&
        i < MaxNameLength
    ) { ++i; }
    if (name[i] != '\0') { return false; }
    for (unsigned int j = 0; j < i; ++j) { _name[j] = name[j]; }
    _name[i] = '\0'; 
    return true;
}

const char* Salalayan::name() const { return _name; }

Salalayan::Salalayan(const char* name) {
    if (name != nullptr) { setName(name); }
    for (unsigned int i = 0; i < Capacity; ++i) {
        _salpakan[i] = Salpakan(i + 1);
    }
}

Salpakan* Salalayan::get(unsigned int id) {
    if (id == 0 || id > Capacity) { return nullptr; }
    return &_salpakan[id - 1];
}

const Salpakan* Salalayan::get(unsigned int id) const {
    if (id == 0 || id > Capacity) { return nullptr; }
    return &_salpakan[id - 1];
}

bool Salalayan::attach(unsigned int id, Sapad* sapad) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false; }
    return salpakan->attach(sapad);
}

bool Salalayan::detach(unsigned int id) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false; }
    return salpakan->detach();
}

bool Salalayan::enable(unsigned int id) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false; }
    return salpakan->enable();
}

bool Salalayan::disable(unsigned int id) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false; }
    return salpakan->disable();
}

Salpakan* Salalayan::findFree() {
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_salpakan[i].isFree()) { return &_salpakan[i]; }
    }
    return nullptr;
}

unsigned int Salalayan::findByName(
    const char* name,
    Salpakan** results,
    unsigned int maxResults
) {
    if (
        name == nullptr ||
        results == nullptr ||
        maxResults == 0
    ) {
        return 0;
    }
    unsigned int foundCount = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (strcmp(_salpakan[i].name(), name) == 0) {
            if (foundCount >= maxResults) { break; }
            results[foundCount] = &_salpakan[i];
            ++foundCount;
        }
    }
    return foundCount;
}

unsigned int Salalayan::findByName(
    const char* name,
    const Salpakan** results,
    unsigned int maxResults
) const {
    if (
        name == nullptr ||
        results == nullptr ||
        maxResults == 0
    ) {
        return 0;
    }
    unsigned int foundCount = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (strcmp(_salpakan[i].name(), name) == 0) {
            if (foundCount >= maxResults) { break; }
            results[foundCount] = &_salpakan[i];
            ++foundCount;
        }
    }
    return foundCount;
}

unsigned int Salalayan::capacity() const {
    return Capacity;
}

unsigned int Salalayan::used() const {
    unsigned int count = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_salpakan[i].isOccupied()) { ++count; }
    }
    return count;
}

unsigned int Salalayan::free() const {
    return Capacity - used();
}