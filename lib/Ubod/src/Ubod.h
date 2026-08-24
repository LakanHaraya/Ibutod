#pragma once

enum class UbodSlotState {
    Initializing, 
    Ready,
    Running,
    Released,
    Invalid
};

enum class UbodSlotAvailability {
    Free,
    Occupied
};

class UbodSlot
{
    public:
        explicit UbodSlot(unsigned int id);

        void begin();
        void update();
        void release();

        unsigned int slotId() const;
        bool isSlotIdValid() const;
        bool setSlotName(const char* name);
        const char* slotName() const;

        bool occupy();
        bool free();
        UbodSlotAvailability availability() const;
        bool isFree() const;
        bool isOccupied() const;

        UbodSlotState state() const;
        bool isReady() const;
        unsigned long uptime() const;

    private:
        friend class UbodContainer;
        UbodSlot();
        unsigned int _slotId;
        static constexpr unsigned int MaxSlotNameLength = 15;
        char _slotName[MaxSlotNameLength + 1] = {};
        bool _idValid = false;
        UbodSlotAvailability _availability = UbodSlotAvailability::Free;
        UbodSlotState _state = UbodSlotState::Initializing;
        unsigned long _startTime = 0;
        unsigned long _finalUptime = 0;
        bool isSlotNameValid(const char* name) const;
};

class UbodContainer {
    public: 
        static constexpr unsigned int Capacity = 4;
        static_assert(Capacity >= 2 && Capacity <= 32, "UbodContainer Capacity must be between 2 and 32.");
        UbodContainer();
        UbodSlot* get(unsigned int id);
        const UbodSlot* get(unsigned int id) const;
        bool occupy(unsigned int id);
        bool free(unsigned int id);
        UbodSlot* findFree();
        unsigned int findBySlotName(const char* name, UbodSlot** results, unsigned int maxResults);
        unsigned int findBySlotName(const char* name, const UbodSlot** results, unsigned int maxResults) const;
        unsigned int capacity() const;
        unsigned int used() const;
        unsigned int free() const;

    private:
        UbodSlot _slots[Capacity];
};