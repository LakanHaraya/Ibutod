#include <Arduino.h>
#include "Ubod.h"
#include <cstring>

UbodSlot::UbodSlot()
    : _slotId(0),
      _idValid(false),
      _state(UbodSlotState::Invalid),
      _startTime(0)
{
    // Default constructor is private to prevent
    // creating UbodSlot without a valid Slot ID.
}

UbodSlot::UbodSlot(unsigned int id)
    : _slotId(id)
{
    _idValid = (_slotId > 0);
    if (!_idValid) {
        _state = UbodSlotState::Invalid;
    }
}

unsigned int UbodSlot::slotId() const {
    return _slotId;
}

bool UbodSlot::isSlotIdValid() const {
    return _idValid;
}

bool UbodSlot::isSlotNameValid(const char* name) const {
    if (name == nullptr || name[0] == '\0') {
        return false;
    }
    unsigned int i = 0;
    bool hasNonWhiteSpace = false;
    while (
        name[i] != '\0' &&
        i < MaxSlotNameLength
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

bool UbodSlot::setSlotName(const char* name) {
    if (!_idValid) {
        return false;
    }
    if (!isSlotNameValid(name)) {
        return false;
    }
    unsigned int i = 0;
    while (
        name[i] != '\0' &&
        i < MaxSlotNameLength
    ) {
        ++i;
    }
    if (name[i] != '\0') {
        return false;
    }
    for (unsigned int j = 0; j < i; ++j) {
        _slotName[j] = name[j];
    }
    _slotName[i] = '\0';
    return true;
}

const char* UbodSlot::slotName() const {
    return _slotName;
}

// --------------------------------------------------
// Attachment
// --------------------------------------------------

bool UbodSlot::attach() {
    if (!_idValid) {
        return false;
    }
    if (_availability == UbodSlotAvailability::Occupied) {
        return false;
    }
    _availability = UbodSlotAvailability::Occupied;
    return true;
}

bool UbodSlot::detach() {
    if (!_idValid) {
        return false;
    }
    if (_availability == UbodSlotAvailability::Free) {
        return false;
    }
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

// --------------------------------------------------
// Lifecycle
// --------------------------------------------------

void UbodSlot::begin() {
    if (!_idValid) {
        return;
    }
    _state = UbodSlotState::Ready;
    _startTime = millis();
}

void UbodSlot::update() {
    if (!_idValid) {
        return;
    }
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
    return millis() - _startTime;
}

// --------------------------------------------------
// Container
// --------------------------------------------------

UbodContainer::UbodContainer() {
    for (unsigned int i = 0; i < Capacity; ++i) {
        _slots[i] = UbodSlot(i + 1);
    }
}

UbodSlot* UbodContainer::get(unsigned int id) {
    if (id == 0 || id > Capacity) {
        return nullptr;
    }
    return &_slots[id - 1];
}

const UbodSlot* UbodContainer::get(unsigned int id) const {
    if (id == 0 || id > Capacity) {
        return nullptr;
    }
    return &_slots[id - 1];
}

bool UbodContainer::attach(unsigned int id) {
    UbodSlot* slot = get(id);
    if (slot == nullptr) {
        return false;
    }
    return slot->attach();
}

bool UbodContainer::detach(unsigned int id) {
    UbodSlot* slot = get(id);
    if (slot == nullptr) {
        return false;
    }
    return slot->detach();
}

UbodSlot* UbodContainer::findFree() {
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_slots[i].isFree()) {
            return &_slots[i];
        }
    }
    return nullptr;
}

unsigned int UbodContainer::findBySlotName(
    const char* name,
    UbodSlot** results,
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
        if (strcmp(_slots[i].slotName(), name) == 0) {
            if (foundCount >= maxResults) {
                break;
            }
            results[foundCount] = &_slots[i];
            ++foundCount;
        }
    }
    return foundCount;
}

unsigned int UbodContainer::findBySlotName(
    const char* name,
    const UbodSlot** results,
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
        if (strcmp(_slots[i].slotName(), name) == 0) {

            if (foundCount >= maxResults) {
                break;
            }
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
        if (_slots[i].isOccupied()) {
            ++count;
        }
    }
    return count;
}

unsigned int UbodContainer::free() const {
    return Capacity - used();
}