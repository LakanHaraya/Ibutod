#pragma once

#include <cstring>

// Minimal type boundary for objects attachable to an Salpakan
// Minimal execution boundary for modular program units.
class Sapad {
    public:
        virtual ~Sapad() = default;
        virtual void run() = 0;
};

enum class SalpakanAvailability {
    Free,
    Occupied
};

enum class SalpakanEnablement {
    Disabled, 
    Enabled
};

class Salpakan
{
    public:
        explicit Salpakan(unsigned int id);

        // Attachment
        bool attach(Sapad* sapad);
        bool detach();
        Sapad* sapad();
        const Sapad* sapad() const;
        bool hasSapad() const;

        // Identity
        unsigned int id() const;
        bool isIdValid() const;

        // Naming
        bool setName(const char* name);
        const char* name() const;

        // Occupancy
        SalpakanAvailability availability() const;
        bool isFree() const;
        bool isOccupied() const;

        // Enablement
        bool enable();
        bool disable();
        bool isEnabled() const;

    private:
        template <unsigned int>
        friend class Salalayan;
        Salpakan();
        unsigned int _id;
        static constexpr unsigned int MaxNameLength = 15;
        char _name[MaxNameLength + 1] = {};
        bool _idValid = false;
        Sapad* _sapad = nullptr;
        SalpakanEnablement _enablement = SalpakanEnablement::Disabled;
        bool isNameValid(const char* name) const;
};

template <unsigned int Capacity>
class Salalayan {
    public: 
        static_assert(
            Capacity >= 1 && Capacity <= 32,
            "Ang Kapasidad ng Salalayan ay dapat nasa pagitan ng 1 at 32."
        );
        explicit Salalayan(const char* name = nullptr);
        bool setName(const char* name);
        const char* name() const;
        Salpakan* get(unsigned int id);
        const Salpakan* get(unsigned int id) const;
        bool attach(unsigned int id, Sapad* sapad);
        bool detach(unsigned int id);
        bool enable(unsigned int id);
        bool disable(unsigned int id);
        Salpakan* findFree();
        unsigned int findByName(const char* name, Salpakan** results, unsigned int maxResults);
        unsigned int findByName(const char* name, const Salpakan** results, unsigned int maxResults) const;
        unsigned int capacity() const;
        unsigned int countOccupied() const;
        unsigned int countFree() const;
        unsigned int countEnabled() const;
        unsigned int countDisabled() const;
        bool isEmpty() const;
        bool isFull() const;

    private:
        static constexpr unsigned int MaxNameLength = 15;
        char _name[MaxNameLength + 1] = {};
        Salpakan _salpakan[Capacity];
        bool isNameValid(const char* name) const;
};

#include "Salalayan.tpp"