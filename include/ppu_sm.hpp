#pragma once

#include "common.hpp"

enum class PPUMode {
    OAM,
    XFER,
    VBLANK,
    HBLANK
};

class PPUManager {
public:
    void mode_oam();
    void mode_xfer();
    void mode_vblank();
    void mode_hblank();
};