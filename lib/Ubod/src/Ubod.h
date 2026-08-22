#pragma once

enum class UbodState {
    Initializing, 
    Ready,
    Running
};
class UbodCore
{
    public:
        void begin();
        void update();

        UbodState state() const;
        bool isReady() const;
        unsigned long uptime() const;

    private:
        UbodState _state = UbodState::Initializing;
        unsigned long _startTime = 0;
};