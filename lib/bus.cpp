#include <cstdint>
#include "../include/common.hpp"
#include "../include/bus.hpp"
#include "../include/cart.hpp"
#include "../include/ppu.hpp"
#include "../include/ram.hpp"
#include "../include/dma.hpp"
#include "../include/cpu.hpp"

// Implementation of the read function
u8 Bus::busRead(u16 address) {
    if (address < 0x8000) {
        // ROM Data
        return cart.cartRead(address);
    } else if (address < 0xA000) {
        // Char/Map Data
        return ppu.vramRead(address);
    } else if (address < 0xC000) {
        // Cartridge RAM
        return cart.cartRead(address);
    } else if (address < 0xE000) {
        // WRAM (Working RAM)
        return ram.wramRead(address);
    } else if (address < 0xFE00) {
        // Reserved Echo RAM
        return 0;
    } else if (address < 0xFEA0) {
        // OAM
        if (dma.getIsTransfering()) {
            return 0xFF;
        }
        return ppu.oamRead(address);
    } else if (address < 0xFF00) {
        // Unusable Reserved
        return 0;
    } else if (address < 0xFF80) {
        // IO Registers...
        return io.read(address);
    } else if (address == 0xFFFF) {
        // CPU ENABLE REGISTER...
        return cpu.getIERegister();
    }

    // NO_IMPL
    return ram.hramRead(address);
}

// Implementation of the write function
void Bus::busWrite(u16 address, u8 value) {
    if (address < 0x8000) {
        // ROM Data
        cart.cartWrite(address, value);
    } else if (address < 0xA000) {
        // Char/Map Data
        ppu.vramWrite(address, value);
    } else if (address < 0xC000) {
        // EXT-RAM
        cart.cartWrite(address, value);
    } else if (address < 0xE000) {
        // WRAM
        ram.wramWrite(address, value);
    } else if (address < 0xFE00) {
        // Reserved Echo RAM
    } else if (address < 0xFEA0) {
        // OAM
        if (dma.getIsTransfering()) {
            return;
        }
        ppu.oamWrite(address, value);
    } else if (address < 0xFF00) {
        // Unusable Reserved
    } else if (address < 0xFF80) {
        // IO Registers...
        io.write(address, value);
    } else if (address == 0xFFFF) {
        // CPU SET ENABLE REGISTER
        cpu.setIERegister(value);
    } else {
        ram.hramWrite(address, value);
    }
}

// Implementation of the read16 function
u16 Bus::read16(u16 address) {
    u16 lo = busRead(address);
    u16 hi = busRead(address + 1);
    return lo | (hi << 8);
}

// Implementation of the write16 function
void Bus::write16(u16 address, u16 value) {
    busWrite(address, value & 0xFF);
    busWrite(address + 1, value >> 8);
}