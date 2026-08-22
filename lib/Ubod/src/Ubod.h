#pragma once

class UbodCore
{
    public:
        void begin();
        void update();

        bool isReady() const;
        unsigned long uptime() const;
};