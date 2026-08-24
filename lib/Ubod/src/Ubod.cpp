#include <Arduino.h>
#include "Ubod.h"
#include <cstring>

UbodSlot::UbodSlot() : 
    _slotId(0), 
    _idValid(false), 
    _state(UbodSlotState::Invalid), 
    _startTime(0), 
    _finalUptime(0) { 
        // Default constructor is private to prevent creating UbodCore without a valid ID
    }

UbodSlot::UbodSlot(unsigned int id) : _slotId(id) {
    _idValid = (_slotId > 0);
    if (!_idValid) { _state = UbodSlotState::Invalid; }
}

void UbodSlot::release() {
    if (!_idValid) { return; }
    _finalUptime = millis() - _startTime;
    _idValid = false;
    _state = UbodSlotState::Released;
}

unsigned int UbodSlot::slotId() const {
    return _slotId;
}

bool UbodSlot::isSlotIdValid() const {
    return _idValid;
}

bool UbodSlot::isSlotNameValid(const char* name) const {
    if (name == nullptr || name[0] == '\0') { return false; }
    unsigned int i = 0;
    bool hasNonWhiteSpace = false;
    while (name[i] != '\0' && i < MaxSlotNameLength) {
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

bool UbodSlot::setSlotName(const char* name) {
    if (!_idValid || _state == UbodSlotState::Released) { return false; }
    if (!isSlotNameValid(name)) { return false; }
    unsigned int i = 0;
    while (name[i] != '\0' && i < MaxSlotNameLength) { ++i; }
    if (name[i] != '\0') { return false; }
    for (unsigned int j = 0; j < i; ++j) { _slotName[j] = name[j]; }
    _slotName[i] = '\0';
    return true;
}

const char* UbodSlot::slotName() const {
    return _slotName;
}

bool UbodSlot::occupy() {
    if (!_idValid || _state == UbodSlotState::Released) { return false; }
    if (_availability == UbodSlotAvailability::Occupied) { return false; }
    _availability = UbodSlotAvailability::Occupied;
    return true;
}

bool UbodSlot::free() {
    if (!_idValid || _state == UbodSlotState::Released) { return false; }
    if (_availability == UbodSlotAvailability::Free) { return false; }
    _availability = UbodSlotAvailability::Free;
    return true;
}

UbodSlotAvailability UbodSlot::availability() const {
    return _availability;
}

bool UbodSlot::isFree() const {
    return _availability == UbodSlotAvailability::Free;
}

bool UbodSlot::isOccupied() const {
    return _availability == UbodSlotAvailability::Occupied;
}

void UbodSlot::begin() {
    if (!_idValid || _state == UbodSlotState::Released) { return; }

    _state = UbodSlotState::Ready;
    _startTime = millis();
}

// Update the state of the UbodCore
void UbodSlot::update() {
    if (!_idValid || _state == UbodSlotState::Released) { return; }

    if (_state == UbodSlotState::Ready) {
        _state = UbodSlotState::Running;
    }
}

UbodSlotState UbodSlot::state() const {
    return _state;
}

bool UbodSlot::isReady() const {
    return _state == UbodSlotState::Ready;
}

unsigned long UbodSlot::uptime() const {
    if (_state == UbodSlotState::Released) {
        return _finalUptime;
    }

    return millis() - _startTime;
}

UbodContainer::UbodContainer() {
    for (unsigned int i = 0; i < Capacity; ++i) {
        _slots[i] = UbodSlot(i + 1);
    }
}

UbodSlot* UbodContainer::get(unsigned int id) {
    if (id == 0 || id > Capacity) { return nullptr; }
    return &_slots[id - 1];
}

const UbodSlot* UbodContainer::get(unsigned int id) const {
    if (id == 0 || id > Capacity) { return nullptr; }
    return &_slots[id - 1];
}

bool UbodContainer::occupy(unsigned int id) {
    UbodSlot* core = get(id);
    if (core == nullptr) { return false; }
    return core->occupy();
}

bool UbodContainer::free(unsigned int id) {
    UbodSlot* core = get(id);
    if (core == nullptr) { return false; }
    return core->free();
}

UbodSlot* UbodContainer::findFree() {
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_slots[i].isFree()) { return &_slots[i]; }
    }
    return nullptr;
}

unsigned int UbodContainer::findBySlotName(const char* name, UbodSlot** results, unsigned int maxResults) {
    if (name == nullptr || results == nullptr || maxResults == 0) { return 0; }
    unsigned int foundCount = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (strcmp(_slots[i].slotName(), name) == 0) {
            if (foundCount >= maxResults) { break; }
            results[foundCount] = &_slots[i];
            ++foundCount;
        }
    }
    return foundCount;
}

unsigned int UbodContainer::findBySlotName(const char* name, const UbodSlot** results, unsigned int maxResults) const {
    if (name == nullptr || results == nullptr || maxResults == 0) { return 0; }
    unsigned int foundCount = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (strcmp(_slots[i].slotName(), name) == 0) {
            if (foundCount >= maxResults) { break; }
            results[foundCount] = &_slots[i];
            ++foundCount;
        }
    }
    return foundCount;
}

unsigned int UbodContainer::capacity() const {
    return Capacity;
}

unsigned int UbodContainer::used() const {
    unsigned int count = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_slots[i].isOccupied()) { ++count; }
    }
    return count;
}

unsigned int UbodContainer::free() const {
    return Capacity - used();
}