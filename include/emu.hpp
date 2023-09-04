#pragma once

#include "common.hpp"

class Emulator {
public:
    Emulator();

    int run(int argc, char **argv);

    // Getters
    bool getPaused() const;
    bool getRunning() const;
    bool getDie() const;
    u64 getTicks() const;

    // Setters
    void setPaused(bool paused);
    void setRunning(bool running);
    void setShouldDie(bool die);
    void setTicks(u64 ticks);

private:
    bool paused;
    bool running;
    bool die;
    u64 ticks;
};