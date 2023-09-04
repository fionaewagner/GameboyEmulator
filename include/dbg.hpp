#pragma once

#include "common.hpp"
#include "cpu.hpp"

#include <iostream>
#include <vector> // You might need to include other headers based on the actual functionality of bus.h

class Debug {
public:
    Debug() : dbgMsg(1024), msgSize(0) {}

    void dbgUpdate();

    void dbgPrint() const;

private:
    std::vector<char> dbgMsg; // Corrected member name here
    int msgSize; // Corrected member name here
};