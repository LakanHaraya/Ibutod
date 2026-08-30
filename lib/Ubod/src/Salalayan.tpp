// --------------------------------------------------
// Salalayan Template Implementation
// --------------------------------------------------

template <unsigned int Capacity>
bool Salalayan<Capacity>::isNameValid(const char* name) const {
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
        ) { hasNonWhiteSpace = true; }
        ++i;
    }
    return name[i] == '\0' && hasNonWhiteSpace;
}

template <unsigned int Capacity>
bool Salalayan<Capacity>::setName(const char* name) {
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

template <unsigned int Capacity>
const char* Salalayan<Capacity>::name() const { return _name; }

template <unsigned int Capacity>
Salalayan<Capacity>::Salalayan(const char* name) {
    if (name != nullptr) { setName(name); }
    for (unsigned int i = 0; i < Capacity; ++i) { _salpakan[i] = Salpakan(i + 1); }
}

template <unsigned int Capacity>
Salpakan* Salalayan<Capacity>::get(unsigned int id) {
    if (id == 0 || id > Capacity) { return nullptr; }
    return &_salpakan[id - 1];
}

template <unsigned int Capacity>
const Salpakan* Salalayan<Capacity>::get(unsigned int id) const {
    if (id == 0 || id > Capacity) { return nullptr; }
    return &_salpakan[id - 1];
}

template <unsigned int Capacity>
bool Salalayan<Capacity>::attach(unsigned int id, Sapad* sapad) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false;}
    return salpakan->attach(sapad);
}

template <unsigned int Capacity>
bool Salalayan<Capacity>::detach(unsigned int id) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false; }
    return salpakan->detach();
}

template <unsigned int Capacity>
bool Salalayan<Capacity>::enable(unsigned int id) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false; }
    return salpakan->enable();
}

template <unsigned int Capacity>
bool Salalayan<Capacity>::disable(unsigned int id) {
    Salpakan* salpakan = get(id);
    if (salpakan == nullptr) { return false; }
    return salpakan->disable();
}

template <unsigned int Capacity>
Salpakan* Salalayan<Capacity>::findFree() {
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_salpakan[i].isFree()) { return &_salpakan[i]; }
    }
    return nullptr;
}

template <unsigned int Capacity>
unsigned int Salalayan<Capacity>::findByName(const char* name, Salpakan** results, unsigned int maxResults) {
    if (name == nullptr || results == nullptr || maxResults == 0) { return 0;}
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

template <unsigned int Capacity>
unsigned int Salalayan<Capacity>::findByName(const char* name, const Salpakan** results, unsigned int maxResults) const {
    if (name == nullptr || results == nullptr || maxResults == 0) { return 0; }
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

template <unsigned int Capacity>
unsigned int Salalayan<Capacity>::capacity() const { return Capacity; }

template <unsigned int Capacity>
unsigned int Salalayan<Capacity>::used() const {
    unsigned int count = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_salpakan[i].isOccupied()) { ++count; }
    }
    return count;
}

template <unsigned int Capacity>
unsigned int Salalayan<Capacity>::free() const { return Capacity - used(); }

template <unsigned int Capacity>
unsigned int Salalayan<Capacity>::enabled() const {
    unsigned int count = 0;
    for (unsigned int i = 0; i < Capacity; ++i) {
        if (_salpakan[i].isEnabled()) { ++count; }
    }
    return count;
}

template <unsigned int Capacity>
unsigned int Salalayan<Capacity>::disabled() const { return Capacity - enabled(); }

template <unsigned int Capacity>
bool Salalayan<Capacity>::isEmpty() const { return used() == 0; }

template <unsigned int Capacity>
bool Salalayan<Capacity>::isFull() const { return used() == Capacity; }