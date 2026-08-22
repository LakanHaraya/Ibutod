#pragma once

enum class UbodState {
    Initializing, 
    Ready,
    Running
};
class UbodCore
{
    public:
        explicit UbodCore(unsigned int id);

        void begin();
        void update();

        unsigned int id() const;
        bool isIdValid() const;
        UbodState state() const;
        bool isReady() const;
        unsigned long uptime() const;

    private:
        unsigned int _id;
        bool _idValid = false;
        UbodState _state = UbodState::Initializing;
        unsigned long _startTime = 0;
};