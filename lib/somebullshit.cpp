#include <iostream>
#include <map>
#include "../include/instructions.hpp"
#include "../include/cpu.hpp"
#include "../include/bus.hpp"


/**
 *  [0x00] = {IN_NOP, AM_IMP},
    [0x01] = {IN_LD, AM_R_D16, RT_BC},
    [0x02] = {IN_LD, AM_MR_R, RT_BC, RT_A},
    [0x03] = {IN_INC, AM_R, RT_BC},
    [0x04] = {IN_INC, AM_R, RT_B},
    [0x05] = {IN_DEC, AM_R, RT_B},
    [0x06] = {IN_LD, AM_R_D8, RT_B},
    [0x07] = {IN_RLCA},
    [0x08] = {IN_LD, AM_A16_R, RT_NONE, RT_SP},
    [0x09] = {IN_ADD, AM_R_R, RT_HL, RT_BC},
    [0x0A] = {IN_LD, AM_R_MR, RT_A, RT_BC},
    [0x0B] = {IN_DEC, AM_R, RT_BC},
    [0x0C] = {IN_INC, AM_R, RT_C},
    [0x0D] = {IN_DEC, AM_R, RT_C},
    [0x0E] = {IN_LD, AM_R_D8, RT_C},
    [0x0F] = {IN_RRCA}
*/

std::map<u8, Instruction> createInstructionMap() {
    std::map<u8, Instruction> instructions;

    instructions[0xFF] = Instruction(AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x38);

    return instructions;
}