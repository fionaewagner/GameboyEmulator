#pragma once

#include "common.hpp"

class Io {
public:
    u8 read(u16 address);
    void write(u16 address, u8 value);
};