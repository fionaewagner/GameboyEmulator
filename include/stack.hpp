#pragma once

#include "common.hpp"

class StackManager {
public:
    void push(u8 data);
    void push16(u16 data);

    u8 pop();
    u16 pop16();
};