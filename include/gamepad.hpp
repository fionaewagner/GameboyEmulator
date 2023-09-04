#pragma once

#include "common.hpp"



class Gamepad {
private:
    u8 output;

    bool buttonSel;
    bool dirSel;

    bool start;
    bool select;
    bool a;
    bool b;
    bool up;
    bool down;
    bool left;
    bool right;

public:
    // Constructor
    Gamepad();

    // Member functions
    void init();
    void gamepadSetSel(u8 value);
    u8 gamepadGetOutput();
    

    // Getters
    bool getStart() const;
    bool getSelect() const;
    bool getA() const;
    bool getB() const;
    bool getUp() const;
    bool getDown() const;
    bool getLeft() const;
    bool getRight() const;
    bool getButtonSel() const { return buttonSel; }
    bool getDirSel() const { return dirSel; }


    // Setters
    void setStart(bool value);
    void setSelect(bool value);
    void setA(bool value);
    void setB(bool value);
    void setUp(bool value);
    void setDown(bool value);
    void setLeft(bool value);
    void setRight(bool value);
    void setButtonSel(bool value);
    void setDirSel(bool value);

    // Getters
    u8 getOutput() const;
};