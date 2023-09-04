#include "../include/gamepad.hpp"
#include <string.h>


void Gamepad::gamepadSetSel(u8 value) {
    buttonSel = value & 0x20;
    dirSel = value & 0x10;
}


u8 Gamepad::gamepadGetOutput() {
    u8 output = 0xCF;

    if (!buttonSel) {
        if (start) {
            output &= ~(1 << 3);
        } 
        if (select) {
            output &= ~(1 << 2);
        } 
        if (a) {
            output &= ~(1 << 0);
        } 
        if (b) {
            output &= ~(1 << 1);
        }
    }

    if (!dirSel) {
        if (left) {
            output &= ~(1 << 1);
        } 
        if (right) {
            output &= ~(1 << 0);
        } 
        if (up) {
            output &= ~(1 << 2);
        } 
        if (down) {
            output &= ~(1 << 3);
        }
    }

    return output;
}