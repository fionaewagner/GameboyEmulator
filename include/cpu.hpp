#pragma once

#include "common.hpp"
#include "instructions.hpp"
#include <functional>
#include "interrupts.hpp"

enum class RegisterType {
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

struct CPURegisters {
    u8 a;
    u8 f;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 h;
    u8 l;
    u16 pc;
    u16 sp;
};

enum class Flag : uint8_t {
    Z = 7, // Zero flag
    N = 6, // Subtract flag
    H = 5, // Half Carry flag
    C = 4  // Carry flag
};



class CPU {
public:
    CPU();

    bool step();

    void fetchData();
    void CPU::fetchData(std::function<u8(u16)> busRead , std::function<void(int)> emuCycles); //get rid of eventually 
    u16 getFetchedData() const;
    void setFetchedData(u16 value);
    void CPU::fetchInstruction()

    u16 getMemDest() const;
    void setMemDest(u16 value);

    bool isDestMem() const;
    void setDestIsMem(bool value);

    u8 getCurOpcode() const;
    void setCurOpcode(u8 value);

    Instruction* getCurInst() const;
    void setCurInst(Instruction* inst);

    bool isHalted() const;
    void setHalted(bool value);

    bool isStepping() const;
    void setStepping(bool value);

    bool isIntMasterEnabled() const;
    void setIntMasterEnabled(bool value);

    bool isEnablingIME() const;
    void setEnablingIME(bool value);

    u8 getIERegister() const;
    void setIERegister(u8 value);

    void instructionToString(char* str);

    u16 cpuReadReg16(RegisterType rt);
    void cpuSetReg16(RegisterType rt, u16 val);

    u8 cpuReadReg8(RegisterType rt);
    void cpuSetReg8(RegisterType rt, u8 val);

    bool isZeroFlagSet();
    bool isSubtractFlagSet();
    bool isHalfCarryFlagSet();
    bool isCarryFlagSet();

    bool checkCond(ConditionType cond);
    void gotoAddr(u16 addr, bool pushPC);
    

    void requestInterrupt(InterruptType t);
    void handleInterrupts();

    void CPU::setFlags(bool z, bool n, bool h, bool c);
    void CPU::setFlag(Flag flag, bool value);

private:
    CPURegisters registers;

    u16 fetchedData;
    u16 memDest;
    bool destIsMem;
    u8 curOpcode;
    Instruction* curInst;
    bool halted;
    bool stepping;
    bool intMasterEnabled;
    bool enablingIME;
    u8 ieRegister;
    u8 flags;

    std::function<void(CPU*)> getProcessorFunction(InstructionType type);

};