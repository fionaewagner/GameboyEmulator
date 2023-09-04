#pragma once

#include "common.hpp"
#include "cart.hpp"
#include "ram.hpp"
#include "dma.hpp"
#include "cpu.hpp"
#include "io.hpp"
#include "ppu.hpp"

class Bus {
public:
    u8 busRead(u16 address);
    void busWrite(u16 address, u8 value);

    u16 read16(u16 address);
    void write16(u16 address, u16 value);

    Cartridge cart;
    PPU ppu;
    Ram ram;
    Dma dma;
    Io io;
    CPU cpu;

};