#pragma once

#include "common.hpp"
#include "ppu.hpp"
#include "bus.hpp"

class DMA {
public:
    DMA() : isActive(false), dmaByte(0), dmaValue(0), startDelay(0) {}

    void start(u8 start);

    void tick();

    bool isTransferring() const;

private:
    bool isActive;
    u8 dmaByte;
    u8 dmaValue;
    u8 startDelay;
};
