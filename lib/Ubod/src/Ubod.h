#pragma once

// Minimal type boundary for objects attachable to an Salpakan
// Execution behavior is intentionally not defined yet.
class Sapad {
};

enum class SalpakanState {
    Initializing, 
    Ready,
    Running,
    Invalid
};

enum class SalpakanAvailability {
    Free,
    Occupied
};

class Salpakan
{
    public:
        explicit Salpakan(unsigned int id);

        void begin();
        void update();
        bool attach(Sapad* sapad);
        bool detach();
        Sapad* sapad();
        const Sapad* sapad() const;
        bool hasSapad() const;

        unsigned int id() const;
        bool isIdValid() const;
        bool setName(const char* name);
        const char* name() const;

        SalpakanAvailability availability() const;
        bool isFree() const;
        bool isOccupied() const;

        SalpakanState state() const;
        bool isReady() const;
        unsigned long uptime() const;

    private:
        friend class Salalayan;
        Salpakan();
        unsigned int _id;
        static constexpr unsigned int MaxNameLength = 15;
        char _name[MaxNameLength + 1] = {};
        bool _idValid = false;
        Sapad* _sapad = nullptr;
        SalpakanState _state = SalpakanState::Initializing;
        unsigned long _startTime = 0;
        bool isNameValid(const char* name) const;
};

class Salalayan {
    public: 
        static constexpr unsigned int Capacity = 4;
        static_assert(Capacity >= 2 && Capacity <= 32, "Ang Kapasidad ng Salalayan ay dapat nasa pagitan ng 2 at 32.");
        Salalayan();
        Salpakan* get(unsigned int id);
        const Salpakan* get(unsigned int id) const;
        bool attach(unsigned int id, Sapad* sapad);
        bool detach(unsigned int id);
        Salpakan* findFree();
        unsigned int findByName(const char* name, Salpakan** results, unsigned int maxResults);
        unsigned int findByName(const char* name, const Salpakan** results, unsigned int maxResults) const;
        unsigned int capacity() const;
        unsigned int used() const;
        unsigned int free() const;

    private:
        Salpakan _salpakan[Capacity];
};