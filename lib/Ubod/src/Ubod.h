#pragma once

// Minimal type boundary for objects attachable to an UbodSlot
// Execution behavior is intentionally not defined yet.
class UbodEngine {
};

enum class UbodSlotState {
    Initializing, 
    Ready,
    Running,
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
        bool attach(UbodEngine* engine);
        bool detach();
        UbodEngine* engine();
        const UbodEngine* engine() const;
        bool hasEngine() const;

        unsigned int slotId() const;
        bool isSlotIdValid() const;
        bool setSlotName(const char* name);
        const char* slotName() const;

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
        UbodEngine* _engine = nullptr;
        UbodSlotState _state = UbodSlotState::Initializing;
        unsigned long _startTime = 0;
        bool isSlotNameValid(const char* name) const;
};

class UbodContainer {
    public: 
        static constexpr unsigned int Capacity = 4;
        static_assert(Capacity >= 2 && Capacity <= 32, "UbodContainer Capacity must be between 2 and 32.");
        UbodContainer();
        UbodSlot* get(unsigned int id);
        const UbodSlot* get(unsigned int id) const;
        bool attach(unsigned int id, UbodEngine* engine);
        bool detach(unsigned int id);
        UbodSlot* findFree();
        unsigned int findBySlotName(const char* name, UbodSlot** results, unsigned int maxResults);
        unsigned int findBySlotName(const char* name, const UbodSlot** results, unsigned int maxResults) const;
        unsigned int capacity() const;
        unsigned int used() const;
        unsigned int free() const;

    private:
        UbodSlot _slots[Capacity];
};