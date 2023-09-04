#include "../include/instructions.hpp"
#include "../include/cpu.hpp"
#include "../include/bus.hpp"

/**process for getting the instructions:
 * 1. get the value of the pc reg
 * 2. this is a u8 value
 * 3. this u8 value is an opcode
 * 4. each opcode has at least 1 instruction associated with it
 * 5. set the current instruction using the opcode value as read, then
 * 6. 
 * **/


Instruction::Instruction(InstructionType t, AddressMode m,
                         RegisterType r1, RegisterType r2,
                         ConditionType c, u8 p)
    : type(t), mode(m), reg_1(r1), reg_2(r2), cond(c), param(p) {
}

Instruction instructions[0x100]


Instruction instructions[0x100] = {
    //0x00
    [0x01] = Instruction(InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_BC)
    [0x02] = {InstructionType::IN_LD, AddressMode::AM_MR_R, RegisterType::RT_BC, RegisterType::RT_A},
    [0x03] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_BC},
    [0x04] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_B},
    [0x05] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_B},
    [0x06] = {InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_B},
    [0x07] = {InstructionType::IN_RLCA},
    [0x08] = {InstructionType::IN_LD, AddressMode::AM_A16_R, RegisterType::RT_NONE, RegisterType::RT_SP},
    [0x09] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_BC},
    [0x0A] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_BC},
    [0x0B] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_BC},
    [0x0C] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_C},
    [0x0D] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_C},
    [0x0E] = {InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_C},
    [0x0F] = {InstructionType::IN_RRCA},
    
    //0x1X
    [0x10] = {InstructionType::IN_STOP},
    [0x11] = {InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_DE},
    [0x12] = {InstructionType::IN_LD, AddressMode::AM_MR_R, RegisterType::RT_DE, RegisterType::RT_A},
    [0x13] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_DE},
    [0x14] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_D},
    [0x15] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_D},
    [0x16] = {InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_D},
    [0x17] = {InstructionType::IN_RLA},
    [0x18] = {InstructionType::IN_JR, AddressMode::AM_D8},
    [0x19] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_DE},
    [0x1A] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_DE},
    [0x1B] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_DE},
    [0x1C] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_E},
    [0x1D] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_E},
    [0x1E] = {InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_E},
    [0x1F] = {InstructionType::IN_RRA},

    //0x2X
    [0x20] = {InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ},
    [0x21] = {InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_HL},
    [0x22] = {InstructionType::IN_LD, AddressMode::AM_HLI_R, RegisterType::RT_HL, RegisterType::RT_A},
    [0x23] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_HL},
    [0x24] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_H},
    [0x25] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_H},
    [0x26] = {InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_H},
    [0x27] = {InstructionType::IN_DAA},
    [0x28] = {InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z},
    [0x29] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_HL},
    [0x2A] = {InstructionType::IN_LD, AddressMode::AM_R_HLI, RegisterType::RT_A, RegisterType::RT_HL},
    [0x2B] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_HL},
    [0x2C] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_L},
    [0x2D] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_L},
    [0x2E] = {InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_L},
    [0x2F] = {InstructionType::IN_CPL}

    //0x3X
    [0x30] = {InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC},
    [0x31] = {InstructionType::IN_LD, AddressMode::AM_R_D16, RegisterType::RT_SP},
    [0x32] = {InstructionType::IN_LD, AddressMode::AM_HLD_R, RegisterType::RT_HL, RegisterType::RT_A},
    [0x33] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_SP},
    [0x34] = {InstructionType::IN_INC, AddressMode::AM_MR, RegisterType::RT_HL},
    [0x35] = {InstructionType::IN_DEC, AddressMode::AM_MR, RegisterType::RT_HL},
    [0x36] = {InstructionType::IN_LD, AddressMode::AM_MR_D8, RegisterType::RT_HL},
    [0x37] = {InstructionType::IN_SCF},
    [0x38] = {InstructionType::IN_JR, AddressMode::AM_D8, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C},
    [0x39] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_HL, RegisterType::RT_SP},
    [0x3A] = {InstructionType::IN_LD, AddressMode::AM_R_HLD, RegisterType::RT_A, RegisterType::RT_HL},
    [0x3B] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_SP},
    [0x3C] = {InstructionType::IN_INC, AddressMode::AM_R, RegisterType::RT_A},
    [0x3D] = {InstructionType::IN_DEC, AddressMode::AM_R, RegisterType::RT_A},
    [0x3E] = {InstructionType::IN_LD, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0x3F] = {InstructionType::IN_CCF}

    //0x4X
    [0x40] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_B},
    [0x41] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_C},
    [0x42] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_D},
    [0x43] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_E},
    [0x44] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_H},
    [0x45] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_L},
    [0x46] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_B, RegisterType::RT_HL},
    [0x47] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_B, RegisterType::RT_A},
    [0x48] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_B},
    [0x49] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_C},
    [0x4A] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_D},
    [0x4B] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_E},
    [0x4C] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_H},
    [0x4D] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_L},
    [0x4E] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_C, RegisterType::RT_HL},
    [0x4F] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_C, RegisterType::RT_A},

    // 0x5X
    [0x50] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_B},
    [0x51] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_C},
    [0x52] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_D},
    [0x53] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_E},
    [0x54] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_H},
    [0x55] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_L},
    [0x56] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_D, RegisterType::RT_HL},
    [0x57] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_D, RegisterType::RT_A},
    [0x58] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_B},
    [0x59] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_C},
    [0x5A] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_D},
    [0x5B] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_E},
    [0x5C] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_H},
    [0x5D] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_L},
    [0x5E] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_E, RegisterType::RT_HL},
    [0x5F] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_E, RegisterType::RT_A},

    // 0x6X
    [0x60] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_B},
    [0x61] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_C},
    [0x62] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_D},
    [0x63] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_E},
    [0x64] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_H},
    [0x65] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_L},
    [0x66] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_H, RegisterType::RT_HL},
    [0x67] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_H, RegisterType::RT_A},
    [0x68] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_B},
    [0x69] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_C},
    [0x6A] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_D},
    [0x6B] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_E},
    [0x6C] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_H},
    [0x6D] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_L},
    [0x6E] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_L, RegisterType::RT_HL},
    [0x6F] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_L, RegisterType::RT_A},

    // 0x7X
    [0x70] = {InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_B},
    [0x71] = {InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_C},
    [0x72] = {InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_D},
    [0x73] = {InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_E},
    [0x74] = {InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_H},
    [0x75] = {InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_L},
    [0x76] = {InstructionType::IN_HALT},
    [0x77] = {InstructionType::IN_LD, AddressMode::AM_MR_R,  RegisterType::RT_HL, RegisterType::RT_A},
    [0x78] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_B},
    [0x79] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_C},
    [0x7A] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_D},
    [0x7B] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_E},
    [0x7C] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_H},
    [0x7D] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_L},
    [0x7E] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0x7F] = {InstructionType::IN_LD, AddressMode::AM_R_R,  RegisterType::RT_A, RegisterType::RT_A},

    // 0x8X
    [0x80] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0x81] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0x82] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0x83] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0x84] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0x85] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0x86] = {InstructionType::IN_ADD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0x87] = {InstructionType::IN_ADD, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},
    [0x88] = {InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0x89] = {InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0x8A] = {InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0x8B] = {InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0x8C] = {InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0x8D] = {InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0x8E] = {InstructionType::IN_ADC, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0x8F] = {InstructionType::IN_ADC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},

    // 0x9X
    [0x90] = {InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0x91] = {InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0x92] = {InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0x93] = {InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0x94] = {InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0x95] = {InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0x96] = {InstructionType::IN_SUB, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0x97] = {InstructionType::IN_SUB, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},
    [0x98] = {InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0x99] = {InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0x9A] = {InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0x9B] = {InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0x9C] = {InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0x9D] = {InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0x9E] = {InstructionType::IN_SBC, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0x9F] = {InstructionType::IN_SBC, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},

    // 0xAX
    [0xA0] = {InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0xA1] = {InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0xA2] = {InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0xA3] = {InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0xA4] = {InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0xA5] = {InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0xA6] = {InstructionType::IN_AND, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0xA7] = {InstructionType::IN_AND, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},
    [0xA8] = {InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0xA9] = {InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0xAA] = {InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0xAB] = {InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0xAC] = {InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0xAD] = {InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0xAE] = {InstructionType::IN_XOR, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0xAF] = {InstructionType::IN_XOR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},

    // 0xBX
    [0xB0] = {InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0xB1] = {InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0xB2] = {InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0xB3] = {InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0xB4] = {InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0xB5] = {InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0xB6] = {InstructionType::IN_OR, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0xB7] = {InstructionType::IN_OR, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},
    [0xB8] = {InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_B},
    [0xB9] = {InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_C},
    [0xBA] = {InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_D},
    [0xBB] = {InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_E},
    [0xBC] = {InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_H},
    [0xBD] = {InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_L},
    [0xBE] = {InstructionType::IN_CP, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_HL},
    [0xBF] = {InstructionType::IN_CP, AddressMode::AM_R_R, RegisterType::RT_A, RegisterType::RT_A},

    // 0xCX
    [0xC0] = {InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ},
    [0xC1] = {InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_BC},
    [0xC2] = {InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ},
    [0xC3] = {InstructionType::IN_JP, AddressMode::AM_D16},
    [0xC4] = {InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NZ},
    [0xC5] = {InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_BC},
    [0xC6] = {InstructionType::IN_ADD, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xC7] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x00},
    [0xC8] = {InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z},
    [0xC9] = {InstructionType::IN_RET},
    [0xCA] = {InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z},
    [0xCB] = {InstructionType::IN_CB, AddressMode::AM_D8},
    [0xCC] = {InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_Z},
    [0xCD] = {InstructionType::IN_CALL, AddressMode::AM_D16},
    [0xCE] = {InstructionType::IN_ADC, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xCF] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x08},

    // 0xDX
    [0xD0] = {InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC},
    [0xD1] = {InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_DE},
    [0xD2] = {InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC},
    [0xD4] = {InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NC},
    [0xD5] = {InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_DE},
    [0xD6] = {InstructionType::IN_SUB, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xD7] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x10},
    [0xD8] = {InstructionType::IN_RET, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C},
    [0xD9] = {InstructionType::IN_RETI},
    [0xDA] = {InstructionType::IN_JP, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C},
    [0xDC] = {InstructionType::IN_CALL, AddressMode::AM_D16, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_C},
    [0xDE] = {InstructionType::IN_SBC, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xDF] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x18},

    // 0xEX
    [0xE0] = {InstructionType::IN_LDH, AddressMode::AM_A8_R, RegisterType::RT_NONE, RegisterType::RT_A},
    [0xE1] = {InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_HL},
    [0xE2] = {InstructionType::IN_LD, AddressMode::AM_MR_R, RegisterType::RT_C, RegisterType::RT_A},
    [0xE5] = {InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_HL},
    [0xE6] = {InstructionType::IN_AND, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xE7] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x20},
    [0xE8] = {InstructionType::IN_ADD, AddressMode::AM_R_D8, RegisterType::RT_SP},
    [0xE9] = {InstructionType::IN_JP, AddressMode::AM_R, RegisterType::RT_HL},
    [0xEA] = {InstructionType::IN_LD, AddressMode::AM_A16_R, RegisterType::RT_NONE, RegisterType::RT_A},
    [0xEE] = {InstructionType::IN_XOR, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xEF] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x28},


    [0xF0] = {InstructionType::IN_LDH, AddressMode::AM_R_A8, RegisterType::RT_A},
    [0xF1] = {InstructionType::IN_POP, AddressMode::AM_R, RegisterType::RT_AF},
    [0xF2] = {InstructionType::IN_LD, AddressMode::AM_R_MR, RegisterType::RT_A, RegisterType::RT_C},
    [0xF3] = {InstructionType::IN_DI},
    [0xF5] = {InstructionType::IN_PUSH, AddressMode::AM_R, RegisterType::RT_AF},
    [0xF6] = {InstructionType::IN_OR, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xF7] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x30},
    [0xF8] = {InstructionType::IN_LD, AddressMode::AM_HL_SPR, RegisterType::RT_HL, RegisterType::RT_SP},
    [0xF9] = {InstructionType::IN_LD, AddressMode::AM_R_R, RegisterType::RT_SP, RegisterType::RT_HL},
    [0xFA] = {InstructionType::IN_LD, AddressMode::AM_R_A16, RegisterType::RT_A},
    [0xFB] = {InstructionType::IN_EI},
    [0xFE] = {InstructionType::IN_CP, AddressMode::AM_R_D8, RegisterType::RT_A},
    [0xFF] = {InstructionType::IN_RST, AddressMode::AM_IMP, RegisterType::RT_NONE, RegisterType::RT_NONE, ConditionType::CT_NONE, 0x38},
};

const Instruction& instruction_by_opcode(Opcode opcode) {
    static Instruction instructions[0x100] = {
        // ... Instructions initialization here
    };
    
    return instructions[opcodeMap[opcode]];
}

instruction *instruction_by_opcode(u8 opcode){
    return &instructions[opcode];
}

char *inst_lookup[] = {
    "<NONE>",
    "NOP",
    "LD",
    "INC",
    "DEC",
    "RLCA",
    "ADD",
    "RRCA",
    "STOP",
    "RLA",
    "JR",
    "RRA",
    "DAA",
    "CPL",
    "SCF",
    "CCF",
    "HALT",
    "ADC",
    "SUB",
    "SBC",
    "AND",
    "XOR",
    "OR",
    "CP",
    "POP",
    "JP",
    "PUSH",
    "RET",
    "CB",
    "CALL",
    "RETI",
    "LDH",
    "JPHL",
    "DI",
    "EI",
    "RST",
    "IN_ERR",
    "IN_RLC", 
    "IN_RRC",
    "IN_RL", 
    "IN_RR",
    "IN_SLA", 
    "IN_SRA",
    "IN_SWAP", 
    "IN_SRL",
    "IN_BIT", 
    "IN_RES", 
    "IN_SET"
};

char *inst_name(in_type t) {
    return inst_lookup[t];
}

static char *rt_lookup[] = {
    "<NONE>",
    "A",
    "F",
    "B",
    "C",
    "D",
    "E",
    "H",
    "L",
    "AF",
    "BC",
    "DE",
    "HL",
    "SP",
    "PC"
};

void inst_to_str(cpu_context *ctx, char *str) {
    instruction *inst = ctx->cur_inst;
    sprintf(str, "%s ", inst_name(inst->type));

    switch(inst->mode) {
        case AM_IMP:
            return;

        case AM_R_D16:
        case AM_R_A16:
            sprintf(str, "%s %s,$%04X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data);
            return;

        case AM_R:
            sprintf(str, "%s %s", inst_name(inst->type), 
                rt_lookup[inst->reg_1]);
            return;

        case AM_R_R: 
            sprintf(str, "%s %s,%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_MR_R:
            sprintf(str, "%s (%s),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_MR:
            sprintf(str, "%s (%s)", inst_name(inst->type), 
                rt_lookup[inst->reg_1]);
            return;

        case AM_R_MR:
            sprintf(str, "%s %s,(%s)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_R_D8:
        case AM_R_A8:
            sprintf(str, "%s %s,$%02X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_R_HLI:
            sprintf(str, "%s %s,(%s+)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_R_HLD:
            sprintf(str, "%s %s,(%s-)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_HLI_R:
            sprintf(str, "%s (%s+),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_HLD_R:
            sprintf(str, "%s (%s-),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_A8_R:
            sprintf(str, "%s $%02X,%s", inst_name(inst->type), 
                bus_read(ctx->regs.pc - 1), rt_lookup[inst->reg_2]);

            return;

        case AM_HL_SPR:
            sprintf(str, "%s (%s),SP+%d", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_D8:
            sprintf(str, "%s $%02X", inst_name(inst->type), 
                ctx->fetched_data & 0xFF);
            return;

        case AM_D16:
            sprintf(str, "%s $%04X", inst_name(inst->type), 
                ctx->fetched_data);
            return;

        case AM_MR_D8:
            sprintf(str, "%s (%s),$%02X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_A16_R:
            sprintf(str, "%s ($%04X),%s", inst_name(inst->type), 
                ctx->fetched_data, rt_lookup[inst->reg_2]);
            return;

        default:
            fprintf(stderr, "INVALID AM: %d\n", inst->mode);
            NO_IMPL
    }
}