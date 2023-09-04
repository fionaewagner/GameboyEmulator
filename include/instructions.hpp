#pragma once

#include "common.hpp"



enum class AddressMode {
    AM_IMP,
    AM_R_D16,
    AM_R_R,
    AM_MR_R,
    AM_R,
    AM_R_D8,
    AM_R_MR,
    AM_R_HLI,
    AM_R_HLD,
    AM_HLI_R,
    AM_HLD_R,
    AM_R_A8,
    AM_A8_R,
    AM_HL_SPR,
    AM_D16,
    AM_D8,
    AM_D16_R,
    AM_MR_D8,
    AM_MR,
    AM_A16_R,
    AM_R_A16
};

enum class RegisterType {
    RT_NONE,
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_SP,
    RT_PC
};

enum class InstructionType {
    IN_NONE,
    IN_NOP,
    IN_LD,
    IN_INC,
    IN_DEC,
    IN_RLCA,
    IN_ADD,
    IN_RRCA,
    IN_STOP,
    IN_RLA,
    IN_JR,
    IN_RRA,
    IN_DAA,
    IN_CPL,
    IN_SCF,
    IN_CCF,
    IN_HALT,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_XOR,
    IN_OR,
    IN_CP,
    IN_POP,
    IN_JP,
    IN_PUSH,
    IN_RET,
    IN_CB,
    IN_CALL,
    IN_RETI,
    IN_LDH,
    IN_JPHL,
    IN_DI,
    IN_EI,
    IN_RST,
    IN_ERR,
    //CB instructions...
    IN_RLC,
    IN_RRC,
    IN_RL,
    IN_RR,
    IN_SLA,
    IN_SRA,
    IN_SWAP,
    IN_SRL,
    IN_BIT,
    IN_RES,
    IN_SET
};

enum class ConditionType {
    CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C
};

class Instruction {
public:

    Instruction(InstructionType t = InstructionType::IN_NONE,
                AddressMode m = AddressMode::AM_NONE,
                RegisterType r1 = RegisterType::RT_NONE,
                RegisterType r2 = RegisterType::RT_NONE,
                ConditionType c = ConditionType::CT_NONE,
                u8 p = 0);

    InstructionType getType() const { return type; }
    AddressMode getMode() const { return mode; }
    RegisterType getReg1() const { return reg_1; }
    RegisterType getReg2() const { return reg_2; }
    ConditionType getCond() const { return cond; }
    u8 getParam() const { return param; }

    void setType(InstructionType t) { type = t; }
    void setMode(AddressMode m) { mode = m; }
    void setReg1(RegisterType r1) { reg_1 = r1; }
    void setReg2(RegisterType r2) { reg_2 = r2; }
    void setCond(ConditionType c) { cond = c; }
    void setParam(u8 p) { param = p; }

    void execute();

private:
    InstructionType type;
    AddressMode mode;
    RegisterType reg_1;
    RegisterType reg_2;
    ConditionType cond;
    u8 param;
};

class InstructionManager {
public:
    static Instruction instructionByOpcode(u8 opcode);
    static const char* instName(InstructionType t);
};