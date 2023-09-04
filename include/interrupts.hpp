#pragma once

#include "cpu.hpp"

enum class InterruptType {
    VBLANK = 1,
    LCD_STAT = 2,
    TIMER = 4,
    SERIAL = 8,
    JOYPAD = 16
};

