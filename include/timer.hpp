#pragma once

#include "common.hpp"

class Timer {
private:
    u16 div;
    u8 tima;
    u8 tma;
    u8 tac;
public:
    void init();
    void tick();

    void write(u16 address, u8 value);
    u8 read(u16 address);

    // Getters
    u16 getDiv() const;
    u8 getTima() const;
    u8 getTma() const;
    u8 getTac() const;

    // Setters
    void setDiv(u16 value);
    void setTima(u8 value);
    void setTma(u8 value);
    void setTac(u8 value);

};