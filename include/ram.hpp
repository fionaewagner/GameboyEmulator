#pragma once

#include "common.hpp"

class Ram {
public:
    u8 wramRead(u16 address);
    void wramWrite(u16 address, u8 value);

    u8 hramRead(u16 address);
    void hramWrite(u16 address, u8 value);

private: 
    u8 wram[0x2000];
    u8 hram[0x80];
};