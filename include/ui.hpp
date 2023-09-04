#pragma once

#include "common.hpp"

class UIManager {
public:
    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;

    void init();
    void handleEvents();
    void update();
    void onKey();
};