#pragma once

#include "common.hpp"

enum class LCDMode {
    HBLANK,
    VBLANK,
    OAM,
    XFER
};

enum class StatSrc {
    HBLANK = (1 << 3),
    VBLANK = (1 << 4),
    OAM = (1 << 5),
    LYC = (1 << 6),
};

class LCD {
private:
    // Registers
    u8 lcdc;
    u8 lcds;
    u8 scroll_y;
    u8 scroll_x;
    u8 ly;
    u8 ly_compare;
    u8 dma;
    u8 bg_palette;
    u8 obj_palette[2];
    u8 win_y;
    u8 win_x;

    // Other data
    u32 bg_colors[4];
    u32 sp1_colors[4];
    u32 sp2_colors[4];

public:
    
    void init();
    u8 read(u16 address);
    void write(u16 address, u8 value);

    // Getters and Setters for LCD control register (lcdc)
    bool isBGWindowEnabled() const;
    bool isObjEnabled() const;
    int getObjHeight() const;
    u16 getBGMapArea() const;
    u16 getBGWindowDataArea() const;
    bool isWindowEnabled() const;
    u16 getWindowMapArea() const;
    bool isLCDEnabled() const;

    // Getters and Setters for LCD status register (lcds)
    LCDMode getMode() const;
    void setMode(LCDMode mode);
    bool isLYC() const;
    void setLYC(bool b);

    // Check if a specific source has triggered an interrupt
    bool isStatInterruptSet(StatSrc src) const;
    
};