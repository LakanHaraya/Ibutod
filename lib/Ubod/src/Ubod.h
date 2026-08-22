#pragma once

enum class UbodState {
    Initializing, 
    Ready,
    Running,
    Released,
    Invalid
};
class UbodCore
{
    public:
        explicit UbodCore(unsigned int id);

        void begin();
        void update();
        void release();

        unsigned int id() const;
        bool isIdValid() const;
        bool setName(const char* name);
        const char* name() const;
        UbodState state() const;
        bool isReady() const;
        unsigned long uptime() const;

    private:
        unsigned int _id;
        static constexpr unsigned int MaxNameLength = 15;
        char _name[MaxNameLength + 1] = {};
        bool _idValid = false;
        UbodState _state = UbodState::Initializing;
        unsigned long _startTime = 0;
        unsigned long _finalUptime = 0;

        bool isNameValid(const char* name) const;
};