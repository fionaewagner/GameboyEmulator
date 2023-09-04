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

    instructions[0x01] = Instruction(InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_BC);
    instructions[0x02] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R, RegisterType::RT_BC, RegisterType::RT_A};
    instructions[0x03] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_BC};
    instructions[0x04] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_B};
    instructions[0x05] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_B};
    instructions[0x06] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_B};
    instructions[0x07] = Instruction{InstructionType::IN_RLCA};
    instructions[0x08] = Instruction{InstructionType::IN_LD, AddressMode::AM_A16_R, RegisterType::RT_NONE, RegisterType::RT_SP};
    instructions[0x09] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_BC};
    instructions[0x0A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_BC};
    instructions[0x0B] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_BC};
    instructions[0x0C] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_C};
    instructions[0x0D] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_C};
    instructions[0x0E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_C};
    instructions[0x0F] = Instruction{InstructionType::IN_RRCA};
    
    //0x1X
    instructions[0x10] = Instruction{InstructionType::IN_STOP};
    instructions[0x11] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_DE};
    instructions[0x12] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R, RegisterType::RT_DE, RegisterType::RT_A};
    instructions[0x13] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_DE};
    instructions[0x14] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_D};
    instructions[0x15] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_D};
    instructions[0x16] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_D};
    instructions[0x17] = Instruction{InstructionType::IN_RLA};
    instructions[0x18] = Instruction{InstructionType::IN_JR, AddressMode::AM_D8};
    instructions[0x19] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_DE};
    instructions[0x1A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_DE};
    instructions[0x1B] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_DE};
    instructions[0x1C] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_E};
    instructions[0x1D] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_E};
    instructions[0x1E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_E};
    instructions[0x1F] = Instruction{InstructionType::IN_RRA};

    //0x2X
    instructions[0x20] = Instruction{InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ};
    instructions[0x21] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_HL};
    instructions[0x22] = Instruction{InstructionType::IN_LD, AddressMode::AM_HLI_R, RegisterType::RT_HL, RegisterType::RT_A};
    instructions[0x23] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_HL};
    instructions[0x24] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_H};
    instructions[0x25] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_H};
    instructions[0x26] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_H};
    instructions[0x27] = Instruction{InstructionType::IN_DAA};
    instructions[0x28] = Instruction{InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z};
    instructions[0x29] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_HL};
    instructions[0x2A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_HLI, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0x2B] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_HL};
    instructions[0x2C] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_L};
    instructions[0x2D] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_L};
    instructions[0x2E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_L};
    instructions[0x2F] = Instruction{InstructionType::IN_CPL};

    //0x3X
    instructions[0x30] = Instruction{InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC};
    instructions[0x31] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_SP};
    instructions[0x32] = Instruction{InstructionType::IN_LD, AddressMode::AM_HLD_R, RegisterType::RT_HL, RegisterType::RT_A};
    instructions[0x33] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_SP};
    instructions[0x34] = Instruction{InstructionType::IN_INC, AddressMode::AM_MR, RegisterType::RT_HL};
    instructions[0x35] = Instruction{InstructionType::IN_DEC, AddressMode::AM_MR, RegisterType::RT_HL};
    instructions[0x36] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_D8, RegisterType::RT_HL};
    instructions[0x37] = Instruction{InstructionType::IN_SCF};
    instructions[0x38] = Instruction{InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C};
    instructions[0x39] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_SP};
    instructions[0x3A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_HLD, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0x3B] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_SP};
    instructions[0x3C] = Instruction{InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_A};
    instructions[0x3D] = Instruction{InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_A};
    instructions[0x3E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0x3F] = Instruction{InstructionType::IN_CCF};

    //0x4X
    instructions[0x40] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_B};
    instructions[0x41] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_C};
    instructions[0x42] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_D};
    instructions[0x43] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_E};
    instructions[0x44] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_H};
    instructions[0x45] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_L};
    instructions[0x46] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_B, RegisterType::RT_HL};
    instructions[0x47] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_A};
    instructions[0x48] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_B};
    instructions[0x49] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_C};
    instructions[0x4A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_D};
    instructions[0x4B] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_E};
    instructions[0x4C] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_H};
    instructions[0x4D] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_L};
    instructions[0x4E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_C, RegisterType::RT_HL};
    instructions[0x4F] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_A};

    // 0x5X
    instructions[0x50] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_B};
    instructions[0x51] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_C};
    instructions[0x52] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_D};
    instructions[0x53] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_E};
    instructions[0x54] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_H};
    instructions[0x55] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_L};
    instructions[0x56] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_D, RegisterType::RT_HL};
    instructions[0x57] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_A};
    instructions[0x58] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_B};
    instructions[0x59] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_C};
    instructions[0x5A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_D};
    instructions[0x5B] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_E};
    instructions[0x5C] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_H};
    instructions[0x5D] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_L};
    instructions[0x5E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_E, RegisterType::RT_HL};
    instructions[0x5F] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_A};

    // 0x6X
    instructions[0x60] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_B};
    instructions[0x61] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_C};
    instructions[0x62] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_D};
    instructions[0x63] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_E};
    instructions[0x64] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_H};
    instructions[0x65] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_L};
    instructions[0x66] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_H, RegisterType::RT_HL};
    instructions[0x67] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_A};
    instructions[0x68] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_B};
    instructions[0x69] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_C};
    instructions[0x6A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_D};
    instructions[0x6B] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_E};
    instructions[0x6C] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_H};
    instructions[0x6D] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_L};
    instructions[0x6E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_L, RegisterType::RT_HL};
    instructions[0x6F] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_A};

    // 0x7X
    instructions[0x70] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_B};
    instructions[0x71] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_C};
    instructions[0x72] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_D};
    instructions[0x73] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_E};
    instructions[0x74] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_H};
    instructions[0x75] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_L};
    instructions[0x76] = Instruction{InstructionType::IN_HALT};
    instructions[0x77] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_A};
    instructions[0x78] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_B};
    instructions[0x79] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_C};
    instructions[0x7A] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_D};
    instructions[0x7B] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_E};
    instructions[0x7C] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_H};
    instructions[0x7D] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_L};
    instructions[0x7E] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0x7F] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_A};

    // 0x8X
    instructions[0x80] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0x81] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0x82] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0x83] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0x84] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0x85] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0x86] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0x87] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};
    instructions[0x88] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0x89] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0x8A] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0x8B] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0x8C] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0x8D] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0x8E] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0x8F] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};

    // 0x9X
    instructions[0x90] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0x91] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0x92] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0x93] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0x94] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0x95] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0x96] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0x97] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};
    instructions[0x98] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0x99] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0x9A] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0x9B] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0x9C] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0x9D] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0x9E] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0x9F] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};

        // 0xAX
    instructions[0xA0] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0xA1] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0xA2] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0xA3] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0xA4] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0xA5] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0xA6] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0xA7] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};
    instructions[0xA8] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0xA9] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0xAA] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0xAB] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0xAC] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0xAD] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0xAE] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0xAF] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};

    // 0xBX
    instructions[0xB0] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0xB1] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0xB2] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0xB3] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0xB4] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0xB5] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0xB6] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0xB7] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};
    instructions[0xB8] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B};
    instructions[0xB9] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0xBA] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D};
    instructions[0xBB] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E};
    instructions[0xBC] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H};
    instructions[0xBD] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L};
    instructions[0xBE] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL};
    instructions[0xBF] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A};

    // 0xCX
    instructions[0xC0] = Instruction{InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ};
    instructions[0xC1] = Instruction{InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_BC};
    instructions[0xC2] = Instruction{InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ};
    instructions[0xC3] = Instruction{InstructionType::IN_JP, AddressMode::AM_D16};
    instructions[0xC4] = Instruction{InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ};
    instructions[0xC5] = Instruction{InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_BC};
    instructions[0xC6] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xC7] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x00};
    instructions[0xC8] = Instruction{InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z};
    instructions[0xC9] = Instruction{InstructionType::IN_RET};
    instructions[0xCA] = Instruction{InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z};
    instructions[0xCB] = Instruction{InstructionType::IN_CB, AddressMode::AM_D8};
    instructions[0xCC] = Instruction{InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z};
    instructions[0xCD] = Instruction{InstructionType::IN_CALL, AddressMode::AM_D16};
    instructions[0xCE] = Instruction{InstructionType::IN_ADC, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xCF] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x08};

    // 0xDX
    instructions[0xD0] = Instruction{InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC};
    instructions[0xD1] = Instruction{InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_DE};
    instructions[0xD2] = Instruction{InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC};
    instructions[0xD4] = Instruction{InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC};
    instructions[0xD5] = Instruction{InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_DE};
    instructions[0xD6] = Instruction{InstructionType::IN_SUB, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xD7] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x10};
    instructions[0xD8] = Instruction{InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C};
    instructions[0xD9] = Instruction{InstructionType::IN_RETI};
    instructions[0xDA] = Instruction{InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C};
    instructions[0xDC] = Instruction{InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C};
    instructions[0xDE] = Instruction{InstructionType::IN_SBC, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xDF] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x18};

    // 0xEX
    instructions[0xE0] = Instruction{InstructionType::IN_LDH, AddressMode::AM_A8_R, RegisterType::RT_NONE, RegisterType::RT_A};
    instructions[0xE1] = Instruction{InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_HL};
    instructions[0xE2] = Instruction{InstructionType::IN_LD, AddressMode::AM_MR_R, RegisterType::RT_C, RegisterType::RT_A};
    instructions[0xE5] = Instruction{InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_HL};
    instructions[0xE6] = Instruction{InstructionType::IN_AND, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xE7] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x20};
    instructions[0xE8] = Instruction{InstructionType::IN_ADD, AddressMode::AM_R_D8, RegisterType::RT_SP};
    instructions[0xE9] = Instruction{InstructionType::IN_JP, AddressMode::AM_R, RegisterType::RT_HL};
    instructions[0xEA] = Instruction{InstructionType::IN_LD, AddressMode::AM_A16_R, RegisterType::RT_NONE, RegisterType::RT_A};
    instructions[0xEE] = Instruction{InstructionType::IN_XOR, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xEF] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x28};

    instructions[0xF0] = Instruction{InstructionType::IN_LDH, AddressMode::AM_R_A8, RegisterType::RT_A};
    instructions[0xF1] = Instruction{InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_AF};
    instructions[0xF2] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_C};
    instructions[0xF3] = Instruction{InstructionType::IN_DI};
    instructions[0xF5] = Instruction{InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_AF};
    instructions[0xF6] = Instruction{InstructionType::IN_OR, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xF7] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x30};
    instructions[0xF8] = Instruction{InstructionType::IN_LD, AddressMode::AM_HL_SPR, RegisterType::RT_HL, RegisterType::RT_SP};
    instructions[0xF9] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_SP, RegisterType::RT_HL};
    instructions[0xFA] = Instruction{InstructionType::IN_LD, AddressMode::AM_R_A16, RegisterType::RT_A};
    instructions[0xFB] = Instruction{InstructionType::IN_EI};
    instructions[0xFE] = Instruction{InstructionType::IN_CP, AddressMode::AM_R_D8, RegisterType::RT_A};
    instructions[0xFF] = Instruction{InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x38};

    return instructions;
}